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

from giscanner.ast import (Callback, Enum, Function, Namespace, Member,
                           Parameter, Return, Sequence, Struct, Type)
from giscanner.sourcescanner import (
    SourceSymbol, ctype_name, symbol_type_name, CTYPE_POINTER,
    CTYPE_BASIC_TYPE, CTYPE_UNION,
    CTYPE_TYPEDEF, CTYPE_VOID, CTYPE_BASIC_TYPE, CTYPE_ENUM,
    CTYPE_FUNCTION, CTYPE_STRUCT, CSYMBOL_TYPE_FUNCTION,
    CSYMBOL_TYPE_TYPEDEF, CSYMBOL_TYPE_STRUCT, CSYMBOL_TYPE_ENUM,
    CSYMBOL_TYPE_UNION, CSYMBOL_TYPE_OBJECT)


class Transformer(object):
    def __init__(self, generator, namespace_name):
        self.generator = generator
        self._namespace = Namespace(namespace_name)
        self._output_ns = {}
        self._type_names = {}
        self._typedefs_ns = {}
        self._strip_prefix = ''

    def get_type_names(self):
        return self._type_names

    def set_strip_prefix(self, strip_prefix):
        self._strip_prefix = strip_prefix

    def parse(self):
        nodes = []
        for symbol in self.generator.get_symbols():
            node = self._traverse_one(symbol)
            if node is None:
                continue
            if node.name.startswith('_'):
                continue
            self._namespace.nodes.append(node)
            self._output_ns[node.name] = node
        return self._namespace

    def register_include(self, filename):
        if filename.endswith('.gir'):
            from .girparser import GIRParser
            parser = GIRParser(filename)
        elif filename.endswith('.gidl'):
            from .gidlparser import GIDLParser
            parser = GIDLParser(filename)
        else:
            raise NotImplementedError(filename)
        nsname = parser.get_namespace_name()
        for node in parser.get_nodes():
            self._type_names[node.type_name] = (nsname, node)

    def strip_namespace_object(self, name):
        orig_name = name
        prefix = self._namespace.name.lower()
        name = name.lower()
        if name.startswith(prefix):
            name = orig_name[len(prefix):]
        return name

    # Private

    def _strip_namespace_func(self, name):
        orig_name = name
        prefix = self._namespace.name.lower() + '_'
        name = name.lower()
        if name.startswith(prefix):
            name = orig_name[len(prefix):]
        return name

    def _remove_prefix(self, name):
        # when --strip-prefix=g:
        #   GHashTable -> HashTable
        #   g_hash_table_new -> hash_table_new
        if name.lower().startswith(self._strip_prefix.lower()):
            name = name[len(self._strip_prefix):]

        while name.startswith('_'):
            name = name[1:]
        return name

    def _traverse_one(self, symbol, stype=None):
        assert isinstance(symbol, SourceSymbol), symbol

        if stype is None:
            stype = symbol.type
        if stype == CSYMBOL_TYPE_FUNCTION:
            return self._create_function(symbol)
        elif stype == CSYMBOL_TYPE_TYPEDEF:
            return self._create_typedef(symbol)
        elif stype == CSYMBOL_TYPE_STRUCT:
            return self._create_struct(symbol)
        elif stype == CSYMBOL_TYPE_ENUM:
            return self._create_enum(symbol)
        elif stype == CSYMBOL_TYPE_OBJECT:
            return self._create_object(symbol)
        elif stype == CSYMBOL_TYPE_UNION:
            # Unions are not supported
            pass
        else:
            raise NotImplementedError(
                'Transformer: unhandled symbol: %r of type %s'
                % (symbol.ident, symbol_type_name(stype)))

    def _create_enum(self, symbol):
        members = []
        for child in symbol.base_type.child_list:
            members.append(Member(child.ident,
                                  child.const_int))

        name = self.strip_namespace_object(symbol.ident)
        return Enum(name, symbol.ident, members)

    def _create_object(self, symbol):
        return Member(symbol.ident, symbol.base_type.name)

    def _create_function(self, symbol):
        directives = symbol.directives()
        parameters = list(self._create_parameters(symbol.base_type, directives))
        return_ = self._create_return(symbol.base_type.base_type,
                                      directives.get('return', []))
        name = self._remove_prefix(symbol.ident)
        name = self._strip_namespace_func(name)

        return Function(name, return_, parameters, symbol.ident)

    def _create_source_type(self, source_type):
        if source_type is None:
            return 'None'
        if source_type.type == CTYPE_VOID:
            value = 'void'
        elif source_type.type == CTYPE_BASIC_TYPE:
            value = source_type.name
        elif source_type.type == CTYPE_TYPEDEF:
            value = source_type.name
        elif source_type.type == CTYPE_POINTER:
            value = self._create_source_type(source_type.base_type) + '*'
        else:
            print 'BUILDER: Unhandled source type %s' % (
                ctype_name(source_type.type),)
            value = '???'
        return value

    def _create_parameters(self, base_type, options=None):
        if not options:
            options = {}
        for child in base_type.child_list:
            yield self._create_parameter(
                child, options.get(child.ident, []))

    def _create_typedef(self, symbol):
        ctype = symbol.base_type.type
        if (ctype == CTYPE_POINTER and
            symbol.base_type.base_type.type == CTYPE_FUNCTION):
            node = self._create_callback(symbol)
        elif ctype == CTYPE_STRUCT:
            node = self._create_typedef_struct(symbol)
        elif ctype == CTYPE_ENUM:
            return self._create_enum(symbol)
        elif ctype in (CTYPE_TYPEDEF,
                       CTYPE_POINTER,
                       CTYPE_BASIC_TYPE,
                       CTYPE_UNION):
            return
        else:
            raise NotImplementedError(
                "symbol %r of type %s" % (symbol.ident, ctype_name(ctype)))
        return node

    def _create_type(self, source_type):
        type_name = self._create_source_type(source_type)
        return Type(type_name)

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
            else:
                print 'Unhandled parameter annotation option: %s' % (
                    option,)
        return param

    def _create_return(self, source_type, options=None):
        if not options:
            options = []
        rtype = Type(self._create_source_type(source_type))
        rtype = self._resolve_param_type(rtype)
        return_ = Return(rtype)
        for option in options:
            if option == 'caller-owns':
                return_.transfer = True
            elif option.startswith('seq '):
                value, element_options = option[3:].split(None, 2)
                element_type = self._parse_type_annotation(value)
                seq = Sequence(rtype.name, element_type)
                seq.transfer = True
                return_.type = seq
            else:
                print 'Unhandled parameter annotation option: %s' % (
                    option,)
        return return_

    def _create_typedef_struct(self, symbol):
        name = self._remove_prefix(symbol.ident)
        struct = Struct(name, symbol.ident)
        self._typedefs_ns[symbol.ident] = struct
        return struct

    def _create_struct(self, symbol):
        struct = self._typedefs_ns.get(symbol.ident, None)
        if struct is None:
            name = self._remove_prefix(symbol.ident)
            name = self._resolve_type_name(name)
            struct = Struct(name, symbol.ident)

        for child in symbol.base_type.child_list:
            # FIXME: This is obviously wrong, we're sending in data
            #        of the wrong type to _traverse_one
            try:
                field = self._traverse_one(child, child.base_type.type)
            except NotImplementedError:
                continue
            
            if field:
                struct.fields.append(field)

        return struct

    def _create_callback(self, symbol):
        parameters = self._create_parameters(symbol.base_type.base_type)
        retval = self._create_return(symbol.base_type.base_type.base_type)
        return Callback(symbol.ident, retval, list(parameters))

    def _parse_type_annotation(self, annotation):
        if (annotation[0] == "[" and
            annotation[-1] == "]"):
            return Sequence(self._parse_type_annotation(annotation[1:-1]))
        return annotation

    def _resolve_type_name(self, type_name):
        item = self._type_names.get(type_name)
        if item is not None:
            nsname, item = item
            if nsname is None:
                return item.name
            return '%s.%s' % (nsname, item.name)
        return type_name

    def _resolve_param_type(self, ptype):
        type_name = ptype.name
        ptype.name = self._resolve_type_name(type_name)
        return ptype

