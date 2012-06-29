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

import re
import os
import subprocess

_debugflags = None
def have_debug_flag(flag):
    """Check for whether a specific debugging feature is enabled.
Well-known flags:
 * start: Drop into debugger just after processing arguments
 * exception: Drop into debugger on fatalexception
 * warning: Drop into debugger on warning
 * posttrans: Drop into debugger just before introspectable pass
"""
    global _debugflags
    if _debugflags is None:
        _debugflags = os.environ.get('GI_SCANNER_DEBUG', '').split(',')
        if '' in _debugflags:
            _debugflags.remove('')
    return flag in _debugflags

def break_on_debug_flag(flag):
    if have_debug_flag(flag):
        import pdb
        pdb.set_trace()

# Copied from h2defs.py
_upperstr_pat1 = re.compile(r'([^A-Z])([A-Z])')
_upperstr_pat2 = re.compile(r'([A-Z][A-Z])([A-Z][0-9a-z])')
_upperstr_pat3 = re.compile(r'^([A-Z])([A-Z])')


def to_underscores(name):
    """Converts a typename to the equivalent underscores name.
    This is used to form the type conversion macros and enum/flag
    name variables.
    In particular, and differently from to_underscores_noprefix(),
    this function treats the first character differently if it is
    uppercase and followed by another uppercase letter."""
    name = _upperstr_pat1.sub(r'\1_\2', name)
    name = _upperstr_pat2.sub(r'\1_\2', name)
    name = _upperstr_pat3.sub(r'\1_\2', name, count=1)
    return name


def to_underscores_noprefix(name):
    """Like to_underscores, but designed for "unprefixed" names.
    to_underscores("DBusFoo") => dbus_foo, not d_bus_foo."""
    name = _upperstr_pat1.sub(r'\1_\2', name)
    name = _upperstr_pat2.sub(r'\1_\2', name)
    return name

_libtool_pat = re.compile("dlname='([A-z0-9\.\-\+]+)'\n")

def _extract_dlname_field(la_file):
    f = open(la_file)
    data = f.read()
    f.close()
    m = _libtool_pat.search(data)
    if m:
        return m.groups()[0]
    else:
        return None

# Returns the name that we would pass to dlopen() the library
# corresponding to this .la file
def extract_libtool_shlib(la_file):
    dlname = _extract_dlname_field(la_file)
    if dlname is None:
        return None

    # From the comments in extract_libtool(), older libtools had
    # a path rather than the raw dlname
    return os.path.basename(dlname)

def extract_libtool(la_file):
    dlname = _extract_dlname_field(la_file)
    if dlname is None:
        raise ValueError("%s has no dlname. Not a shared library?" % la_file)
    libname = os.path.join(os.path.dirname(la_file),
                           '.libs', dlname)
    # FIXME: This hackish, but I'm not sure how to do this
    #        in a way which is compatible with both libtool 2.2
    #        and pre-2.2. Johan 2008-10-21
    libname = libname.replace('.libs/.libs', '.libs')
    return libname

# Returns arguments for invoking libtool, if applicable, otherwise None
def get_libtool_command(options):
    libtool_infection = not options.nolibtool
    if not libtool_infection:
        return None

    libtool_path = options.libtool_path
    if libtool_path:
        # Automake by default sets:
        # LIBTOOL = $(SHELL) $(top_builddir)/libtool
        # To be strictly correct we would have to parse shell.  For now
        # we simply split().
        return libtool_path.split(' ')

    try:
        subprocess.check_call(['libtool', '--version'],
                              stdout=open(os.devnull))
    except (subprocess.CalledProcessError, OSError):
        # If libtool's not installed, assume we don't need it
        return None

    return ['libtool']


def files_are_identical(path1, path2):
    f1 = open(path1)
    f2 = open(path2)
    buf1 = f1.read(8192)
    buf2 = f2.read(8192)
    while buf1 == buf2 and buf1 != '':
        buf1 = f1.read(8192)
        buf2 = f2.read(8192)
    f1.close()
    f2.close()
    return buf1 == buf2
