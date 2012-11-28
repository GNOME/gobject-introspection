# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2012 Dieter Verfaillie <dieterv@optionexplicit.be>
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
This module provides regular expression programs that can be used to identify
and extract useful information from different parts of GTK-Doc comment blocks.
These programs are built to:
 - match (or substitute) a single comment block line at a time;
 - support MULTILINE mode and should support (but remains untested)
   LOCALE and UNICODE modes.
'''


import re


# Program matching the start of a comment block.
#
# Results in 0 symbolic groups.
COMMENT_START_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    /                                        # 1 forward slash character
    \*{2}                                    # exactly 2 asterisk characters
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE | re.MULTILINE)

# Program matching the end of a comment block.
#
# Results in 0 symbolic groups.
COMMENT_END_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    \*+                                      # 1 or more asterisk characters
    /                                        # 1 forward slash character
    $                                        # end
    ''',
    re.VERBOSE | re.MULTILINE)

# Program matching the "*" at the beginning of every
# line inside a comment block.
#
# Results in 0 symbolic groups.
COMMENT_ASTERISK_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    \*                                       # 1 asterisk character
    [^\S\n\r]?                               # 0 or 1 whitespace characters
                                             #   Carefull: removing more would
                                             #   break embedded example program
                                             #   indentation
    ''',
    re.VERBOSE)

# Program matching an empty line.
#
# Results in 0 symbolic groups.
EMPTY_LINE_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or 1 whitespace characters
    $                                        # end
    ''',
    re.VERBOSE | re.MULTILINE)

# Program matching SECTION identifiers.
#
# Results in 2 symbolic groups:
#   - group 1 = colon
#   - group 2 = section_name
SECTION_RE = re.compile(r'''
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
    re.VERBOSE | re.MULTILINE)

# Program matching symbol (function, constant, struct and enum) identifiers.
#
# Results in 3 symbolic groups:
#   - group 1 = symbol_name
#   - group 2 = colon
#   - group 3 = annotations
SYMBOL_RE = re.compile(r'''
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
    re.VERBOSE | re.MULTILINE)

# Program matching property identifiers.
#
# Results in 4 symbolic groups:
#   - group 1 = class_name
#   - group 2 = property_name
#   - group 3 = colon
#   - group 4 = annotations
PROPERTY_RE = re.compile(r'''
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
    re.VERBOSE | re.MULTILINE)

# Program matching signal identifiers.
#
# Results in 4 symbolic groups:
#   - group 1 = class_name
#   - group 2 = signal_name
#   - group 3 = colon
#   - group 4 = annotations
SIGNAL_RE = re.compile(r'''
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
    re.VERBOSE | re.MULTILINE)

# Program matching parameters.
#
# Results in 4 symbolic groups:
#   - group 1 = parameter_name
#   - group 2 = annotations
#   - group 3 = colon
#   - group 4 = description
PARAMETER_RE = re.compile(r'''
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
    re.VERBOSE | re.MULTILINE)

# Program matching old style "Description:" tag.
#
# Results in 0 symbolic groups.
DESCRIPTION_TAG_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    Description:                             # 'Description:' literal
    ''',
    re.VERBOSE | re.MULTILINE)

# Program matching tags.
#
# Results in 4 symbolic groups:
#   - group 1 = tag_name
#   - group 2 = annotations
#   - group 3 = colon
#   - group 4 = description
TAG_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<tag_name>virtual|since|stability|
                 deprecated|returns|
                 return\ value|attributes|
                 rename\ to|type|
                 unref\ func|ref\ func|
                 set\ value\ func|
                 get\ value\ func|
                 transfer|value)             # tag name
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
    re.VERBOSE | re.MULTILINE | re.IGNORECASE)

# Program matching multiline annotation continuations.
# This is used on multiline parameters and tags (but not on the first line) to
# generate warnings about invalid annotations spanning multiple lines.
#
# Results in 3 symbolic groups:
#   - group 2 = annotations
#   - group 3 = colon
#   - group 4 = description
MULTILINE_ANNOTATION_CONTINUATION_RE = re.compile(r'''
    ^                                        # start
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<annotations>(?:\(.*?\)[^\S\n\r]*)*)  # annotations
    (?P<colon>:)                             # colon
    [^\S\n\r]*                               # 0 or more whitespace characters
    (?P<description>.*?)                     # description
    [^\S\n\r]*                               # 0 or more whitespace characters
    $                                        # end
    ''',
    re.VERBOSE | re.MULTILINE)
