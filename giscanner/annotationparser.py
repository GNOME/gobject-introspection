# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008-2010 Johan Dahlin
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

# AnnotationParser - extract annotations from gtk-doc comments

import re

from . import message
from .odict import odict

# Tags - annotations applied to comment blocks
TAG_VFUNC = 'virtual'
TAG_SINCE = 'since'
TAG_STABILITY = 'stability'
TAG_DEPRECATED = 'deprecated'
TAG_RETURNS = 'returns'
TAG_ATTRIBUTES = 'attributes'
TAG_RENAME_TO = 'rename to'
TAG_TYPE = 'type'
TAG_UNREF_FUNC = 'unref func'
TAG_REF_FUNC = 'ref func'
TAG_SET_VALUE_FUNC = 'set value func'
TAG_GET_VALUE_FUNC = 'get value func'
TAG_TRANSFER = 'transfer'
TAG_VALUE = 'value'
_ALL_TAGS = [TAG_VFUNC,
             TAG_SINCE,
             TAG_STABILITY,
             TAG_DEPRECATED,
             TAG_RETURNS,
             TAG_ATTRIBUTES,
             TAG_RENAME_TO,
             TAG_TYPE,
             TAG_UNREF_FUNC,
             TAG_REF_FUNC,
             TAG_SET_VALUE_FUNC,
             TAG_GET_VALUE_FUNC,
             TAG_TRANSFER,
             TAG_VALUE]

# Options - annotations for parameters and return values
OPT_ALLOW_NONE = 'allow-none'
OPT_ARRAY = 'array'
OPT_ATTRIBUTE = 'attribute'
OPT_CLOSURE = 'closure'
OPT_DESTROY = 'destroy'
OPT_ELEMENT_TYPE = 'element-type'
OPT_FOREIGN = 'foreign'
OPT_IN = 'in'
OPT_INOUT = 'inout'
OPT_INOUT_ALT = 'in-out'
OPT_OUT = 'out'
OPT_SCOPE = 'scope'
OPT_TRANSFER = 'transfer'
OPT_TYPE = 'type'
OPT_SKIP = 'skip'
OPT_CONSTRUCTOR = 'constructor'
OPT_METHOD = 'method'

ALL_OPTIONS = [
    OPT_ALLOW_NONE,
    OPT_ARRAY,
    OPT_ATTRIBUTE,
    OPT_CLOSURE,
    OPT_DESTROY,
    OPT_ELEMENT_TYPE,
    OPT_FOREIGN,
    OPT_IN,
    OPT_INOUT,
    OPT_INOUT_ALT,
    OPT_OUT,
    OPT_SCOPE,
    OPT_TRANSFER,
    OPT_TYPE,
    OPT_SKIP,
    OPT_CONSTRUCTOR,
    OPT_METHOD]

# Array options - array specific annotations
OPT_ARRAY_FIXED_SIZE = 'fixed-size'
OPT_ARRAY_LENGTH = 'length'
OPT_ARRAY_ZERO_TERMINATED = 'zero-terminated'

# Out options
OPT_OUT_CALLER_ALLOCATES = 'caller-allocates'
OPT_OUT_CALLEE_ALLOCATES = 'callee-allocates'

# Scope options
OPT_SCOPE_ASYNC = 'async'
OPT_SCOPE_CALL = 'call'
OPT_SCOPE_NOTIFIED = 'notified'

# Transfer options
OPT_TRANSFER_NONE = 'none'
OPT_TRANSFER_CONTAINER = 'container'
OPT_TRANSFER_FULL = 'full'
OPT_TRANSFER_FLOATING = 'floating'


