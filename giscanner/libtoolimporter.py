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

import imp
import os
import sys

from .utils import extract_libtool


class LibtoolImporter(object):

    def __init__(self, name, path):
        self.name = name
        self.path = path

    @classmethod
    def find_module(cls, name, relpath=None):
        modparts = name.split('.')
        filename = modparts.pop() + '.la'

        # Given some.package.module 'path' is where subpackages of some.package
        # should be looked for. See if we can find a ".libs/module.la" relative
        # to those directories and failing that look for file
        # "some/package/.libs/module.la" relative to sys.path
        if relpath is None:
            paths = relpath
            module = ''
        else:
            paths = sys.path
            module = os.path.join(*modparts)

        for path in paths:
            full = os.path.join(path, module, '.libs', filename)
            if os.path.exists(full):
                return cls(name, full)

    def load_module(self, name):
        realpath = extract_libtool(self.path)
        mod = imp.load_module(name, open(realpath), realpath,
                              ('.so', 'rb', 3))
        return mod

    @classmethod
    def __enter__(cls):
        sys.meta_path.append(cls)

    @classmethod
    def __exit__(cls, type, value, traceback):
        sys.meta_path.remove(cls)
