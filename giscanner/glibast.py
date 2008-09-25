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

from .ast import Class, Enum, Interface, Member, Node, Property, Struct, Union
from .ast import (
    type_names,
    TYPE_STRING, TYPE_INT8, TYPE_UINT8, TYPE_INT16, TYPE_UINT16,
    TYPE_INT, TYPE_UINT, TYPE_UINT32, TYPE_INT32, TYPE_LONG,
    TYPE_ULONG, TYPE_INT64, TYPE_UINT64, TYPE_FLOAT,
    TYPE_DOUBLE, TYPE_BOOLEAN, TYPE_ANY, TYPE_SSIZET,
    TYPE_SIZET)


# Glib type names
type_names['gchararray'] = TYPE_STRING
type_names['gint8'] = TYPE_INT8
type_names['guint8'] = TYPE_UINT8
type_names['gint16'] = TYPE_INT16
type_names['guint16'] = TYPE_UINT16
type_names['gint'] = TYPE_INT
type_names['guint'] = TYPE_UINT
type_names['gint32'] = TYPE_INT32
type_names['guint32'] = TYPE_UINT32
type_names['glong'] = TYPE_LONG
type_names['gulong'] = TYPE_ULONG
type_names['gint64'] = TYPE_INT64
type_names['guint64'] = TYPE_UINT64
type_names['gfloat'] = TYPE_FLOAT
type_names['gdouble'] = TYPE_DOUBLE
type_names['gchar*'] = TYPE_STRING
type_names['gboolean'] = TYPE_BOOLEAN
type_names['gpointer'] = TYPE_ANY
type_names['gconstpointer'] = TYPE_ANY
type_names['gsize'] = TYPE_SIZET
type_names['gssize'] = TYPE_SSIZET
type_names['guchar'] = TYPE_UINT8
type_names['gshort'] = TYPE_INT16
type_names['gushort'] = TYPE_UINT16


class GLibEnum(Enum):

    def __init__(self, name, type_name, members, get_type):
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

    def __init__(self, name, value, symbol, nick):
        Member.__init__(self, name, value, symbol)
        self.nick = nick


class GLibObject(Class):

    def __init__(self, name, parent, type_name, get_type, ctype=None):
        Class.__init__(self, name, parent)
        self.type_name = type_name
        self.get_type = get_type
        self.signals = []
        self.ctype = ctype or type_name


class GLibBoxed:

    def __init__(self, type_name, get_type):
        self.constructors = []
        self.methods = []
        self.type_name = type_name
        self.get_type = get_type


class GLibBoxedStruct(Struct, GLibBoxed):

    def __init__(self, name, type_name, get_type, ctype=None):
        Struct.__init__(self, name, ctype or type_name)
        GLibBoxed.__init__(self, type_name, get_type)


class GLibBoxedUnion(Union, GLibBoxed):

    def __init__(self, name, type_name, get_type, ctype=None):
        Union.__init__(self, name, ctype or type_name)
        GLibBoxed.__init__(self, type_name, get_type)


class GLibBoxedOther(Node, GLibBoxed):

    def __init__(self, name, type_name, get_type):
        Node.__init__(self, name)
        GLibBoxed.__init__(self, type_name, get_type)
        self.ctype = type_name


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
