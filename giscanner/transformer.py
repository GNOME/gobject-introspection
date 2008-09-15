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

from giscanner.ast import (Callback, Enum, Function, Namespace, Member,
                           Parameter, Return, Sequence, Struct, Field,
                           Type, Alias, Interface, Class, Node, Union,
                           type_name_from_ctype, type_names)
from giscanner.config import DATADIR
from .glibast import GLibBoxed
from giscanner.sourcescanner import (
    SourceSymbol, ctype_name, CTYPE_POINTER,
    CTYPE_BASIC_TYPE, CTYPE_UNION, CTYPE_ARRAY, CTYPE_TYPEDEF,
    CTYPE_VOID, CTYPE_ENUM, CTYPE_FUNCTION, CTYPE_STRUCT,
    CSYMBOL_TYPE_FUNCTION, CSYMBOL_TYPE_TYPEDEF, CSYMBOL_TYPE_STRUCT,
    CSYMBOL_TYPE_ENUM, CSYMBOL_TYPE_UNION, CSYMBOL_TYPE_OBJECT,
    CSYMBOL_TYPE_MEMBER)
from .odict import odict
from .utils import strip_common_prefix, to_underscores

_xdg_data_dirs = [x for x in os.environ.get('XDG_DATA_DIRS', '').split(':') \
                      + [DATADIR, '/usr/share'] if x]


class SkipError(Exception):
    pass


class Names(object):
    names = property(lambda self: self._names)
    aliases = property(lambda self: self._aliases)
    type_names = property(lambda self: self._type_names)
    ctypes = property(lambda self: self._ctypes)

    def __init__(self):
        super(Names, self).__init__()
        self._names = odict() # Maps from GIName -> (namespace, node)
        self._aliases = {} # Maps from GIName -> GIName
        self._type_names = {} # Maps from GTName -> (namespace, node)
        self._ctypes = {} # Maps from CType -> (namespace, node)


