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

# Tags - annotations applyed to comment blocks
TAG_VFUNC = 'virtual'
TAG_SINCE = 'since'
TAG_DEPRECATED = 'deprecated'
TAG_RETURNS = 'returns'
TAG_ATTRIBUTES = 'attributes'
TAG_RENAME_TO = 'rename to'
TAG_TYPE = 'type'
TAG_UNREF_FUNC = 'unref func'
TAG_REF_FUNC = 'ref func'
TAG_SET_VALUE_FUNC = 'set value func'
TAG_GET_VALUE_FUNC = 'get value func'

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
                             OPT_TRANSFER_NONE])
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
    COMMENT_HEADER_RE = re.compile(r'^\*[ \t]*\n ')
    WHITESPACE_RE = re.compile(r'^\s*$')
    ASCII_TEXT_RE = re.compile(r'\s*[A-Za-z]+')
    OPTION_RE = re.compile(r'\([A-Za-z]+[^(]*\)')
    RETURNS_RE = re.compile(r'^return(s?)( value)?:', re.IGNORECASE)

    def __init__(self):
        self._blocks = {}

    def parse(self, comments):
        for comment in comments:
            self._parse_comment(comment)
        return self._blocks

    def _parse_comment(self, cmt):
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
        comment, filename, lineno = cmt
        comment = comment.lstrip()
        if not self.COMMENT_HEADER_RE.search(comment):
            return
        comment = self.COMMENT_HEADER_RE.sub('', comment, count=1)
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
        block_name = block_header
        raw_name = block_header
        if cpos != -1:
            block_name = block_name[:cpos].strip()
        if block_name.endswith(':'):
            block_name = block_name[:-1]
        block = DocBlock(block_name)
        block.set_position(message.Position(filename, lineno))

        if cpos:
            block.options = self.parse_options(block, block_header[cpos+2:])
        comment_lines = []
        parsing_parameters = True
        last_param_tag = None

        # Second phase: parse parameters, return values, Tag: format
        # annotations.
        #
        # Valid lines look like:
        # * @foo: some comment here
        # * @baz: (inout): This has an annotation
        # * @bar: (out) (allow-none): this is a long parameter comment
        # *  that gets wrapped to the next line.
        # *
        # * Some documentation for the function.
        # *
        # * Returns: (transfer none): A value

        # offset of the first doctag in relation to the start of
        # the docblock, we parsed /** and the xxx: lines already
        lineno = 2
        for line in comment[pos+1:].split('\n'):
            line = line.lstrip()
            if (not line.startswith('*') or
                self.WHITESPACE_RE.match(line[1:])):
                # As soon as we find a line that's just whitespace,
                # we're done parsing the parameters.
                parsing_parameters = False
                lineno += 1
                continue

            line = line[1:].lstrip()

            # Look for a parameter or return value.  Both of these can
            # have parenthesized options.
            first_colonspace_index = line.find(': ')
            is_parameter = line.startswith('@')
            is_return_value = self.RETURNS_RE.search(line)
            parse_options = True
            if ((is_parameter or is_return_value)
                and first_colonspace_index > 0):
                # Skip lines which has non-whitespace before first (
                first_paren = line[first_colonspace_index+1:].find('(')
                if (first_paren != -1 and
                    line[first_colonspace_index+1:first_paren].strip()):
                    parse_options = False

                if is_parameter:
                    argname = line[1:first_colonspace_index]
                else:
                    argname = TAG_RETURNS
                tag = DocTag(block, argname)
                tag.set_position(block.position.offset(lineno))
                line_after_first_colon_space = line[first_colonspace_index + 2:]
                second_colon_index = line_after_first_colon_space.find(':')
                if second_colon_index >= 0:
                    second_colon_index += first_colonspace_index + 2
                    assert line[second_colon_index] == ':'
                found_options = False
                if second_colon_index > first_colonspace_index:
                    value_line = \
                      line[first_colonspace_index+2:second_colon_index]
                    if ')' in value_line:
                        after_last_paren = value_line[value_line.rfind(')'):]
                        if not after_last_paren.rstrip().endswith(')'):
                            parse_options = False
                    if parse_options and self.OPTION_RE.search(value_line):
                        # The OPTION_RE is a little bit heuristic.  If
                        # we found two colons, we scan inside for something
                        # that looks like (foo).
                        # *Ideally* we'd change the gtk-doc format to
                        # require double colons, and then there'd be
                        # no ambiguity.  I.e.:
                        # @foo:: Some documentation here
                        # But that'd be a rather incompatible change.
                        found_options = True
                        tag.comment = line[second_colon_index+1:].strip()
                        tag.options = self.parse_options(tag, value_line)
                if not found_options:
                    # We didn't find any options, so just take the whole thing
                    # as documentation.
                    tag.comment = line[first_colonspace_index+2:].strip()
                block.tags[argname] = tag
                last_param_tag = tag
                if is_parameter:
                    block.params.append(argname)
            elif (not is_parameter) and parsing_parameters and last_param_tag:
                # We need to handle continuation lines on parameters.  The
                # conditional above - if a line doesn't start with '@', we're
                # not yet in the documentation block for the whole function,
                # and we've seen at least one parameter.
                last_param_tag.comment += (' ' + line.strip())
            elif first_colonspace_index > 0:
                # The line is of the form "Tag: some value here", like:
                # Since: 0.8
                tag_name = line[:first_colonspace_index]
                if self.ASCII_TEXT_RE.match(tag_name):
                    tag_name = tag_name.lower()
                    tag = DocTag(block, tag_name)
                    tag.value = line[first_colonspace_index+2:]
                    tag.position = block.position.offset(lineno)
                    block.tags[tag_name] = tag
                else:
                    comment_lines.append(line)
            elif (not is_parameter):
                comment_lines.append(line)
            lineno += 1
        block.comment = '\n'.join(comment_lines)
        block.validate()
        self._blocks[block.name] = block

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