class DocBlock(object):

    def __init__(self, name):
        self.name = name
        self.options = DocOptions()
        self.value = None
        self.tags = odict()
        self.comment = None
        self.params = []
        self.position = None

    def __cmp__(self, other):
        return cmp(self.name, other.name)

    def __repr__(self):
        return '<DocBlock %r %r>' % (self.name, self.options)

    def set_position(self, position):
        self.position = position
        self.options.position = position

    def get(self, name):
        return self.tags.get(name)

    def to_gtk_doc(self):
        options = ''
        if self.options:
            options += ' '
            options += ' '.join('(%s)' % o for o in self.options)
        lines = [self.name]
        if 'SECTION' not in self.name:
            lines[0] += ':'
        lines[0] += options
        tags = []
        for name, tag in self.tags.iteritems():
            if name in self.params:
                lines.append(tag.to_gtk_doc_param())
            else:
                tags.append(tag)

        lines.append('')
        for l in self.comment.split('\n'):
            lines.append(l)
        if tags:
            lines.append('')
            for tag in tags:
                lines.append(tag.to_gtk_doc_tag())

        comment = ''
        #comment += '# %d \"%s\"\n' % (
        #    self.position.line,
        #    self.position.filename)
        comment += '/**\n'
        for line in lines:
            line = line.rstrip()
            if line:
                comment += ' * %s\n' % (line, )
            else:
                comment += ' *\n'
        comment += ' */\n'
        return comment

    def validate(self):
        for tag in self.tags.values():
            tag.validate()


