# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#

import ctypes

from . import cgobject
from .ast import (Callback, Enum, Function, Member, Namespace, Parameter,
                  Sequence, Property, Return, Struct, Type, Alias,
                  type_name_from_ctype)
from .transformer import Names
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject, GLibSignal, type_names)
from .utils import extract_libtool, to_underscores


class Unresolved(object):

    def __init__(self, target):
        self.target = target


class UnknownTypeError(Exception):
    pass


class GLibTransformer(object):

    def __init__(self, transformer, noclosure=False):
        self._transformer = transformer
        self._namespace_name = None
        self._names = Names()
        self._libraries = []
        self._failed_types = {}
        self._noclosure = noclosure
        self._validating = False

    # Public API

    def add_library(self, libname):
        if libname.endswith('.la'):
            libname = extract_libtool(libname)
        self._libraries.append(ctypes.cdll.LoadLibrary(libname))

    def parse(self):
        namespace = self._transformer.parse()
        self._namespace_name = namespace.name

        # First pass, parsing
        for node in namespace.nodes:
            self._parse_node(node)

        # Introspection is done from within parsing

        # Second pass, delete class structures, resolve
        # all types we now know about
        nodes = list(self._names.names.itervalues())
        for (ns, node) in nodes:
            self._resolve_node(node)
            # associate GtkButtonClass with GtkButton
            if isinstance(node, Struct):
                self._pair_class_struct(node)
        for (ns, alias) in self._names.aliases.itervalues():
            self._resolve_alias(alias)

        # Third pass; ensure all types are known
        if not self._noclosure:
            self._validate(nodes)

        # Create a new namespace with what we found
        namespace = Namespace(namespace.name)
        namespace.nodes = map(lambda x: x[1], self._names.aliases.itervalues())
        for (ns, x) in self._names.names.itervalues():
            namespace.nodes.append(x)
        return namespace

    # Private

    def _add_attribute(self, node, replace=False):
        node_name = node.name
        if (not replace) and node_name in self._names.names:
            return
        self._names.names[node_name] = (None, node)

    def _remove_attribute(self, name):
        del self._names.names[name]

    def _get_attribute(self, name):
        node = self._names.names.get(name)
        if node:
            return node[1]
        return None

    def _register_internal_type(self, type_name, node):
        self._names.type_names[type_name] = (None, node)

    # Helper functions

    def _create_type(self, type_id):
        ctype = cgobject.type_name(type_id)
        type_name = type_name_from_ctype(ctype)
        type_name = type_name.replace('*', '')
        type_name = self._resolve_type_name(type_name)
        return Type(type_name, ctype)

    def _resolve_gtypename(self, gtype_name):
        try:
            return self._transformer.gtypename_to_giname(gtype_name,
                                                         self._names)
        except KeyError, e:
            return Unresolved(gtype_name)

    def _create_gobject(self, node):
        type_name = 'G' + node.name
        if type_name == 'GObject':
            parent_gitype = None
            symbol = 'intern'
        else:
            type_id = cgobject.type_from_name(type_name)
            parent_type_name = cgobject.type_name(
                cgobject.type_parent(type_id))
            parent_gitype = self._resolve_gtypename(parent_type_name)
            symbol = to_underscores(type_name).lower() + '_get_type'
        node = GLibObject(node.name, parent_gitype, type_name, symbol)
        type_id = cgobject.TYPE_OBJECT
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        self._add_attribute(node)
        self._register_internal_type(type_name, node)

    # Parser

    def _parse_node(self, node):
        if isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Struct):
            self._parse_struct(node)
        elif isinstance(node, Callback):
            self._parse_callback(node)
        elif isinstance(node, Alias):
            self._parse_alias(node)
        elif isinstance(node, Member):
            # FIXME: atk_misc_instance singletons
            pass
        else:
            print 'GOBJECT BUILDER: Unhandled node:', node

    def _parse_alias(self, alias):
        self._names.aliases[alias.name] = (None, alias)

    def _parse_enum(self, enum):
        self._add_attribute(enum)

    def _parse_function(self, func):
        if self._parse_get_type_function(func):
            return
        elif self._parse_constructor(func):
            return
        elif self._parse_method(func):
            return

        self._add_attribute(func)

    def _parse_get_type_function(self, func):
        symbol = func.symbol
        if not symbol.endswith('_get_type'):
            return False
        # GType *_get_type(void)
        # This is a bit fishy, why do we need all these aliases?
        if func.retval.type.name not in ['Type',
                                         'GType',
                                         'Object.Type',
                                         'GObject.Type',
                                         'GObject.GType']:
            print ("Warning: *_get_type function returns '%r'"
                   ", not GObject.Type") % (func.retval.type.name, )
            return False
        if func.parameters:
            return False

        if not self._libraries:
            print "Warning: No libraries loaded, cannot call %s" % (symbol, )
            return False

        for library in self._libraries:
            try:
                func = getattr(library, symbol)
                break
            except AttributeError:
                continue
        else:
            print 'Warning: could not find symbol: %s' % symbol
            name = symbol.replace('_get_type', '')
            self._failed_types[name] = True
            return False

        func.restype = cgobject.GType
        func.argtypes = []
        type_id = func()
        self._introspect_type(type_id, symbol)
        return True

    def _name_is_internal_gtype(self, giname):
        try:
            node = self._get_attribute(giname)
            return isinstance(node, (GLibObject, GLibInterface, GLibBoxed,
                                     GLibEnum, GLibFlags))
        except KeyError, e:
            return False

    def _parse_method(self, func):
        if not func.parameters:
            return False
        return self._parse_method_common(func, True)

    def _parse_constructor(self, func):
        return self._parse_method_common(func, False)

    def _parse_method_common(self, func, is_method):
        if not is_method:
            target_arg = func.retval
        else:
            target_arg = func.parameters[0]
        klass = self._get_attribute(target_arg.type.name)
        if klass is None or not isinstance(klass, (GLibObject, GLibBoxed)):
            return False

        # Look at the original C type (before namespace stripping), without
        # pointers: GtkButton -> gtk_button_, so we can figure out the
        # method name
        orig_type = target_arg.type.ctype.replace('*', '')
        prefix = to_underscores(orig_type).lower() + '_'
        if not func.symbol.startswith(prefix):
            return False

        # Strip namespace and object prefix: gtk_window_new -> new
        func.name = func.symbol[len(prefix):]
        if is_method:
            klass.methods.append(func)
        else:
            klass.constructors.append(func)
        return True

    def _parse_struct(self, struct):
        # This is a hack, but GObject is a rather fundamental piece so.
        internal_names = ["Object", 'InitiallyUnowned']
        g_internal_names = ["G" + x for x in internal_names]
        if (self._namespace_name == 'GObject' and
            struct.name in internal_names):
            self._create_gobject(struct)
            return
        elif struct.name in g_internal_names:
            # Avoid duplicates
            return
        node = self._names.names.get(struct.name)
        if node is None:
            self._add_attribute(struct, replace=True)
            return
        (ns, node) = node
        node.fields = struct.fields[:]

    def _parse_callback(self, callback):
        self._add_attribute(callback)

    def _strip_class_suffix(self, name):
        if (name.endswith('Class') or
            name.endswith('Iface')):
            return name[:-5]
        elif name.endswith('Interface'):
            return name[:-9]
        else:
            return name

    def _arg_is_failed(self, param):
        ctype = self._transformer.ctype_of(param).replace('*', '')
        uscored = to_underscores(self._strip_class_suffix(ctype)).lower()
        if uscored in self._failed_types:
            print "Warning: failed type: %r" % (param, )
            return True
        return False

    def _pair_class_struct(self, maybe_class):
        name = self._strip_class_suffix(maybe_class.name)
        if name == maybe_class.name:
            return

        if self._arg_is_failed(maybe_class):
            print "WARNING: deleting no-type %r" % (maybe_class.name, )
            del self._names.names[maybe_class.name]
            return

        name = self._resolve_type_name(name)
        resolved = self._transformer.strip_namespace_object(name)
        pair_class = self._get_attribute(resolved)
        if pair_class and isinstance(pair_class,
                                     (GLibObject, GLibBoxed, GLibInterface)):
            del self._names.names[maybe_class.name]
            for field in maybe_class.fields[1:]:
                pair_class.fields.append(field)
            return
        name = self._transformer.strip_namespace_object(maybe_class.name)
        pair_class = self._get_attribute(name)
        if pair_class and isinstance(pair_class,
                                     (GLibObject, GLibBoxed, GLibInterface)):

            del self._names.names[maybe_class.name]

    # Introspection

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
        elif fundamental_type_id == cgobject.TYPE_BOXED:
            self._introspect_boxed(type_id, symbol)
        elif fundamental_type_id == cgobject.TYPE_POINTER:
            # FIXME: Should we do something about these?
            #        GHashTable, GValue and a few other fundamentals are
            #        covered here
            return
        else:
            print 'unhandled GType: %s(%d)' % (cgobject.type_name(type_id),
                                               type_id)

    def _introspect_enum(self, ftype_id, type_id, symbol):
        type_class = cgobject.type_class_ref(type_id)
        if type_class is None:
            return

        members = []
        for enum_value in type_class.get_values():
            members.append(GLibEnumMember(enum_value.value_nick,
                                          enum_value.value,
                                          enum_value.value_name,
                                          enum_value.value_nick))

        klass = (GLibFlags if ftype_id == cgobject.TYPE_FLAGS else GLibEnum)
        type_name = cgobject.type_name(type_id)
        enum_name = self._transformer.strip_namespace_object(type_name)
        node = klass(enum_name, type_name, members, symbol)
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_object(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        parent_type_name = cgobject.type_name(cgobject.type_parent(type_id))
        parent_gitype = self._resolve_gtypename(parent_type_name)
        node = GLibObject(
            self._transformer.strip_namespace_object(type_name),
            parent_gitype,
            type_name, symbol)
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_interface(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        parent_type_name = cgobject.type_name(cgobject.type_parent(type_id))
        if parent_type_name == 'GInterface':
            parent_gitype = None
        else:
            parent_gitype = self._resolve_gtypename(parent_type_name)
        node = GLibInterface(
            self._transformer.strip_namespace_object(type_name),
            parent_gitype,
            type_name, symbol)
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_boxed(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        node = GLibBoxed(self._transformer.strip_namespace_object(type_name),
                         type_name, symbol)
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

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
            ctype = cgobject.type_name(pspec.value_type)
            node.properties.append(Property(
                pspec.name,
                type_name_from_ctype(ctype),
                ctype,
                ))

    def _introspect_signals(self, node, type_id):
        for signal_info in cgobject.signal_list(type_id):
            rtype = self._create_type(signal_info.return_type)
            return_ = Return(rtype)
            signal = GLibSignal(signal_info.signal_name, return_)
            for i, parameter in enumerate(signal_info.get_params()):
                if i == 0:
                    name = 'object'
                else:
                    name = 'p%s' % (i-1, )
                ptype = self._create_type(parameter)
                param = Parameter(name, ptype)
                signal.parameters.append(param)
            node.signals.append(signal)

    # Resolver

    def _resolve_type_name(self, type_name):
        res = self._transformer.resolve_type_name_full
        try:
            return res(type_name, None, self._names)
        except KeyError, e:
            return self._transformer.resolve_type_name(type_name, None)

    def _validate_type_name(self, name):
        if name in type_names:
            return True
        if name.find('.') >= 0:
            return True
        if name in self._names.aliases:
            return True
        if name in self._names.names:
            return True
        return False

    def _validate_type(self, ptype):
        if isinstance(ptype, Sequence):
            etype = ptype.element_type
            if isinstance(etype, Sequence):
                return self._validate_type(etype)
            return self._validate_type_name(etype)
        return self._validate_type_name(ptype.name)

    def _resolve_param_type_validate(self, ptype):
        ptype = self._resolve_param_type(ptype)
        if self._validating and not self._validate_type(ptype):
            raise UnknownTypeError("Unknown type %r" % (ptype, ))
        return ptype

    def _resolve_param_type(self, ptype):
        try:
            return self._transformer.resolve_param_type_full(ptype,
                                                             self._names)
        except KeyError, e:
            return self._transformer.resolve_param_type(ptype)
        return ptype

    def _resolve_node(self, node):
        if isinstance(node, (Callback, Function)):
            self._resolve_function(node)
        elif isinstance(node, GLibObject):
            self._resolve_glib_object(node)
        elif isinstance(node, GLibInterface):
            self._resolve_glib_interface(node)
        elif isinstance(node, GLibBoxed):
            self._resolve_glib_boxed(node)
        elif isinstance(node, Struct):
            self._resolve_struct(node)
        elif isinstance(node, Alias):
            self._resolve_alias(node)

    def _resolve_struct(self, node):
        for field in node.fields:
            self._resolve_field(field)

    def _resolve_parent(self, node):
        if not isinstance(node, (GLibInterface, GLibObject)):
            raise AssertionError
        if isinstance(node.parent, Unresolved):
            node.parent = \
                self._transformer.gtypename_to_giname(node.parent.target,
                                                      self._names)

    def _resolve_glib_interface(self, node):
        self._resolve_parent(node)
        self._resolve_methods(node.methods)
        self._resolve_properties(node.properties)
        self._resolve_signals(node.signals)

    def _resolve_glib_object(self, node):
        self._resolve_parent(node)
        self._resolve_constructors(node.constructors)
        self._resolve_methods(node.methods)
        self._resolve_properties(node.properties)
        self._resolve_signals(node.signals)

    def _resolve_glib_boxed(self, node):
        self._resolve_constructors(node.constructors)
        self._resolve_methods(node.methods)

    def _resolve_constructors(self, constructors):
        for ctor in constructors:
            self._resolve_function(ctor)

    def _resolve_methods(self, methods):
        for method in methods:
            self._resolve_function(method)

    def _resolve_signals(self, signals):
        for signal in signals:
            self._resolve_function(signal)

    def _resolve_properties(self, properties):
        for prop in properties:
            self._resolve_property(prop)

    def _resolve_property(self, prop):
        prop.type = self._resolve_param_type(prop.type)

    def _resolve_function(self, func):
        self._resolve_parameters(func.parameters)
        func.retval.type = self._resolve_param_type(func.retval.type)

    def _resolve_parameters(self, parameters):
        for parameter in parameters:
            parameter.type = self._resolve_param_type(parameter.type)

    def _resolve_field(self, field):
        if isinstance(field, Callback):
            self._resolve_function(field)
            return
        field.type = self._resolve_param_type(field.type)

    def _resolve_alias(self, alias):
        alias.target = self._resolve_type_name(alias.target)

    # Validation

    def _validate(self, nodes):
        nodes = list(self._names.names.itervalues())
        i = 0
        self._validating = True
        while True:
            print "Type resolution; pass=%d" % (i, )
            initlen = len(nodes)
            nodes = list(self._names.names.itervalues())
            for node in nodes:
                try:
                    self._resolve_node(node)
                except UnknownTypeError, e:
                    print "WARNING: %s: Deleting %r" % (e, node)
                    self._remove_attribute(node.name)
            if len(nodes) == initlen:
                break
            i += 1
        self._validating = False
