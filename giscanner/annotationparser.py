# -*- coding: utf-8 -*-
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008-2010 Johan Dahlin
# Copyright (C) 2012-2013 Dieter Verfaillie <dieterv@optionexplicit.be>
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


'''
GTK-Doc comment block format
----------------------------

A GTK-Doc comment block is built out of multiple parts. Each part can be further
divided into fields which are separated by a colon ("``:``") delimiter.

Known parts and the fields they are constructed from look like the following
(optional fields are enclosed in square brackets)::

    ┌───────────────────────────────────────────────────────────┐
    │ /**                                                       │ ─▷ start token
    ├────────────────────┬──────────────────────────────────────┤
    │  * identifier_name │ [: annotations]                      │ ─▷ identifier part
    ├────────────────────┼─────────────────┬────────────────────┤
    │  * @parameter_name │ [: annotations] │ : description      │ ─▷ parameter part
    ├────────────────────┴─────────────────┴────────────────────┤
    │  *                                                        │ ─▷ comment block description
    │  * comment_block_description                              │
    ├─────────────┬─────────────────┬───────────┬───────────────┤
    │  * tag_name │ [: annotations] │ [: value] │ : description │ ─▷ tag part
    ├─────────────┴─────────────────┴───────────┴───────────────┤
    │  */                                                       │ ─▷ end token
    └───────────────────────────────────────────────────────────┘

There are two conditions that must be met before a comment block is recognized
as a GTK-Doc comment block:

#. The comment block is opened with a GTK-Doc start token ("``/**``")
#. The first line following the start token contains a valid identifier part

Once a GTK-Doc comment block has been identified as such and has been stripped
from its start and end tokens the remaining parts have to be written in a
specific order:

#. There must be exactly 1 `identifier` part on the first line of the
   comment block which consists of:

   * a required `identifier_name` field
   * an optional `annotations` field

#. Zero or more `parameter` parts, each consisting of:

   * a required `parameter_name` field
   * an optional `annotations` field
   * a required `description` field (can be the empty string)

#. One optional `comment block description` part which must begin with at
   least 1 empty line signaling the start of this part.

#. Zero or more `tag` parts, each consisting of:

   * a required `tag_name` field
   * an optional `annotations` field
   * an optional `value` field
   * a required `description` field (can be the empty string)

Additionally, the following restrictions are in effect:

#. Separating parts with an empty line:

   * `identifier` and `parameter` parts cannot be separated from each other by
     an empty line as this would signal the start of the
     `comment block description` part (see above).
   * it is required to separate the `comment block description` part from the
     `identifier` or `parameter` parts with an empty line (see above)
   * `comment block description` and `tag` parts can optionally be separated
     by an empty line

#. Parts and fields cannot span multiple lines, except for:

   * the `comment_block_description` part
   * `parameter description` and `tag description` fields

#. Taking the above restrictions into account, spanning multiple paragraphs is
   limited to the `comment block description` part and `tag description` fields.

Refer to the `GTK-Doc manual`_ for more detailed usage information.

.. _GTK-Doc manual:
        http://developer.gnome.org/gtk-doc-manual/1.18/documenting.html.en
'''


import re

from . import message
from .collections import OrderedDict


# GTK-Doc comment block parts
PART_IDENTIFIER = 'identifier'
PART_PARAMETERS = 'parameters'
PART_DESCRIPTION = 'description'
PART_TAGS = 'tags'

# Identifiers
IDENTIFIER_SECTION = 'section'
IDENTIFIER_SYMBOL = 'symbol'
IDENTIFIER_PROPERTY = 'property'
IDENTIFIER_SIGNAL = 'signal'

# Tags - annotations applied to comment blocks
TAG_VFUNC = 'virtual'
TAG_SINCE = 'since'
TAG_STABILITY = 'stability'
TAG_DEPRECATED = 'deprecated'
TAG_RETURNS = 'returns'
TAG_RETURNVALUE = 'return value'
TAG_DESCRIPTION = 'description'
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
             TAG_RETURNVALUE,
             TAG_DESCRIPTION,
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


