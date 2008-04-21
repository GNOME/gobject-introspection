from __future__ import with_statement

from .gobjecttreebuilder import (GLibBoxed, GLibEnum, GLibEnumMember,
                                 GLibFlags, GLibObject, GLibInterface)
from .treebuilder import Class, Enum, Function, Interface
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
        elif isinstance(node, Class):
            self._write_class(node)
        elif isinstance(node, Interface):
            self._write_interface(node)
        elif isinstance(node, GLibBoxed):
            self._write_boxed(node)
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
        self.write_tag('return-type', [('type', return_.type)])

    def _write_parameters(self, parameters):
        if not parameters:
            return
        with self.tagcontext('parameters'):
            for parameter in parameters:
                self._write_parameter(parameter)

    def _write_parameter(self, parameter):
        self.write_tag('parameter', [('name', parameter.name),
                                     ('type', parameter.type)])

    def _write_enum(self, enum):
        attrs = [('name', enum.name)]
        tag_name = 'enum'
        if isinstance(enum, GLibEnum):
            attrs.append(('get-type', enum.get_type))
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

    def _write_class(self, class_):
        attrs = [('name', class_.name),
                 ('parent', class_.parent)]
        if isinstance(class_, GLibObject):
            attrs.append(('get-type', class_.get_type))
        with self.tagcontext('object', attrs):
            for method in class_.constructors:
                self._write_constructor(method)
            for method in class_.methods:
                self._write_method(method)

    def _write_interface(self, interface):
        attrs = [('name', interface.name)]
        if isinstance(interface, GLibInterface):
            attrs.append(('get-type', interface.get_type))
        with self.tagcontext('interface', attrs):
            for method in interface.methods:
                self._write_method(method)

    def _write_boxed(self, boxed):
        attrs = [('name', boxed.name)]
        if isinstance(boxed, GLibBoxed):
            attrs.append(('get-type', boxed.get_type))
        with self.tagcontext('boxed', attrs):
            for method in boxed.constructors:
                self._write_constructor(method)
            for method in boxed.methods:
                self._write_method(method)
