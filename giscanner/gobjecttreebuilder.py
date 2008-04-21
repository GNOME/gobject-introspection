import ctypes
import re
import os

from . import cgobject
from .treebuilder import (Class, Enum, Function, Interface, Member, Property,
                          Struct)
from .odict import odict


# Copied from h2defs.py
_upperstr_pat1 = re.compile(r'([^A-Z])([A-Z])')
_upperstr_pat2 = re.compile(r'([A-Z][A-Z])([A-Z][0-9a-z])')
_upperstr_pat3 = re.compile(r'^([A-Z])([A-Z])')

def to_underscores(name):
    """Converts a typename to the equivalent underscores name.
    This is used to form the type conversion macros and enum/flag
    name variables"""
    name = _upperstr_pat1.sub(r'\1_\2', name)
    name = _upperstr_pat2.sub(r'\1_\2', name)
    name = _upperstr_pat3.sub(r'\1_\2', name, count=1)
    return name

_libtool_pat = re.compile("dlname='([A-z0-9\.]+)'\n")

def resolve_libtool(libname):
    data = open(libname).read()
    filename = _libtool_pat.search(data).groups()[0]
    libname = os.path.join(os.path.dirname(libname),
                           '.libs', filename)
    return libname


class GLibEnum(Enum):
    def __init__(self, name, members, get_type):
        Enum.__init__(self, name, members)
        self.get_type = get_type

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name,
            self.members,
            self.get_type)


class GLibFlags(GLibEnum):
    pass


class GLibEnumMember(Member):
    def __init__(self, name, value, nick):
        Member.__init__(self, name, value)
        self.nick = nick


class GLibObject(Class):
    def __init__(self, name, parent, get_type):
        Class.__init__(self, name, parent)
        self.get_type = get_type


class GLibBoxed(Struct):
    def __init__(self, name, get_type):
        Struct.__init__(self, name)
        self.constructors = []
        self.methods = []
        self.get_type = get_type


class GLibInterface(Interface):
    def __init__(self, name, get_type):
        Interface.__init__(self, name)
        self.get_type = get_type


class GLibProperty(Property):
    pass


