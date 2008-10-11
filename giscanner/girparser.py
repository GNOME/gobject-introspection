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

from .ast import (Alias, Callback, Function, Field, Parameter, Property,
                  Return, Union, Struct, Type, Array, Namespace, Varargs)
from .glibast import (GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject, GLibBoxedStruct,
                      GLibBoxedUnion, GLibBoxedOther)

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

    def __init__(self, filename, initial_parse=True):
        self._includes = set()
        self._namespace = None
        self._shared_libraries = []
        self._tree = parse(filename)

        if (initial_parse):
            self.parse()

    # Public API

    def parse(self):
        self._includes.clear()
        del self._namespace
        del self._shared_libraries[:]

        self._parse_api(self._tree.getroot())

    def get_namespace(self):
        return self._namespace

    def get_shared_libraries(self):
        return self._shared_libraries

    def get_includes(self):
        return self._includes

    def get_doc(self):
        return self._tree

    # Private

    def _add_node(self, node):
        self._namespace.nodes.append(node)

    def _parse_api(self, root):
        assert root.tag == _corens('repository')
        for node in root.getchildren():
            if node.tag == _corens('include'):
                self._includes.add(node.attrib['name'])
        ns = root.find(_corens('namespace'))
        assert ns is not None
        self._namespace = Namespace(ns.attrib['name'])
        self._shared_libraries.extend(ns.attrib['shared-library'].split(','))
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
        elif node.tag == _corens('union'):
            self._parse_union(node)
        elif node.tag == _glibns('boxed'):
            self._parse_boxed(node)
        elif node.tag in [_corens('enumeration'),
                          _corens('bitfield')]:
            self._parse_enumeration_bitfield(node)

    def _parse_alias(self, node):
        return Alias(node.attrib['name'],
                     node.attrib['target'],
                     node.attrib.get(_cns('type')))

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
                    node.attrib[_glibns('get-type')],
                    node.attrib.get(_cns('type')))
        for iface in node.findall(_corens('implements')):
            obj.interfaces.append(iface.attrib['name'])
        for method in node.findall(_corens('method')):
            obj.methods.append(self._parse_function(method, Function))
        for ctor in node.findall(_corens('constructor')):
            obj.constructors.append(self._parse_function(ctor, Function))
        for callback in node.findall(_corens('callback')):
            obj.fields.append(self._parse_function(callback, Callback))
        for field in node.findall(_corens('field')):
            obj.fields.append(self._parse_field(field))
        for property in node.findall(_corens('property')):
            obj.properties.append(self._parse_property(property))
        for signal in node.findall(_glibns('signal')):
            obj.signals.append(self._parse_function(signal, Function))
        self._add_node(obj)

    def _parse_function(self, node, klass):
        name = node.attrib['name']
        returnnode = node.find(_corens('return-value'))
        if not returnnode:
            raise ValueError('node %r has no return-value' % (name, ))
        transfer = False
        transfer_param = returnnode.attrib.get('transfer-ownership')
        if transfer_param is not None:
            transfer = (transfer_param == '1')
        retval = Return(self._parse_type(returnnode), transfer)
        parameters_node = node.find(_corens('parameters'))
        parameters = []
        if (parameters_node is not None):
            for paramnode in parameters_node.findall(_corens('parameter')):
                parameters.append(Parameter(paramnode.attrib.get('name'),
                                  self._parse_type(paramnode)))
        if klass is Callback:
            return klass(name, retval, parameters,
                         node.attrib.get(_cns('type')))
        else:
            identifier = node.attrib.get(_cns('identifier'))
            return klass(name, retval, parameters, identifier)

    def _parse_struct(self, node):
        if _glibns('type-name') in node.attrib:
            struct = GLibBoxedStruct(node.attrib['name'],
                                     node.attrib[_glibns('type-name')],
                                     node.attrib[_glibns('get-type')],
                                     node.attrib.get(_cns('type')))
        else:
            struct = Struct(node.attrib['name'],
                            node.attrib.get(_cns('type')))
        for field in node.findall(_corens('field')):
            struct.fields.append(self._parse_field(field))
        for callback in node.findall(_corens('callback')):
            struct.fields.append(self._parse_function(callback, Callback))
        for method in node.findall(_corens('method')):
            struct.fields.append(self._parse_function(method, Function))
        for ctor in node.findall(_corens('constructor')):
            struct.constructors.append(self._parse_function(ctor, Function))
        self._add_node(struct)

    def _parse_union(self, node):
        if _glibns('type-name') in node.attrib:
            struct = GLibBoxedUnion(node.attrib['name'],
                                    node.attrib[_glibns('type-name')],
                                    node.attrib[_glibns('get-type')],
                                    node.attrib.get(_cns('type')))
        else:
            struct = Union(node.attrib['name'],
                           node.attrib.get(_cns('type')))
        for callback in node.findall(_corens('callback')):
            struct.fields.append(self._parse_function(callback, Callback))
        for field in node.findall(_corens('field')):
            struct.fields.append(self._parse_field(field))
        for method in node.findall(_corens('method')):
            struct.fields.append(self._parse_function(method, Function))
        for ctor in node.findall(_corens('constructor')):
            struct.constructors.append(self._parse_function(ctor, Function))
        self._add_node(struct)

    def _parse_type(self, node):
        typenode = node.find(_corens('type'))
        if typenode is not None:
            return Type(typenode.attrib['name'],
                        typenode.attrib.get(_cns('type')))
        typenode = node.find(_corens('array'))
        if typenode is not None:
            return Array(typenode.attrib.get(_cns('type')),
                         self._parse_type(typenode))
        typenode = node.find(_corens('varargs'))
        if typenode is not None:
            return Varargs()
        raise ValueError("Couldn't parse type of node %r; children=%r",
                         node, list(node))

    def _parse_boxed(self, node):
        obj = GLibBoxedOther(node.attrib[_glibns('name')],
                             node.attrib[_glibns('type-name')],
                             node.attrib[_glibns('get-type')])
        for method in node.findall(_corens('method')):
            obj.methods.append(self._parse_function(method, Function))
        for ctor in node.findall(_corens('constructor')):
            obj.constructors.append(self._parse_function(ctor, Function))
        for callback in node.findall(_corens('callback')):
            obj.fields.append(self._parse_function(callback, Callback))
        self._add_node(obj)

    def _parse_field(self, node):
        type_node = self._parse_type(node)
        return Field(node.attrib['name'],
                     type_node,
                     type_node.ctype)

    def _parse_property(self, node):
        type_node = self._parse_type(node)
        return Property(node.attrib['name'],
                        type_node.name,
                        node.attrib.get('readable') != '0',
                        node.attrib.get('writable') == '1',
                        node.attrib.get('construct') == '1',
                        node.attrib.get('construct-only') == '1',
                        type_node.ctype)

    def _parse_member(self, node):
        return GLibEnumMember(node.attrib['name'],
                              node.attrib['value'],
                              node.attrib.get(_cns('identifier')),
                              node.attrib.get(_glibns('nick')))

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
