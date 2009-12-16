# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
# Copyright (C) 2008, 2009 Red Hat, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
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
TYPE_SHORT = 'short'
TYPE_USHORT = 'ushort'
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
                   TYPE_UINT64, TYPE_SHORT, TYPE_USHORT, TYPE_INT,
                   TYPE_UINT, TYPE_LONG, TYPE_ULONG, TYPE_SSIZET,
                   TYPE_SIZET, TYPE_FLOAT, TYPE_DOUBLE, TYPE_TIMET,
                   TYPE_GTYPE]
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

PARAM_SCOPE_CALL = 'call'
PARAM_SCOPE_ASYNC = 'async'
PARAM_SCOPE_NOTIFIED = 'notified'

PARAM_TRANSFER_NONE = 'none'
PARAM_TRANSFER_CONTAINER = 'container'
PARAM_TRANSFER_FULL = 'full'

type_names = {}
for name in GIR_TYPES:
    type_names[name] = name

# C builtin
type_names['char'] = TYPE_INT8
type_names['signed char'] = TYPE_INT8
type_names['unsigned char'] = TYPE_UINT8
type_names['short'] = TYPE_SHORT
type_names['signed short'] = TYPE_SHORT
type_names['unsigned short'] = TYPE_USHORT
type_names['int'] = TYPE_INT
type_names['signed int'] = TYPE_INT
type_names['unsigned short int'] = TYPE_USHORT
type_names['signed'] = TYPE_INT
type_names['unsigned int'] = TYPE_UINT
type_names['unsigned'] = TYPE_UINT
type_names['long'] = TYPE_LONG
type_names['signed long'] = TYPE_LONG
type_names['unsigned long'] = TYPE_ULONG
type_names['unsigned long int'] = TYPE_ULONG
type_names['float'] = TYPE_FLOAT
type_names['double'] = TYPE_DOUBLE
type_names['char*'] = TYPE_STRING
type_names['void*'] = TYPE_ANY
type_names['void'] = TYPE_NONE

# Unix types that we special case here (and that have their own introspection
# type tag) because of wide use in GLib.
type_names['size_t'] = TYPE_SIZET
type_names['ssize_t'] = TYPE_SSIZET

# One off C unix type definitions; note some of these may be GNU Libc
# specific.  If someone is actually bitten by this, feel free to do
# the required configure goop to determine their size and replace
# here.
#
# We don't want to encourage people to use these in their APIs because
# they compromise the platform-independence that GLib gives you.
# These are here mostly to avoid blowing when random platform-specific
# methods are added under #ifdefs inside GLib itself.  We could just (skip)
# the relevant methods, but on the other hand, since these types are just
# integers it's easy enough to expand them.
type_names['off_t'] = TYPE_SIZET
type_names['pid_t'] = TYPE_INT
type_names['uid_t'] = TYPE_UINT
type_names['gid_t'] = TYPE_UINT
type_names['dev_t'] = TYPE_INT
type_names['socklen_t'] = TYPE_INT32

# Obj-C
type_names['id'] = TYPE_ANY

# Suppress some GLib names
type_names['uchar'] = TYPE_UINT8
type_names['ushort'] = TYPE_USHORT
type_names['size'] = TYPE_SIZET
type_names['ssize'] = TYPE_SSIZET
type_names['pointer'] = TYPE_ANY
type_names['constpointer'] = TYPE_ANY


# These types, when seen by reference, are converted into an Array()
# by default
# If you add/change these, be sure to update glibast.py too
default_array_types = {}
default_array_types['uint8*'] = TYPE_UINT8
default_array_types['utf8*'] = TYPE_STRING

# These types, when seen by reference, are interpreted as out parameters
default_out_types = (TYPE_SHORT, TYPE_USHORT, TYPE_INT, TYPE_UINT,
                     TYPE_LONG, TYPE_ULONG, TYPE_FLOAT, TYPE_DOUBLE,
                     TYPE_SIZET, TYPE_SSIZET)


def type_name_from_ctype(ctype):
    return type_names.get(ctype, ctype)


