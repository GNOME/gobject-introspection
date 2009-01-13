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

# AnnotationParser - parses gtk-doc annotations

from .ast import (Array, Callback, Class, Enum, Field, Function, Interface,
                  List, Map, Parameter, Record, Return, Type, Union, Varargs,
                  default_array_types,
                  BASIC_GIR_TYPES,
                  PARAM_DIRECTION_INOUT,
                  PARAM_DIRECTION_IN,
                  PARAM_DIRECTION_OUT,
                  PARAM_TRANSFER_NONE,
                  PARAM_TRANSFER_CONTAINER,
                  PARAM_TRANSFER_FULL,
                  TYPE_ANY, TYPE_NONE)
from .odict import odict
from .glibast import GLibBoxed

# All gtk-doc comments needs to start with this:
_COMMENT_HEADER = '*\n '

# Tags - annotations applyed to comment blocks
TAG_SINCE = 'Since'
TAG_DEPRECATED = 'Deprecated'
TAG_RETURNS = 'Returns'
TAG_RETURNS_ALT = 'Return value'

# Options - annotations for parameters and return values
OPT_ALLOW_NONE = 'allow-none'
OPT_ARRAY = 'array'
OPT_ELEMENT_TYPE = 'element-type'
OPT_IN = 'in'
OPT_INOUT = 'inout'
OPT_INOUT_ALT = 'in-out'
OPT_OUT = 'out'
OPT_SCOPE = 'scope'
OPT_TRANSFER = 'transfer'
OPT_TYPE = 'type'

# Array options - array specific annotations
OPT_ARRAY_FIXED_SIZE = 'fixed-size'
OPT_ARRAY_LENGTH = 'length'
OPT_ARRAY_ZERO_TERMINATED = 'zero-terminated'


class InvalidAnnotationError(Exception):
    pass


class DocBlock(object):

    def __init__(self, name):
        self.name = name
        self.value = None
        self.tags = odict()

    def __repr__(self):
        return '<DocBlock %r>' % (self.name, )

    def get(self, name):
        if name == TAG_RETURNS:
            value = self.tags.get(name)
            if value is None:
                return self.tags.get(TAG_RETURNS_ALT)
            else:
                return value
        else:
            return self.tags.get(name)


class DocTag(object):

    def __init__(self, name):
        self.name = name
        self.options = []


class Option(object):

    def __init__(self, option):
        self._array = []
        self._dict = {}
        for p in option.split(' '):
            if '=' in p:
                name, value = p.split('=', 1)
            else:
                name = p
                value = None
            self._dict[name] = value
            if value is None:
                self._array.append(name)
            else:
                self._array.append((name, value))

    def __repr__(self):
        return '<Option %r>' % (self._array, )

    def one(self):
        assert len(self._array) == 1
        return self._array[0]

    def flat(self):
        return self._array

    def all(self):
        return self._dict


class AnnotationParser(object):

    def __init__(self, namespace, source_scanner, transformer):
        self._blocks = {}
        self._namespace = namespace
        self._transformer = transformer
        for comment in source_scanner.get_comments():
            self._parse_comment(comment)

    def parse(self):
        aa = AnnotationApplier(self._blocks, self._transformer)
        aa.parse(self._namespace)

    def _parse_comment(self, comment):
        comment = comment.lstrip()
        if not comment.startswith(_COMMENT_HEADER):
            return
        comment = comment[len(_COMMENT_HEADER):]
        comment = comment.strip()
        if not comment.startswith('* '):
            return
        comment = comment[2:]

        pos = comment.index('\n ')

        block_name = comment[:pos]
        block_name = block_name.strip()
        if not block_name.endswith(':'):
            return
        block = DocBlock(block_name[:-1])
        content = comment[pos+1:]
        for line in content.split('\n'):
            line = line.lstrip()
            line = line[2:].strip() # Skip ' *'
            if not line:
                continue

            if line.startswith('@'):
                line = line[1:]
            elif not ': ' in line:
                continue
            tag = self._parse_tag(line)
            block.tags[tag.name] = tag

        self._blocks[block.name] = block

    def _parse_tag(self, value):
        # Tag: bar
        # Tag: bar opt1 opt2
        parts = value.split(': ', 1)
        if len(parts) == 1:
            tag_name = parts[0]
            options = ''
        else:
            tag_name, options = parts
        tag = DocTag(tag_name)
        tag.value = options
        tag.options = self._parse_options(options)
        return tag

    def _parse_options(self, value):
        # (foo)
        # (bar opt1 opt2...)
        opened = -1
        options = {}
        for i, c in enumerate(value):
            if c == '(' and opened == -1:
                opened = i+1
            if c == ')' and opened != -1:
                segment = value[opened:i]
                parts = segment.split(' ', 1)
                if len(parts) == 2:
                    name, option = parts
                elif len(parts) == 1:
                    name = parts[0]
                    option = None
                else:
                    raise AssertionError
                if option is not None:
                    option = Option(option)
                options[name] = option
                opened = -1
        return options


