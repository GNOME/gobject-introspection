#!/usr/bin/env python
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2010 Zach Goldberg
# Copyright (C) 2011 Johan Dahlin
# Copyright (C) 2011 Shaun McCance
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

import os
import re

from xml.sax import saxutils
from mako.template import Template
from mako.runtime import supports_caller

from . import ast

def format(doc):
    if doc is None:
        return ''

    result = ''
    for para in doc.split('\n\n'):
        result += '<p>'
        result += format_inline(para)
        result += '</p>'
    return result

def escape(text):
    return saxutils.escape(text.encode('utf-8')).decode('utf-8')

def format_inline(para):
    result = ''

    poss = []
    poss.append((para.find('#'), '#'))
    poss = [pos for pos in poss if pos[0] >= 0]
    poss.sort(cmp=lambda x, y: cmp(x[0], y[0]))
    if len(poss) == 0:
        result += escape(para)
    elif poss[0][1] == '#':
        pos = poss[0][0]
        result += escape(para[:pos])
        rest = para[pos + 1:]
        link = re.split('[^a-zA-Z_:-]', rest, maxsplit=1)[0]
        xref = link #self.writer._xrefs.get(link, link)
        result += '<link xref="%s">%s</link>' % (xref, link)
        if len(link) < len(rest):
            result += format_inline(rest[len(link):])

    return result

class MallardWriter(object):
    def __init__(self, transformer, language):
        if language not in ["Python", "C"]:
            raise SystemExit("Unsupported language: %s" % language)

        self._transformer = transformer
        self._language = language

    def write(self, output):
        self._render_node(self._transformer.namespace, output)
        for node in self._transformer.namespace.itervalues():
            self._render_node(node, output)
            if isinstance(node, (ast.Class, ast.Record)):
                for method in node.methods:
                    self._render_node(method, output, node)

    def _render_node(self, node, output, parent=None):
        namespace = self._transformer.namespace
        if isinstance(node, ast.Namespace):
            template_name = 'mallard-%s-namespace.tmpl' % self._language
            page_id = 'index'
        elif isinstance(node, (ast.Class, ast.Interface)):
            template_name = 'mallard-%s-class.tmpl' % self._language
            page_id = '%s.%s' % (namespace.name, node.name)
        elif isinstance(node, ast.Record):
            template_name = 'mallard-%s-record.tmpl' % self._language
            page_id = '%s.%s' % (namespace.name, node.name)
        elif isinstance(node, ast.Function) and parent is not None:
            template_name = 'mallard-%s-method.tmpl' % self._language
            page_id = '%s.%s.%s' % (namespace.name, parent.name, node.name)
        elif isinstance(node, ast.Function):
            template_name = 'mallard-%s-function.tmpl' % self._language
            page_id = '%s.%s' % (namespace.name, node.name)
        else:
            template_name = 'mallard-%s-default.tmpl' % self._language
            page_id = '%s.%s' % (namespace.name, node.name)

        if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
            top_srcdir = os.environ['UNINSTALLED_INTROSPECTION_SRCDIR']
            template_dir = os.path.join(top_srcdir, 'giscanner')
        else:
            template_dir = 'unimplemented'

        file_name = os.path.join(template_dir, template_name)
        template = Template(filename=file_name)
        result = template.render(namespace=namespace,
                                 node=node,
                                 format=format,
                                 parent=parent)

        output_file_name = os.path.join(os.path.dirname(output),
                                        page_id + '.page')
        fp = open(output_file_name, 'w')
        fp.write(result)
        fp.close()

    def _render_page_object_hierarchy(self, page_node):
        parent_chain = self._get_parent_chain(page_node)
        parent_chain.append(page_node)
        lines = []

        for level, parent in enumerate(parent_chain):
            prepend = ""
            if level > 0:
                prepend = _space((level - 1)* 6) + " +----"
            lines.append(_space(2) + prepend + self._formatter.get_class_name(parent))

        self._writer.disable_whitespace()
        self._writer.write_line("\n".join(lines))
        self._writer.enable_whitespace()
