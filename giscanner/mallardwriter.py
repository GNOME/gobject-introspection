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
import tempfile

from xml.sax import saxutils
from mako.template import Template

from . import ast
from .utils import to_underscores

def make_page_id(namespace, node):
    if isinstance(node, ast.Namespace):
        return 'index'
    elif isinstance(node, (ast.Class, ast.Interface)):
        return '%s.%s' % (namespace.name, node.name)
    elif isinstance(node, ast.Record):
        return '%s.%s' % (namespace.name, node.name)
    elif isinstance(node, ast.Function):
        if node.parent is not None:
            return '%s.%s.%s' % (namespace.name, node.parent.name, node.name)
        else:
            return '%s.%s' % (namespace.name, node.name)
    elif isinstance(node, ast.Enum):
        return '%s.%s' % (namespace.name, node.name)
    elif isinstance(node, ast.Property) and node.parent is not None:
        return '%s.%s-%s' % (namespace.name, node.parent.name, node.name)
    elif isinstance(node, ast.Signal) and node.parent is not None:
        return '%s.%s-%s' % (namespace.name, node.parent.name, node.name)
    elif isinstance(node, ast.VFunction) and node.parent is not None:
        return '%s.%s-%s' % (namespace.name, node.parent.name, node.name)
    else:
        return '%s.%s' % (namespace.name, node.name)

def make_template_name(node, language):
    if isinstance(node, ast.Namespace):
        node_kind = 'namespace'
    elif isinstance(node, (ast.Class, ast.Interface)):
        node_kind = 'class'
    elif isinstance(node, ast.Record):
        node_kind = 'record'
    elif isinstance(node, ast.Function):
        node_kind = 'function'
    elif isinstance(node, ast.Enum):
        node_kind = 'enum'
    elif isinstance(node, ast.Property) and node.parent is not None:
        node_kind = 'property'
    elif isinstance(node, ast.Signal) and node.parent is not None:
        node_kind = 'signal'
    elif isinstance(node, ast.VFunction) and node.parent is not None:
        node_kind = 'vfunc'
    else:
        node_kind = 'default'

    return 'mallard-%s-%s.tmpl' % (language, node_kind)

class TemplatedScanner(object):
    def __init__(self, specs):
        self.specs = self.unmangle_specs(specs)
        self.regex = self.make_regex(self.specs)

    def unmangle_specs(self, specs):
        mangled = re.compile('<<([a-zA-Z_:]+)>>')
        specdict = dict((name.lstrip('!'), spec) for name, spec in specs)

        def unmangle(spec, name=None):
            def replace_func(match):
                child_spec_name = match.group(1)

                if ':' in child_spec_name:
                    pattern_name, child_spec_name = child_spec_name.split(':', 1)
                else:
                    pattern_name = None

                child_spec = specdict[child_spec_name]
                # Force all child specs of this one to be unnamed
                unmangled = unmangle(child_spec, None)
                if pattern_name and name:
                    return '(?P<%s_%s>%s)' % (name, pattern_name, unmangled)
                else:
                    return unmangled

            return mangled.sub(replace_func, spec)

        return [(name, unmangle(spec, name)) for name, spec in specs]

    def make_regex(self, specs):
        regex = '|'.join('(?P<%s>%s)' % (name, spec) for name, spec in specs if not name.startswith('!'))
        return re.compile(regex)

    def get_properties(self, name, match):
        groupdict = match.groupdict()
        properties = { name: groupdict.pop(name) }
        name = name + "_"
        for group, value in groupdict.iteritems():
            if group.startswith(name):
                key = group[len(name):]
                properties[key] = value
        return properties

    def scan(self, text):
        pos = 0
        while True:
            match = self.regex.search(text, pos)
            if match is None:
                break

            start = match.start()
            if start > pos:
                yield ('other', text[pos:start], None)

            pos = match.end()
            name = match.lastgroup
            yield (name, match.group(0), self.get_properties(name, match))

        if pos < len(text):
            yield ('other', text[pos:], None)

class DocstringScanner(TemplatedScanner):
    def __init__(self):
        specs = [
            ('!alpha'        , r'[a-zA-Z0-9_]+'),
            ('!alpha_dash'   , r'[a-zA-Z0-9_-]+'),
            ('property'      , r'<<type_name:type_name>>:(<<property_name:alpha_dash>>)'),
            ('signal'        , r'<<type_name:type_name>>::(<<signal_name:alpha_dash>>)'),
            ('type_name'     , r'#(<<type_name:alpha>>)'),
            ('fundamental'   , r'%(<<fundamental:alpha>>)'),
            ('function_call' , r'<<symbol_name:alpha>>\(\)'),
        ]

        super(DocstringScanner, self).__init__(specs)

