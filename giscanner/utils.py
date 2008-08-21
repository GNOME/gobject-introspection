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

import re
import os

# Copied from h2defs.py
_upperstr_pat1 = re.compile(r'([^A-Z])([A-Z])')
_upperstr_pat2 = re.compile(r'([A-Z][A-Z])([A-Z][0-9a-z])')
_upperstr_pat3 = re.compile(r'^([A-Z])([A-Z])')


def to_underscores(name):
    """Converts a typename to the equivalent underscores name.
    This is used to form the type conversion macros and enum/flag
    name variables"""
    name = _upperstr_pat1.sub(r'\1_\2', name)
    name = _upperstr_pat2.sub(r'\1_\2', name)
    name = _upperstr_pat3.sub(r'\1_\2', name, count=1)
    return name


def _gen_pascal_combinations(nameset):
    firstname = [nameset[0].title(), nameset[0].upper()]
    if len(nameset) == 1:
        return firstname
    else:
        subset = _gen_pascal_combinations(nameset[1:])
        results = []
        for x in subset:
            results.append(firstname[0] + x)
            results.append(firstname[1] + x)
        return results


def to_pascal_combinations(name):
    return _gen_pascal_combinations(name.split('_'))


_libtool_pat = re.compile("dlname='([A-z0-9\.\-\+]+)'\n")


def extract_libtool(libname):
    data = open(libname).read()
    filename = _libtool_pat.search(data).groups()[0]
    libname = os.path.join(os.path.dirname(libname),
                           '.libs', filename)
    return libname


def strip_common_prefix(first, second):
    second = second.replace('_', '')
    for i, c in enumerate(first.upper()):
        if c != second[i]:
            break
    return second[i:]
