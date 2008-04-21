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
    _fields_ = [('g_type_class',  GTypeClass),
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


_gobj = ctypes.cdll.LoadLibrary('libgobject-2.0.so')
_gobj.g_type_init()

# Workaround this error:
#   GLib-GObject-CRITICAL **: g_param_spec_pool_list:
#   assertion `pool != NULL' failed
# which happens when trying to introspect an interface before instantiating
# a GObject.
_gobj.g_object_new(TYPE_OBJECT, None)

# Functions

_gobj.g_type_name.restype = ctypes.c_char_p
def type_name(type_id):
    return _gobj.g_type_name(type_id)

_gobj.g_type_from_name.argtypes = [ctypes.c_char_p]
def type_from_name(name):
    return _gobj.g_type_from_name(name)

def type_fundamental(type_id):
    return _gobj.g_type_fundamental(type_id)

def type_parent(type_id):
    return _gobj.g_type_parent(type_id)

_gobj.g_type_class_ref.restype = ctypes.POINTER(GTypeClass)
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

_gobj.g_object_class_list_properties.restype = ctypes.POINTER(
    ctypes.POINTER(GParamSpec))
def object_class_list_properties(type_id):
    klass = _gobj.g_type_class_ref(type_id)
    n = ctypes.c_uint()
    pspecs = _gobj.g_object_class_list_properties(klass, ctypes.byref(n))
    for i in range(n.value):
        yield ctypes.cast(pspecs[i], ctypes.POINTER(GParamSpec)).contents

_gobj.g_object_interface_list_properties.restype = ctypes.POINTER(
    ctypes.POINTER(GParamSpec))
def object_interface_list_properties(type_id):
    iface = _gobj.g_type_default_interface_ref(type_id)
    n = ctypes.c_uint()
    pspecs = _gobj.g_object_interface_list_properties(iface, ctypes.byref(n))
    for i in range(n.value):
        yield ctypes.cast(pspecs[i], ctypes.POINTER(GParamSpec)).contents

_gobj.g_type_interfaces.restype = ctypes.POINTER(ctypes.c_int)
def type_interfaces(type_id):
    n = ctypes.c_uint()
    type_ids = _gobj.g_type_interfaces(type_id, ctypes.byref(n))
    for i in range(n.value):
        yield type_ids[i]

_gobj.g_type_interface_prerequisites.restype = ctypes.POINTER(ctypes.c_int)
def type_interface_prerequisites(type_id):
    n = ctypes.c_uint()
    type_ids = _gobj.g_type_interface_prerequisites(type_id, ctypes.byref(n))
    for i in range(n.value):
        yield type_ids[i]
