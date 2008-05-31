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

from xml.etree.cElementTree import parse

from .glibast import GLibObject

CORE_NS = "http://www.gtk.org/introspection/core/1.0"
GLIB_NS = "http://www.gtk.org/introspection/glib/1.0"

def _corens(tag):
    return '{%s}%s' % (CORE_NS, tag)

def _glibns(tag):
    return '{%s}%s' % (GLIB_NS, tag)


class GIRParser(object):
    def __init__(self, filename):
        self._nodes = []
        self._namespace_name = None

        tree = parse(filename)
        self._parse_api(tree.getroot())

    def _parse_api(self, root):
        assert root.tag == _corens('repository')
        ns = root.find(_corens('namespace'))
        assert ns is not None
        self._namespace_name = ns.attrib['name']
        for child in ns.getchildren():
            if child.tag == _corens('class'):
                self._parse_object(child)
            elif child.tag in [_corens('callback'),
                               _corens('function'),
                               _corens('record'),
                               _corens('enumeration'),
                               ]:
                continue
            else:
                print 'PARSER: Unhandled %s' % (child.tag,)

    def _parse_object(self, node):
        gobj = GLibObject(node.attrib['name'],
                          node.attrib.get('parent'),
                          node.attrib[_glibns('type-name')],
                          node.attrib[_glibns('get-type')])
        self._nodes.append(gobj)

    def get_namespace_name(self):
        return self._namespace_name

    def get_nodes(self):
        return self._nodes
