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


class LibToolImporter(object):
    def __init__(self, name, path):
        self.name = name
        self.path = path

    @staticmethod
    def find_module(name, path=None):
        modname = name.split('.')[-1]
        for part in path or sys.path:
            full = os.path.join(part, '.libs', modname + '.la')
            if os.path.exists(full):
                return LibToolImporter(name, full)

    def load_module(self, name):
        realpath = extract_libtool(self.path)
        mod = imp.load_module(name, open(realpath), realpath,
                              ('.so', 'rb', 3))
        return mod

def install_libtoolimporter():
    sys.meta_path.append(LibToolImporter)

def uninstall_libtoolimporter():
    sys.meta_path.remove(LibToolImporter)
