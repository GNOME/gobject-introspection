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

from .odict import odict

# All gtk-doc comments needs to start with this:
_COMMENT_HEADER = '*\n '

# Tags - annotations applyed to comment blocks
TAG_VFUNC = 'virtual'
TAG_SINCE = 'since'
TAG_DEPRECATED = 'deprecated'
TAG_RETURNS = 'returns'
TAG_ATTRIBUTES = 'attributes'
TAG_RENAME_TO = 'rename to'
TAG_TYPE = 'type'
TAG_TRANSFER = 'transfer'
TAG_UNREF_FUNC = 'unref func'
TAG_REF_FUNC = 'ref func'
TAG_SET_VALUE_FUNC = 'set value func'
TAG_GET_VALUE_FUNC = 'get value func'

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

# Array options - array specific annotations
OPT_ARRAY_FIXED_SIZE = 'fixed-size'
OPT_ARRAY_LENGTH = 'length'
OPT_ARRAY_ZERO_TERMINATED = 'zero-terminated'

OPT_SCOPE_ASYNC = 'async'
OPT_SCOPE_CALL = 'call'
OPT_SCOPE_NOTIFIED = 'notified'

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
        return self.tags.get(name)


class DocTag(object):

    def __init__(self, name):
        self.name = name
        self.options = {}
        self.comment = None
        self.value = ''

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
            block_options = self.parse_options(block_header[cpos+2:])
        else:
            block_name, block_options = block_header, {}
        block = DocBlock(block_name, block_options)
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
        for line in comment[pos+1:].split('\n'):
            line = line.lstrip()
            if (not line.startswith('*') or
                self.WHITESPACE_RE.match(line[1:])):
                # As soon as we find a line that's just whitespace,
                # we're done parsing the parameters.
                parsing_parameters = False
                continue

            line = line[1:].lstrip()

            # Look for a parameter or return value.  Both of these can
            # have parenthesized options.
            first_colonspace_index = line.find(': ')
            is_parameter = line.startswith('@')
            is_return_value = self.RETURNS_RE.search(line)
            if ((is_parameter or is_return_value)
                and first_colonspace_index > 0):
                if is_parameter:
                    argname = line[1:first_colonspace_index]
                else:
                    argname = TAG_RETURNS
                tag = DocTag(argname)
                second_colon_index = line.rfind(':')
                found_options = False
                if second_colon_index > first_colonspace_index:
                    value_line = \
                      line[first_colonspace_index+2:second_colon_index]
                    if self.OPTION_RE.search(value_line):
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
                        tag.options = self.parse_options(value_line)
                if not found_options:
                    # We didn't find any options, so just take the whole thing
                    # as documentation.
                    tag.comment = line[first_colonspace_index+2:].strip()
                block.tags[argname] = tag
                last_param_tag = tag
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
                    tag = DocTag(tag_name)
                    tag.value = line[first_colonspace_index+2:]
                    block.tags[tag_name] = tag
                else:
                    comment_lines.append(line)
            elif (not is_parameter):
                comment_lines.append(line)
        block.comment = '\n'.join(comment_lines)
        self._blocks[block.name] = block

    @classmethod
    def parse_options(cls, value):
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

        return options