#The following regular expression programs are built to:
# - match (or substitute) a single comment block line at a time;
# - support (but remains untested) LOCALE and UNICODE modes.

# Program matching the start of a comment block.
#
# Results in 0 symbolic groups.
COMMENT_START_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    /                                        # 1 forward slash character
    \*{2}                                    # exactly 2 asterisk characters
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Program matching the end of a comment block. We need to take care
# of comment ends that aren't on their own line for legacy support
# reasons. See https://bugzilla.gnome.org/show_bug.cgi?id=689354
#
# Results in 1 symbolic group:
#    - group 1 = description
COMMENT_END_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<description>.*?)                     # description text
    [^\S\n\r]*                               # 0 or more whitespace characters
    \*+                                      # 1 or more asterisk characters
    /                                        # 1 forward slash character
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Pattern matching the ' * ' at the beginning of every
# line inside a comment block.
COMMENT_ASTERISK_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    \*                                       # 1 asterisk character
    [^\S\n\r]?                               # 0 or 1 whitespace characters
                                             #   WARNING: removing more than 1
                                             #   whitespace character breaks
                                             #   embedded example program indentation
    ''',
    re.VERBOSE)

# Program matching the indentation at the beginning of every
# line (stripped from the ' * ') inside a comment block.
#
# Results in 1 symbolic group:
#   - group 1 = indentation
COMMENT_INDENTATION_RE = re.compile(
    r'''
    ^
    (?P<indentation>[^\S\n\r]*)              # 0 or more whitespace characters
    .*
    $
    ''',
    re.VERBOSE)

# Pattern matching an empty line.
EMPTY_LINE_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Program matching SECTION identifiers.
#
# Results in 2 symbolic groups:
#   - group 1 = colon
#   - group 2 = section_name
SECTION_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    SECTION                                  # SECTION
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<colon>:?)                            # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<section_name>\w\S+)?                 # section name
    [^\S\n\r]*                               # 0 or more whitespace characters
    $
    ''',
    re.VERBOSE)

# Program matching symbol (function, constant, struct and enum) identifiers.
#
# Results in 3 symbolic groups:
#   - group 1 = symbol_name
#   - group 2 = colon
#   - group 3 = annotations
SYMBOL_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<symbol_name>[\w-]*\w)                # symbol name
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<colon>:?)                            # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Program matching property identifiers.
#
# Results in 4 symbolic groups:
#   - group 1 = class_name
#   - group 2 = property_name
#   - group 3 = colon
#   - group 4 = annotations
PROPERTY_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<class_name>[\w]+)                    # class name
    [^\S\n\r]*                               # 0 or more whitespace characters
    :{1}                                     # required colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<property_name>[\w-]*\w)              # property name
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<colon>:?)                            # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Program matching signal identifiers.
#
# Results in 4 symbolic groups:
#   - group 1 = class_name
#   - group 2 = signal_name
#   - group 3 = colon
#   - group 4 = annotations
SIGNAL_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<class_name>[\w]+)                    # class name
    [^\S\n\r]*                               # 0 or more whitespace characters
    :{2}                                     # 2 required colons
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<signal_name>[\w-]*\w)                # signal name
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<colon>:?)                            # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Program matching parameters.
#
# Results in 4 symbolic groups:
#   - group 1 = parameter_name
#   - group 2 = annotations
#   - group 3 = colon
#   - group 4 = description
PARAMETER_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    @                                        # @ character
    (?P<parameter_name>[\w-]*\w|\.\.\.)      # parameter name
    [^\S\n\r]*                               # 0 or more whitespace characters
    :{1}                                     # required colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    (?P<colon>:?)                            # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<description>.*?)                     # description
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)

