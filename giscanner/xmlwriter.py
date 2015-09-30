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

from __future__ import with_statement
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import os
import sys

from contextlib import contextmanager
from xml.sax.saxutils import escape

from .libtoolimporter import LibtoolImporter

if sys.version_info.major < 3:
    from StringIO import StringIO
else:
    from io import StringIO
    unicode = str


with LibtoolImporter(None, None):
    if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
        from _giscanner import collect_attributes
    else:
        from giscanner._giscanner import collect_attributes


def build_xml_tag(tag_name, attributes=None, data=None, self_indent=0,
                  self_indent_char=' '):
    if attributes is None:
        attributes = []
    prefix = '<%s' % (tag_name, )
    if data is not None:
        if isinstance(data, bytes):
            data = data.decode('UTF-8')
        suffix = '>%s</%s>' % (escape(data), tag_name)
    else:
        suffix = '/>'
    attrs = collect_attributes(
        tag_name, attributes,
        self_indent,
        self_indent_char,
        len(prefix) + len(suffix))
    return prefix + attrs + suffix


class XMLWriter(object):

    def __init__(self):
        # Build up the XML buffer as unicode strings. When writing to disk,
        # we can assume the lack of a Byte Order Mark (BOM) and lack
        # of an "encoding" xml property means utf-8.
        # See: http://www.opentag.com/xfaq_enc.htm#enc_default
        self._data = StringIO()
        self._data.write('<?xml version="1.0"?>\n')
        self._tag_stack = []
        self._indent = 0
        self._indent_unit = 2
        self.enable_whitespace()

    # Private

    def _open_tag(self, tag_name, attributes=None):
        if attributes is None:
            attributes = []
        attrs = collect_attributes(tag_name, attributes,
                                   self._indent, self._indent_char, len(tag_name) + 2)
        self.write_line('<%s%s>' % (tag_name, attrs))

    def _close_tag(self, tag_name):
        self.write_line('</%s>' % (tag_name, ))

    # Public API

    def enable_whitespace(self):
        self._indent_char = ' '
        self._newline_char = '\n'

    def disable_whitespace(self):
        self._indent_char = ''
        self._newline_char = ''

    def get_xml(self):
        """Returns a unicode string containing the XML."""
        return self._data.getvalue()

    def get_encoded_xml(self):
        """Returns a utf-8 encoded bytes object containing the XML."""
        return self._data.getvalue().encode('utf-8')

    def write_line(self, line='', indent=True, do_escape=False):
        if isinstance(line, bytes):
            line = line.decode('utf-8')
        assert isinstance(line, unicode)
        if do_escape:
            line = escape(line)
        if indent:
            self._data.write('%s%s%s' % (self._indent_char * self._indent,
                                         line,
                                         self._newline_char))
        else:
            self._data.write('%s%s' % (line, self._newline_char))

    def write_comment(self, text):
        self.write_line('<!-- %s -->' % (text, ))

    def write_tag(self, tag_name, attributes, data=None):
        self.write_line(build_xml_tag(tag_name, attributes, data,
                                      self._indent, self._indent_char))

    def push_tag(self, tag_name, attributes=None):
        if attributes is None:
            attributes = []
        self._open_tag(tag_name, attributes)
        self._tag_stack.append(tag_name)
        self._indent += self._indent_unit

    def pop_tag(self):
        self._indent -= self._indent_unit
        tag_name = self._tag_stack.pop()
        self._close_tag(tag_name)
        return tag_name

    @contextmanager
    def tagcontext(self, tag_name, attributes=None):
        self.push_tag(tag_name, attributes)
        try:
            yield
        finally:
            self.pop_tag()


def test():
    w = XMLWriter()
    w.push_tag('repository')
    w.push_tag('namespace')
    w.push_tag('enumeration')
    w.push_tag('member',
               [('name', 'west'),
                ('value', '7'),
                ('c:identifier', 'GTK_ANCHOR_WEST'),
                ('glib:nick', 'west')])

    w.pop_tag()
    w.pop_tag()
    w.pop_tag()
    x = w.get_xml()
    lines = x.split('\n')
    import pprint
    pprint.pprint(lines)
    assert len(lines[3]) < 80, len(lines[3])

if __name__ == '__main__':
    test()
