import ctypes

from giscanner import cgobject
from giscanner.treebuilder import Class, Enum, Function, Member, Struct
from giscanner.odict import odict


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
    def __init__(self, name, parent, methods, get_type):
        Class.__init__(self, name, parent, methods)
        self.get_type = get_type


class GObjectTreeBuilder(object):
    def __init__(self):
        self.nodes = []
        self._namespace = odict()
        self._library = None

    # Public API

    def get_nodes(self):
        return self._namespace.values()

    def load_library(self, libname):
        self._library = ctypes.cdll.LoadLibrary(libname)

    def parse(self, nodes):
        nodes = list(nodes)
        for node in nodes:
            self._parse_node(node)

    # Private

    def _add_attribute(self, node, replace=False):
        node_name = node.name
        if node_name in self._namespace and not replace:
            return
        self._namespace[node_name] = node

    def _call_get_type_function(self, symbol_name):
        func = getattr(self._library, symbol_name)
        func.restype = cgobject.GType
        func.argtypes = []
        return func()

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
        self._add_attribute(enum)

    def _parse_function(self, func):
        if self._parse_get_type_function(func):
            return
        elif self._parse_method(func):
            return
        else:
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

        type_id = self._call_get_type_function(symbol)
        self._parse_gtype(type_id, symbol)
        return True


    def _parse_method(self, func):
        if not func.parameters:
            return False

        first_arg = func.parameters[0].type
        if first_arg.count('*') != 1:
            return False

        object_name = first_arg.replace('*', '')
        class_ = self._namespace.get(object_name, None)
        if class_ is None or not isinstance(class_, GLibObject):
            return False

        class_.methods.append(func)
        return True

    def _parse_struct(self, struct):
        if (struct.name.startswith('_') or
            struct.name.endswith('Iface') or
            struct.name.endswith('Class')):
            return
        self._add_attribute(struct)

    def _parse_gtype(self, type_id, symbol):
        fundamental_type_id = cgobject.type_fundamental(type_id)
        if (fundamental_type_id == cgobject.TYPE_ENUM or
            fundamental_type_id == cgobject.TYPE_FLAGS):
            pass #self._introspect_enum(fundamental_type_id, type_id, symbol)
        elif fundamental_type_id == cgobject.TYPE_OBJECT:
            self._introspect_object(type_id, symbol)
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
        cenum = klass(cgobject.type_name(type_id), members, symbol)
        self._add_attribute(cenum, replace=True)

    def _introspect_object(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        parent_name = cgobject.type_name(cgobject.type_parent(type_id))
        node = GLibObject(type_name, parent_name, [], symbol)
        self._add_attribute(node, replace=True)