# Program matching tags.
#
# Results in 4 symbolic groups:
#   - group 1 = tag_name
#   - group 2 = annotations
#   - group 3 = colon
#   - group 4 = description
_all_tags = '|'.join(_ALL_TAGS).replace(' ', '\\ ')
TAG_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<tag_name>''' + _all_tags + r''')     # tag name
    [^\S\n\r]*                               # 0 or more whitespace characters
    :{1}                                     # required colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    (?P<colon>:?)                            # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<description>.*?)                     # description
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE | re.IGNORECASE)

# Program matching multiline annotation continuations.
# This is used on multiline parameters and tags (but not on the first line) to
# generate warnings about invalid annotations spanning multiple lines.
#
# Results in 3 symbolic groups:
#   - group 2 = annotations
#   - group 3 = colon
#   - group 4 = description
MULTILINE_ANNOTATION_CONTINUATION_RE = re.compile(
    r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    (?P<colon>:)                             # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<description>.*?)                     # description
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE)


class DocBlock(object):

    def __init__(self, name):
        self.name = name
        self.options = DocOptions()
        self.value = None
        self.tags = OrderedDict()
        self.comment = None
        self.params = OrderedDict()
        self.position = None

    def __cmp__(self, other):
        # Note: This is used by g-ir-annotation-tool, which does a ``sorted(blocks.values())``,
        #       meaning that keeping this around makes update-glib-annotations.py patches
        #       easier to review.
        return cmp(self.name, other.name)

    def __repr__(self):
        return '<DocBlock %r %r>' % (self.name, self.options)

    def to_gtk_doc(self):
        options = ''
        if self.options:
            options += ' '
            options += ' '.join('(%s)' % o for o in self.options)
        lines = [self.name]
        if 'SECTION' not in self.name:
            lines[0] += ':'
        lines[0] += options
        for param in self.params.values():
            lines.append(param.to_gtk_doc_param())
        if self.comment:
            lines.append('')
            for l in self.comment.split('\n'):
                lines.append(l)
        if self.tags:
            lines.append('')
            for tag in self.tags.values():
                lines.append(tag.to_gtk_doc_tag())

        comment = ''
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
        for param in self.params.values():
            param.validate()

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
            if ((n_params > 0 and (value is None or value.length() != n_params))
            or n_params == 0 and value is not None):
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

    def _validate_array(self, option, value):
        if value is None:
            return

        for name, v in value.all().items():
            if name in [OPT_ARRAY_ZERO_TERMINATED, OPT_ARRAY_FIXED_SIZE]:
                try:
                    int(v)
                except (TypeError, ValueError):
                    if v is None:
                        message.warn('array option %s needs a value' % (name, ),
                                     positions=self.position)
                    else:
                        message.warn('invalid array %s option value %r, '
                                     'must be an integer' % (name, v, ),
                                     positions=self.position)
            elif name == OPT_ARRAY_LENGTH:
                if v is None:
                    message.warn('array option length needs a value',
                                 positions=self.position)
            else:
                message.warn('invalid array annotation value: %r' % (name, ),
                             self.position)

    def _validate_closure(self, option, value):
        if value is not None and value.length() > 1:
            message.warn('closure takes at most 1 value, %d given' % (value.length(), ),
                         self.position)

    def _validate_element_type(self, option, value):
        self._validate_option(option, value, required=True)
        if value is None:
            message.warn('element-type takes at least one value, none given',
                         self.position)
            return
        if value.length() > 2:
            message.warn('element-type takes at most 2 values, %d given' % (value.length(), ),
                         self.position)
            return

    def _validate_out(self, option, value):
        if value is None:
            return
        if value.length() > 1:
            message.warn('out annotation takes at most 1 value, %d given' % (value.length(), ),
                         self.position)
            return
        value_str = value.one()
        if value_str not in [OPT_OUT_CALLEE_ALLOCATES,
                             OPT_OUT_CALLER_ALLOCATES]:
            message.warn("out annotation value is invalid: %r" % (value_str, ),
                         self.position)
            return

    def _get_gtk_doc_value(self):
        def serialize_one(option, value, fmt, fmt2):
            if value:
                if type(value) != str:
                    value = ' '.join((serialize_one(k, v, '%s=%s', '%s')
                                      for k, v in value.all().items()))
                return fmt % (option, value)
            else:
                return fmt2 % (option, )
        annotations = []
        for option, value in self.options.items():
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
        if self.name == TAG_ATTRIBUTES:
            # The 'Attributes:' tag allows free form annotations so the
            # validation below is most certainly going to fail.
            return

        for option, value in self.options.items():
            if option == OPT_ALLOW_NONE:
                self._validate_option(option, value, n_params=0)
            elif option == OPT_ARRAY:
                self._validate_array(option, value)
            elif option == OPT_ATTRIBUTE:
                self._validate_option(option, value, n_params=2)
            elif option == OPT_CLOSURE:
                self._validate_closure(option, value)
            elif option == OPT_DESTROY:
                self._validate_option(option, value, n_params=1)
            elif option == OPT_ELEMENT_TYPE:
                self._validate_element_type(option, value)
            elif option == OPT_FOREIGN:
                self._validate_option(option, value, n_params=0)
            elif option == OPT_IN:
                self._validate_option(option, value, n_params=0)
            elif option in [OPT_INOUT, OPT_INOUT_ALT]:
                self._validate_option(option, value, n_params=0)
            elif option == OPT_OUT:
                self._validate_out(option, value)
            elif option == OPT_SCOPE:
                self._validate_option(
                    option, value, required=True,
                    n_params=1,
                    choices=[OPT_SCOPE_ASYNC,
                             OPT_SCOPE_CALL,
                             OPT_SCOPE_NOTIFIED])
            elif option == OPT_SKIP:
                self._validate_option(option, value, n_params=0)
            elif option == OPT_TRANSFER:
                self._validate_option(
                    option, value, required=True,
                    n_params=1,
                    choices=[OPT_TRANSFER_FULL,
                             OPT_TRANSFER_CONTAINER,
                             OPT_TRANSFER_NONE,
                             OPT_TRANSFER_FLOATING])
            elif option == OPT_TYPE:
                self._validate_option(option, value, required=True,
                                      n_params=1)
            elif option == OPT_CONSTRUCTOR:
                self._validate_option(option, value, n_params=0)
            elif option == OPT_METHOD:
                self._validate_option(option, value, n_params=0)
            else:
                message.warn('invalid annotation option: %s' % (option, ),
                             self.position)