class Node(object):

    def __init__(self, name=None):
        self.name = name
        self.attributes = [] # (key, value)*
        self.skip = False
        self.deprecated = None
        self.deprecated_version = None
        self.version = None
        self.foreign = False

    def __cmp__(self, other):
        return cmp(self.name, other.name)

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.name)

    def remove_matching_children(self, pred):
        pass

class Namespace(Node):

    def __init__(self, name, version):
        Node.__init__(self, name)
        self.version = version
        self.nodes = []

    def __repr__(self):
        return '%s(%r, %r, %r)' % (self.__class__.__name__, self.name,
                                   self.version, self.nodes)

    def remove_matching(self, pred):

        def recursive_pred(node):
            node.remove_matching_children(pred)
            return pred(node)

        self.nodes = filter(recursive_pred, self.nodes)

class Include(Node):

    def __init__(self, name, version):
        Node.__init__(self, 'include')
        self.name = name
        self.version = version

    @classmethod
    def from_string(self, string):
        return Include(*string.split('-', 1))

    def __cmp__(self, other):
        if not isinstance(other, Include):
            return cmp(self, other)
        namecmp = cmp(self.name, other.name)
        if namecmp != 0:
            return namecmp
        return cmp(self.version, other.version)

    def __hash__(self):
        return hash((self.name, self.version))

    def __str__(self):
        return '%s-%s' % (self.name, self.version)

class Callable(Node):

    def __init__(self, name, retval, parameters, throws):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters
        self.throws = not not throws
        self.doc = None

    def __repr__(self):
        return '%s(%r, %r, %r)' % (self.__class__.__name__,
                                   self.name, self.retval,
                                   self.parameters)

class Function(Callable):

    def __init__(self, name, retval, parameters, symbol, throws=None):
        Callable.__init__(self, name, retval, parameters, throws)
        self.symbol = symbol
        self.is_method = False
        self.doc = None

    def get_parameter_index(self, name):
        for i, parameter in enumerate(self.parameters):
            if parameter.name == name:
                return i + int(self.is_method)

    def get_parameter(self, name):
        for parameter in self.parameters:
            if parameter.name == name:
                return parameter


class VFunction(Callable):

    def __init__(self, name, retval, parameters, throws):
        Callable.__init__(self, name, retval, parameters, throws)
        self.invoker = None

    @classmethod
    def from_callback(cls, cb):
        obj = cls(cb.name, cb.retval, cb.parameters[1:],
                  cb.throws)
        return obj


class Type(Node):

    def __init__(self, name, ctype=None):
        Node.__init__(self, name)
        self.ctype = ctype
        self.resolved = False
        self.is_const = False
        self.canonical = None
        self.derefed_canonical = None


class Varargs(Type):

    def __init__(self):
        Type.__init__(self, '<varargs>')


class Array(Type):

    def __init__(self, name, ctype, element_type):
        if name is None:
            name = '<carray>'
        Type.__init__(self, name, ctype)
        self.element_type = element_type
        self.zeroterminated = True
        self.length_param_index = -1
        self.length_param_name = None
        self.size = None

    def __repr__(self):
        return 'Array(%r, %r)' % (self.name, self.element_type, )


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
        return 'Map(%r <%r,%r>)' % (self.name, self.key_type, self.value_type)


class Alias(Node):

    def __init__(self, name, target, ctype=None):
        Node.__init__(self, name)
        self.target = target
        self.ctype = ctype

    def __repr__(self):
        return 'Alias(%r, %r)' % (self.name, self.target)


class TypeContainer(Node):

    def __init__(self, name, typenode, transfer):
        Node.__init__(self, name)
        self.type = typenode
        if transfer in [PARAM_TRANSFER_NONE, PARAM_TRANSFER_CONTAINER,
                        PARAM_TRANSFER_FULL]:
            self.transfer = transfer
        else:
            self.transfer = None


class Parameter(TypeContainer):

    def __init__(self, name, typenode, direction=None,
                 transfer=None, allow_none=False, scope=None):
        TypeContainer.__init__(self, name, typenode, transfer)
        if direction in [PARAM_DIRECTION_IN, PARAM_DIRECTION_OUT,
                         PARAM_DIRECTION_INOUT, None]:
            self.direction = direction
        else:
            self.direction = PARAM_DIRECTION_IN

        self.caller_allocates = False
        self.allow_none = allow_none
        self.scope = scope
        self.closure_index = -1
        self.destroy_index = -1
        self.doc = None

    def __repr__(self):
        return 'Parameter(%r, %r)' % (self.name, self.type)