class MallardFormatter(object):
    def __init__(self, transformer):
        self._transformer = transformer
        self._scanner = DocstringScanner()

    def escape(self, text):
        return saxutils.escape(text)

    def format(self, doc):
        if doc is None:
            return ''

        result = ''
        for para in doc.split('\n\n'):
            result += '<p>'
            result += self.format_inline(para)
            result += '</p>'
        return result

    def _process_other(self, namespace, match, props):
        return self.escape(match)

    def _process_property(self, namespace, match, props):
        type_node = namespace.get_by_ctype(props['type_name'])
        if type_node is None:
            return match

        try:
            node = type_node.properties[props['property_name']]
        except (AttributeError, KeyError), e:
            return match

        xref_name = "%s.%s:%s" % (namespace.name, type_node.name, node.name)
        return '<link xref="%s">%s</link>' % (make_page_id(namespace, node), xref_name)

    def _process_signal(self, namespace, match, props):
        type_node = namespace.get_by_ctype(props['type_name'])
        if type_node is None:
            return match

        try:
            node = type_node.signals[props['signal_name']]
        except (AttributeError, KeyError), e:
            return match

        xref_name = "%s.%s::%s" % (namespace.name, type_node.name, node.name)
        return '<link xref="%s">%s</link>' % (make_page_id(namespace, node), xref_name)

    def _process_type_name(self, namespace, match, props):
        node = namespace.get_by_ctype(props['type_name'])
        if node is None:
            return match
        xref_name = "%s.%s" % (namespace.name, node.name)
        return '<link xref="%s">%s</link>' % (make_page_id(namespace, node), xref_name)

    def _process_function_call(self, namespace, match, props):
        node = namespace.get_by_symbol(props['symbol_name'])
        if node is None:
            return match

        return '<link xref="%s">%s</link>' % (make_page_id(namespace, node), self.format_function_name(node))

    def _process_fundamental(self, namespace, match, props):
        raise NotImplementedError

    def _process_token(self, tok):
        namespace = self._transformer.namespace

        kind, match, props = tok

        dispatch = {
            'other': self._process_other,
            'property': self._process_property,
            'signal': self._process_signal,
            'type_name': self._process_type_name,
            'function_call': self._process_function_call,
            'fundamental': self._process_fundamental,
        }

        return dispatch[kind](namespace, match, props)

    def format_inline(self, para):
        tokens = self._scanner.scan(para)
        words = [(tok, self._process_token(tok)) for tok in tokens]
        words = [w[1] for w in words]
        return ' '.join(words)

    def format_function_name(self, func):
        raise NotImplementedError

    def format_type(self, type_):
        raise NotImplementedError

    def format_property_flags(self, property_):
        flags = []
        if property_.readable:
            flags.append("Read")
        if property_.writable:
            flags.append("Write")
        if property_.construct:
            flags.append("Construct")
        if property_.construct_only:
            flags.append("Construct Only")

        return " / ".join(flags)

    def to_underscores(self, string):
        return to_underscores(string)

    def get_class_hierarchy(self, node):
        parent_chain = [node]

        while node.parent:
            node = self._transformer.lookup_giname(str(node.parent))
            parent_chain.append(node)

        parent_chain.reverse()
        return parent_chain

class MallardFormatterC(MallardFormatter):
    language = "C"

    def format_type(self, type_):
        if isinstance(type_, ast.Array):
            return self.format_type(type_.element_type) + '*'
        elif type_.ctype is not None:
            return type_.ctype
        else:
            return type_.target_fundamental

    def format_function_name(self, func):
        return func.symbol

    def _process_fundamental(self, namespace, match, props):
        return props['fundamental']

class MallardFormatterPython(MallardFormatter):
    language = "Python"

    def format_type(self, type_):
        if isinstance(type_, ast.Array):
            return '[' + self.format_type(type_.element_type) + ']'
        elif isinstance(type_, ast.Map):
            return '{%s: %s}' % (self.format_type(type_.key_type),
                                 self.format_type(type_.value_type))
        elif type_.target_giname is not None:
            return type_.target_giname
        else:
            return type_.target_fundamental

    def format_function_name(self, func):
        if func.parent is not None:
            return "%s.%s" % (self.format_type(func.parent), func.name)
        else:
            return func.name

    def _process_fundamental(self, namespace, match, props):
        translation = {
            "NULL": "None",
            "TRUE": "True",
            "FALSE": "False",
        }

        return translation.get(props['fundamental'], match)

LANGUAGES = {
    "c": MallardFormatterC,
    "python": MallardFormatterPython,
}

class MallardWriter(object):
    def __init__(self, transformer, language):
        self._transformer = transformer

        try:
            formatter_class = LANGUAGES[language.lower()]
        except KeyError:
            raise SystemExit("Unsupported language: %s" % (language,))

        self._formatter = formatter_class(self._transformer)
        self._language = self._formatter.language

    def write(self, output):
        nodes = [self._transformer.namespace]
        for node in self._transformer.namespace.itervalues():
            if isinstance(node, ast.Function) and node.moved_to is not None:
                continue
            if getattr(node, 'disguised', False):
                continue
            if isinstance(node, ast.Record) and \
               self._language == 'Python' and \
               node.is_gtype_struct_for is not None:
                continue
            nodes.append(node)
            if isinstance(node, (ast.Class, ast.Interface, ast.Record)):
                nodes += getattr(node, 'methods', [])
                nodes += getattr(node, 'static_methods', [])
                nodes += getattr(node, 'virtual_methods', [])
                nodes += getattr(node, 'properties', [])
                nodes += getattr(node, 'signals', [])
                if self._language == 'C':
                    nodes += getattr(node, 'constructors', [])
        for node in nodes:
            self._render_node(node, output)

    def _render_node(self, node, output):
        namespace = self._transformer.namespace

        if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
            top_srcdir = os.environ['UNINSTALLED_INTROSPECTION_SRCDIR']
            template_dir = os.path.join(top_srcdir, 'giscanner')
        else:
            template_dir = os.path.dirname(__file__)

        template_name = make_template_name(node, self._language)
        page_id = make_page_id(namespace, node)

        file_name = os.path.join(template_dir, template_name)
        file_name = os.path.abspath(file_name)
        template = Template(filename=file_name, output_encoding='utf-8',
                            module_directory=tempfile.gettempdir())
        result = template.render(namespace=namespace,
                                 node=node,
                                 page_id=page_id,
                                 formatter=self._formatter)

        output_file_name = os.path.join(os.path.abspath(output),
                                        page_id + '.page')
        fp = open(output_file_name, 'w')
        fp.write(result)
        fp.close()
