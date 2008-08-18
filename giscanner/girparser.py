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

from .ast import Alias, Callback, Function, Parameter, Return, Struct, Type
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject)

CORE_NS = "http://www.gtk.org/introspection/core/1.0"
C_NS = "http://www.gtk.org/introspection/c/1.0"
GLIB_NS = "http://www.gtk.org/introspection/glib/1.0"


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

    # Public API

    def get_namespace_name(self):
        return self._namespace_name

    def get_nodes(self):
        return self._nodes

    # Private

    def _add_node(self, node):
        self._nodes.append(node)

    def _parse_api(self, root):
        assert root.tag == _corens('repository')
        ns = root.find(_corens('namespace'))
        assert ns is not None
        self._namespace_name = ns.attrib['name']
        for child in ns.getchildren():
            self._parse_node(child)

    def _parse_node(self, node):
        if node.tag == _corens('alias'):
            self._add_node(self._parse_alias(node))
        elif node.tag in [_corens('callback')]:
            self._add_node(self._parse_function(node, Callback))
        elif node.tag in [_corens('function')]:
            self._add_node(self._parse_function(node, Function))
        elif node.tag in [_corens('class'),
                          _corens('interface')]:
            self._parse_object_interface(node)
        elif node.tag == _corens('record'):
            self._parse_struct(node)
        elif node.tag == _glibns('boxed'):
            self._parse_boxed(node)
        elif node.tag in [_corens('enumeration'),
                          _corens('bitfield')]:
            self._parse_enumeration_bitfield(node)

    def _parse_alias(self, node):
        return Alias(node.attrib['name'],
                     node.attrib['target'])

    def _parse_object_interface(self, node):
        if node.tag == _corens('interface'):
            klass = GLibInterface
        elif node.tag == _corens('class'):
            klass = GLibObject
        else:
            raise AssertionError(node)

        obj = klass(node.attrib['name'],
                    node.attrib.get('parent'),
                    node.attrib[_glibns('type-name')],
                    node.attrib[_glibns('get-type')])
        for method in node.findall(_corens('method')):
            obj.methods.append(self._parse_function(method, Function))
        for ctor in node.findall(_corens('constructor')):
            obj.constructors.append(self._parse_function(ctor, Function))
        for callback in node.findall(_corens('callback')):
            obj.fields.append(self._parse_function(callback, Callback))
        self._add_node(obj)

    def _parse_function(self, node, klass):
        name = node.attrib['name']
        retval = Return(self._parse_type(node.find(_corens('return-value'))))
        parameters = []
        for paramnode in node.findall('parameter'):
            parameters.append(Parameter(paramnode.attrib['name'],
                                        self._parse_type(paramnode)))
        if klass is Callback:
            return klass(name, retval, parameters)
        else:
            identifier = node.attrib.get(_cns('identifier'))
            return klass(name, retval, parameters, identifier)

    def _parse_struct(self, node):
        struct = Struct(node.attrib['name'],
                        node.attrib[_cns('type')])
        self._add_node(struct)

    def _parse_type(self, node):
        typenode = node.find(_corens('type'))
        if node is None:
            raise ValueError("failed to find type")
        return Type(typenode.attrib['name'],
                    typenode.attrib[_cns('type')])

    def _parse_boxed(self, node):
        obj = GLibBoxed(node.attrib[_glibns('name')],
                        node.attrib[_glibns('type-name')],
                        node.attrib[_glibns('get-type')])
        for method in node.findall(_corens('method')):
            obj.methods.append(self._parse_function(method, Function))
        for ctor in node.findall(_corens('constructor')):
            obj.constructors.append(self._parse_function(ctor, Function))
        for callback in node.findall(_corens('callback')):
            obj.fields.append(self._parse_function(callback, Callback))
        self._add_node(obj)

    def _parse_member(self, node):
        return GLibEnumMember(node.attrib['name'],
                              node.attrib['value'],
                              node.attrib[_cns('identifier')],
                              node.attrib.get(_glibns('get-type')))

    def _parse_enumeration_bitfield(self, node):
        klass = (GLibFlags if node.tag == _corens('bitfield') else GLibEnum)
        members = []
        for member in node.findall(_corens('member')):
            members.append(self._parse_member(member))
        obj = klass(node.attrib.get('name'),
                    node.attrib.get(_glibns('type-name')),
                    members,
                    node.attrib.get(_glibns('get-type')))
        obj.ctype = node.attrib.get(_cns('type'))
        self._add_node(obj)
