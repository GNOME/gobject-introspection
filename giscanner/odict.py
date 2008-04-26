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

"""odict - an ordered dictionary"""

from UserDict import DictMixin


class odict(DictMixin):
    def __init__(self):
        self._items = {}
        self._keys = []

    def __setitem__(self, key, value):
        if key not in self._items:
            self._keys.append(key)
        self._items[key] = value

    def __getitem__(self, key):
        return self._items[key]

    def __delitem__(self, key):
        del self._items[key]
        self._keys.remove(key)

    def keys(self):
        return self._keys[:]