class GObjectTreeBuilder(object):
    def __init__(self, namespace_name):
        self._namespace_name = namespace_name
        self._output_ns = odict()
        self._library = None

    # Public API

    def get_nodes(self):
        return self._output_ns.values()

    def load_library(self, libname):
        if libname.endswith('.la'):
            libname = resolve_libtool(libname)
        self._library = ctypes.cdll.LoadLibrary(libname)

    def parse(self, nodes):
        for node in nodes:
            self._parse_node(node)

    # Private

    def _add_attribute(self, node, replace=False):
        node_name = node.name
        if node_name in self._output_ns and not replace:
            return
        self._output_ns[node_name] = node

    def _remove_attribute(self, name):
        del self._output_ns[name]

    def _get_attribute(self, name):
        return self._output_ns.get(name)

    def _strip_namespace(self, node):
        prefix = self._namespace_name.lower()
        if isinstance(node, Function):
            # gtk_init_check -> init_check
            prefix += '_'
            name = node.name.lower()
        elif isinstance(node, (Interface, Class, Struct, Enum)):
            # GtkButton -> Button
            # GtkTreeModel -> TreeModel
            # etc
            name = node.name.lower()
        else:
            raise NotImplementedError(node)

        if name.startswith(prefix):
            old = node.name
            node.name = node.name[len(prefix):]

    def _parse_node(self, node):
        if isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Struct):
            self._parse_struct(node)
        else:
            print 'Unhandled node:', node

    def _parse_enum(self, enum):
        self._strip_namespace(enum)
        self._add_attribute(enum)

    def _parse_function(self, func):
        if self._parse_get_type_function(func):
            return
        elif self._parse_constructor(func):
            return
        elif self._parse_method(func):
            return

        self._strip_namespace(func)
        self._add_attribute(func)

    def _parse_get_type_function(self, func):
        # GType *_get_type(void)
        symbol = func.name
        if not symbol.endswith('_get_type'):
            return False
        if func.retval.type != 'GType':
            return False
        if func.parameters:
            return False

        func = getattr(self._library, symbol)
        func.restype = cgobject.GType
        func.argtypes = []
        type_id = func()
        self._introspect_type(type_id, symbol)
        return True

    def _parse_method(self, func):
        if not func.parameters:
            return False

        # FIXME: This is hackish, we should preserve the pointer structures
        #        here, so we can find pointers to objects and not just
        #        pointers to anything
        first_arg = func.parameters[0].type
        if first_arg.count('*') != 1:
            return False

        object_name = first_arg.replace('*', '')
        return self._parse_method_common(func, object_name, is_method=True)

    def _parse_constructor(self, func):
        # FIXME: This is hackish, we should preserve the pointer structures
        #        here, so we can find pointers to objects and not just
        #        pointers to anything
        rtype = func.retval.type
        if rtype.count('*') != 1:
            return False

        object_name = rtype.replace('*', '')
        return self._parse_method_common(func, object_name, is_method=False)

    def _parse_method_common(self, func, object_name, is_method):
        orig_name = object_name
        if object_name.lower().startswith(self._namespace_name.lower()):
            object_name = object_name[len(self._namespace_name):]
        class_ = self._get_attribute(object_name)
        if class_ is None or not isinstance(class_, (GLibObject, GLibBoxed)):
            return False

        # GtkButton -> gtk_button_, so we can figure out the method name
        prefix = to_underscores(orig_name).lower() + '_'
        if not func.name.startswith(prefix):
            return False

        # Strip namespace and object prefix: gtk_window_new -> new
        func.name = func.name[len(prefix):]
        if is_method:
            class_.methods.append(func)
        else:
            class_.constructors.append(func)
        return True

    def _parse_struct(self, struct):
        if (struct.name.startswith('_') or
            struct.name.endswith('Iface') or
            struct.name.endswith('Class')):
            return
        self._add_attribute(struct)

    def _introspect_type(self, type_id, symbol):
        fundamental_type_id = cgobject.type_fundamental(type_id)
        if (fundamental_type_id == cgobject.TYPE_ENUM or
            fundamental_type_id == cgobject.TYPE_FLAGS):
            self._introspect_enum(fundamental_type_id, type_id, symbol)
        elif fundamental_type_id == cgobject.TYPE_OBJECT:
            self._introspect_object(type_id, symbol)
        elif fundamental_type_id == cgobject.TYPE_INTERFACE:
            self._introspect_interface(type_id, symbol)
        elif fundamental_type_id == cgobject.TYPE_BOXED:
            self._introspect_boxed(type_id, symbol)
        else:
            print 'unhandled GType: %s' % (cgobject.type_name(type_id),)

    def _introspect_enum(self, ftype_id, type_id, symbol):
        type_class = cgobject.type_class_ref(type_id)
        if type_class is None:
            return

        members = []
        for enum_value in type_class.get_values():
            members.append(GLibEnumMember(enum_value.value_name,
                                          enum_value.value,
                                          enum_value.value_nick))

        klass = (GLibFlags if ftype_id == cgobject.TYPE_FLAGS else GLibEnum)
        type_name = cgobject.type_name(type_id)
        cenum = klass(type_name, members, symbol)
        self._strip_namespace(cenum)
        self._add_attribute(cenum, replace=True)

    def _introspect_object(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        parent_name = cgobject.type_name(cgobject.type_parent(type_id))
        node = GLibObject(type_name, parent_name, symbol)
        self._introspect_properties(node, type_id)
        self._strip_namespace(node)
        self._add_attribute(node)
        self._remove_attribute(type_name)

    def _introspect_interface(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        node = GLibInterface(type_name, symbol)
        self._strip_namespace(node)
        self._introspect_properties(node, type_id)
        self._add_attribute(node)
        self._remove_attribute(type_name)

    def _introspect_boxed(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        node = GLibBoxed(type_name, symbol)
        self._strip_namespace(node)
        self._add_attribute(node)
        self._remove_attribute(type_name)

    def _introspect_properties(self, node, type_id):
        fundamental_type_id = cgobject.type_fundamental(type_id)
        if fundamental_type_id == cgobject.TYPE_OBJECT:
            pspecs = cgobject.object_class_list_properties(type_id)
        elif fundamental_type_id == cgobject.TYPE_INTERFACE:
            pspecs = cgobject.object_interface_list_properties(type_id)
        else:
            raise AssertionError

        for pspec in pspecs:
            if pspec.owner_type != type_id:
                continue
            node.properties.append(Property(
                pspec.name,
                cgobject.type_name(pspec.value_type)))
