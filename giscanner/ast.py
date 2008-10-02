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

"""AST nodes
This file descbribes abstract data type nodes independent on the
implementation language.

These can later on be extended (eg subclassed) with additional information
which is language/library/domain specific.
"""

##
## Basic types, modeled on GITypeTag but not equivalent
##

TYPE_NONE = 'none' # We differ from repository on these first two
TYPE_ANY = 'any'
TYPE_BOOLEAN = 'boolean'
TYPE_INT8 = 'int8'
TYPE_UINT8 = 'uint8'
TYPE_INT16 = 'int16'
TYPE_UINT16 = 'uint16'
TYPE_INT = 'int'
TYPE_UINT = 'uint'
TYPE_INT32 = 'int32'
TYPE_UINT32 = 'uint32'
TYPE_INT64 = 'int64'
TYPE_UINT64 = 'uint64'
TYPE_LONG = 'long'
TYPE_ULONG = 'ulong'
TYPE_SSIZET = 'ssize_t'
TYPE_SIZET = 'size_t'
TYPE_TIMET = 'time_t'
TYPE_GTYPE = 'GType'
TYPE_FLOAT = 'float'
TYPE_DOUBLE = 'double'
TYPE_STRING = 'utf8' # requires zero-terminated
TYPE_FILENAME = 'filename'

BASIC_GIR_TYPES = [TYPE_BOOLEAN, TYPE_INT8, TYPE_UINT8, TYPE_INT16,
                   TYPE_UINT16, TYPE_INT32, TYPE_UINT32, TYPE_INT64,
                   TYPE_UINT64, TYPE_INT, TYPE_UINT, TYPE_LONG,
                   TYPE_ULONG, TYPE_SSIZET, TYPE_SIZET, TYPE_FLOAT,
                   TYPE_DOUBLE, TYPE_TIMET, TYPE_GTYPE]
GIR_TYPES = [TYPE_NONE, TYPE_ANY]
GIR_TYPES.extend(BASIC_GIR_TYPES)
GIR_TYPES.extend([TYPE_STRING, TYPE_FILENAME])

# Higher-level data types
TYPE_SEQUENCE = 'sequence' # Sequence of something

# Wide/Unicode
TYPE_UCHAR = 'uchar'
TYPE_USTRING = 'ustring'

##
## Parameters
##

PARAM_DIRECTION_IN = 'in'
PARAM_DIRECTION_OUT = 'out'
PARAM_DIRECTION_INOUT = 'inout'

type_names = {}
for name in GIR_TYPES:
    type_names[name] = name

# C
type_names['char'] = TYPE_INT8
type_names['unsigned char'] = TYPE_UINT8
type_names['short'] = TYPE_INT16
type_names['unsigned short'] = TYPE_UINT16
type_names['int'] = TYPE_INT
type_names['unsigned int'] = TYPE_UINT
type_names['long'] = TYPE_LONG
type_names['unsigned long'] = TYPE_ULONG
type_names['float'] = TYPE_FLOAT
type_names['double'] = TYPE_DOUBLE
type_names['char*'] = TYPE_STRING
type_names['void*'] = TYPE_ANY
type_names['void'] = TYPE_NONE
type_names['size_t'] = TYPE_SIZET
type_names['ssize_t'] = TYPE_SSIZET
# FIXME - can we make libraries use GPid?
type_names['pid_t'] = TYPE_INT

# Suppress some GLib names
type_names['uchar'] = TYPE_UINT8
type_names['ushort'] = TYPE_UINT16
type_names['size'] = TYPE_SIZET
type_names['ssize'] = TYPE_SSIZET
type_names['pointer'] = TYPE_ANY
type_names['constpointer'] = TYPE_ANY


# These types, when seen by reference, are converted into an Array()
# by default
default_array_types = {}
default_array_types['uint8*'] = TYPE_UINT8
default_array_types['char**'] = TYPE_STRING


def type_name_from_ctype(ctype):
    return type_names.get(ctype, ctype)


class Node(object):

    def __init__(self, name=None):
        self.name = name
        self.deprecated = None
        self.deprecated_version = None

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.name)


class Namespace(Node):

    def __init__(self, name):
        Node.__init__(self, name)
        self.nodes = []

    def __repr__(self):
        return '%s(%r, %r)' % (self.__class__.__name__, self.name,
                               self.nodes)


class Function(Node):

    def __init__(self, name, retval, parameters, symbol):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters
        self.symbol = symbol

    def __repr__(self):
        return '%s(%r, %r, %r)' % (self.__class__.__name__,
                                   self.name, self.retval,
                                   self.parameters)