class DocOptions(object):
    def __init__(self):
        self.values = []
        self.position = None

    def __repr__(self):
        return '<DocOptions %r>' % (self.values, )

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

    def items(self):
        return iter(self.values)


class DocOption(object):

    def __init__(self, tag, option):
        self.tag = tag
        self._array = []
        self._dict = OrderedDict()
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
    """
    GTK-Doc comment block parser.

    Parses GTK-Doc comment blocks into a parse tree built out of :class:`DockBlock`,
    :class:`DocTag`, :class:`DocOptions` and :class:`DocOption` objects. This
    parser tries to accept malformed input whenever possible and does not emit
    syntax errors. However, it does emit warnings at the slightest indication
    of malformed input when possible. It is usually a good idea to heed these
    warnings as malformed input is known to result in invalid GTK-Doc output.

    A GTK-Doc comment block can be constructed out of multiple parts that can
    be combined to write different types of documentation.
    See `GTK-Doc's documentation`_ to learn more about possible valid combinations.
    Each part can be further divided into fields which are separated by `:` characters.

    Possible parts and the fields they are constructed from look like the
    following (optional fields are enclosed in square brackets):

    .. code-block:: c
        /**
         * identifier_name [:annotations]
         * @parameter_name [:annotations] [:description]
         *
         * comment_block_description
         * tag_name [:annotations] [:description]
         */

    The order in which the different parts have to be specified is important::

        - There has to be exactly 1 `identifier` part on the first line of the
          comment block which consists of:
              * an `identifier_name` field
              * an optional `annotations` field
        - Followed by 0 or more `parameters` parts, each consisting of:
              * a `parameter_name` field
              * an optional `annotations` field
              * an optional `description` field
        - Followed by at least 1 empty line signaling the beginning of
          the `comment_block_description` part
        - Followed by an optional `comment block description` part.
        - Followed by 0 or more `tag` parts, each consisting of:
              * a `tag_name` field
              * an optional `annotations` field
              * an optional `description` field

    Additionally, the following restrictions are in effect::

        - Parts can optionally be separated by an empty line, except between
          the `parameter` parts and the `comment block description` part where
          an empty line is required (see above).
        - Parts and fields cannot span multiple lines, except for
          `parameter descriptions`, `tag descriptions` and the
          `comment_block_description` fields.
        - `parameter descriptions` fields can not span multiple paragraphs.
        - `tag descriptions` and `comment block description` fields can
          span multiple paragraphs.

    .. NOTE:: :class:`AnnotationParser` functionality is heavily based on gtkdoc-mkdb's
        `ScanSourceFile()`_ function and is currently in sync with GTK-Doc
        commit `47abcd5`_.

    .. _GTK-Doc's documentation:
            http://developer.gnome.org/gtk-doc-manual/1.18/documenting.html.en
    .. _ScanSourceFile():
            http://git.gnome.org/browse/gtk-doc/tree/gtkdoc-mkdb.in#n3722
    .. _47abcd5: 47abcd53b8489ebceec9e394676512a181c1f1f6
    """

    def parse(self, comments):
        '''
        Parse multiple GTK-Doc comment blocks.

        :param comments: an iterable of ``(comment, filename, lineno)`` tuples
        :returns: a dictionary mapping identifier names to :class:`GtkDocCommentBlock` objects
        '''

        comment_blocks = {}

        for comment in comments:
            try:
                comment_block = self.parse_comment_block(comment)
            except Exception:
                message.warn('unrecoverable parse error, please file a GObject-Introspection '
                             'bug report including the complete comment block at the '
                             'indicated location.', message.Position(comment[1], comment[2]))
                continue

            if comment_block is not None:
                # Note: previous versions of this parser did not check
                # if an identifier was already stored in comment_blocks,
                # so when multiple comment blocks where encountered documenting
                # the same identifier the last one seen "wins".
                # Keep this behavior for backwards compatibility, but
                # emit a warning.
                if comment_block.name in comment_blocks:
                    message.warn("multiple comment blocks documenting '%s:' identifier." %
                                 (comment_block.name, ),
                                 comment_block.position)

                comment_blocks[comment_block.name] = comment_block

        return comment_blocks

    def parse_comment_block(self, comment):
        '''
        Parse a single GTK-Doc comment block.

        :param comment: string representing the GTK-Doc comment block including it's
                        start ("``/**``") and end ("``*/``") tokens.
        :returns: a :class:`DocBlock` object or ``None``
        '''

        comment, filename, lineno = comment

        # Assign line numbers to each line of the comment block,
        # which will later be used as the offset to calculate the
        # real line number in the source file
        comment_lines = list(enumerate(comment.split('\n')))

        # Check for the start the comment block.
        if COMMENT_START_RE.match(comment_lines[0][1]):
            del comment_lines[0]
        else:
            # Not a GTK-Doc comment block.
            return None

        # Check for the end the comment block.
        line_offset, line = comment_lines[-1]
        result = COMMENT_END_RE.match(line)
        if result:
            description = result.group('description')
            if description:
                comment_lines[-1] = (line_offset, description)
                position = message.Position(filename, lineno + line_offset)
                marker = ' ' * result.end('description') + '^'
                message.warn("Comments should end with */ on a new line:\n%s\n%s" %
                             (line, marker),
                             position)
            else:
                del comment_lines[-1]
        else:
            # Not a GTK-Doc comment block.
            return None

        # If we get this far, we must be inside something
        # that looks like a GTK-Doc comment block.
        return self._parse_comment_block(comment_lines, filename, lineno)

    def _parse_comment_block(self, comment_lines, filename, lineno):
        """
        Parses a single GTK-Doc comment block already stripped from its
        comment start (/**) and comment end (*/) marker lines.

        :param comment_lines: list of (line_offset, line) tuples representing a
                              GTK-Doc comment block already stripped from it's
                              start (/**) and end (*/) marker lines
        :param filename: source file name where the comment block originated from
        :param lineno:  line in the source file where the comment block starts
        :returns: a :class:`DocBlock` object or ``None``

        .. NOTE:: If you are tempted to refactor this method and split it
            further up (for example into _parse_identifier(), _parse_parameters(),
            _parse_description(), _parse_tags() methods) then please resist the
            urge. It is considered important that this method should be more or
            less easily comparable with gtkdoc-mkdb's `ScanSourceFile()`_ function.

            The different parsing steps are marked with a comment surrounded
            by `#` characters in an attempt to make it clear what is going on.

        .. _ScanSourceFile():
                http://git.gnome.org/browse/gtk-doc/tree/gtkdoc-mkdb.in#n3722
        """
        comment_block = None
        part_indent = None
        line_indent = None
        in_part = None
        identifier = None
        current_param = None
        current_tag = None
        returns_seen = False

        for line_offset, line in comment_lines:
            position = message.Position(filename, line_offset + lineno)

            # Store the original line (without \n) and column offset
            # so we can generate meaningful warnings later on.
            original_line = line
            column_offset = 0

            # Get rid of the ' * ' at the start of the line.
            result = COMMENT_ASTERISK_RE.match(line)
            if result:
                column_offset = result.end(0)
                line = line[result.end(0):]

            # Store indentation level of the line.
            result = COMMENT_INDENTATION_RE.match(line)
            line_indent = len(result.group('indentation').replace('\t', '  '))

            ####################################################################
            # Check for GTK-Doc comment block identifier.
            ####################################################################
            if not comment_block:
                if not identifier:
                    result = SECTION_RE.match(line)
                    if result:
                        identifier = IDENTIFIER_SECTION
                        identifier_name = 'SECTION:%s' % (result.group('section_name'), )
                        column = result.start('section_name') + column_offset

                if not identifier:
                    result = SYMBOL_RE.match(line)
                    if result:
                        identifier = IDENTIFIER_SYMBOL
                        identifier_name = '%s' % (result.group('symbol_name'), )
                        column = result.start('symbol_name') + column_offset

                if not identifier:
                    result = PROPERTY_RE.match(line)
                    if result:
                        identifier = IDENTIFIER_PROPERTY
                        identifier_name = '%s:%s' % (result.group('class_name'),
                                                     result.group('property_name'))
                        column = result.start('property_name') + column_offset

                if not identifier:
                    result = SIGNAL_RE.match(line)
                    if result:
                        identifier = IDENTIFIER_SIGNAL
                        identifier_name = '%s::%s' % (result.group('class_name'),
                                                      result.group('signal_name'))
                        column = result.start('signal_name') + column_offset

                if identifier:
                    in_part = PART_IDENTIFIER
                    part_indent = line_indent

                    comment_block = DocBlock(identifier_name)
                    comment_block.position = position

                    if 'colon' in result.groupdict() and result.group('colon') != ':':
                        colon_start = result.start('colon')
                        colon_column = column_offset + colon_start
                        marker = ' ' * colon_column + '^'
                        message.warn("missing ':' at column %s:\n%s\n%s" %
                                     (colon_column + 1, original_line, marker),
                                     position)

                    if 'annotations' in result.groupdict():
                        comment_block.options = self.parse_options(comment_block,
                                                                   result.group('annotations'))

                    continue
                else:
                    # If we get here, the identifier was not recognized, so
                    # ignore the rest of the block just like the old annotation
                    # parser did. Doing this is a bit more strict than
                    # gtkdoc-mkdb (which continues to search for the identifier
                    # until either it is found or the end of the block is
                    # reached). In practice, however, ignoring the block is the
                    # right thing to do because sooner or later some long
                    # descriptions will contain something matching an identifier
                    # pattern by accident.
                    marker = ' ' * column_offset + '^'
                    message.warn('ignoring unrecognized GTK-Doc comment block, identifier not '
                                 'found:\n%s\n%s' % (original_line, marker),
                                 position)

                    return None

            ####################################################################
            # Check for comment block parameters.
            ####################################################################
            result = PARAMETER_RE.match(line)
            if result:
                param_name = result.group('parameter_name')
                param_annotations = result.group('annotations')
                param_description = result.group('description')

                if in_part == PART_IDENTIFIER:
                    in_part = PART_PARAMETERS

                part_indent = line_indent

                if in_part != PART_PARAMETERS:
                    column = result.start('parameter_name') + column_offset
                    marker = ' ' * column + '^'
                    message.warn("'@%s' parameter unexpected at this location:\n%s\n%s" %
                                 (param_name, original_line, marker),
                                 position)

                # Old style GTK-Doc allowed return values to be specified as
                # parameters instead of tags.
                if param_name.lower() == TAG_RETURNS:
                    param_name = TAG_RETURNS

                    if not returns_seen:
                        returns_seen = True
                    else:
                        message.warn("encountered multiple 'Returns' parameters or tags for "
                                     "'%s'." % (comment_block.name, ),
                                     position)
                elif param_name in comment_block.params.keys():
                    column = result.start('parameter_name') + column_offset
                    marker = ' ' * column + '^'
                    message.warn("multiple '@%s' parameters for identifier '%s':\n%s\n%s" %
                                 (param_name, comment_block.name, original_line, marker),
                                 position)

                tag = DocTag(comment_block, param_name)
                tag.position = position
                tag.comment = param_description
                if param_annotations:
                    tag.options = self.parse_options(tag, param_annotations)
                if param_name == TAG_RETURNS:
                    comment_block.tags[param_name] = tag
                else:
                    comment_block.params[param_name] = tag
                current_param = tag
                continue

            ####################################################################
            # Check for comment block description.
            #
            # When we are parsing comment block parameters or the comment block
            # identifier (when there are no parameters) and encounter an empty
            # line, we must be parsing the comment block description.
            ####################################################################
            if (EMPTY_LINE_RE.match(line) and in_part in [PART_IDENTIFIER, PART_PARAMETERS]):
                in_part = PART_DESCRIPTION
                part_indent = line_indent
                continue

            ####################################################################
            # Check for GTK-Doc comment block tags.
            ####################################################################
            result = TAG_RE.match(line)
            if result and line_indent <= part_indent:
                tag_name = result.group('tag_name')
                tag_annotations = result.group('annotations')
                tag_description = result.group('description')

                marker = ' ' * (result.start('tag_name') + column_offset) + '^'

                # Deprecated GTK-Doc Description: tag
                if tag_name.lower() == TAG_DESCRIPTION:
                    message.warn("GTK-Doc tag \"Description:\" has been deprecated:\n%s\n%s" %
                                 (original_line, marker),
                                 position)

                    in_part = PART_DESCRIPTION
                    part_indent = line_indent

                    if not comment_block.comment:
                        comment_block.comment = tag_description
                    else:
                        comment_block.comment += '\n' + tag_description
                    continue

                # Now that the deprecated stuff is out of the way, continue parsing real tags
                if in_part == PART_DESCRIPTION:
                    in_part = PART_TAGS

                part_indent = line_indent

                if in_part != PART_TAGS:
                    column = result.start('tag_name') + column_offset
                    marker = ' ' * column + '^'
                    message.warn("'%s:' tag unexpected at this location:\n%s\n%s" %
                                 (tag_name, original_line, marker),
                                 position)

                if tag_name.lower() in [TAG_RETURNS, TAG_RETURNVALUE]:
                    if not returns_seen:
                        returns_seen = True
                    else:
                        message.warn("encountered multiple 'Returns' parameters or tags for "
                                     "'%s'." % (comment_block.name, ),
                                     position)

                    tag = DocTag(comment_block, TAG_RETURNS)
                    tag.position = position
                    tag.comment = tag_description
                    if tag_annotations:
                        tag.options = self.parse_options(tag, tag_annotations)
                    comment_block.tags[TAG_RETURNS] = tag
                    current_tag = tag
                    continue
                else:
                    if tag_name.lower() in comment_block.tags.keys():
                        column = result.start('tag_name') + column_offset
                        marker = ' ' * column + '^'
                        message.warn("multiple '%s:' tags for identifier '%s':\n%s\n%s" %
                                     (tag_name, comment_block.name, original_line, marker),
                                     position)

                    tag = DocTag(comment_block, tag_name.lower())
                    tag.position = position
                    tag.value = tag_description
                    if tag_annotations:
                        if tag_name.lower() == TAG_ATTRIBUTES:
                            tag.options = self.parse_options(tag, tag_annotations)
                        else:
                            message.warn("annotations not supported for tag '%s:'." %
                                         (tag_name, ),
                                         position)
                    comment_block.tags[tag_name.lower()] = tag
                    current_tag = tag
                    continue

            ####################################################################
            # If we get here, we must be in the middle of a multiline
            # comment block, parameter or tag description.
            ####################################################################
            if in_part in [PART_IDENTIFIER, PART_DESCRIPTION]:
                if not comment_block.comment:
                    comment_block.comment = line
                else:
                    comment_block.comment += '\n' + line
                continue
            elif in_part == PART_PARAMETERS:
                self._validate_multiline_annotation_continuation(line, original_line,
                                                                 column_offset, position)
                # Append to parameter description.
                current_param.comment += ' ' + line.strip()
                continue
            elif in_part == PART_TAGS:
                self._validate_multiline_annotation_continuation(line, original_line,
                                                                 column_offset, position)
                # Append to tag description.
                if current_tag.name.lower() in [TAG_RETURNS, TAG_RETURNVALUE]:
                    current_tag.comment += ' ' + line.strip()
                else:
                    current_tag.value += ' ' + line.strip()
                continue

        ########################################################################
        # Finished parsing this comment block.
        ########################################################################
        if comment_block:
            # We have picked up a couple of \n characters that where not
            # intended. Strip those.
            if comment_block.comment:
                comment_block.comment = comment_block.comment.strip()

            for tag in comment_block.tags.values():
                self._clean_comment_block_part(tag)

            for param in comment_block.params.values():
                self._clean_comment_block_part(param)

            # Validate and store block.
            comment_block.validate()
            return comment_block
        else:
            return None

    def _clean_comment_block_part(self, part):
        if part.comment:
            part.comment = part.comment.strip()
        else:
            part.comment = None

        if part.value:
            part.value = part.value.strip()
        else:
            part.value = ''

    def _validate_multiline_annotation_continuation(self, line, original_line,
                                                    column_offset, position):
        '''
        Validate parameters and tags (except the first line) and generate
        warnings about invalid annotations spanning multiple lines.

        :param line: line to validate, stripped from ' * ' at start of the line.
        :param original_line: original line to validate (used in warning messages)
        :param column_offset: column width of ' * ' at the time it was stripped from `line`
        :param position: position of `line` in the source file
        '''

        result = MULTILINE_ANNOTATION_CONTINUATION_RE.match(line)
        if result:
            column = result.start('annotations') + column_offset
            marker = ' ' * column + '^'
            message.warn('ignoring invalid multiline annotation continuation:\n'
                         '%s\n%s' % (original_line, marker),
                         position)

    @classmethod
    def parse_options(cls, tag, value):
        # (annotation)
        # (annotation opt1 opt2 ...)
        # (annotation opt1=value1 opt2=value2 ...)
        opened = -1
        options = DocOptions()
        options.position = tag.position

        for i, c in enumerate(value):
            if c == '(' and opened == -1:
                opened = i + 1
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
                opened = -1

        return options
