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

import re
import sys

from .ast import (Array, Bitfield, Callback, Class, Enum, Field, Function,
                  Interface, List, Map, Parameter, Record, Return, Type, Union,
                  Varargs,
                  default_array_types,
                  BASIC_GIR_TYPES,
                  PARAM_DIRECTION_INOUT,
                  PARAM_DIRECTION_IN,
                  PARAM_DIRECTION_OUT,
                  PARAM_SCOPE_CALL,
                  PARAM_SCOPE_ASYNC,
                  PARAM_SCOPE_NOTIFIED,
                  PARAM_TRANSFER_NONE,
                  PARAM_TRANSFER_CONTAINER,
                  PARAM_TRANSFER_FULL,
                  TYPE_ANY, TYPE_NONE)
from .odict import odict
from .glibast import GLibBoxed

# All gtk-doc comments needs to start with this:
_COMMENT_HEADER = '*\n '

# Tags - annotations applyed to comment blocks
TAG_VFUNC = 'virtual'
TAG_SINCE = 'since'
TAG_DEPRECATED = 'deprecated'
TAG_RETURNS = 'returns'
TAG_RETURNS_ALT = 'return value'
TAG_ATTRIBUTES = 'attributes'
TAG_RENAME_TO = 'rename to'
TAG_TYPE = 'type'

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
OPT_CLOSURE = 'closure'
OPT_DESTROY = 'destroy'
OPT_SKIP = 'skip'
OPT_FOREIGN = 'foreign'

# Specific option values
OPT_VAL_BITFIELD = 'bitfield'

# Array options - array specific annotations
OPT_ARRAY_FIXED_SIZE = 'fixed-size'
OPT_ARRAY_LENGTH = 'length'
OPT_ARRAY_ZERO_TERMINATED = 'zero-terminated'

OPT_SCOPE_ASYNC = 'async'
OPT_SCOPE_CALL = 'call'
OPT_SCOPE_NOTIFIED = 'notified'

class InvalidAnnotationError(Exception):
    pass


class DocBlock(object):

    def __init__(self, name, options):
        self.name = name
        self.options = options
        self.value = None
        self.tags = odict()
        self.comment = None

    def __repr__(self):
        return '<DocBlock %r %r>' % (self.name, self.options)

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
        self.options = {}
        self.comment = None

    def __repr__(self):
        return '<DocTag %r %r>' % (self.name, self.options)

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
        # We're looking for gtk-doc comments here, they look like this:
        # /**
        #   * symbol:
        #
        # Or, alternatively, with options:
        # /**
        #   * symbol: (name value) ...
        #
        # symbol is currently one of:
        #  - function: gtk_widget_show
        #  - signal:   GtkWidget::destroy
        #  - property: GtkWidget:visible
        #
        comment = comment.lstrip()
        if not comment.startswith(_COMMENT_HEADER):
            return
        comment = comment[len(_COMMENT_HEADER):]
        comment = comment.strip()
        if not comment.startswith('* '):
            return
        comment = comment[2:]

        pos = comment.find('\n ')
        if pos == -1:
            return
        block_header = comment[:pos]
        block_header = block_header.strip()
        cpos = block_header.find(': ')
        if cpos:
            block_name = block_header[:cpos]
            block_options, rest = self._parse_options(block_header[cpos+2:])
            if rest:
                return
        else:
            block_name, block_options = block_header, {}
        block = DocBlock(block_name, block_options)
        comment_lines = []
        parse_parameters = True
        canon_name = ''
        for line in comment[pos+1:].split('\n'):
            line = line.lstrip()
            line = line[2:].strip() # Skip ' *'
            if not line:
                if parse_parameters:
                    parse_parameters = False
                continue
            if line.startswith('@'):
                line = line[1:]
            elif not ': ' in line:
                if parse_parameters and line:
                    if canon_name != '' and canon_name in block.tags:
                        block.tags[canon_name].comment += ' ' + line
                else:
                    comment_lines.append(line)
                continue
            tag_name, value = self._split_tag_namevalue(line)
            canon_name = tag_name.lower()
            if canon_name in block.tags:
                print >> sys.stderr, (
                    "Symbol %s has multiple definition of tag %r" % (
                    block_name, canon_name, ))
            block.tags[canon_name] = self._create_tag(canon_name, value)
        block.comment = '\n'.join(comment_lines)
        self._blocks[block.name] = block

    def _split_tag_namevalue(self, raw):
        """Split a line into tag name and value"""
        parts = raw.split(': ', 1)
        if len(parts) == 1:
            tag_name = parts[0]
            value = ''
            if tag_name.endswith(':'):
                tag_name = tag_name[:-1]
        else:
            tag_name, value = parts
        return (tag_name, value)

    def _create_tag(self, tag_name, value):
        # Tag: bar
        # Tag: bar opt1 opt2
        tag = DocTag(tag_name)
        tag.value = value
        options, rest = self._parse_options(tag.value)
        tag.options = options
        tag.comment = rest or ''
        return tag

    def _parse_options(self, value):
        # (foo)
        # (bar opt1 opt2...)
        opened = -1
        options = {}
        last = None
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
                last = i + 2
                opened = -1

        if last is not None:
            rest = value[last:].strip()
        else:
            rest = None
        return options, rest