class Transformer(object):

    def __init__(self, generator, namespace_name):
        self.generator = generator
        self._namespace = Namespace(namespace_name)
        self._names = Names()
        self._typedefs_ns = {}
        self._strip_prefix = ''
        self._includes = set()
        self._includepaths = []

    def get_names(self):
        return self._names

    def get_includes(self):
        return self._includes

    def set_strip_prefix(self, strip_prefix):
        self._strip_prefix = strip_prefix

    def parse(self):
        nodes = []
        for symbol in self.generator.get_symbols():
            node = self._traverse_one(symbol)
            self._add_node(node)
        return self._namespace

    def register_include(self, filename):
        (path, suffix) = os.path.splitext(filename)
        name = os.path.basename(path)
        if name in self._includes:
            return
        if suffix == '':
            suffix = '.gir'
            filename = path + suffix
        if suffix == '.gir':
            source = filename
            if not os.path.exists(filename):
                searchdirs = [os.path.join(d, 'gir') for d \
                                  in _xdg_data_dirs]
                searchdirs.extend(self._includepaths)
                source = None
                for d in searchdirs:
                    source = os.path.join(d, filename)
                    if os.path.exists(source):
                        break
                    source = None
            if not source:
                raise ValueError("Couldn't find include %r (search path: %r)"\
                                     % (filename, searchdirs))
            d = os.path.dirname(source)
            if d not in self._includepaths:
                self._includepaths.append(d)
            self._includes.add(name)
            from .girparser import GIRParser
            parser = GIRParser(source)
        else:
            raise NotImplementedError(filename)
        for include in parser.get_includes():
            self.register_include(include)
        nsname = parser.get_namespace_name()
        for node in parser.get_nodes():
            if isinstance(node, Alias):
                self._names.aliases[node.name] = (nsname, node)
            elif isinstance(node, (GLibBoxed, Interface, Class)):
                self._names.type_names[node.type_name] = (nsname, node)
            self._names.names[node.name] = (nsname, node)
            if hasattr(node, 'ctype'):
                self._names.ctypes[node.ctype] = (nsname, node)
            elif hasattr(node, 'symbol'):
                self._names.ctypes[node.symbol] = (nsname, node)

    def strip_namespace_object(self, name):
        prefix = self._namespace.name.lower()
        if len(name) > len(prefix) and name.lower().startswith(prefix):
            return name[len(prefix):]
        return self._remove_prefix(name)

    # Private

    def _add_node(self, node):
        if node is None:
            return
        if node.name.startswith('_'):
            return
        self._namespace.nodes.append(node)
        self._names.names[node.name] = (None, node)

    def _strip_namespace_func(self, name):
        prefix = self._namespace.name.lower() + '_'
        if name.lower().startswith(prefix):
            name = name[len(prefix):]
        else:
            prefix = to_underscores(self._namespace.name).lower() + '_'
            if name.lower().startswith(prefix):
                name = name[len(prefix):]
        return self._remove_prefix(name, isfunction=True)

    def _remove_prefix(self, name, isfunction=False):
        # when --strip-prefix=g:
        #   GHashTable -> HashTable
        #   g_hash_table_new -> hash_table_new
        prefix = self._strip_prefix.lower()
        if isfunction:
            prefix += '_'
        if name.lower().startswith(prefix):
            name = name[len(prefix):]

        while name.startswith('_'):
            name = name[1:]
        return name

    def _traverse_one(self, symbol, stype=None):
        assert isinstance(symbol, SourceSymbol), symbol

        if stype is None:
            stype = symbol.type
        if stype == CSYMBOL_TYPE_FUNCTION:
            try:
                return self._create_function(symbol)
            except SkipError:
                return
        elif stype == CSYMBOL_TYPE_TYPEDEF:
            return self._create_typedef(symbol)
        elif stype == CSYMBOL_TYPE_STRUCT:
            return self._create_struct(symbol)
        elif stype == CSYMBOL_TYPE_ENUM:
            return self._create_enum(symbol)
        elif stype == CSYMBOL_TYPE_OBJECT:
            return self._create_object(symbol)
        elif stype == CSYMBOL_TYPE_MEMBER:
            return self._create_member(symbol)
        elif stype == CSYMBOL_TYPE_UNION:
            return self._create_union(symbol)
        else:
            raise NotImplementedError(
                'Transformer: unhandled symbol: %r' % (symbol, ))

    def _create_enum(self, symbol):
        members = []
        for child in symbol.base_type.child_list:
            name = strip_common_prefix(symbol.ident, child.ident).lower()
            members.append(Member(name,
                                  child.const_int,
                                  child.ident))

        enum_name = self.strip_namespace_object(symbol.ident)
        enum_name = symbol.ident[-len(enum_name):]
        enum_name = self._remove_prefix(enum_name)
        enum = Enum(enum_name, symbol.ident, members)
        self._names.type_names[symbol.ident] = (None, enum)
        return enum

    def _create_object(self, symbol):
        return Member(symbol.ident, symbol.base_type.name,
                      symbol.ident)

    def _parse_deprecated(self, node, directives):
        deprecated = directives.get('deprecated', False)
        if deprecated:
            deprecated_value = deprecated[0]
            print "DEPRECATED: %r" % (deprecated_value, )
            if ':' in deprecated_value:
                # Split out gtk-doc version
                (node.deprecated_version, node.deprecated) = \
                    [x.strip() for x in deprecated_value.split(':', 1)]
            else:
                # No version, just include str
                node.deprecated = deprecated_value.strip()

    def _create_function(self, symbol):
        directives = symbol.directives()
        parameters = list(self._create_parameters(
            symbol.base_type, directives))
        return_ = self._create_return(symbol.base_type.base_type,
                                      directives.get('return', []))
        name = self._strip_namespace_func(symbol.ident)
        func = Function(name, return_, parameters, symbol.ident)
        self._parse_deprecated(func, directives)
        return func

    def _create_source_type(self, source_type):
        if source_type is None:
            return 'None'
        if source_type.type == CTYPE_VOID:
            value = 'void'
        elif source_type.type == CTYPE_BASIC_TYPE:
            value = source_type.name
        elif source_type.type == CTYPE_TYPEDEF:
            value = source_type.name
        elif source_type.type == CTYPE_ARRAY:
            return self._create_source_type(source_type.base_type)
        elif source_type.type == CTYPE_POINTER:
            value = self._create_source_type(source_type.base_type) + '*'
        else:
            print 'TRANSFORMER: Unhandled source type %r' % (
                source_type, )
            value = 'any'
        return value

    def _create_parameters(self, base_type, options=None):
        if not options:
            options = {}
        for child in base_type.child_list:
            yield self._create_parameter(
                child, options.get(child.ident, []))

    def _create_member(self, symbol):
        ctype = symbol.base_type.type
        if (ctype == CTYPE_POINTER and
            symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_callback(symbol)
        else:
            ftype = self._create_type(symbol.base_type)
            node = Field(symbol.ident, ftype, symbol.ident)
        return node

    def _create_typedef(self, symbol):
        ctype = symbol.base_type.type
        if (ctype == CTYPE_POINTER and
            symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_callback(symbol)
        elif ctype == CTYPE_STRUCT:
            node = self._create_typedef_struct(symbol)
        elif ctype == CTYPE_UNION:
            node = self._create_typedef_union(symbol)
        elif ctype == CTYPE_ENUM:
            return self._create_enum(symbol)
        elif ctype in (CTYPE_TYPEDEF,
                       CTYPE_POINTER,
                       CTYPE_BASIC_TYPE,
                       CTYPE_VOID):
            name = self.strip_namespace_object(symbol.ident)
            if symbol.base_type.name:
                target = self.strip_namespace_object(symbol.base_type.name)
            else:
                target = 'none'
            if name in type_names:
                return None
            return Alias(name, target, ctype=symbol.ident)
        else:
            raise NotImplementedError(
                "symbol %r of type %s" % (symbol.ident, ctype_name(ctype)))
        return node

    def _create_type(self, source_type):
        ctype = self._create_source_type(source_type)
        if ctype == 'va_list':
            raise SkipError
        # FIXME: FILE* should not be skipped, it should be handled
        #        properly instead
        elif ctype == 'FILE*':
            raise SkipError
        type_name = type_name_from_ctype(ctype)
        type_name = type_name.replace('*', '')
        resolved_type_name = self.resolve_type_name(type_name)
        return Type(resolved_type_name, ctype)

    def _create_parameter(self, symbol, options):
        ptype = self._create_type(symbol.base_type)
        param = Parameter(symbol.ident, ptype)
        for option in options:
            if option in ['in-out', 'inout']:
                param.direction = 'inout'
            elif option == 'in':
                param.direction = 'in'
            elif option == 'out':
                param.direction = 'out'
            elif option == 'callee-owns':
                param.transfer = True
            elif option == 'allow-none':
                param.allow_none = True
            else:
                print 'Unhandled parameter annotation option: %s' % (
                    option, )
        return param

    def _create_return(self, source_type, options=None):
        if not options:
            options = []
        rtype = self._create_type(source_type)
        rtype = self.resolve_param_type(rtype)
        return_ = Return(rtype)
        for option in options:
            if option == 'caller-owns':
                return_.transfer = True
            elif option.startswith('seq '):
                value, element_options = option[3:].split(None, 2)
                c_element_type = self._parse_type_annotation(value)
                element_type = c_element_type.replace('*', '')
                element_type = self.resolve_type_name(element_type,
                                                      c_element_type)
                seq = Sequence(rtype.name,
                               type_name_from_ctype(rtype.name),
                               element_type)
                seq.transfer = True
                return_.type = seq
            else:
                print 'Unhandled parameter annotation option: %s' % (
                    option, )
        return return_

    def _create_typedef_struct(self, symbol):
        name = self.strip_namespace_object(symbol.ident)
        struct = Struct(name, symbol.ident)
        self._typedefs_ns[symbol.ident] = struct
        return struct

    def _create_typedef_union(self, symbol):
        name = self._remove_prefix(symbol.ident)
        name = self.strip_namespace_object(name)
        union = Union(name, symbol.ident)
        self._typedefs_ns[symbol.ident] = union
        return union

    def _create_struct(self, symbol):
        struct = self._typedefs_ns.get(symbol.ident, None)
        if struct is None:
            # This is a bit of a hack; really we should try
            # to resolve through the typedefs to find the real
            # name
            if symbol.ident.startswith('_'):
                name = symbol.ident[1:]
            else:
                name = symbol.ident
            name = self.strip_namespace_object(name)
            name = self.resolve_type_name(name)
            struct = Struct(name, symbol.ident)

        for child in symbol.base_type.child_list:
            field = self._traverse_one(child)
            if field:
                struct.fields.append(field)

        return struct

    def _create_union(self, symbol):
        union = self._typedefs_ns.get(symbol.ident, None)
        if union is None:
            # This is a bit of a hack; really we should try
            # to resolve through the typedefs to find the real
            # name
            if symbol.ident.startswith('_'):
                name = symbol.ident[1:]
            else:
                name = symbol.ident
            name = self.strip_namespace_object(name)
            name = self.resolve_type_name(name)
            union = Union(name, symbol.ident)

        for child in symbol.base_type.child_list:
            field = self._traverse_one(child)
            if field:
                union.fields.append(field)

        return union

    def _create_callback(self, symbol):
        parameters = self._create_parameters(symbol.base_type.base_type)
        retval = self._create_return(symbol.base_type.base_type.base_type)
        if symbol.ident.find('_') > 0:
            name = self._strip_namespace_func(symbol.ident)
        else:
            name = self.strip_namespace_object(symbol.ident)
        return Callback(name, retval, list(parameters), symbol.ident)

    def _parse_type_annotation(self, annotation):
        if (annotation[0] == "[" and
            annotation[-1] == "]"):
            return Sequence(self._parse_type_annotation(annotation[1:-1]))
        return annotation

    def _typepair_to_str(self, item):
        nsname, item = item
        if nsname is None:
            return item.name
        return '%s.%s' % (nsname, item.name)

    def _resolve_type_name_1(self, type_name, ctype, names):
        # First look using the built-in names
        if ctype:
            try:
                return type_names[ctype]
            except KeyError, e:
                pass
        try:
            return type_names[type_name]
        except KeyError, e:
            pass
        type_name = self.strip_namespace_object(type_name)
        resolved = names.aliases.get(type_name)
        if resolved:
            return self._typepair_to_str(resolved)
        resolved = names.names.get(type_name)
        if resolved:
            return self._typepair_to_str(resolved)
        if ctype:
            ctype = ctype.replace('*', '')
            resolved = names.ctypes.get(ctype)
            if resolved:
                return self._typepair_to_str(resolved)
        resolved = names.type_names.get(type_name)
        if resolved:
            return self._typepair_to_str(resolved)
        raise KeyError("failed to find %r" % (type_name, ))

    def resolve_type_name_full(self, type_name, ctype,
                               names):
        try:
            return self._resolve_type_name_1(type_name, ctype, names)
        except KeyError, e:
            try:
                return self._resolve_type_name_1(type_name, ctype, self._names)
            except KeyError, e:
                return type_name

    def resolve_type_name(self, type_name, ctype=None):
        try:
            return self.resolve_type_name_full(type_name, ctype, self._names)
        except KeyError, e:
            return type_name

    def gtypename_to_giname(self, gtname, names):
        resolved = names.type_names.get(gtname)
        if resolved:
            return self._typepair_to_str(resolved)
        resolved = self._names.type_names.get(gtname)
        if resolved:
            return self._typepair_to_str(resolved)
        raise KeyError("Failed to resolve GType name: %r" % (gtname, ))

    def ctype_of(self, obj):
        if hasattr(obj, 'ctype'):
            return obj.ctype
        elif hasattr(obj, 'symbol'):
            return obj.symbol
        else:
            return None

    def resolve_param_type_full(self, ptype, names):
        if isinstance(ptype, Sequence):
            ptype.element_type = \
                self.resolve_param_type_full(ptype.element_type, names)
        elif isinstance(ptype, Node):
            ptype.name = self.resolve_type_name_full(ptype.name,
                                                     self.ctype_of(ptype),
                                                     names)
        elif isinstance(ptype, basestring):
            return self.resolve_type_name_full(ptype, None, names)
        else:
            raise AssertionError("Unhandled param: %r" % (ptype, ))
        return ptype

    def resolve_param_type(self, ptype):
        try:
            return self.resolve_param_type_full(ptype, self._names)
        except KeyError, e:
            return ptype

    def follow_aliases(self, type_name, names):
        while True:
            resolved = names.aliases.get(type_name)
            if resolved:
                (ns, alias) = resolved
                type_name = alias.target
            else:
                break
        return type_name
