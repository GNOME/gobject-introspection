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

from __future__ import with_statement

from .ast import Callback, Class, Enum, Function, Interface
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember,
                      GLibFlags, GLibObject, GLibInterface)
from .xmlwriter import XMLWriter


class GIDLWriter(XMLWriter):
    def __init__(self, namespace, nodes):
        super(GIDLWriter, self).__init__()
        self._write_api(namespace, nodes)

    def _write_api(self, namespace, nodes):
        with self.tagcontext('api', [('version', '1.0')]):
            self._write_namespace(namespace, nodes)

    def _write_namespace(self, namespace, nodes):
        with self.tagcontext('namespace', [('name', namespace)]):
            for node in nodes:
                self._write_node(node)

    def _write_node(self, node):
        if isinstance(node, Function):
            self._write_function(node)
        elif isinstance(node, Enum):
            self._write_enum(node)
        elif isinstance(node, (Class, Interface)):
            self._write_class(node)
        elif isinstance(node, GLibBoxed):
            self._write_boxed(node)
        elif isinstance(node, Callback):
            self._write_callback(node)
        else:
            print 'WRITER: Unhandled node', node

    def _write_function(self, func, tag_name='function'):
        attrs = [('name', func.name),
                 ('symbol', func.symbol)]
        with self.tagcontext(tag_name, attrs):
            self._write_return_type(func.retval)
            self._write_parameters(func.parameters)

    def _write_method(self, method):
        self._write_function(method, tag_name='method')

    def _write_constructor(self, method):
        self._write_function(method, tag_name='constructor')

    def _write_return_type(self, return_):
        if not return_:
            return
        attrs = [('type', return_.ctype.name)]
        if return_.transfer != 'none':
            attrs.append(('transfer', return_.transfer))
        self.write_tag('return-type', attrs)

    def _write_parameters(self, parameters):
        if not parameters:
            return
        with self.tagcontext('parameters'):
            for parameter in parameters:
                self._write_parameter(parameter)

    def _write_parameter(self, parameter):
        attrs = [('name', parameter.name),
                 ('type', parameter.type.name)]
        if parameter.direction != 'in':
            attrs.append(('direction', parameter.direction))
        if parameter.transfer != 'none':
            attrs.append(('transfer', parameter.transfer))
        self.write_tag('parameter', attrs)

    def _write_enum(self, enum):
        attrs = [('name', enum.name)]
        tag_name = 'enum'
        if isinstance(enum, GLibEnum):
            attrs.extend([('type-name', enum.type_name),
                          ('get-type', enum.get_type)])
            if isinstance(enum, GLibFlags):
                tag_name = 'flags'

        with self.tagcontext(tag_name, attrs):
            for member in enum.members:
                self._write_member(member)

    def _write_member(self, member):
        attrs = [('name', member.name),
                 ('value', str(member.value))]
        if isinstance(member, GLibEnumMember):
            attrs.append(('nick', member.nick))
        self.write_tag('member', attrs)

    def _write_class(self, node):
        attrs = [('name', node.name)]
        if isinstance(node, Class):
            tag_name = 'object'
            if node.parent is not None:
                attrs.append(('parent', node.parent))
        else:
            tag_name = 'interface'
        if isinstance(node, (GLibObject, GLibInterface)):
            attrs.append(('type-name', node.type_name))
            attrs.append(('get-type', node.get_type))
        with self.tagcontext(tag_name, attrs):
            if isinstance(node, Class):
                for method in node.constructors:
                    self._write_constructor(method)
            for method in node.methods:
                self._write_method(method)
            for prop in node.properties:
                self._write_property(prop)
            for field in node.fields:
                self._write_field(field)
            for signal in node.signals:
                self._write_signal(signal)

    def _write_boxed(self, boxed):
        attrs = [('name', boxed.name),
                 ('type-name', boxed.type_name),
                 ('get-type', boxed.get_type)]

        with self.tagcontext('boxed', attrs):
            for method in boxed.constructors:
                self._write_constructor(method)
            for method in boxed.methods:
                self._write_method(method)

    def _write_property(self, prop):
        attrs = [('name', prop.name),
                 ('prop', prop.type.name)]
        self.write_tag('property', attrs)

    def _write_signal(self, signal):
        attrs = [('name', signal.name)]
        with self.tagcontext('signal', attrs):
            self._write_return_type(signal.retval)
            self._write_parameters(signal.parameters)

    def _write_callback(self, func):
        attrs = [('name', func.name)]
        with self.tagcontext('callback', attrs):
            self._write_return_type(func.retval)
            self._write_parameters(func.parameters)

    def _write_field(self, field):
        if isinstance(field, Callback):
            self._write_callback(field)
            return

        attrs = [('name', field.name),
                 ('type', str(field.type))]
        self.write_tag('field', attrs)
