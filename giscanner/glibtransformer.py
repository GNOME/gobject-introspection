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

import os
import re
import ctypes
from ctypes.util import find_library

from . import cgobject
from .ast import (Callback, Constant, Enum, Function, Member, Namespace,
                  Parameter, Property, Return, Struct, Type, Alias,
                  Union, Field, type_name_from_ctype,
                  default_array_types, TYPE_UINT8, PARAM_DIRECTION_IN)
from .transformer import Names
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject, GLibSignal, GLibBoxedStruct,
                      GLibBoxedUnion, GLibBoxedOther, type_names)
from .utils import extract_libtool, to_underscores, to_underscores_noprefix

default_array_types['guchar*'] = TYPE_UINT8

SYMBOL_BLACKLIST = [
    # These ones break GError conventions
    'g_simple_async_result_new_from_error',
    'g_simple_async_result_set_from_error',
    'g_simple_async_result_propagate_error',
    'g_simple_async_result_report_error_in_idle',
    'gtk_print_operation_get_error',
]

SYMBOL_BLACKLIST_RE = [re.compile(x) for x in \
                           [r'\w+_marshal_[A-Z]+__', ]]


class Unresolved(object):

    def __init__(self, target):
        self.target = target


class UnknownTypeError(Exception):
    pass