class VFunction(Function):
    pass


class Type(Node):

    def __init__(self, name, ctype=None):
        Node.__init__(self, name)
        self.ctype = ctype
        self.resolved = False


class Varargs(Type):

    def __init__(self):
        Type.__init__(self, '<varargs>')


class Array(Type):

    def __init__(self, ctype, element_type):
        Type.__init__(self, '<carray>', ctype)
        self.element_type = element_type
        self.zeroterminated = True
        self.length_param_index = -1

    def __repr__(self):
        return 'Array(%r of %r)' % (self.name, self.element_type, )


class List(Type):

    def __init__(self, name, ctype, element_type):
        Type.__init__(self, name, ctype)
        self.element_type = element_type

    def __repr__(self):
        return 'List(%r of %r)' % (self.name, self.element_type, )


class Map(Type):

    def __init__(self, name, ctype, key_type, value_type):
        Type.__init__(self, name, ctype)
        self.key_type = key_type
        self.value_type = value_type

    def __repr__(self):
        return 'Map(%r <%r,%r.)' % (self.name, self.key_type, self.value_type)


class Alias(Node):

    def __init__(self, name, target, ctype=None):
        Node.__init__(self, name)
        self.target = target
        self.ctype = ctype

    def __repr__(self):
        return 'Alias(%r, %r)' % (self.name, self.target)


class Parameter(Node):

    def __init__(self, name, typenode):
        Node.__init__(self, name)
        self.type = typenode
        self.direction = PARAM_DIRECTION_IN
        self.transfer = False
        self.allow_none = False

    def __repr__(self):
        return 'Parameter(%r, %r)' % (self.name, self.type)


class Enum(Node):

    def __init__(self, name, symbol, members):
        Node.__init__(self, name)
        self.symbol = symbol
        self.members = members

    def __repr__(self):
        return 'Enum(%r, %r)' % (self.name, self.members)


class Member(Node):

    def __init__(self, name, value, symbol):
        Node.__init__(self, name)
        self.value = value
        self.symbol = symbol

    def __repr__(self):
        return 'Member(%r, %r)' % (self.name, self.value)


class Struct(Node):

    def __init__(self, name, symbol):
        Node.__init__(self, name)
        self.fields = []
        self.symbol = symbol


class Field(Node):

    def __init__(self, name, typenode, symbol):
        Node.__init__(self, name)
        self.type = typenode
        self.symbol = symbol

    def __repr__(self):
        return 'Field(%r, %r)' % (self.name, self.type)


class Return(Node):

    def __init__(self, rtype):
        Node.__init__(self)
        self.type = rtype
        self.transfer = isinstance(rtype, (List, Map, Array)) or \
            rtype.name in ('utf8', 'filename')

    def __repr__(self):
        return 'Return(%r)' % (self.type, )


class Class(Node):

    def __init__(self, name, parent):
        Node.__init__(self, name)
        self.ctype = name
        self.parent = parent
        self.methods = []
        self.interfaces = []
        self.constructors = []
        self.properties = []
        self.fields = []

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.parent, self.methods)


class Interface(Node):

    def __init__(self, name, parent):
        Node.__init__(self, name)
        self.parent = parent
        self.methods = []
        self.properties = []
        self.fields = []

    def __repr__(self):
        return '%s(%r, %r)' % (
            self.__class__.__name__,
            self.name, self.methods)


class Constant(Node):

    def __init__(self, name, type_name, value):
        Node.__init__(self, name)
        self.type = Type(type_name)
        self.value = value

    def __repr__(self):
        return 'Constant(%r, %r, %r)' % (
            self.name, self.type, self.value)


class Property(Node):

    def __init__(self, name, type_name, readable, writable,
                 construct, construct_only, ctype=None):
        Node.__init__(self, name)
        self.type = Type(type_name, ctype)
        self.readable = readable
        self.writable = writable
        self.construct = construct
        self.construct_only = construct_only

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.type, self.value)


# FIXME: Inherit from Function


class Callback(Node):

    def __init__(self, name, retval, parameters, ctype=None):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters
        self.ctype = ctype

    def __repr__(self):
        return 'Callback(%r, %r, %r)' % (
            self.name, self.retval, self.parameters)


class Union(Node):

    def __init__(self, name, symbol):
        Node.__init__(self, name)
        self.fields = []
        self.symbol = symbol

    def __repr__(self):
        return 'Union(%r, %r)' % (self.name, self.fields, )