class Enum(Node):

    def __init__(self, name, symbol, members):
        Node.__init__(self, name)
        self.symbol = symbol
        self.members = members
        self.doc = None

    def __repr__(self):
        return 'Enum(%r, %r)' % (self.name, self.members)


class Bitfield(Node):

    def __init__(self, name, symbol, members):
        Node.__init__(self, name)
        self.symbol = symbol
        self.members = members
        self.doc = None

    def __repr__(self):
        return 'Bitfield(%r, %r)' % (self.name, self.members)


class Member(Node):

    def __init__(self, name, value, symbol):
        Node.__init__(self, name)
        self.value = value
        self.symbol = symbol

    def __repr__(self):
        return 'Member(%r, %r)' % (self.name, self.value)


class Record(Node):

    def __init__(self, name, symbol, disguised=False):
        Node.__init__(self, name)
        self.fields = []
        self.constructors = []
        self.symbol = symbol
        self.disguised = disguised
        self.doc = None
        self.methods = []

    def remove_matching_children(self, pred):
        self.fields = filter(pred, self.fields)
        self.constructors = filter(pred, self.constructors)
        self.methods = filter(pred, self.methods)

# BW compat, remove
Struct = Record


class Field(Node):

    def __init__(self, name, typenode, symbol, readable, writable, bits=None):
        Node.__init__(self, name)
        self.type = typenode
        self.symbol = symbol
        self.readable = readable
        self.writable = writable
        self.bits = bits

    def __repr__(self):
        if self.bits:
            return 'Field(%r, %r, %r)' % (self.name, self.type, self.bits)
        else:
            return 'Field(%r, %r)' % (self.name, self.type)


class Return(TypeContainer):

    def __init__(self, rtype, transfer=None):
        TypeContainer.__init__(self, None, rtype, transfer)
        self.direction = PARAM_DIRECTION_OUT
        self.doc = None

    def __repr__(self):
        return 'Return(%r)' % (self.type, )


class Class(Node):

    def __init__(self, name, parent, is_abstract):
        Node.__init__(self, name)
        self.ctype = name
        self.parent = parent
        self.glib_type_struct = None
        self.is_abstract = is_abstract
        self.methods = []
        self.virtual_methods = []
        self.static_methods = []
        self.interfaces = []
        self.constructors = []
        self.properties = []
        self.fields = []
        self.doc = None

    def remove_matching_children(self, pred):
        self.methods = filter(pred, self.methods)
        self.constructors = filter(pred, self.constructors)
        self.properties = filter(pred, self.properties)
        self.fields = filter(pred, self.fields)

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.parent, self.methods)


class Interface(Node):

    def __init__(self, name, parent):
        Node.__init__(self, name)
        self.parent = parent
        self.methods = []
        self.virtual_methods = []
        self.glib_type_struct = None
        self.properties = []
        self.fields = []
        self.prerequisites = []
        self.doc = None

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
        self.doc = None

    def __repr__(self):
        return '%s(%r, %r)' % (
            self.__class__.__name__,
            self.name, self.type)


# FIXME: Inherit from Function


class Callback(Node):

    def __init__(self, name, retval, parameters, ctype=None):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters
        self.ctype = ctype
        self.throws = False
        self.doc = None

    def get_parameter_index(self, name):
        for i, parameter in enumerate(self.parameters):
            if parameter.name == name:
                return i

    def get_parameter(self, name):
        for parameter in self.parameters:
            if parameter.name == name:
                return parameter

    def __repr__(self):
        return 'Callback(%r, %r, %r)' % (
            self.name, self.retval, self.parameters)


class Union(Node):

    def __init__(self, name, symbol):
        Node.__init__(self, name)
        self.fields = []
        self.constructors = []
        self.methods = []
        self.symbol = symbol
        self.doc = None

    def __repr__(self):
        return 'Union(%r, %r)' % (self.name, self.fields, )
