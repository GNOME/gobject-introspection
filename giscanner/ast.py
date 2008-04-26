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


class Node(object):
    def __init__(self, name=None):
        self.name = name


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


class Parameter(Node):
    def __init__(self, name, type):
        Node.__init__(self, name)
        self.type = type
        self.direction = 'in'
        self.transfer = 'none'

    def __repr__(self):
        return 'Parameter(%r, %r)' % (self.name, self.type)


class Enum(Node):
    def __init__(self, name, members):
        Node.__init__(self, name)
        self.members = members

    def __repr__(self):
        return 'Enum(%r, %r)' % (self.name, self.members)


class Member(Node):
    def __init__(self, name, value):
        Node.__init__(self, name)
        self.value = value

    def __repr__(self):
        return 'Member(%r, %r)' % (self.name, self.value)


class Struct(Node):
    def __init__(self, name):
        Node.__init__(self, name)
        self.fields = []

    def __repr__(self):
        return 'Struct(%r)' % (self.name,)


class Return(Node):
    def __init__(self, type):
        Node.__init__(self)
        self.type = type
        self.transfer = 'none'

    def __repr__(self):
        return 'Return(%r)' % (self.type,)


class Class(Node):
    def __init__(self, name, parent):
        Node.__init__(self, name)
        self.parent = parent
        self.methods = []
        self.constructors = []
        self.properties = []
        self.fields = []

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.parent, self.methods)


class Interface(Node):
    def __init__(self, name):
        Node.__init__(self, name)
        self.methods = []
        self.properties = []
        self.fields = []

    def __repr__(self):
        return '%s(%r, %r)' % (
            self.__class__.__name__,
            self.name, self.methods)


class Constant(Node):
    def __init__(self, name, type, value):
        Node.__init__(self, name)
        self.type = type
        self.value = value

    def __repr__(self):
        return 'Constant(%r, %r, %r)' % (
            self.name, self.type, self.value)


class Property(Node):
    def __init__(self, name, type):
        Node.__init__(self, name)
        self.type = type

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.type, self.value)


class Callback(Node):
    def __init__(self, name, retval, parameters):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters

    def __repr__(self):
        return 'Callback(%r, %r, %r)' % (
            self.name, self.retval, self.parameters)
