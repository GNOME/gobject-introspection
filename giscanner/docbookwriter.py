#!/usr/bin/env python
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2010 Zach Goldberg
# Copyright (C) 2011 Johan Dahlin
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

import sys

from . import ast
from .girparser import GIRParser
from .xmlwriter import XMLWriter

XMLNS = "http://docbook.org/ns/docbook"
XMLVERSION = "5.0"

def _space(num):
    return " " * num

class DocBookFormatter(object):
    def __init__(self, writer):
        self._namespace = None
        self._writer = writer

    def set_namespace(self, namespace):
        self._namespace = namespace

    def get_type_string(self, type):
        return str(type.ctype)

    def render_parameter(self, param_type, param_name):
        return "%s %s" % (param_type, param_name)

    def _render_parameter(self, param):
        self._writer.push_tag("parameter", [])

        if param.type.ctype is not None:
            link_dest = param.type.ctype.replace("*", "")
        else:
            link_dest = param.type.ctype
        self._writer.push_tag("link", [("linkend", "%s" % link_dest)])

        self._writer.write_tag("type", [], self.get_type_string(param.type))
        self._writer.pop_tag()

    def _render_parameters(self, parent, parameters):
        self._writer.write_line(
            "%s(" % _space(40 - len(parent.symbol)))

        parent_class = parent.parent_class
        ctype = ast.Type(parent.parent_class.ctype + '*')
        params = []
        params.append(ast.Parameter(parent_class.name.lower(), ctype))
        params.extend(parameters)

        first_param = True
        for param in params:
            if not first_param:
                self._writer.write_line("\n%s" % _space(61))
            else:
                first_param = False

            self._render_parameter(param)
            if not param == params[-1]:
                comma = ", "
            else:
                comma = ""

            self._writer.write_line(" %s%s" % (param.argname, comma))
            self._writer.pop_tag()

        self._writer.write_line(");\n")

    def render_method(self, entity, link=False):
        method = entity.get_ast()
        self._writer.disable_whitespace()

        retval_type = method.retval.type
        if retval_type.ctype:
            link_dest = retval_type.ctype.replace("*", "")
        else:
            link_dest = str(retval_type)

        if retval_type.target_giname:
            ns = retval_type.target_giname.split('.')
            if ns[0] == self._namespace.name:
                link_dest = "%s" % (
                    retval_type.ctype.replace("*", ""))

        with self._writer.tagcontext("link", [("linkend", link_dest)]):
            self._writer.write_tag("returnvalue", [],
                                   self.get_type_string(method.retval.type))

        self._writer.write_line(
            _space(20 - len(self.get_type_string(method.retval.type))))

        if link:
            self._writer.write_tag("link", [("linkend",
                                            "%s-details" % (method.name))],
                                  method.symbol)
        else:
            self._writer.write_line(method.symbol)

        self._render_parameters(method, method.parameters)
        self._writer.enable_whitespace()


class DocBookPage(object):
    def __init__(self, name, description=""):
        self.entities = []
        self.name = name
        self.description = description

    def add_entity(self, entity):
        self.entities.append(entity)

    def get_entities(self):
        return self.entities


class DocBookEntity(object):
    def __init__(self, entity_name, entity_type, entity_ast):
        self.entity_name = entity_name
        self.entity_type = entity_type
        self.entity_ast = entity_ast

    def get_ast(self):
        return self.entity_ast

    def get_type(self):
        return self.entity_type

    def get_name(self):
        return self.entity_name


class DocBookWriter(object):
    def __init__(self):
        self._namespace = None
        self._pages = []

        self._writer = XMLWriter()
        self._formatter = DocBookFormatter(self._writer)

    def _add_page(self, page):
        self._pages.append(page)

    def add_namespace(self, namespace):
        self._namespace = namespace
        self._formatter.set_namespace(namespace)

        for name, node in namespace.iteritems():
            self._add_node(node, name)

    def _add_node(self, node, name):
        page = DocBookPage(name, node.doc)
        self._add_page(page)

        if isinstance(node, (ast.Class, ast.Record, ast.Interface)):
            for method in node.methods:
                method.parent_class = node
                page.add_entity(DocBookEntity(method.name, "method", method))

    def write(self, output):
        with self._writer.tagcontext("book", [
            ("xml:id", "page_%s" % self._namespace.name),
            ("xmlns", XMLNS),
            ("version", XMLVERSION)]):
            self._writer.write_tag("title", [], "%s Documentation" % (
                self._namespace.name))

            for page in self._pages:
                self._render_page(page)

        fp = open(output, 'w')
        fp.write(self._writer.get_xml())
        fp.close()

    def _render_page(self, page):
        with self._writer.tagcontext("chapter", [("xml:id", "ch_%s" % (
                        page.name))]):
            self._writer.write_tag(
                "anchor", [("id", "ch_%s" % (page.name))])
            self._writer.write_tag(
                "anchor", [("id", "%s%s" % (self._namespace.name, page.name))])
            self._writer.write_tag(
                "title", [], "%s %s" % (self._namespace.name, page.name))

            with self._writer.tagcontext("refsynopsisdiv", [
                    ('id', '%s.synopsis' % page.name),
                    ('role', 'synopsis')
                    ]):
                self._writer.write_tag(
                    "title", [("role", "synopsis.title")], "Synopsis")
                with self._writer.tagcontext('synopsis'):
                    for entity in page.get_entities():
                        self._formatter.render_method(entity, link=True)

            # if page.description:
            #     with self._writer.tagcontext(
            #         'refsect1',
            #         [('id', '%s.description' % (page.name, )),
            #          ]):
            #         self._writer.write_tag(
            #             "title", [("role", "desc.title")], "Description")
            #         import cgi
            #         desc = page.description
            #         while True:
            #             start = desc.find('|[')
            #             if start == -1:
            #                 break
            #             end = desc.find(']|')
            #             desc = desc[:start] + cgi.escape(desc[start+2:end]) + desc[end+2:]
            #         desc = desc.replace("&", "&amp;")
            #         self._writer.write_line(desc)

            for entity in page.get_entities():
                self._render_entity(entity)

    def _render_entity(self, entity):
        with self._writer.tagcontext('refsect1',
                                    [('id', "%s-details" % (entity.get_name())),
                                     ("role", "details")]):
            self._writer.write_tag("title", [("role", "details.title")],
                                  "Details")

        self._writer.push_tag('refsect2',
                             [('id', "%s-function" % entity.get_name()),
                              ('role', 'struct')])
        self._writer.write_tag("title", [], entity.get_name())

        with self._writer.tagcontext("indexterm",
                                    [("zone", "%s" % entity.get_name())]):
            self._writer.write_tag("primary", [], entity.get_name())

        with self._writer.tagcontext("programlisting"):
            self._formatter.render_method(entity)

        self._writer.write_tag("para", [], entity.get_ast().doc)
        self._writer.pop_tag()