class DocTag(object):

    def __init__(self, block, name):
        self.block = block
        self.name = name
        self.options = DocOptions()
        self.comment = None
        self.value = ''
        self.position = None

    def __repr__(self):
        return '<DocTag %r %r>' % (self.name, self.options)

    def _validate_option(self, name, value, required=False,
                         n_params=None, choices=None):
        if required and value is None:
            message.warn('%s annotation needs a value' % (
                name, ), self.position)
            return

        if n_params is not None:
            if n_params == 0:
                s = 'no value'
            elif n_params == 1:
                s = 'one value'
            else:
                s = '%d values' % (n_params, )
            if ((n_params > 0 and (value is None or value.length() != n_params)) or
                n_params == 0 and value is not None):
                if value is None:
                    length = 0
                else:
                    length = value.length()
                message.warn('%s annotation needs %s, not %d' % (
                    name, s, length), self.position)
                return

        if choices is not None:
            valuestr = value.one()
            if valuestr not in choices:
                message.warn('invalid %s annotation value: %r' % (
                    name, valuestr, ), self.position)
                return

    def set_position(self, position):
        self.position = position
        self.options.position = position

    def _get_gtk_doc_value(self):
        def serialize_one(option, value, fmt, fmt2):
            if value:
                if type(value) != str:
                    value = ' '.join((serialize_one(k, v, '%s=%s', '%s')
                                      for k, v in value.all().iteritems()))
                return fmt % (option, value)
            else:
                return fmt2 % (option, )
        annotations = []
        for option, value in self.options.iteritems():
            annotations.append(
                serialize_one(option, value, '(%s %s)', '(%s)'))
        if annotations:
            return ' '.join(annotations) + ': '
        else:
            return self.value

    def to_gtk_doc_param(self):
        return '@%s: %s%s' % (self.name, self._get_gtk_doc_value(), self.comment)

    def to_gtk_doc_tag(self):
        return '%s: %s%s' % (self.name.capitalize(),
                             self._get_gtk_doc_value(),
                             self.comment or '')

    def validate(self):
        for option in self.options:
            value = self.options[option]
            if option == OPT_ALLOW_NONE:
                self._validate_option('allow-none', value, n_params=0)
            elif option == OPT_ARRAY:
                if value is None:
                    continue
                for name, v in value.all().iteritems():
                    if name in [OPT_ARRAY_ZERO_TERMINATED, OPT_ARRAY_FIXED_SIZE]:
                        try:
                            int(v)
                        except (TypeError, ValueError):
                            if v is None:
                                message.warn(
                                    'array option %s needs a value' % (
                                    name, ),
                                    positions=self.position)
                            else:
                                message.warn(
                                    'invalid array %s option value %r, '
                                    'must be an integer' % (name, v, ),
                                    positions=self.position)
                            continue
                    elif name == OPT_ARRAY_LENGTH:
                        if v is None:
                            message.warn(
                                'array option length needs a value',
                                positions=self.position)
                            continue
                    else:
                        message.warn(
                            'invalid array annotation value: %r' % (
                            name, ), self.position)

            elif option == OPT_ATTRIBUTE:
                self._validate_option('attribute', value, n_params=2)
            elif option == OPT_CLOSURE:
                if value is not None and value.length() > 1:
                    message.warn(
                        'closure takes at maximium 1 value, %d given' % (
                        value.length()), self.position)
                    continue
            elif option == OPT_DESTROY:
                self._validate_option('destroy', value, n_params=1)
            elif option == OPT_ELEMENT_TYPE:
                self._validate_option('element-type', value, required=True)
                if value is None:
                    message.warn(
                        'element-type takes at least one value, none given',
                        self.position)
                    continue
                if value.length() > 2:
                    message.warn(
                        'element-type takes at maximium 2 values, %d given' % (
                        value.length()), self.position)
                    continue
            elif option == OPT_FOREIGN:
                self._validate_option('foreign', value, n_params=0)
            elif option == OPT_IN:
                self._validate_option('in', value, n_params=0)
            elif option in [OPT_INOUT, OPT_INOUT_ALT]:
                self._validate_option('inout', value, n_params=0)
            elif option == OPT_OUT:
                if value is None:
                    continue
                if value.length() > 1:
                    message.warn(
                        'out annotation takes at maximium 1 value, %d given' % (
                        value.length()), self.position)
                    continue
                value_str = value.one()
                if value_str not in [OPT_OUT_CALLEE_ALLOCATES,
                                     OPT_OUT_CALLER_ALLOCATES]:
                    message.warn("out annotation value is invalid: %r" % (
                        value_str), self.position)
                    continue
            elif option == OPT_SCOPE:
                self._validate_option(
                    'scope', value, required=True,
                    n_params=1,
                    choices=[OPT_SCOPE_ASYNC,
                             OPT_SCOPE_CALL,
                             OPT_SCOPE_NOTIFIED])
            elif option == OPT_SKIP:
                self._validate_option('skip', value, n_params=0)
            elif option == OPT_TRANSFER:
                self._validate_option(
                    'transfer', value, required=True,
                    n_params=1,
                    choices=[OPT_TRANSFER_FULL,
                             OPT_TRANSFER_CONTAINER,
                             OPT_TRANSFER_NONE,
                             OPT_TRANSFER_FLOATING])
            elif option == OPT_TYPE:
                self._validate_option('type', value, required=True,
                                      n_params=1)
            elif option == OPT_CONSTRUCTOR:
                self._validate_option('constructor', value, n_params=0)
            elif option == OPT_METHOD:
                self._validate_option('method', value, n_params=0)
            else:
                message.warn('invalid annotation option: %s' % (option, ),
                             self.position)


class DocOptions(object):
    def __init__(self):
        self.values = []

    def __getitem__(self, item):
        for key, value in self.values:
            if key == item:
                return value
        raise KeyError

    def __nonzero__(self):
        return bool(self.values)

    def __iter__(self):
        return (k for k, v in self.values)

    def add(self, name, value):
        self.values.append((name, value))

    def get(self, item, default=None):
        for key, value in self.values:
            if key == item:
                return value
        return default

    def getall(self, item):
        for key, value in self.values:
            if key == item:
                yield value

    def iteritems(self):
        return iter(self.values)


class DocOption(object):

    def __init__(self, tag, option):
        self.tag = tag
        self._array = []
        self._dict = {}
        # (annotation option1=value1 option2=value2) etc
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
        return '<DocOption %r>' % (self._array, )

    def length(self):
        return len(self._array)

    def one(self):
        assert len(self._array) == 1
        return self._array[0]

    def flat(self):
        return self._array

    def all(self):
        return self._dict


