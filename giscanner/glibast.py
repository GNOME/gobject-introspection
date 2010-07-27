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

from . import ast

class GLibRecord(ast.Record):
    def __init__(self, *args, **kwargs):
        ast.Record.__init__(self, *args, **kwargs)

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

class GLibEnum(ast.Enum):

    def __init__(self, name, type_name, members, get_type):
        ast.Enum.__init__(self, name, type_name, members)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type
        self.error_quark = None

    def __repr__(self):
        return 'GlibEnum(%r, %r, %r)' % (self.name, self.members,
                                         self.get_type)


class GLibFlags(ast.Bitfield):

    def __init__(self, name, type_name, members, get_type):
        ast.Bitfield.__init__(self, name, type_name, members)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type

    def __repr__(self):
        return 'GlibFlags(%r, %r, %r)' % (self.name, self.members,
                                          self.get_type)


class GLibEnumMember(ast.Member):

    def __init__(self, name, value, symbol, nick):
        ast.Member.__init__(self, name, value, symbol)
        self.nick = nick


class GLibObject(ast.Class):

    def __init__(self, name, parent, type_name, get_type,
                 c_symbol_prefix, is_abstract, ctype=None):
        ast.Class.__init__(self, name, parent, is_abstract)
        self.type_name = type_name
        self.get_type = get_type
        self.c_symbol_prefix = c_symbol_prefix
        self.fundamental = False
        self.unref_func = None
        self.ref_func = None
        self.set_value_func = None
        self.get_value_func = None
        self.signals = []
        self.ctype = ctype or type_name

    def _walk(self, callback, chain):
        super(GLibObject, self)._walk(callback, chain)
        for sig in self.signals:
            sig.walk(callback, chain)


class GLibBoxed:

    def __init__(self, type_name, get_type, c_symbol_prefix):
        self.type_name = type_name
        self.get_type = get_type
        self.c_symbol_prefix = c_symbol_prefix


class GLibBoxedStruct(ast.Record, GLibBoxed):

    def __init__(self, name, type_name, get_type, c_symbol_prefix, ctype=None):
        ast.Record.__init__(self, name, ctype or type_name)
        GLibBoxed.__init__(self, type_name, get_type, c_symbol_prefix)


class GLibBoxedUnion(ast.Union, GLibBoxed):

    def __init__(self, name, type_name, get_type, c_symbol_prefix, ctype=None):
        ast.Union.__init__(self, name, ctype or type_name)
        GLibBoxed.__init__(self, type_name, get_type, c_symbol_prefix)


class GLibBoxedOther(ast.Node, GLibBoxed):

    def __init__(self, name, type_name, get_type, c_symbol_prefix):
        ast.Node.__init__(self, name)
        GLibBoxed.__init__(self, type_name, get_type, c_symbol_prefix)
        self.constructors = []
        self.methods = []
        self.static_methods = []
        self.ctype = type_name
        self.doc = None

    def _walk(self, callback, chain):
        for ctor in self.constructors:
            ctor.walk(callback, chain)
        for meth in self.methods:
            meth.walk(callback, chain)
        for meth in self.static_methods:
            meth.walk(callback, chain)


class GLibInterface(ast.Interface):

    def __init__(self, name, parent, type_name, get_type,
                 c_symbol_prefix, ctype=None):
        ast.Interface.__init__(self, name, parent)
        self.type_name = type_name
        self.get_type = get_type
        self.c_symbol_prefix = c_symbol_prefix
        self.signals = []
        self.ctype = ctype or type_name

    def _walk(self, callback, chain):
        super(GLibInterface, self)._walk(callback, chain)
        for sig in self.signals:
            sig.walk(callback, chain)

class GLibProperty(ast.Property):
    pass


class GLibSignal(ast.Callable):

    def __init__(self, name, retval, parameters):
        ast.Callable.__init__(self, name, retval, parameters, False)
