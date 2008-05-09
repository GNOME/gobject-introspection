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

from .ast import Class, Enum, Interface, Member, Node, Property, Struct


class GLibEnum(Enum):
    def __init__(self, name, members, type_name, get_type):
        Enum.__init__(self, name, type_name, members)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name,
            self.members,
            self.get_type)


class GLibFlags(GLibEnum):
    pass


class GLibEnumMember(Member):
    def __init__(self, name, value, nick):
        Member.__init__(self, name, value)
        self.nick = nick


class GLibObject(Class):
    def __init__(self, name, parent, type_name, get_type):
        Class.__init__(self, name, parent)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type
        self.signals = []

class GLibBoxed(Struct):
    def __init__(self, name, type_name, get_type):
        Struct.__init__(self, name, get_type)
        self.ctype = name
        self.constructors = []
        self.methods = []
        self.type_name = type_name
        self.symbol = type_name
        self.get_type = get_type


class GLibInterface(Interface):
    def __init__(self, name, type_name, get_type):
        Interface.__init__(self, name)
        self.ctype = type_name
        self.type_name = type_name
        self.get_type = get_type
        self.signals = []


class GLibProperty(Property):
    pass


class GLibSignal(Node):
    def __init__(self, name, retval):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = []
