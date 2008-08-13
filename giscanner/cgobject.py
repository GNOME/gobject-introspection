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

# Poor mans GObject python bindings
# Incidentally portable beyond CPython, due to usage of ctypes
# Why not PyGObject?
# - 1) Avoid PyGObject dependency
# - 2) Low-level binding
# - 3) Implementation independent
# - 4) Usage lower in the stack
#
# based on defsgen.py (C) 2006 John Finlay
#

import ctypes
from ctypes.util import find_library


def gwrap(lib, fname, ret, *argtypes):

    def _deco(f):
        f._cfunc = getattr(lib, fname)
        f._cfunc.restype = ret
        f._cfunc.argtypes = argtypes
        return f
    return _deco

# Constants

# FIXME: Are these stable?
TYPE_INVALID = 0
TYPE_INTERFACE = 8
TYPE_ENUM = 48
TYPE_FLAGS = 52
TYPE_STRING = 64
TYPE_BOXED = 72
TYPE_OBJECT = 80


# Typedefs

# FIXME - this is wrong on win64, where long == 32 but size_t == 64
GType = ctypes.c_ulong


# Structs


class GTypeClass(ctypes.Structure):
    _fields_ = [('g_type', GType)]


class GTypeInstance(ctypes.Structure):
    _fields_ = [('g_class', ctypes.POINTER(GTypeClass))]


class GEnumValue(ctypes.Structure):
    _fields_ = [('value', ctypes.c_int),
                ('value_name', ctypes.c_char_p),
                ('value_nick', ctypes.c_char_p)]


class GFlagsValue(ctypes.Structure):
    _fields_ = [('value', ctypes.c_uint),
                ('value_name', ctypes.c_char_p),
                ('value_nick', ctypes.c_char_p)]


class GEnumClass(ctypes.Structure):
    _fields_ = [('g_type_class', GTypeClass),
                ('minimum', ctypes.c_int),
                ('maximum', ctypes.c_int),
                ('n_values', ctypes.c_uint),
                ('values', ctypes.POINTER(GEnumValue))]

    def get_values(self):
        for i in range(self.n_values):
            yield self.values[i]


class GFlagsClass(ctypes.Structure):
    _fields_ = [('g_type_class', GTypeClass),
               ('mask', ctypes.c_uint),
               ('n_values', ctypes.c_uint),
               ('values', ctypes.POINTER(GFlagsValue))]

    def get_values(self):
        for i in range(self.n_values):
            yield self.values[i]


class GTypeInterface(ctypes.Structure):
    _fields_ = [('g_type', GType),
                ('g_instance_type', GType)]


class GParamSpec(ctypes.Structure):
    _fields_ = [('g_type_instance', GTypeInstance),
                ('name', ctypes.c_char_p),
                ('flags', ctypes.c_uint),
                ('value_type', GType),
                ('owner_type', GType)]


class GSignalInfo(ctypes.Structure):
    _fields_ = [('signal_id', ctypes.c_uint),
                ('signal_name', ctypes.c_char_p),
                ('itype', GType),
                ('signal_flags', ctypes.c_uint),
                ('return_type', GType),
                ('n_params', ctypes.c_uint),
                ('param_types', ctypes.POINTER(GType))]

    def get_params(self):
        for i in range(self.n_params):
            yield self.param_types[i]


_library_path = find_library('gobject-2.0')
if not _library_path:
    raise ImportError("Could not find gobject-2.0 library")
_gobj = ctypes.cdll.LoadLibrary(_library_path)
_gobj.g_type_init()

# Workaround this error:
#   GLib-GObject-CRITICAL **: g_param_spec_pool_list:
#   assertion `pool != NULL' failed
# which happens when trying to introspect an interface before instantiating
# a GObject.
_gobj.g_object_new(TYPE_OBJECT, None)
_gobj.g_initially_unowned_get_type()

# Functions


@gwrap(_gobj, 'g_type_name', ctypes.c_char_p, GType)
def type_name(type_id):
    return _gobj.g_type_name(type_id)


@gwrap(_gobj, 'g_type_from_name', GType, ctypes.c_char_p)
def type_from_name(name):
    return _gobj.g_type_from_name(name)


@gwrap(_gobj, 'g_type_fundamental', GType)
def type_fundamental(type_id):
    return _gobj.g_type_fundamental(type_id)


@gwrap(_gobj, 'g_type_parent', GType, GType)
def type_parent(type_id):
    return _gobj.g_type_parent(type_id)


@gwrap(_gobj, 'g_type_class_ref', ctypes.POINTER(GTypeClass), GType)
def type_class_ref(type_id):
    fundamental_type = type_fundamental(type_id)
    if fundamental_type == TYPE_INVALID:
        return None
    if fundamental_type == TYPE_ENUM:
        typeclass = GEnumClass
    elif fundamental_type == TYPE_FLAGS:
        typeclass = GFlagsClass
    else:
        raise NotImplementedError(fundamental_type)
    ptr = _gobj.g_type_class_ref(type_id)
    return ctypes.cast(ptr, ctypes.POINTER(typeclass)).contents


@gwrap(_gobj, 'g_object_class_list_properties',
       ctypes.POINTER(ctypes.POINTER(GParamSpec)),
       ctypes.POINTER(GTypeClass), ctypes.POINTER(ctypes.c_uint))
def object_class_list_properties(type_id):
    klass = _gobj.g_type_class_ref(type_id)
    n = ctypes.c_uint()
    pspecs = _gobj.g_object_class_list_properties(klass, ctypes.byref(n))
    for i in range(n.value):
        yield ctypes.cast(pspecs[i], ctypes.POINTER(GParamSpec)).contents


@gwrap(_gobj, 'g_object_interface_list_properties',
       ctypes.POINTER(ctypes.POINTER(GParamSpec)),
       ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint))
def object_interface_list_properties(type_id):
    iface = _gobj.g_type_default_interface_ref(type_id)
    n = ctypes.c_uint()
    pspecs = _gobj.g_object_interface_list_properties(iface, ctypes.byref(n))
    for i in range(n.value):
        yield ctypes.cast(pspecs[i], ctypes.POINTER(GParamSpec)).contents


@gwrap(_gobj, 'g_type_interfaces', ctypes.POINTER(GType), GType,
       ctypes.POINTER(ctypes.c_uint))
def type_interfaces(type_id):
    n = ctypes.c_uint()
    type_ids = _gobj.g_type_interfaces(type_id, ctypes.byref(n))
    for i in range(n.value):
        yield type_ids[i]


@gwrap(_gobj, 'g_type_interface_prerequisites', ctypes.POINTER(GType), GType,
       ctypes.POINTER(ctypes.c_uint))
def type_interface_prerequisites(type_id):
    n = ctypes.c_uint()
    type_ids = _gobj.g_type_interface_prerequisites(type_id, ctypes.byref(n))
    for i in range(n.value):
        yield type_ids[i]


@gwrap(_gobj, 'g_signal_list_ids', ctypes.POINTER(ctypes.c_uint),
       GType, ctypes.POINTER(ctypes.c_uint))
def signal_list(type_id):
    n = ctypes.c_uint()
    signal_ids = _gobj.g_signal_list_ids(type_id, ctypes.byref(n))
    for i in range(n.value):
        info = GSignalInfo()
        _gobj.g_signal_query(signal_ids[i], ctypes.byref(info))
        yield info