class AnnotationApplier(object):

    def __init__(self, blocks, transformer):
        self._blocks = blocks
        self._transformer = transformer

    def _get_tag(self, block, tag_name):
        if block is None:
            return None

        return block.get(tag_name)

    def parse(self, namespace):
        for node in namespace.nodes:
            self._parse_node(node)

    # Boring parsing boilerplate.

    def _parse_node(self, node):
        if isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Class):
            self._parse_class(node)
        elif isinstance(node, Interface):
            self._parse_interface(node)
        elif isinstance(node, Callback):
            self._parse_callback(node)
        elif isinstance(node, Record):
            self._parse_record(node)
        elif isinstance(node, Union):
            self._parse_union(node)
        elif isinstance(node, GLibBoxed):
            self._parse_boxed(node)

    def _parse_class(self, class_):
        block = self._blocks.get(class_.name)
        self._parse_version(class_, block)
        self._parse_constructors(class_.constructors)
        self._parse_methods(class_.methods)
        self._parse_methods(class_.static_methods)
        self._parse_properties(class_, class_.properties)
        self._parse_signals(class_, class_.signals)
        self._parse_fields(class_, class_.fields)

    def _parse_interface(self, interface):
        block = self._blocks.get(interface.name)
        self._parse_version(interface, block)
        self._parse_methods(interface.methods)
        self._parse_properties(interface, interface.properties)
        self._parse_signals(interface, interface.signals)
        self._parse_fields(interface, interface.fields)

    def _parse_record(self, record):
        block = self._blocks.get(record.symbol)
        self._parse_version(record, block)
        self._parse_constructors(record.constructors)
        self._parse_fields(record, record.fields)
        if isinstance(record, GLibBoxed):
            self._parse_methods(record.methods)

    def _parse_boxed(self, boxed):
        block = self._blocks.get(boxed.name)
        self._parse_version(boxed, block)
        self._parse_constructors(boxed.constructors)
        self._parse_methods(boxed.methods)

    def _parse_union(self, union):
        block = self._blocks.get(union.name)
        self._parse_fields(union, union.fields)
        self._parse_constructors(union.constructors)
        if isinstance(union, GLibBoxed):
            self._parse_methods(union.methods)

    def _parse_enum(self, enum):
        block = self._blocks.get(enum.symbol)
        self._parse_version(enum, block)

    def _parse_constructors(self, constructors):
        for ctor in constructors:
            self._parse_function(ctor)

    def _parse_fields(self, parent, fields):
        for field in fields:
            self._parse_field(parent, field)

    def _parse_properties(self, parent, properties):
        for prop in properties:
            self._parse_property(parent, prop)

    def _parse_methods(self, methods):
        for method in methods:
            self._parse_function(method)

    def _parse_signals(self, parent, signals):
        for signal in signals:
            self._parse_signal(parent, signal)

    def _parse_property(self, parent, prop):
        block = self._blocks.get('%s:%s' % (parent.type_name, prop.name))
        self._parse_version(prop, block)
        self._parse_deprecated(prop, block)

    def _parse_callback(self, callback):
        block = self._blocks.get(callback.ctype)
        self._parse_version(callback, block)
        self._parse_params(callback, callback.parameters, block)
        self._parse_return(callback, callback.retval, block)

    def _parse_function(self, func):
        block = self._blocks.get(func.symbol)
        self._parse_version(func, block)
        self._parse_deprecated(func, block)
        self._parse_params(func, func.parameters, block)
        self._parse_return(func, func.retval, block)

    def _parse_signal(self, parent, signal):
        block = self._blocks.get('%s::%s' % (parent.type_name, signal.name))
        self._parse_version(signal, block)
        self._parse_deprecated(signal, block)
        # We're only attempting to name the signal parameters if
        # the number of parameter tags (@foo) is the same or greater
        # than the number of signal parameters
        if block and len(block.tags) > len(signal.parameters):
            names = block.tags.items()
        else:
            names = []
        for i, param in enumerate(signal.parameters):
            if names:
                name, tag = names[i+1]
                param.name = name
                options = getattr(tag, 'options', {})
                param_type = options.get(OPT_TYPE)
                if param_type:
                    param.type.name = param_type.one()
            else:
                tag = None
            self._parse_param(signal, param, tag)
        self._parse_return(signal, signal.retval, block)

    def _parse_field(self, parent, field):
        if isinstance(field, Callback):
            self._parse_callback(field)

    def _parse_params(self, parent, params, block):
        for param in params:
            tag = self._get_tag(block, param.name)
            self._parse_param(parent, param, tag)

    def _parse_return(self, parent, return_, block):
        tag = self._get_tag(block, TAG_RETURNS)
        options = getattr(tag, 'options', {})
        self._parse_param_ret_common(parent, return_, options)

    def _parse_param(self, parent, param, tag):
        options = getattr(tag, 'options', {})

        if isinstance(parent, Function):
            scope = options.get(OPT_SCOPE)
            if scope:
                param.scope = scope.one()
                param.transfer = PARAM_TRANSFER_NONE
        self._parse_param_ret_common(parent, param, options)

    def _parse_param_ret_common(self, parent, node, options):
        node.direction = self._extract_direction(node, options)
        container_type = self._extract_container_type(
            parent, node, options)
        if container_type is not None:
            node.type = container_type
        if node.direction is None:
            node.direction = self._guess_direction(node)
        node.transfer = self._extract_transfer(parent, node, options)
        if OPT_ALLOW_NONE in options:
            node.allow_none = True

        assert node.transfer is not None

    def _extract_direction(self, node, options):
        if (OPT_INOUT in options or
            OPT_INOUT_ALT in options):
            direction = PARAM_DIRECTION_INOUT
        elif OPT_OUT in options:
            direction = PARAM_DIRECTION_OUT
        elif OPT_IN in options:
            direction = PARAM_DIRECTION_IN
        else:
            direction = node.direction
        return direction

    def _guess_array(self, node):
        ctype = node.type.ctype
        if ctype is None:
            return False
        if not ctype.endswith('*'):
            return False
        if node.type.canonical in default_array_types:
            return True
        return False

    def _extract_container_type(self, parent, node, options):
        has_element_type = OPT_ELEMENT_TYPE in options
        has_array = OPT_ARRAY in options

        # FIXME: This is a hack :-(
        if (not isinstance(node, Field) and
            (not has_element_type and
             (node.direction is None
              or node.direction == PARAM_DIRECTION_IN))):
            if self._guess_array(node):
                has_array = True

        if has_array:
            container_type = self._parse_array(parent, node, options)
        elif has_element_type:
            container_type = self._parse_element_type(parent, node, options)
        else:
            container_type = None

        return container_type

    def _parse_array(self, parent, node, options):
        array_opt = options.get(OPT_ARRAY)
        if array_opt:
            array_values = array_opt.all()
        else:
            array_values = {}

        element_type = options.get(OPT_ELEMENT_TYPE)
        if element_type is not None:
            element_type_name = element_type.one()
        else:
            element_type_name = node.type.name

        container_type = Array(node.type.ctype,
                               element_type_name)
        if OPT_ARRAY_ZERO_TERMINATED in array_values:
            container_type.zeroterminated = array_values.get(
                OPT_ARRAY_ZERO_TERMINATED) == '1'
        length = array_values.get(OPT_ARRAY_LENGTH)
        if length is not None:
            param_index = parent.get_parameter_index(length)
            container_type.length_param_index = param_index
            # For in parameters we're incorrectly deferring
            # char/unsigned char to utf8 when a length annotation
            # is specified.
            if (isinstance(node, Parameter) and
                node.type.name == 'utf8' and
                self._guess_direction(node) == PARAM_DIRECTION_IN):
                # FIXME: unsigned char/guchar should be uint8
                container_type.element_type = 'int8'
        container_type.size = array_values.get(OPT_ARRAY_FIXED_SIZE)
        return container_type

    def _parse_element_type(self, parent, node, options):
        element_type_opt = options.get(OPT_ELEMENT_TYPE)
        element_type = element_type_opt.flat()
        if node.type.name in ['GLib.List', 'GLib.SList']:
            assert len(element_type) == 1
            etype = Type(element_type[0])
            container_type = List(
                node.type.name,
                node.type.ctype,
                self._transformer.resolve_param_type(etype))
        elif node.type.name in ['GLib.HashTable']:
            assert len(element_type) == 2
            key_type = Type(element_type[0])
            value_type = Type(element_type[1])
            container_type = Map(
                node.type.name,
                node.type.ctype,
                self._transformer.resolve_param_type(key_type),
                self._transformer.resolve_param_type(value_type))
        else:
            print 'FIXME: unhandled element-type container:', node
        return container_type

    def _extract_transfer(self, parent, node, options):
        transfer_opt = options.get(OPT_TRANSFER)
        if transfer_opt is None:
            transfer = self._guess_transfer(node, options)
        else:
            transfer = transfer_opt.one()
            if transfer is None:
                transfer = PARAM_TRANSFER_FULL
            if transfer not in [PARAM_TRANSFER_NONE,
                                PARAM_TRANSFER_CONTAINER,
                                PARAM_TRANSFER_FULL]:
                raise InvalidAnnotationError(
                    "transfer for %s of %r is invalid (%r), must be one of "
                    "none, container, full." % (node, parent.name, transfer))
        return transfer

    def _parse_version(self, node, block):
        since_tag = self._get_tag(block, TAG_SINCE)
        if since_tag is None:
            return
        node.version = since_tag.value

    def _parse_deprecated(self, node, block):
        deprecated_tag = self._get_tag(block, TAG_DEPRECATED)
        if deprecated_tag is None:
            return
        value = deprecated_tag.value
        if ': ' in value:
            version, desc = value.split(': ')
        else:
            desc = value
            version = None
        node.deprecated = desc
        if version is not None:
            node.deprecated_version = version

    def _guess_direction(self, node):
        if node.direction:
            return node.direction
        is_pointer = False
        if node.type.ctype:
            is_pointer = '*' in node.type.ctype

        if is_pointer and node.type.name in BASIC_GIR_TYPES:
            return PARAM_DIRECTION_OUT

        return PARAM_DIRECTION_IN

    def _guess_transfer(self, node, options):
        if node.transfer is not None:
            return node.transfer

        if isinstance(node.type, Array):
            return PARAM_TRANSFER_NONE
        # Anything with 'const' gets none
        if node.type.is_const:
            return PARAM_TRANSFER_NONE

        elif node.type.name in [TYPE_NONE, TYPE_ANY]:
            return PARAM_TRANSFER_NONE
        elif isinstance(node.type, Varargs):
            return PARAM_TRANSFER_NONE
        elif isinstance(node, Parameter):
            if node.direction in [PARAM_DIRECTION_INOUT,
                                  PARAM_DIRECTION_OUT]:
                return PARAM_TRANSFER_FULL
            # This one is a hack for compatibility; the transfer
            # for string parameters really has no defined meaning.
            elif node.type.canonical == 'utf8':
                return PARAM_TRANSFER_FULL
            else:
                return PARAM_TRANSFER_NONE
        elif isinstance(node, Return):
            if (node.type.canonical in BASIC_GIR_TYPES or
                (node.type.canonical in [TYPE_NONE, TYPE_ANY] and
                 node.type.is_const)):
                return PARAM_TRANSFER_NONE
            else:
                return PARAM_TRANSFER_FULL
        elif isinstance(node, Field):
            return PARAM_TRANSFER_NONE
        else:
            raise AssertionError(node)
