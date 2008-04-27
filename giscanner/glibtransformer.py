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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

import ctypes
import re
import os

from . import cgobject
from .odict import odict
from .ast import (Callback, Enum, Function, Parameter, Property, Return,
                  Sequence, Struct)
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject, GLibSignal)


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




class GLibTransformer(object):
    def __init__(self, namespace_name):
        self._namespace_name = namespace_name
        self._output_ns = odict()
        self._library = None
        self._type_names = {}

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

        # Second round, associate GtkButtonClass with GtkButton
        for node in self._output_ns.values():
            if isinstance(node, Struct):
                self._pair_class_struct(node)

    def register_include(self, filename):
        from .gidlparser import GIDLParser
        parser = GIDLParser(filename)
        nsname = parser.get_namespace_name()
        for node in parser.get_nodes():
            self._type_names[node.type_name] = (nsname, node)

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

    def _register_internal_type(self, type_name, node):
        self._type_names[type_name] = (None, node)

    def _strip_namespace_func(self, name):
        orig_name = name
        prefix = self._namespace_name.lower() + '_'
        name = name.lower()
        if name.startswith(prefix):
            name = orig_name[len(prefix):]
        return name

    def _strip_namespace_object(self, name):
        orig_name = name
        prefix = self._namespace_name.lower()
        name = name.lower()
        if name.startswith(prefix):
            name = orig_name[len(prefix):]
        return name

    def _resolve_type_name(self, type_name):
        item = self._type_names.get(type_name)
        if item is not None:
            nsname, item = item
            if nsname is None:
                return item.name
            return '%s.%s' % (nsname, item.name)
        return type_name

    def _resolve_param_type(self, ptype):
        type_name = ptype.name.replace('*', '')
        ptype.name = ptype.name.replace(type_name,
                                        self._resolve_type_name(type_name))
        return ptype

    def _parse_node(self, node):
        if isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Struct):
            self._parse_struct(node)
        elif isinstance(node, Callback):
            self._parse_callback(node)
        else:
            print 'GOBJECT BUILDER: Unhandled node:', node

    def _parse_enum(self, enum):
        enum.name = self._strip_namespace_object(enum.name)
        self._add_attribute(enum)

    def _parse_function(self, func):
        if self._parse_get_type_function(func):
            return
        elif self._parse_constructor(func):
            return
        elif self._parse_method(func):
            return

        self._parse_parameters(func.parameters)
        func.retval.type = self._resolve_param_type(func.retval.type)

        func.name = self._strip_namespace_func(func.name)
        self._add_attribute(func)

    def _parse_parameters(self, parameters):
        for parameter in parameters:
            parameter.type = self._resolve_param_type(parameter.type)

    def _parse_get_type_function(self, func):
        # GType *_get_type(void)
        symbol = func.name
        if not symbol.endswith('_get_type'):
            return False
        if func.retval.type.name != 'GType':
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
        first_arg = func.parameters[0].type.name
        if first_arg.count('*') != 1:
            return False

        object_name = first_arg.replace('*', '')
        return self._parse_method_common(func, object_name, is_method=True)

    def _parse_constructor(self, func):
        # FIXME: This is hackish, we should preserve the pointer structures
        #        here, so we can find pointers to objects and not just
        #        pointers to anything
        rtype = func.retval.type
        if rtype.name.count('*') != 1:
            return False

        object_name = rtype.name.replace('*', '')
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
        self._parse_parameters(func.parameters)
        func.retval.type = self._resolve_param_type(func.retval.type)
        return True

    def _parse_struct(self, struct):
        self._add_attribute(struct)

    def _parse_callback(self, callback):
        self._add_attribute(callback)

    def _pair_class_struct(self, class_node):
        name = class_node.name
        if (name.endswith('Class') or
            name.endswith('Iface')):
            name = name[:-5]
        elif name.endswith('Interface'):
            name = name[:-9]
        else:
            return

        node = self._output_ns.get(self._resolve_type_name(name))
        del self._output_ns[class_node.name]
        for field in class_node.fields[1:]:
            node.fields.append(field)

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
        node = klass(self._strip_namespace_object(type_name),
                      members, type_name, symbol)
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_object(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        parent_type_name = cgobject.type_name(cgobject.type_parent(type_id))
        node = GLibObject(self._strip_namespace_object(type_name),
                          self._resolve_type_name(parent_type_name),
                          type_name, symbol)
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        self._add_attribute(node)
        self._remove_attribute(type_name)
        self._register_internal_type(type_name, node)

    def _introspect_interface(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        node = GLibInterface(self._strip_namespace_object(type_name),
                             type_name, symbol)
        self._introspect_properties(node, type_id)
        self._introspect_signals(node, type_id)
        self._add_attribute(node)
        self._register_internal_type(type_name, node)

    def _introspect_boxed(self, type_id, symbol):
        type_name = cgobject.type_name(type_id)
        node = GLibBoxed(self._strip_namespace_object(type_name),
                         type_name, symbol)
        self._add_attribute(node)
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
            node.properties.append(Property(
                pspec.name,
                cgobject.type_name(pspec.value_type)))

    def _introspect_signals(self, node, type_id):
        for signal_info in cgobject.signal_list(type_id):
            retval = Return(cgobject.type_name(signal_info.return_type))
            signal = GLibSignal(signal_info.signal_name, retval)
            for i, parameter in enumerate(signal_info.get_params()):
                if i == 0:
                    name = 'object'
                else:
                    name = 'p%s' % (i-1,)
                signal.parameters.append(
                    Parameter(name, cgobject.type_name(parameter)))
            node.signals.append(signal)
