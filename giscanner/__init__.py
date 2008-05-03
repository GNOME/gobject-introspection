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

(CSYMBOL_TYPE_INVALID,
 CSYMBOL_TYPE_CONST,
 CSYMBOL_TYPE_OBJECT,
 CSYMBOL_TYPE_FUNCTION,
 CSYMBOL_TYPE_STRUCT,
 CSYMBOL_TYPE_UNION,
 CSYMBOL_TYPE_ENUM,
 CSYMBOL_TYPE_TYPEDEF) = range(8)

(CTYPE_INVALID,
 CTYPE_VOID,
 CTYPE_BASIC_TYPE,
 CTYPE_TYPEDEF,
 CTYPE_STRUCT,
 CTYPE_UNION,
 CTYPE_ENUM,
 CTYPE_POINTER,
 CTYPE_ARRAY,
 CTYPE_FUNCTION) = range(10)

STORAGE_CLASS_NONE = 0
STORAGE_CLASS_TYPEDEF = 1 << 1
STORAGE_CLASS_EXTERN = 1 << 2
STORAGE_CLASS_STATIC = 1 << 3
STORAGE_CLASS_AUTO = 1 << 4
STORAGE_CLASS_REGISTER = 1 << 5

TYPE_QUALIFIER_NONE = 0
TYPE_QUALIFIER_CONST = 1 << 1
TYPE_QUALIFIER_RESTRICT = 1 << 2
TYPE_QUALIFIER_VOLATILE = 1 << 3

FUNCTION_NONE = 0
FUNCTION_INLINE = 1 << 1

(UNARY_ADDRESS_OF,
 UNARY_POINTER_INDIRECTION,
 UNARY_PLUS,
 UNARY_MINUS,
 UNARY_BITWISE_COMPLEMENT,
 UNARY_LOGICAL_NEGATION) = range(6)

def symbol_type_name(symbol_type):
    return {
        CSYMBOL_TYPE_INVALID: 'invalid',
        CSYMBOL_TYPE_CONST: 'const',
        CSYMBOL_TYPE_OBJECT: 'object',
        CSYMBOL_TYPE_FUNCTION: 'function',
        CSYMBOL_TYPE_STRUCT: 'struct',
        CSYMBOL_TYPE_UNION: 'union',
        CSYMBOL_TYPE_ENUM: 'enum',
        CSYMBOL_TYPE_TYPEDEF: 'typedef'
        }.get(symbol_type)

