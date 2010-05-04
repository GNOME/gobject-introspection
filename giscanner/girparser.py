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

from xml.etree.cElementTree import parse

from .ast import (Alias, Array, Callback, Constant, Enum, Function, Field,
                  Namespace, Parameter, Property, Return, Union, Struct, Type,
                  Varargs, Include)
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

    def __init__(self):
        self._include_parsing = False
        self._shared_libraries = []
        self._includes = set()
        self._pkgconfig_packages = set()
        self._namespace = None

    # Public API

    def parse(self, filename):
        tree = parse(filename)
        self.parse_tree(tree)

    def parse_tree(self, tree):
        self._includes.clear()
        self._namespace = None
        self._shared_libraries = []
        self._pkgconfig_packages = set()
        self._parse_api(tree.getroot())

    def get_namespace(self):
        return self._namespace

    def get_shared_libraries(self):
        return self._shared_libraries

    def get_includes(self):
        return self._includes

    def get_pkgconfig_packages(self):
        if not hasattr(self, '_pkgconfig_packages'):
            self._pkgconfig_packages = []
        return self._pkgconfig_packages

    def get_doc(self):
        return parse(self._filename)

    def set_include_parsing(self, include_parsing):
        self._include_parsing = include_parsing

    # Private

    def _add_node(self, node):
        self._namespace.nodes.append(node)

    def _parse_api(self, root):
        assert root.tag == _corens('repository')
        for node in root.getchildren():
            if node.tag == _corens('include'):
                self._parse_include(node)
            elif node.tag == _corens('package'):
                self._parse_pkgconfig_package(node)

        ns = root.find(_corens('namespace'))
        assert ns is not None
        self._namespace = Namespace(ns.attrib['name'],
                                    ns.attrib['version'])
        if 'shared-library' in ns.attrib:
            self._shared_libraries.extend(
                ns.attrib['shared-library'].split(','))

        parser_methods = {
            _corens('alias'): self._parse_alias,
            _corens('bitfield'): self._parse_enumeration_bitfield,
            _corens('callback'): self._parse_callback,
            _corens('class'): self._parse_object_interface,
            _corens('constant'): self._parse_constant,
            _corens('function'): self._parse_function,
            _corens('enumeration'): self._parse_enumeration_bitfield,
            _corens('interface'): self._parse_object_interface,
            _corens('record'): self._parse_record,
            _corens('union'): self._parse_union,
            _corens('boxed'): self._parse_boxed,
            }

        for node in ns.getchildren():
            method = parser_methods.get(node.tag)
            if method is not None:
                method(node)

    def _parse_include(self, node):
        include = Include(node.attrib['name'],
                          node.attrib['version'])
        self._includes.add(include)

    def _parse_pkgconfig_package(self, node):
        if not hasattr(self, '_pkgconfig_packages'):
            self._pkgconfig_packages = []
        self._pkgconfig_packages.add(node.attrib['name'])

    def _parse_alias(self, node):
        alias = Alias(node.attrib['name'],
                      node.attrib['target'],
                      node.attrib.get(_cns('type')))
        self._add_node(alias)

    def _parse_object_interface(self, node):
        ctor_args = [node.attrib['name'],
                     node.attrib.get('parent'),
                     node.attrib[_glibns('type-name')],
                     node.attrib[_glibns('get-type')]]
        if node.tag == _corens('interface'):
            klass = GLibInterface
        elif node.tag == _corens('class'):
            klass = GLibObject
            is_abstract = node.attrib.get('abstract')
            is_abstract = is_abstract and is_abstract != '0'
            ctor_args.append(is_abstract)
        else:
            raise AssertionError(node)

        obj = klass(*ctor_args)
        self._add_node(obj)

        if self._include_parsing:
            return
        ctor_args.append(node.attrib.get(_cns('type')))
        for iface in node.findall(_corens('implements')):
            obj.interfaces.append(iface.attrib['name'])
        for iface in node.findall(_corens('prerequisites')):
            obj.prerequisities.append(iface.attrib['name'])
        for method in node.findall(_corens('method')):
            func = self._parse_function_common(method, Function)
            func.is_method = True
            obj.methods.append(func)
        for ctor in node.findall(_corens('constructor')):
            obj.constructors.append(
                self._parse_function_common(ctor, Function))
        for callback in node.findall(_corens('callback')):
            obj.fields.append(self._parse_function_common(callback, Callback))
        for field in node.findall(_corens('field')):
            obj.fields.append(self._parse_field(field))
        for prop in node.findall(_corens('property')):
            obj.properties.append(self._parse_property(prop))
        for signal in node.findall(_glibns('signal')):
            obj.signals.append(self._parse_function_common(signal, Function))

    def _parse_callback(self, node):
        callback = self._parse_function_common(node, Callback)
        self._add_node(callback)

    def _parse_function(self, node):
        function = self._parse_function_common(node, Function)
        self._add_node(function)

    def _parse_function_common(self, node, klass):
        name = node.attrib['name']
        returnnode = node.find(_corens('return-value'))
        if not returnnode:
            raise ValueError('node %r has no return-value' % (name, ))
        transfer = returnnode.attrib.get('transfer-ownership')
        retval = Return(self._parse_type(returnnode), transfer)
        parameters = []

        if klass is Callback:
            func = klass(name, retval, parameters,
                         node.attrib.get(_cns('type')))
        else:
            identifier = node.attrib.get(_cns('identifier'))
            throws = (node.attrib.get('throws') == '1')
            func = klass(name, retval, parameters, identifier, throws)

        if self._include_parsing:
            return func

        parameters_node = node.find(_corens('parameters'))
        if (parameters_node is not None):
            for paramnode in parameters_node.findall(_corens('parameter')):
                param = Parameter(paramnode.attrib.get('name'),
                                  self._parse_type(paramnode),
                                  paramnode.attrib.get('direction'),
                                  paramnode.attrib.get('transfer-ownership'),
                                  paramnode.attrib.get('allow-none') == '1')
                parameters.append(param)

        return func

    def _parse_record(self, node):
        if _glibns('type-name') in node.attrib:
            struct = GLibBoxedStruct(node.attrib['name'],
                                     node.attrib[_glibns('type-name')],
                                     node.attrib[_glibns('get-type')],
                                     node.attrib.get(_cns('type')))
        else:
            disguised = node.attrib.get('disguised') == '1'
            struct = Struct(node.attrib['name'],
                            node.attrib.get(_cns('type')),
                            disguised=disguised)
        self._add_node(struct)

        if self._include_parsing:
            return
        for field in node.findall(_corens('field')):
            struct.fields.append(self._parse_field(field))
        for callback in node.findall(_corens('callback')):
            struct.fields.append(
                self._parse_function_common(callback, Callback))
        for method in node.findall(_corens('method')):
            struct.fields.append(
                self._parse_function_common(method, Function))
        for ctor in node.findall(_corens('constructor')):
            struct.constructors.append(
                self._parse_function_common(ctor, Function))

    def _parse_union(self, node):
        if _glibns('type-name') in node.attrib:
            union = GLibBoxedUnion(node.attrib['name'],
                                    node.attrib[_glibns('type-name')],
                                    node.attrib[_glibns('get-type')],
                                    node.attrib.get(_cns('type')))
        else:
            union = Union(node.attrib['name'],
                          node.attrib.get(_cns('type')))
        self._add_node(union)

        if self._include_parsing:
            return
        for callback in node.findall(_corens('callback')):
            union.fields.append(
                self._parse_function_common(callback, Callback))
        for field in node.findall(_corens('field')):
            union.fields.append(self._parse_field(field))
        for method in node.findall(_corens('method')):
            union.fields.append(
                self._parse_function_common(method, Function))
        for ctor in node.findall(_corens('constructor')):
            union.constructors.append(
                self._parse_function_common(ctor, Function))

    def _parse_type(self, node):
        typenode = node.find(_corens('type'))
        if typenode is not None:
            return Type(typenode.attrib['name'],
                        typenode.attrib.get(_cns('type')))

        typenode = node.find(_corens('array'))
        if typenode is not None:

            array_type = typenode.attrib.get(_cns('type'))
            if array_type.startswith('GArray*') or \
               array_type.startswith('GPtrArray*') or \
               array_type.startswith('GByteArray*'):
                element_type = None
            else:
                element_type = self._parse_type(typenode)

            ret = Array(None, array_type, element_type)

            lenidx = typenode.attrib.get('length')
            if lenidx:
                ret.length_param_index = int(lenidx)
            return ret

        typenode = node.find(_corens('varargs'))
        if typenode is not None:
            return Varargs()

        raise ValueError("Couldn't parse type of node %r; children=%r",
                         node, list(node))

    def _parse_boxed(self, node):
        obj = GLibBoxedOther(node.attrib[_glibns('name')],
                             node.attrib[_glibns('type-name')],
                             node.attrib[_glibns('get-type')])
        self._add_node(obj)
        if self._include_parsing:
            return
        for method in node.findall(_corens('method')):
            func = self._parse_function_common(method, Function)
            func.is_method = True
            obj.methods.append(func)
        for ctor in node.findall(_corens('constructor')):
            obj.constructors.append(
                self._parse_function_common(ctor, Function))
        for callback in node.findall(_corens('callback')):
            obj.fields.append(
                self._parse_function_common(callback, Callback))

    def _parse_field(self, node):
        type_node = self._parse_type(node)
        return Field(node.attrib['name'],
                     type_node,
                     type_node.ctype,
                     node.attrib.get('readable') != '0',
                     node.attrib.get('writable') == '1',
                     node.attrib.get('bits'))

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

    def _parse_constant(self, node):
        type_node = self._parse_type(node)
        constant = Constant(node.attrib['name'],
                            type_node.name,
                            node.attrib['value'])
        self._add_node(constant)

    def _parse_enumeration_bitfield(self, node):
        name = node.attrib.get('name')
        ctype = node.attrib.get(_cns('type'))
        get_type = node.attrib.get(_glibns('get-type'))
        type_name = node.attrib.get(_glibns('type-name'))
        if get_type:
            if node.tag == _corens('bitfield'):
                klass = GLibFlags
            else:
                klass = GLibEnum
        else:
            klass = Enum
            type_name = ctype
        members = []
        if klass is Enum:
            obj = klass(name, type_name, members)
        else:
            obj = klass(name, type_name, members, get_type)
            obj.ctype = ctype
        self._add_node(obj)

        if self._include_parsing:
            return
        for member in node.findall(_corens('member')):
            members.append(self._parse_member(member))