class GLibTransformer(object):

    def __init__(self, transformer, noclosure=False):
        self._transformer = transformer
        self._transformer.set_container_types(['GList*', 'GSList*'],
                                              ['GHashtable*'])
        self._namespace_name = None
        self._names = Names()
        self._uscore_type_names = {}
        self._libraries = []
        self._failed_types = {}
        self._boxed_types = {}
        self._private_internal_types = {}
        self._noclosure = noclosure
        self._validating = False

    # Public API

    def add_library(self, libname):
        # For testing mainly.
        libtool_libname = 'lib' + libname + '.la'
        if os.path.exists(libtool_libname):
            found_libname = extract_libtool(libtool_libname)
        elif libname.endswith('.la'):
            found_libname = extract_libtool(libname)
        else:
            found_libname = find_library(libname)
        if not found_libname:
            raise ValueError("Failed to find library: %r" % (libname, ))
        self._libraries.append(ctypes.cdll.LoadLibrary(found_libname))

    def _print_statistics(self):
        nodes = list(self._names.names.itervalues())

        def count_type(otype):
            return len([x for x in nodes
                        if isinstance(x[1], otype)])
        objectcount = count_type(GLibObject)
        ifacecount = count_type(GLibInterface)
        enumcount = count_type(GLibEnum)
        print " %d nodes; %d objects, %d interfaces, %d enums" \
            % (len(nodes), objectcount, ifacecount, enumcount)

    def parse(self):
        namespace = self._transformer.parse()
        self._namespace_name = namespace.name

        # First pass: parsing
        for node in namespace.nodes:
            self._parse_node(node)

        # We don't want an alias for this - it's handled specially in
        # the typelib compiler.
        if namespace.name == 'GObject':
            del self._names.aliases['Type']

        # Introspection is done from within parsing

        # Second pass: pair boxed structures
        for boxed in self._boxed_types.itervalues():
            self._pair_boxed_type(boxed)
        # Third pass: delete class structures, resolve
        # all types we now know about
        nodes = list(self._names.names.itervalues())
        for (ns, node) in nodes:
            try:
                self._resolve_node(node)
            except KeyError, e:
                print "WARNING: DELETING node %s: %s" % (node.name, e)
                self._remove_attribute(node.name)
            # associate GtkButtonClass with GtkButton
            if isinstance(node, Struct):
                self._pair_class_struct(node)
        for (ns, alias) in self._names.aliases.itervalues():
            self._resolve_alias(alias)

        self._print_statistics()
        # Fourth pass: ensure all types are known
        if not self._noclosure:
            self._validate(nodes)

        # Create a new namespace with what we found
        namespace = Namespace(namespace.name, namespace.version)
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
        uscored = to_underscores(type_name).lower()
        self._uscore_type_names[uscored] = node
        # Besides the straight underscore conversion, we also try
        # removing the underscores from the namespace as a possible C
        # mapping; e.g. it's webkit_web_view, not web_kit_web_view
        suffix = self._transformer.remove_prefix(type_name)
        prefix = type_name[:-len(suffix)]
        no_uscore_prefixed = (prefix + '_' + to_underscores(suffix)).lower()
        self._uscore_type_names[no_uscore_prefixed] = node

    # Helper functions

    def _type_from_gtype(self, type_id):
        ctype = cgobject.type_name(type_id)
        type_name = type_name_from_ctype(ctype)
        type_name = type_name.replace('*', '')
        type_name = self._resolve_type_name(type_name)

        type = Type(type_name, ctype)
        type._gtype = type_id
        return type

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
        node = GLibObject(node.name, parent_gitype, type_name, symbol, True)
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
        elif isinstance(node, Union):
            self._parse_union(node)
        elif isinstance(node, Constant):
            self._parse_constant(node)
        else:
            print 'GLIB Transformer: Unhandled node:', node

    def _parse_alias(self, alias):
        self._names.aliases[alias.name] = (None, alias)

    def _parse_enum(self, enum):
        self._add_attribute(enum)

    def _parse_constant(self, constant):
        self._add_attribute(constant)

    def _parse_function(self, func):
        if func.symbol in SYMBOL_BLACKLIST:
            return
        if func.symbol.startswith('_'):
            return
        for regexp in SYMBOL_BLACKLIST_RE:
            if regexp.match(func.symbol):
                return
        if self._parse_get_type_function(func):
            return

        self._add_attribute(func)

    def _parse_get_type_function(self, func):
        symbol = func.symbol
        if not symbol.endswith('_get_type'):
            return False
        if self._namespace_name == 'GLib':
            # No GObjects in GLib
            return False
        # GType *_get_type(void)
        if func.retval.type.name not in ['Type',
                                         'GType',
                                         'GObject.Type',
                                         'Gtk.Type']:
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
            return isinstance(node, (GLibObject, GLibInterface,
                                     GLibBoxed, GLibEnum, GLibFlags))
        except KeyError, e:
            return False

    def _parse_method(self, func):
        if not func.parameters:
            return False
        return self._parse_method_common(func, True)

    def _parse_constructor(self, func):
        return self._parse_method_common(func, False)

    def _parse_method_common(self, func, is_method):
        # Skip _get_type functions, we processed them
        # already
        if func.symbol.endswith('_get_type'):
            return None
        if self._namespace_name == 'GLib':
            # No GObjects in GLib
            return None

        if not is_method:
            target_arg = func.retval
        else:
            target_arg = func.parameters[0]
        target_arg.type = self._resolve_param_type(target_arg.type)

        if is_method:
            # Methods require their first arg to be a known class
            # Look at the original C type (before namespace stripping), without
            # pointers: GtkButton -> gtk_button_, so we can figure out the
            # method name
            argtype = target_arg.type.ctype.replace('*', '')
            name = self._transformer.remove_prefix(argtype)
            name_uscore = to_underscores_noprefix(name).lower()
            name_offset = func.symbol.find(name_uscore)
            if name_offset < 0:
                return None
            prefix = func.symbol[:name_offset+len(name_uscore)]
        else:
            # Constructors must have _new
            # Take everything before that as class name
            new_idx = func.symbol.find('_new')
            if new_idx < 0:
                return None
            # Constructors don't return basic types
            derefed = self._transformer.follow_aliases(target_arg.type.name,
                                                       self._names)
            if derefed in type_names:
                #print "NOTE: Rejecting constructor returning basic: %r" \
                #    % (func.symbol, )
                return None
            prefix = func.symbol[:new_idx]

        klass = None

        def valid_matching_klass(tclass):
            if tclass is None:
                return False
            elif isinstance(klass, (GLibEnum, GLibFlags)):
                return False
            elif not isinstance(tclass, (GLibObject, GLibBoxed,
                                          GLibInterface)):
                return False
            else:
                return True

        klass = self._uscore_type_names.get(prefix)
        if klass is None:
            #print "NOTE: No valid matching class for likely "+\
            #    "method or constructor: %r" % (func.symbol, )
            return None
        # Enums can't have ctors or methods
        if isinstance(klass, (GLibEnum, GLibFlags)):
            return None

        # The _uscore_type_names member holds the plain GLibBoxed
        # object; we want to actually use the struct/record associated
        if isinstance(klass, GLibBoxed):
            name = self._transformer.remove_prefix(klass.type_name)
            klass = self._get_attribute(name)

        if not is_method:
            # Interfaces can't have constructors, punt to global scope
            if isinstance(klass, GLibInterface):
                #print "NOTE: Rejecting constructor for"+\
                #    " interface type: %r" % (func.symbol, )
                return None
            # TODO - check that the return type is a subclass of the
            # class from the prefix
            # But for now, ensure that constructor returns are always
            # the most concrete class
            func.retval.type = Type(klass.name,
                                    self._transformer.ctype_of(klass)+'*')

        self._remove_attribute(func.name)
        # Strip namespace and object prefix: gtk_window_new -> new
        func.name = func.symbol[len(prefix)+1:]
        if is_method:
            # We don't need the "this" parameter
            del func.parameters[0]
            klass.methods.append(func)
        else:
            klass.constructors.append(func)
        return func

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

    def _parse_union(self, union):
        node = self._names.names.get(union.name)
        if node is None:
            self._add_attribute(union, replace=True)
            return
        (ns, node) = node
        node.fields = union.fields[:]

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

        # Object class fields are assumed to be read-only
        # (see also _introspect_object and transformer.py)
        for field in maybe_class.fields:
            if isinstance(field, Field):
                field.writable = False

        name = self._resolve_type_name(name)
        resolved = self._transformer.remove_prefix(name)
        pair_class = self._get_attribute(resolved)
        if pair_class and isinstance(pair_class,
                                     (GLibObject, GLibInterface)):
            for field in maybe_class.fields[1:]:
                pair_class.fields.append(field)
            return
        name = self._transformer.remove_prefix(maybe_class.name)
        pair_class = self._get_attribute(name)
        if pair_class and isinstance(pair_class,
                                     (GLibObject, GLibInterface)):

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
        enum_name = self._transformer.remove_prefix(type_name)
        node = klass(enum_name, type_name, members, symbol)
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_object(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        # We handle this specially above; in 2.16 and below there
        # was no g_object_get_type, for later versions we need
        # to skip it
        if type_name == 'GObject':
            return
        parent_type_name = cgobject.type_name(cgobject.type_parent(type_id))
        parent_gitype = self._resolve_gtypename(parent_type_name)
        is_abstract = cgobject.type_is_abstract(type_id)
        node = GLibObject(
            self._transformer.remove_prefix(type_name),
            parent_gitype,
            type_name,
            symbol, is_abstract)
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        self._introspect_implemented_interfaces(node, type_id)

        # add struct fields
        struct = self._get_attribute(node.name)
        if struct is not None:
            node.fields = struct.fields
            for field in node.fields:
                if isinstance(field, Field):
                    # Object instance fields are assumed to be read-only
                    # (see also _pair_class_struct and transformer.py)
                    field.writable = False

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
            self._transformer.remove_prefix(type_name),
            parent_gitype,
            type_name, symbol)
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        # GtkFileChooserEmbed is an example of a private interface, we
        # just filter them out
        if symbol.startswith('_'):
            print "NOTICE: Marking %s as internal type" % (type_name, )
            self._private_internal_types[type_name] = node
        else:
            self._add_attribute(node, replace=True)
            self._register_internal_type(type_name, node)

    def _introspect_boxed(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        # This one doesn't go in the main namespace; we associate it with
        # the struct or union
        node = GLibBoxed(type_name, symbol)
        self._boxed_types[node.type_name] = node
        self._register_internal_type(type_name, node)

    def _introspect_implemented_interfaces(self, node, type_id):
        fundamental_type_id = cgobject.type_fundamental(type_id)
        if fundamental_type_id != cgobject.TYPE_OBJECT:
            raise AssertionError
        interfaces = cgobject.type_interfaces(type_id)
        gt_interfaces = []
        for interface_typeid in interfaces:
            iname = cgobject.type_name(interface_typeid)
            gitype = self._resolve_gtypename(iname)
            gt_interfaces.append(gitype)
        node.interfaces = gt_interfaces

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
            readable = (pspec.flags & 1) != 0
            writable = (pspec.flags & 2) != 0
            construct = (pspec.flags & 4) != 0
            construct_only = (pspec.flags & 8) != 0
            node.properties.append(Property(
                pspec.name,
                type_name_from_ctype(ctype),
                readable, writable, construct, construct_only,
                ctype,
                ))

    def _introspect_signals(self, node, type_id):
        for signal_info in cgobject.signal_list(type_id):
            rtype = self._type_from_gtype(signal_info.return_type)
            return_ = Return(rtype)
            signal = GLibSignal(signal_info.signal_name, return_)
            for i, parameter in enumerate(signal_info.get_params()):
                if i == 0:
                    name = 'object'
                else:
                    name = 'p%s' % (i-1, )
                ptype = self._type_from_gtype(parameter)
                param = Parameter(name, ptype)
                signal.parameters.append(param)
            node.signals.append(signal)

    # Resolver

    def _resolve_type_name(self, type_name, ctype=None):
        # Workaround glib bug #548689, to be included in 2.18.0
        if type_name == "GParam":
            type_name = "GObject.ParamSpec"

        res = self._transformer.resolve_type_name_full
        try:
            return res(type_name, ctype, self._names)
        except KeyError, e:
            return self._transformer.resolve_type_name(type_name, ctype)

    def _resolve_param_type(self, ptype, **kwargs):
        return self._transformer.resolve_param_type_full(ptype,
                                                         self._names,
                                                         **kwargs)

    def _resolve_node(self, node):
        if isinstance(node, Function):
            self._resolve_function_toplevel(node)

        elif isinstance(node, Callback):
            self._resolve_function(node)
        elif isinstance(node, GLibObject):
            self._resolve_glib_object(node)
        elif isinstance(node, GLibInterface):
            self._resolve_glib_interface(node)
        elif isinstance(node, Struct):
            self._resolve_struct(node)
        elif isinstance(node, Union):
            self._resolve_union(node)
        elif isinstance(node, Alias):
            self._resolve_alias(node)

    def _resolve_function_toplevel(self, func):
        newfunc = self._parse_constructor(func)
        if not newfunc:
            newfunc = self._parse_method(func)
            if not newfunc:
                self._resolve_function(func)
                return
        self._resolve_function(newfunc)

    def _pair_boxed_type(self, boxed):
        name = self._transformer.remove_prefix(boxed.type_name)
        pair_node = self._get_attribute(name)
        if not pair_node:
            boxed_item = GLibBoxedOther(name, boxed.type_name,
                                        boxed.get_type)
        elif isinstance(pair_node, Struct):
            boxed_item = GLibBoxedStruct(pair_node.name, boxed.type_name,
                                         boxed.get_type)
            boxed_item.fields = pair_node.fields
        elif isinstance(pair_node, Union):
            boxed_item = GLibBoxedUnion(pair_node.name, boxed.type_name,
                                         boxed.get_type)
            boxed_item.fields = pair_node.fields
        else:
            return False
        self._add_attribute(boxed_item, replace=True)

    def _resolve_struct(self, node):
        for field in node.fields:
            self._resolve_field(field)

    def _resolve_union(self, node):
        for field in node.fields:
            self._resolve_field(field)

    def _force_resolve(self, item, allow_unknown=False):
        if isinstance(item, Unresolved):
            if item.target in self._private_internal_types:
                return None
            try:
                return self._transformer.gtypename_to_giname(item.target,
                                                             self._names)
            except KeyError, e:
                if allow_unknown:
                    print "WARNING: Skipping unknown interface %s" % \
                        (item.target, )
                    return None
                else:
                    raise
        if item in self._private_internal_types:
            return None
        return item

    def _resolve_glib_interface(self, node):
        node.parent = self._force_resolve(node.parent)
        self._resolve_methods(node.methods)
        self._resolve_properties(node.properties, node)
        self._resolve_signals(node.signals)

    def _resolve_glib_object(self, node):
        node.parent = self._force_resolve(node.parent)
        node.interfaces = filter(None,
            [self._force_resolve(x, allow_unknown=True)
                                    for x in node.interfaces])
        self._resolve_constructors(node.constructors)
        self._resolve_methods(node.methods)
        self._resolve_properties(node.properties, node)
        self._resolve_signals(node.signals)
        for field in node.fields:
            self._resolve_field(field)

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

    def _resolve_properties(self, properties, context):
        failed = []
        for prop in properties:
            try:
                self._resolve_property(prop)
            except KeyError, e:
                failed.append(prop)
        for fail in failed:
            print ("WARNING: Deleting object property %r (of %r)" +\
                       "with unknown type") % (fail, context)
            properties.remove(fail)

    def _resolve_property(self, prop):
        prop.type = self._resolve_param_type(prop.type, allow_invalid=False)

    def _adjust_transfer(self, param):
        # Do GLib/GObject-specific type transformations here

        transfer = None
        is_object = None
        if hasattr(param.type, '_gtype'):
            ftype = cgobject.type_fundamental(param.type._gtype)
            assert ftype != cgobject.TYPE_INVALID, param.type._gtype

            is_object = ftype in [cgobject.TYPE_OBJECT,
                                  cgobject.TYPE_INTERFACE]

            if ftype in [cgobject.TYPE_OBJECT,
                         cgobject.TYPE_INTERFACE,
                         cgobject.TYPE_STRING,
                         cgobject.TYPE_BOXED,
                         cgobject.TYPE_PARAM]:
                transfer = 'full'
            else:
                # if type is a cgobject.TYPE_POINTER we could require direction
                # and transfer-ownership annotations
                transfer = 'none'

        if is_object is None:
            is_object = (param.type.name == 'GObject.Object' or
                         (self._namespace_name == 'GObject' and
                          param.type.name == 'Object'))

        # Default to full transfer for GObjects
        if isinstance(param, Parameter):
            is_out = (param.direction != PARAM_DIRECTION_IN)
        else:
            is_out = True
        if param.transfer is None or param.transfer_inferred:
            if is_out and is_object:
                param.transfer = 'full'
            elif transfer is not None:
                param.transfer = transfer

    def _adjust_throws(self, func):
        if func.parameters == []:
            return

        last_param = func.parameters.pop()

        if (last_param.type.name == 'GLib.Error' or
            (self._namespace_name == 'GLib' and
             last_param.type.name == 'Error')):
            func.throws = True
        else:
            func.parameters.append(last_param)

    def _resolve_function(self, func):
        self._resolve_parameters(func.parameters)
        func.retval.type = self._resolve_param_type(func.retval.type)
        self._adjust_throws(func)
        self._adjust_transfer(func.retval)

    def _resolve_parameters(self, parameters):
        for parameter in parameters:
            parameter.type = self._resolve_param_type(parameter.type)
            self._adjust_transfer(parameter)

    def _resolve_field(self, field):
        if isinstance(field, Callback):
            self._resolve_function(field)
            return
        field.type = self._resolve_param_type(field.type)

    def _resolve_alias(self, alias):
        alias.target = self._resolve_type_name(alias.target, alias.target)

    # Validation

    def _validate(self, nodes):
        nodes = list(self._names.names.itervalues())
        i = 0
        self._validating = True
        while True:
            initlen = len(nodes)

            print "Type resolution; pass=%d" % (i, )
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
            self._print_statistics()
        self._validating = False
