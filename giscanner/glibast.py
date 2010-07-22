# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
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

from .ast import (Bitfield, Class, Enum, Interface, Member, Node,
                  Property, Union, Record)

class GLibRecord(Record):
    def __init__(self, *args, **kwargs):
        Record.__init__(self, *args, **kwargs)

    @classmethod
    def from_record(cls, record):
        obj = cls(record.name, record.symbol)
        obj.fields = record.fields
        obj.constructors = record.constructors
        obj.disguised = record.disguised
        obj.doc = record.doc
        obj.methods = record.methods
        # If true, this record defines the FooClass C structure
        # for some Foo GObject (or similar for GInterface)
        obj.is_gtype_struct_for = False
        return obj

class GLibEnum(Enum):

    def __init__(self, name, type_name, members, get_type):
        Enum.__init__(self, name, type_name, members)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type
        self.error_quark = None

    def __repr__(self):
        return 'GlibEnum(%r, %r, %r)' % (self.name, self.members,
                                         self.get_type)


class GLibFlags(Bitfield):

    def __init__(self, name, type_name, members, get_type):
        Bitfield.__init__(self, name, type_name, members)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type

    def __repr__(self):
        return 'GlibFlags(%r, %r, %r)' % (self.name, self.members,
                                          self.get_type)


class GLibEnumMember(Member):

    def __init__(self, name, value, symbol, nick):
        Member.__init__(self, name, value, symbol)
        self.nick = nick


class GLibObject(Class):

    def __init__(self, name, parent, type_name, get_type,
                 is_abstract, ctype=None):
        Class.__init__(self, name, parent, is_abstract)
        self.type_name = type_name
        self.get_type = get_type
        self.fundamental = False
        self.unref_func = None
        self.ref_func = None
        self.set_value_func = None
        self.get_value_func = None
        self.signals = []
        self.ctype = ctype or type_name


class GLibBoxed:

    def __init__(self, type_name, get_type):
        self.type_name = type_name
        self.get_type = get_type




class GLibBoxedStruct(Record, GLibBoxed):

    def __init__(self, name, type_name, get_type, ctype=None):
        Record.__init__(self, name, ctype or type_name)
        GLibBoxed.__init__(self, type_name, get_type)


class GLibBoxedUnion(Union, GLibBoxed):

    def __init__(self, name, type_name, get_type, ctype=None):
        Union.__init__(self, name, ctype or type_name)
        GLibBoxed.__init__(self, type_name, get_type)


class GLibBoxedOther(Node, GLibBoxed):

    def __init__(self, name, type_name, get_type):
        Node.__init__(self, name)
        GLibBoxed.__init__(self, type_name, get_type)
        self.constructors = []
        self.methods = []
        self.ctype = type_name
        self.doc = None


class GLibInterface(Interface):

    def __init__(self, name, parent, type_name, get_type,
                 ctype=None):
        Interface.__init__(self, name, parent)
        self.type_name = type_name
        self.get_type = get_type
        self.signals = []
        self.ctype = ctype or type_name


class GLibProperty(Property):
    pass


class GLibSignal(Node):

    def __init__(self, name, retval):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = []
        self.doc = None