class AnnotationApplier(object):

    def __init__(self, blocks, transformer):
        self._blocks = blocks
        self._transformer = transformer

    def _get_tag(self, block, tag_name):
        if block is None:
            return None

        return block.get(tag_name)

    def parse(self, namespace):
        self._namespace = namespace
        for node in namespace.nodes[:]:
            self._parse_node(node)
        del self._namespace

    # Boring parsing boilerplate.

    def _parse_node(self, node):
        if isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Bitfield):
            self._parse_bitfield(node)
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
        block = self._blocks.get(class_.type_name)
        self._parse_node_common(class_, block)
        self._parse_constructors(class_.constructors)
        self._parse_methods(class_, class_.methods)
        self._parse_vfuncs(class_, class_.virtual_methods)
        self._parse_methods(class_, class_.static_methods)
        self._parse_properties(class_, class_.properties)
        self._parse_signals(class_, class_.signals)
        self._parse_fields(class_, class_.fields)
        if block:
            class_.doc = block.comment

    def _parse_interface(self, interface):
        block = self._blocks.get(interface.type_name)
        self._parse_node_common(interface, block)
        self._parse_methods(interface, interface.methods)
        self._parse_vfuncs(interface, interface.virtual_methods)
        self._parse_properties(interface, interface.properties)
        self._parse_signals(interface, interface.signals)
        self._parse_fields(interface, interface.fields)
        if block:
            interface.doc = block.comment

    def _parse_record(self, record):
        block = self._blocks.get(record.symbol)
        self._parse_node_common(record, block)
        self._parse_constructors(record.constructors)
        self._parse_methods(record, record.methods)
        self._parse_fields(record, record.fields, block)
        if block:
            record.doc = block.comment

    def _parse_boxed(self, boxed):
        block = self._blocks.get(boxed.name)
        self._parse_node_common(boxed, block)
        self._parse_constructors(boxed.constructors)
        self._parse_methods(boxed, boxed.methods)
        if block:
            boxed.doc = block.comment

    def _parse_union(self, union):
        block = self._blocks.get(union.name)
        self._parse_node_common(union, block)
        self._parse_fields(union, union.fields, block)
        self._parse_constructors(union.constructors)
        self._parse_methods(union, union.methods)
        if block:
            union.doc = block.comment

    def _parse_enum(self, enum):
        block = self._blocks.get(enum.symbol)
        self._parse_node_common(enum, block)
        if block:
            enum.doc = block.comment
            type_opt = block.options.get(OPT_TYPE)
            if type_opt and type_opt.one() == OPT_VAL_BITFIELD:
                # This is hack, but hey, it works :-)
                enum.__class__ = Bitfield

    def _parse_bitfield(self, bitfield):
        block = self._blocks.get(bitfield.symbol)
        self._parse_node_common(bitfield, block)
        if block:
            bitfield.doc = block.comment

    def _parse_constructors(self, constructors):
        for ctor in constructors:
            self._parse_function(ctor)

    def _parse_fields(self, parent, fields, block=None):
        for field in fields:
            self._parse_field(parent, field, block)

    def _parse_properties(self, parent, properties):
        for prop in properties:
            self._parse_property(parent, prop)

    def _parse_methods(self, parent, methods):
        for method in methods:
            self._parse_method(parent, method)

    def _parse_vfuncs(self, parent, vfuncs):
        for vfunc in vfuncs:
            self._parse_vfunc(parent, vfunc)

    def _parse_signals(self, parent, signals):
        for signal in signals:
            self._parse_signal(parent, signal)

    def _parse_property(self, parent, prop):
        block = self._blocks.get('%s:%s' % (parent.type_name, prop.name))
        self._parse_node_common(prop, block)
        if block:
            prop.doc = block.comment
        type_tag = self._get_tag(block, TAG_TYPE)
        if type_tag:
            prop.type = self._resolve(type_tag.value, prop.type)

    def _parse_callback(self, callback):
        block = self._blocks.get(callback.ctype)
        self._parse_node_common(callback, block)
        self._parse_params(callback, callback.parameters, block)
        self._parse_return(callback, callback.retval, block)
        if block:
            callback.doc = block.comment

    def _parse_callable(self, callable, block):
        self._parse_node_common(callable, block)
        for i, param in enumerate(callable.parameters):
            if (param.type.ctype != 'GDestroyNotify' and
                param.type.name != 'GLib.DestroyNotify'):
                continue
            if i < 2:
                break
            callback_param = callable.parameters[i-2]
            if callback_param.closure_index != -1:
                callback_param.scope = OPT_SCOPE_NOTIFIED
                callback_param.transfer = PARAM_TRANSFER_NONE

        self._parse_params(callable, callable.parameters, block)
        self._parse_return(callable, callable.retval, block)
        if block:
            callable.doc = block.comment

    def _parse_function(self, func):
        block = self._blocks.get(func.symbol)
        self._parse_callable(func, block)
        self._parse_rename_to_func(func, block)

    def _parse_signal(self, parent, signal):
        block = self._blocks.get('%s::%s' % (parent.type_name, signal.name))
        self._parse_node_common(signal, block)
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
                    param.type = self._resolve(param_type.one(), param.type)
            else:
                tag = None
            self._parse_param(signal, param, tag)
        self._parse_return(signal, signal.retval, block)
        if block:
            signal.doc = block.comment

    def _parse_method(self, parent, meth):
        block = self._blocks.get(meth.symbol)
        self._parse_function(meth)
        virtual = self._get_tag(block, TAG_VFUNC)
        if virtual:
            invoker_name = virtual.value
            matched = False
            for vfunc in parent.virtual_methods:
                if vfunc.name == invoker_name:
                    matched = True
                    vfunc.invoker = meth.name
                    break
            if not matched:
                print "warning: unmatched virtual invoker %r for method %r" % \
                    (invoker_name, meth.symbol)

    def _parse_vfunc(self, parent, vfunc):
        key = '%s::%s' % (parent.type_name, vfunc.name)
        self._parse_callable(vfunc, self._blocks.get(key))

    def _parse_field(self, parent, field, block=None):
        if isinstance(field, Callback):
            self._parse_callback(field)
        else:
            if not block:
                return
            tag = block.get(field.name)
            if not tag:
                return
            t = tag.options.get('type')
            if not t:
                return
            field.type.name = self._transformer.resolve_type_name(t.one())

    def _check_arg_annotations(self, parent, params, block):
        if block is None:
            return
        for tag in block.tags.keys():
            if tag == TAG_RETURNS:
                continue
            for param in params:
                if param.name == tag:
                    break
            else:
                return
                #print 'WARNING: annotation for "%s" refers to unknown ' \
                #        'argument "%s"' % (parent.name, tag)

    def _parse_params(self, parent, params, block):
        self._check_arg_annotations(parent, params, block)
        for param in params:
            tag = self._get_tag(block, param.name)
            self._parse_param(parent, param, tag)

    def _parse_return(self, parent, return_, block):
        tag = self._get_tag(block, TAG_RETURNS)
        self._parse_param_ret_common(parent, return_, tag)

    def _get_parameter_index(self, parent, param_name, location_name):
        index = parent.get_parameter_index(param_name)
        if index is None:
            raise InvalidAnnotationError(
                "can't find parameter %s referenced by parameter %s of %r"
                % (param_name, location_name, parent.name))

        return index

    def _parse_param(self, parent, param, tag):
        options = getattr(tag, 'options', {})
        if isinstance(parent, Function):
            scope = options.get(OPT_SCOPE)
            if scope:
                param.scope = scope.one()
                if param.scope not in [PARAM_SCOPE_CALL,
                                       PARAM_SCOPE_ASYNC,
                                       PARAM_SCOPE_NOTIFIED]:
                    raise InvalidAnnotationError(
                        "scope for %s of %r is invalid (%r), must be one of "
                        "call, async, notified."
                        % (param.name, parent.name, param.scope))
                param.transfer = PARAM_TRANSFER_NONE
            elif (param.type.ctype == 'GAsyncReadyCallback' or
                  param.type.name == 'Gio.AsyncReadyCallback'):
                param.scope = OPT_SCOPE_ASYNC
                param.transfer = PARAM_TRANSFER_NONE

            destroy = options.get(OPT_DESTROY)
            if destroy:
                param.destroy_index = self._get_parameter_index(parent,
                                                                destroy.one(),
                                                                param.name)
                self._fixup_param_destroy(parent, param)
            closure = options.get(OPT_CLOSURE)
            if closure:
                param.closure_index = self._get_parameter_index(parent,
                                                                closure.one(),
                                                                param.name)
                self._fixup_param_closure(parent, param)
        if isinstance(parent, Callback):
            if OPT_CLOSURE in options:
                # For callbacks, (closure) appears without an
                # argument, and tags a parameter that is a closure. We
                # represent it (weirdly) in the gir and typelib by
                # setting param.closure_index to its own index.
                param.closure_index = parent.get_parameter_index(param.name)
                self._fixup_param_closure(parent, param)

        self._parse_param_ret_common(parent, param, tag)

    def _fixup_param_destroy(self, parent, param):
        for p in parent.parameters:
            if p is not param and p.destroy_index == param.destroy_index:
                p.destroy_index = -1

    def _fixup_param_closure(self, parent, param):
        for p in parent.parameters:
            if p is not param and p.closure_index == param.closure_index:
                p.closure_index = -1

    def _parse_param_ret_common(self, parent, node, tag):
        options = getattr(tag, 'options', {})
        (node.direction, node.caller_allocates) = \
            self._extract_direction(node, options)
        container_type = self._extract_container_type(
            parent, node, options)
        if container_type is not None:
            node.type = container_type
        if node.direction is None:
            node.direction = self._guess_direction(node)
            node.caller_allocates = False
        node.transfer = self._extract_transfer(parent, node, options)
        param_type = options.get(OPT_TYPE)
        if param_type:
            node.type = self._resolve(param_type.one(), node.type)

        if (OPT_ALLOW_NONE in options or
            node.type.ctype == 'GCancellable*'):
            node.allow_none = True

        assert node.transfer is not None
        if tag is not None and tag.comment is not None:
            node.doc = tag.comment

    def _extract_direction(self, node, options):
        caller_allocates = False
        if (OPT_INOUT in options or
            OPT_INOUT_ALT in options):
            direction = PARAM_DIRECTION_INOUT
        elif OPT_OUT in options:
            subtype = options[OPT_OUT]
            if subtype is not None:
                subtype = subtype.one()
            direction = PARAM_DIRECTION_OUT
            if subtype in (None, ''):
                if (node.type.name not in BASIC_GIR_TYPES) and node.type.ctype:
                    caller_allocates = '**' not in node.type.ctype
                else:
                    caller_allocates = False
            elif subtype == 'caller-allocates':
                caller_allocates = True
            elif subtype == 'callee-allocates':
                caller_allocates = False
            else:
                raise InvalidAnnotationError(
                    "out direction for %s is invalid (%r)" % (node, subtype))
        elif OPT_IN in options:
            direction = PARAM_DIRECTION_IN
        else:
            direction = node.direction
        return (direction, caller_allocates)

    def _guess_array(self, node):
        ctype = node.type.ctype
        if ctype is None:
            return False
        if not ctype.endswith('*'):
            return False
        if node.type.canonical in default_array_types:
            return True
        return False

    def _is_array_type(self, node):
        if node.type.name in ['GLib.Array', 'GLib.PtrArray',
                              'GLib.ByteArray']:
            return True
        if node.type.ctype in ['GArray*', 'GPtrArray*', 'GByteArray*']:
            return True
        return False

    def _extract_container_type(self, parent, node, options):
        has_element_type = OPT_ELEMENT_TYPE in options
        has_array = OPT_ARRAY in options

        if not has_array:
            has_array = self._is_array_type(node)

        # FIXME: This is a hack :-(
        if (not isinstance(node, Field) and
            (not has_element_type and
             (node.direction is None
              or isinstance(node, Return)
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

        is_g_array = (node.type.ctype.startswith('GArray*') or
                      node.type.ctype.startswith('GPtrArray*') or
                      node.type.ctype.startswith('GByteArray*'))

        element_type = options.get(OPT_ELEMENT_TYPE)
        if element_type is not None:
            element_type_node = self._resolve(element_type.one())
        else:
            if is_g_array:
                element_type_node = None
            else:
                element_type_node = Type(node.type.name) # erase ctype

        if is_g_array:
            type_name = node.type.name
        else:
            type_name = None

        container_type = Array(type_name, node.type.ctype,
                               element_type_node)
        container_type.is_const = node.type.is_const
        if OPT_ARRAY_ZERO_TERMINATED in array_values:
            container_type.zeroterminated = array_values.get(
                OPT_ARRAY_ZERO_TERMINATED) == '1'
        length = array_values.get(OPT_ARRAY_LENGTH)
        if length is not None:
            param_index = self._get_parameter_index(parent, length, node.name)
            container_type.length_param_index = param_index
            # For in parameters we're incorrectly deferring
            # char/unsigned char to utf8 when a length annotation
            # is specified.
            if (isinstance(node, Parameter) and
                node.type.name == 'utf8' and
                self._guess_direction(node) == PARAM_DIRECTION_IN and
                element_type is None):
                # FIXME: unsigned char/guchar should be uint8
                container_type.element_type = Type('int8')
        container_type.size = array_values.get(OPT_ARRAY_FIXED_SIZE)
        return container_type

    def _resolve(self, type_str, orig_node=None):
        def grab_one(type_str, resolver, top_combiner, combiner):
            """Return a complete type, and the trailing string part after it.
            Use resolver() on each identifier, and combiner() on the parts of
            each complete type. (top_combiner is used on the top-most type.)"""
            bits = re.split(r'([,<>])', type_str, 1)
            first, sep, rest = [bits[0], '', ''] if (len(bits)==1) else bits
            args = [resolver(first)]
            if sep == '<':
                while sep != '>':
                    next, rest = grab_one(rest, resolver, combiner, combiner)
                    args.append(next)
                    sep, rest = rest[0], rest[1:]
            else:
                rest = sep + rest
            return top_combiner(*args), rest
        def resolver(ident):
            return self._transformer.resolve_param_type(Type(ident))
        def combiner(base, *rest):
            if not rest:
                return base
            if (base.name in ['GLib.List', 'GLib.SList'] or
                base.ctype in ['GList*', 'GSList*']) and len(rest)==1:
                return List(base.name, base.ctype, *rest)
            if (base.name in ['GLib.HashTable'] or
                base.ctype in ['GHashTable*']) and len(rest)==2:
                return Map(base.name, base.ctype, *rest)
            print "WARNING: throwing away type parameters:", type_str
            return base
        def top_combiner(base, *rest):
            """For the top most type, recycle orig_node if possible."""
            if orig_node is not None:
                orig_node.name = base.name
                base = orig_node # preserve other properties of orig_node
            return combiner(base, *rest)

        result, rest = grab_one(type_str, resolver, top_combiner, combiner)
        if rest:
            print "WARNING: throwing away trailing part of type:", type_str
        return result

    def _parse_element_type(self, parent, node, options):
        element_type_opt = options.get(OPT_ELEMENT_TYPE)
        element_type = element_type_opt.flat()
        if (node.type.name in ['GLib.List', 'GLib.SList'] or
            node.type.ctype in ['GList*', 'GSList*']):
            assert len(element_type) == 1
            container_type = List(
                node.type.name,
                node.type.ctype,
                self._resolve(element_type[0]))
        elif (node.type.name in ['GLib.HashTable'] or
              node.type.ctype in ['GHashTable*']):
            assert len(element_type) == 2
            container_type = Map(
                node.type.name,
                node.type.ctype,
                self._resolve(element_type[0]),
                self._resolve(element_type[1]))
        elif self._is_array_type(node):
            container_type = Array(node.type.name,
                                   node.type.ctype,
                                   self._resolve(element_type[0]))
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

    def _parse_node_common(self, node, block):
        self._parse_version(node, block)
        self._parse_deprecated(node, block)
        self._parse_attributes(node, block)
        self._parse_skip(node, block)
        self._parse_foreign(node, block)

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

    def _parse_attributes(self, node, block):
        annos_tag = self._get_tag(block, TAG_ATTRIBUTES)
        if annos_tag is None:
            return
        for key, value in annos_tag.options.iteritems():
            if value:
                node.attributes.append((key, value.one()))

    def _parse_skip(self, node, block):
        if block is not None:
            if OPT_SKIP in block.options:
                node.skip = True

    def _parse_foreign(self, node, block):
        if block is not None:
            if OPT_FOREIGN in block.options:
                node.foreign = True

    def _parse_rename_to_func(self, node, block):
        rename_to_tag = self._get_tag(block, TAG_RENAME_TO)
        if rename_to_tag is None:
            return
        new_name = rename_to_tag.value

        shadowed = []

        def shadowed_filter(n):
            if isinstance(n, Function) and n.symbol == new_name:
                shadowed.append(n)
                return False
            return True

        self._namespace.remove_matching(shadowed_filter)
        if len(shadowed) == 1:
            # method override; use the same (stripped) name as the overloaded
            # method referenced.
            # Note that 'g_timeout_add_full' may specify a new_name of
            # 'g_timeout_add' but the *real* name desired is the stripped name
            # of 'g_timeout_add' which is 'timeout_add' (for example).
            node.name = shadowed[0].name
        elif len(shadowed) == 0:
            # literal rename, to force a particular prefix strip or whatever
            # Example: the "nm-utils" package uses a "NM" prefix in most places
            # but some functions have an "nm_utils_" prefix; the 'Rename To:'
            # annotation in this case is used to strip the 'utils_' part off.
            node.name = new_name
        else:
            assert False # more than two shadowed methods?  Shouldn't happen.

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
                if node.caller_allocates:
                    return PARAM_TRANSFER_NONE
                return PARAM_TRANSFER_FULL
            # This one is a hack for compatibility; the transfer
            # for string parameters really has no defined meaning.
            elif node.type.canonical == 'utf8':
                return PARAM_TRANSFER_FULL
            else:
                return PARAM_TRANSFER_NONE
        elif isinstance(node, Return):
            if (isinstance(node.type, Array) and
                    node.type.element_type is not None and
                    node.type.element_type.name == 'utf8'):
                return PARAM_TRANSFER_FULL
            elif (node.type.canonical in BASIC_GIR_TYPES or
                (node.type.canonical in [TYPE_NONE, TYPE_ANY] and
                 node.type.is_const)):
                return PARAM_TRANSFER_NONE
            else:
                return PARAM_TRANSFER_FULL
        elif isinstance(node, Field):
            return PARAM_TRANSFER_NONE
        else:
            raise AssertionError(node)
