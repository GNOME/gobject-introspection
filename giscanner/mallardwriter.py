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

class MallardFormatter(object):
    @classmethod
    def escape(cls, text):
        return saxutils.escape(text.encode('utf-8')).decode('utf-8')

    @classmethod
    def format(cls, doc):
        if doc is None:
            return ''

        result = ''
        for para in doc.split('\n\n'):
            result += '<p>'
            result += cls.format_inline(para)
            result += '</p>'
        return result

    @classmethod
    def format_inline(cls, para):
        result = ''

        poss = []
        poss.append((para.find('#'), '#'))
        poss = [pos for pos in poss if pos[0] >= 0]
        poss.sort(cmp=lambda x, y: cmp(x[0], y[0]))
        if len(poss) == 0:
            result += cls.escape(para)
        elif poss[0][1] == '#':
            pos = poss[0][0]
            result += cls.escape(para[:pos])
            rest = para[pos + 1:]
            link = re.split('[^a-zA-Z_:-]', rest, maxsplit=1)[0]
            xref = link #self.writer._xrefs.get(link, link)
            result += '<link xref="%s">%s</link>' % (xref, link)
            if len(link) < len(rest):
                result += cls.format_inline(rest[len(link):])

        return result

    @classmethod
    def format_type(cls, type_):
        raise NotImplementedError

class MallardFormatterC(MallardFormatter):
    @classmethod
    def format_type(cls, type_):
        if isinstance(type_, ast.Array):
            try:
                return cls.format_type(type_.element_type) + '*'
            except:
                return type_.target_fundamental
        elif type_.ctype is not None:
            return type_.ctype
        else:
            return type_.target_fundamental

class MallardFormatterPython(MallardFormatter):
    @classmethod
    def format_type(cls, type_):
        if isinstance(type_, ast.Array):
            return '[' + cls.format_type(type_.element_type) + ']'
        elif type_.target_giname is not None:
            return type_.target_giname
        else:
            return type_.target_fundamental

    @classmethod
    def format(cls, doc):
        doc = MallardFormatter.format(doc)
        doc = doc.replace('%NULL', 'None')
        return doc

class MallardWriter(object):
    def __init__(self, transformer, language):
        if language not in ["Python", "C"]:
            raise SystemExit("Unsupported language: %s" % language)

        self._transformer = transformer
        self._language = language

    def write(self, output):
        nodes = [self._transformer.namespace]
        for node in self._transformer.namespace.itervalues():
            if isinstance(node, ast.Function) and node.moved_to is not None:
                continue
            if getattr(node, 'disguised', False):
                continue
            nodes.append(node)
            if isinstance(node, (ast.Class, ast.Interface, ast.Record)):
                nodes += getattr(node, 'methods', [])
                nodes += getattr(node, 'constructors', [])
                nodes += getattr(node, 'static_methods', [])
                nodes += getattr(node, 'virtual_methods', [])
                nodes += getattr(node, 'properties', [])
                nodes += getattr(node, 'signals', [])
        for node in nodes:
            self._render_node(node, output)

    def _render_node(self, node, output):
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
        elif isinstance(node, ast.Function):
            template_name = 'mallard-%s-function.tmpl' % self._language
            if node.parent is not None:
                page_id = '%s.%s.%s' % (namespace.name, node.parent.name, node.name)
            else:
                page_id = '%s.%s' % (namespace.name, node.name)
        elif isinstance(node, ast.Property) and node.parent is not None:
            template_name = 'mallard-%s-property.tmpl' % self._language
            page_id = '%s.%s-%s' % (namespace.name, node.parent.name, node.name)
        elif isinstance(node, ast.Signal) and node.parent is not None:
            template_name = 'mallard-%s-signal.tmpl' % self._language
            page_id = '%s.%s-%s' % (namespace.name, node.parent.name, node.name)
        else:
            template_name = 'mallard-%s-default.tmpl' % self._language
            page_id = '%s.%s' % (namespace.name, node.name)

        if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
            top_srcdir = os.environ['UNINSTALLED_INTROSPECTION_SRCDIR']
            template_dir = os.path.join(top_srcdir, 'giscanner')
        else:
            template_dir = 'unimplemented'

        file_name = os.path.join(template_dir, template_name)
        template = Template(filename=file_name, output_encoding='utf-8')
        if self._language == 'C':
            formatter = MallardFormatterC
        elif self._language == 'Python':
            formatter = MallardFormatterPython
        else:
            raise RuntimeError('Unavailable formatter for language %s',
                               self._language)
        result = template.render(namespace=namespace,
                                 node=node,
                                 page_id=page_id,
                                 formatter=formatter)

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