class AnnotationParser(object):
    PARAM_FIELD_COUNT = 2

    COMMENT_BLOCK_RE = re.compile(r'^\s*/\*\*\s')
    COMMENT_BLOCK_END_RE = re.compile(r'^\s*\*+/')
    COMMENT_STAR_RE = re.compile(r'^\s*\*\s?')
    SYMBOL_SECTION_RE = re.compile(r'^\s*(SECTION:\s*\S+)')
    SYMBOL_RE = re.compile(r'^\s*([\w:-]*\w)\s*:?\s*(\([a-z ]+\)\s*)*$')
    DESCRIPTION_RE = re.compile(r'^\s*Description:')
    RETURNS_RE = re.compile(r'^\s*(returns:|return\s+value:)', re.IGNORECASE)
    BROKEN_RETURNS_RE = re.compile(r'^\s*(returns\b\s*)', re.IGNORECASE)
    SINCE_RE = re.compile(r'^\s*since:', re.IGNORECASE)
    DEPRECATED_RE = re.compile(r'^\s*deprecated:', re.IGNORECASE)
    STABILITY_RE = re.compile(r'^\s*stability:', re.IGNORECASE)
    EMPTY_LINE_RE = re.compile(r'^\s*$')
    PARAMETER_NAME_RE = re.compile(r'^\s*@(\S+)\s*:\s*')
    VARARGS_RE = re.compile(r'^.*\.\.\.$')

    def __init__(self):
        self._blocks = {}

    def parse(self, comments):
        in_comment_block = False
        symbol = ''
        symbol_options = ''
        in_description = False
        in_return = False
        in_since = False
        in_stability = False
        in_deprecated = False
        in_part = ''
        description = ''
        return_desc = ''
        return_start = ''
        return_style = ''
        since_desc = ''
        deprecated_desc = ''
        stability_desc = ''
        deprecated_desc = ''
        current_param = 0
        ignore_broken_returns = False
        params = odict()

        for comment in comments:
            comment, filename, lineno = comment

            for line in comment.split('\n'):
                line += '\n'

                # Check if we are at the start of a comment block
                if not in_comment_block:
                    if self.COMMENT_BLOCK_RE.search(line):
                        in_comment_block = True

                        # Reset all the symbol data
                        symbol = ''
                        symbol_options = ''
                        in_description = False
                        in_return = False
                        in_since = False
                        in_stability = False
                        in_deprecated = False
                        in_part = ''
                        description = ''
                        return_desc = ''
                        return_start = ''
                        return_style = ''
                        since_desc = ''
                        deprecated_desc = ''
                        stability_desc = ''
                        deprecated_desc = ''
                        current_param = 0
                        ignore_broken_returns = False
                        params = odict()

                    continue

                # Check if we are at the end of a comment block
                if self.COMMENT_BLOCK_END_RE.search(line):
                    if not symbol:
                        # maybe its not even meant to be a gtk-doc comment?
                        pass
                    else:
                        block = DocBlock(symbol)
                        block.set_position(message.Position(filename, lineno))
                        block.comment = description.strip()

                        if symbol_options:
                            block.options = self.parse_options(block, symbol_options)

                        for param_name, param_desc in params.iteritems():
                            tag = DocTag(block, param_name)
                            tag.set_position(lineno)
                            block.tags[param_name] = tag

                        # Add the return value description onto the end of the params.
                        if return_desc:
                            tag = DocTag(block, TAG_RETURNS)
                            tag.value = return_desc.strip()
                            block.tags[TAG_RETURNS] = tag

                            if return_style == 'broken':
                                pass

                        # gtk-doc handles Section docs here, but we have no need
                        # for them...

                        if since_desc:
                            tag = DocTag(block, TAG_SINCE)
                            tag.value = since_desc.strip()
                            block.tags[TAG_SINCE] = tag

                        if stability_desc:
                            tag = DocTag(block, TAG_STABILITY)
                            tag.value = stability_desc.strip()
                            block.tags[TAG_STABILITY] = tag

                        if deprecated_desc:
                            tag = DocTag(block, TAG_DEPRECATED)
                            tag.value = deprecated_desc.strip()
                            block.tags[TAG_DEPRECATED] = tag

                        block.validate()
                        self._blocks[symbol] = block

                        in_comment_block = False
                        continue

                # Get rid of ' * ' at start of every line in the comment block.
                line = re.sub(self.COMMENT_STAR_RE, '', line)
                # But make sure we don't get rid of the newline at the end.
                if not line.endswith('\n'):
                    line += '\n'

                # If we haven't found the symbol name yet, look for it.
                if not symbol:
                    symbol_section_match = self.SECTION_RE.search(line)
                    symbol_match = self.SYMBOL_RE.search(line)

                    if symbol_section_match:
                        symbol = symbol_section_match.group(1)
                        ignore_broken_returns = True
                    elif symbol_match:
                        symbol = symbol_match.group(1).strip()
                        symbol_options = line[symbol_match.end(0):].strip()

                    continue

                return_match = self.RETURNS_RE.search(line)
                broken_return_match = self.BROKEN_RETURNS_RE.search(line)
                since_match = self.SINCE_RE.search(line)
                deprecated_match = self.DEPRECATED_RE.search(line)
                stability_match = self.STABILITY_RE.search(line)

                if return_match:
                    if return_style == 'broken':
                        description += return_start + return_desc

                    return_start = return_match.group(0)

                    if return_style == 'sane':
                        pass

                    return_style = 'sane'
                    ignore_broken_returns = True
                    return_desc = line[return_match.end(0):]
                    in_part = 'return'
                    continue
                elif not ignore_broken_returns and broken_return_match:
                    return_start = broken_return_match.group(0)
                    return_style = 'broken'
                    return_desc = line[broken_return_match.end(0):]
                    in_part = 'return'
                    continue
                elif since_match:
                    since_desc = line[since_match.end(0):]
                    in_part = 'since'
                    continue
                elif deprecated_match:
                    deprecated_desc = line[deprecated_match.end(0):]
                    in_part = 'deprecated'
                    continue
                elif stability_match:
                    stability_desc = line[stability_match.end(0):]
                    in_part = 'stability'
                    continue

                if in_part == 'description':
                    # Get rid of 'Description:'
                    line = re.sub(self.DESCRIPTION_RE, '', line)
                    description += line
                    continue
                elif in_part == 'return':
                    return_desc += line
                    continue
                elif in_part == 'since':
                    since_desc += line
                    continue
                elif in_part == 'stability':
                    stability_desc += line
                    continue
                elif in_part == 'deprecated':
                    deprecated_desc += line
                    continue

                # We must be in the parameters. Check for the empty line below them.
                if self.EMPTY_LINE_RE.search(line):
                    in_part = 'description'
                    continue

                # Look for a parameter name.
                match = self.PARAMETER_NAME_RE.search(line)
                if match:
                    param_name = match.group(1)
                    param_desc = line[match.end(0):]

                    # Allow varargs variations
                    if self.VARARGS_RE.search(param_name):
                        param_name = '...'
                    if param_name.lower() == 'returns':
                        return_style = 'sane'
                        ignore_broken_returns = True

                    params[param_name] = param_desc
                    current_param += 1
                    continue

                # We must be in the middle of a parameter description, so add it on
                # to the last element in @params.
                if current_param:
                    params[params.keys()[-1]] += line
                else:
                    pass

        return self._blocks


    @classmethod
    def parse_options(cls, tag, value):
        # (foo)
        # (bar opt1 opt2...)
        opened = -1
        options = DocOptions()
        options.position = tag.position
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
                    option = DocOption(tag, option)
                options.add(name, option)
                last = i + 2
                opened = -1

        return options
