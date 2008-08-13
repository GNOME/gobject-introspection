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

import os
import sys

from xml.etree.cElementTree import parse

from .ast import (Callback, Enum, Function, Member, Namespace, Parameter,
                  Property, Return, Sequence, Struct, Field, Type, Alias,
                  type_name_from_ctype)
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject, GLibSignal)

CORE_NS = "http://www.gtk.org/introspection/core/1.0"
GLIB_NS = "http://www.gtk.org/introspection/glib/1.0"
C_NS = "http://www.gtk.org/introspection/c/1.0"


def _corens(tag):
    return '{%s}%s' % (CORE_NS, tag)


def _glibns(tag):
    return '{%s}%s' % (GLIB_NS, tag)

def _cns(tag):
    return '{%s}%s' % (C_NS, tag)

class GIRParser(object):

    def __init__(self, filename):
        self._nodes = []
        self._namespace_name = None

        tree = parse(filename)
        self._parse_api(tree.getroot())


    def _add_node(self, node):
        self._nodes.append(node)


    def _parse_api(self, root):
        assert root.tag == _corens('repository')
        ns = root.find(_corens('namespace'))
        assert ns is not None
        self._namespace_name = ns.attrib['name']
        for child in ns.getchildren():
            if child.tag in (_corens('callback'), ):
                self._add_node(self._parse_function(child, Callback))
            if child.tag in (_corens('function'), ):
                self._add_node(self._parse_function(child, Function))
            if child.tag == _corens('class'):
                c = GLibObject(child.attrib['name'],
                               child.attrib.get('parent'),
                               child.attrib[_glibns('type-name')],
                               child.attrib[_glibns('get-type')])
                self._parse_functions_props(child, c)
                self._add_node(c)
            if child.tag == _corens('interface'):
                c = GLibInterface(child.attrib['name'], child.attrib[_glibns('type-name')], child.attrib[_glibns('get-type')])
                self._parse_functions_props(child, c)
                self._add_node(c)
            if child.tag in [_corens('record'), _corens('interface'),
                             _glibns('boxed'),
                             _corens('enumeration'),
                             _corens('bitfield'),
                             ]:
                pass


    def _parse_functions_props(self, child, obj):
        for meth in child.findall(_corens('method')):
            obj.methods.append(self._parse_function(meth, Function))
        for ctor in child.findall(_corens('constructor')):
            obj.constructors.append(self._parse_function(ctor, Function))
        for cb in child.findall(_corens('callback')):
            obj.fields.append(self._parse_function(cb, Callback))


    def _parse_function(self, child, klass):
        retval = Return(self._parse_type(child.find(_corens('return-value'))))
        params = []
        for paramnode in child.findall('parameter'):
            paramtype = self._parse_type(paramnode)
            params.append(Parameter(paramnode.attrib['name'], paramtype))
        if klass is not Callback:
            try:
                ident = child.attrib[_cns('identifier')]
            except KeyError, e:
                ident = None
        else:
            ident = None
        args = [child.attrib['name'], retval, params]
        if ident:
            args.append(ident)
        return klass(*args)


    def _parse_type(self, node):
        typenode = node.find(_corens('type'))
        if node is None:
            raise ValueError("failed to find type")
        return Type(typenode.attrib['name'], typenode.attrib[_cns('type')])


    def get_namespace_name(self):
        return self._namespace_name


    def get_nodes(self):
        return self._nodes

