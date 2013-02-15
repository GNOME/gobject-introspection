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
from mako.lookup import TemplateLookup

from . import ast, xmlwriter
from .utils import to_underscores

def make_page_id(node):
    if isinstance(node, ast.Namespace):
        return 'index'

    namespace = node.namespace
    if isinstance(node, (ast.Class, ast.Interface)):
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

def get_node_kind(node):
    if isinstance(node, ast.Namespace):
        node_kind = 'namespace'
    elif isinstance(node, (ast.Class, ast.Interface)):
        node_kind = 'class'
    elif isinstance(node, ast.Record):
        node_kind = 'record'
    elif isinstance(node, ast.Function):
        if node.is_method:
            node_kind = 'method'
        elif node.is_constructor:
            node_kind = 'constructor'
        else:
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

    return node_kind

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
        regex = '|'.join('(?P<%s>%s)' % (name, spec) for name, spec in specs
                         if not name.startswith('!'))
        return re.compile(regex)

    def get_properties(self, name, match):
        groupdict = match.groupdict()
        properties = {name: groupdict.pop(name)}
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
            ('!alpha', r'[a-zA-Z0-9_]+'),
            ('!alpha_dash', r'[a-zA-Z0-9_-]+'),
            ('property', r'#<<type_name:alpha>>:(<<property_name:alpha_dash>>)'),
            ('signal', r'#<<type_name:alpha>>::(<<signal_name:alpha_dash>>)'),
            ('type_name', r'#(<<type_name:alpha>>)'),
            ('enum_value', r'%(<<member_name:alpha>>)'),
            ('parameter', r'@<<param_name:alpha>>'),
            ('function_call', r'<<symbol_name:alpha>>\(\)'),
        ]

        super(DocstringScanner, self).__init__(specs)

class DocFormatter(object):
    def __init__(self, transformer):
        self._transformer = transformer
        self._scanner = DocstringScanner()

    def escape(self, text):
        return saxutils.escape(text)

    def should_render_node(self, node):
        if isinstance(node, ast.Constant):
            return False

        return True

    def format(self, node, doc):
        if doc is None:
            return ''

        result = ''
        for para in doc.split('\n\n'):
            result += '<p>'
            result += self.format_inline(node, para)
            result += '</p>'
        return result

    def _resolve_type(self, ident):
        try:
            matches = self._transformer.split_ctype_namespaces(ident)
        except ValueError:
            return None
        for namespace, name in matches:
            node = namespace.get(name)
            if node:
                return node
        return None

    def _resolve_symbol(self, symbol):
        try:
            matches = self._transformer.split_csymbol_namespaces(symbol)
        except ValueError:
            return None
        for namespace, name in matches:
            node = namespace.get_by_symbol(symbol)
            if node:
                return node
        return None

    def _find_thing(self, list_, name):
        for item in list_:
            if item.name == name:
                return item
        raise KeyError("Could not find %s" % (name, ))

    def _process_other(self, node, match, props):
        return self.escape(match)

    def _process_property(self, node, match, props):
        type_node = self._resolve_type(props['type_name'])
        if type_node is None:
            return match

        try:
            prop = self._find_thing(type_node.properties, props['property_name'])
        except (AttributeError, KeyError), e:
            return match

        return self.format_xref(prop)

    def _process_signal(self, node, match, props):
        type_node = self._resolve_type(props['type_name'])
        if type_node is None:
            return match

        try:
            signal = self._find_thing(type_node.signals, props['signal_name'])
        except (AttributeError, KeyError), e:
            return match

        return self.format_xref(signal)

    def _process_type_name(self, node, match, props):
        type_ = self._resolve_type(props['type_name'])
        if type_ is None:
            return match

        return self.format_xref(type_)

    def _process_enum_value(self, node, match, props):
        member_name = props['member_name']

        try:
            return '<code>%s</code>' % (self.fundamentals[member_name], )
        except KeyError:
            pass

        enum_value = self._resolve_symbol(member_name)
        if enum_value:
            return self.format_xref(enum_value)

        return match

    def _process_parameter(self, node, match, props):
        try:
            parameter = node.get_parameter(props['param_name'])
        except (AttributeError, ValueError), e:
            return match

        return '<code>%s</code>' % (self.format_parameter_name(node, parameter), )

    def _process_function_call(self, node, match, props):
        func = self._resolve_symbol(props['symbol_name'])
        if func is None:
            return match

        return self.format_xref(func)

    def _process_token(self, node, tok):
        kind, match, props = tok

        dispatch = {
            'other': self._process_other,
            'property': self._process_property,
            'signal': self._process_signal,
            'type_name': self._process_type_name,
            'enum_value': self._process_enum_value,
            'parameter': self._process_parameter,
            'function_call': self._process_function_call,
        }

        return dispatch[kind](node, match, props)

    def get_parameters(self, node):
        raise NotImplementedError

    def format_inline(self, node, para):
        tokens = self._scanner.scan(para)
        words = [self._process_token(node, tok) for tok in tokens]
        return ''.join(words)

    def format_parameter_name(self, node, parameter):
        if isinstance(parameter.type, ast.Varargs):
            return "..."
        else:
            return parameter.argname

    def format_function_name(self, func):
        raise NotImplementedError

    def format_type(self, type_):
        raise NotImplementedError

    def format_page_name(self, node):
        if isinstance(node, ast.Namespace):
            return 'Index'
        elif isinstance(node, ast.Function):
            return self.format_function_name(node)
        elif isinstance(node, ast.Property) and node.parent is not None:
            return '%s:%s' % (self.format_page_name(node.parent), node.name)
        elif isinstance(node, ast.Signal) and node.parent is not None:
            return '%s::%s' % (self.format_page_name(node.parent), node.name)
        elif isinstance(node, ast.VFunction) and node.parent is not None:
            return '%s::%s' % (self.format_page_name(node.parent), node.name)
        else:
            return make_page_id(node)

    def format_xref(self, node):
        if isinstance(node, ast.Member):
            # Enum/BitField members are linked to the main enum page.
            return self.format_xref(node.parent) + '.' + node.name
        else:
            return xmlwriter.build_xml_tag('link', [('xref', make_page_id(node))])

    def format_property_flags(self, property_, construct_only=False):
        flags = []
        if property_.readable and not construct_only:
            flags.append("Read")
        if property_.writable and not construct_only:
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
            node = self._transformer.lookup_typenode(node.parent)
            parent_chain.append(node)

        parent_chain.reverse()
        return parent_chain

class DocFormatterC(DocFormatter):
    language = "C"
    mime_type = "text/x-csrc"

    fundamentals = {
        "TRUE": "TRUE",
        "FALSE": "FALSE",
        "NULL": "NULL",
    }

    def format_type(self, type_):
        if isinstance(type_, ast.Array):
            return self.format_type(type_.element_type) + '*'
        elif type_.ctype is not None:
            return type_.ctype
        elif type_.target_fundamental:
            return type_.target_fundamental
        else:
            node = self._transformer.lookup_typenode(type_)
            return getattr(node, 'ctype')

    def format_function_name(self, func):
        if isinstance(func, (ast.Function)):
            return func.symbol
        else:
            return func.name

    def get_parameters(self, node):
        return node.all_parameters

class DocFormatterIntrospectableBase(DocFormatter):
    def should_render_node(self, node):
        if isinstance(node, ast.Record) and node.is_gtype_struct_for is not None:
            return False

        if not getattr(node, "introspectable", True):
            return False

        return super(DocFormatterIntrospectableBase, self).should_render_node(node)

class DocFormatterPython(DocFormatterIntrospectableBase):
    language = "Python"
    mime_type = "text/python"

    fundamentals = {
        "TRUE": "True",
        "FALSE": "False",
        "NULL": "None",
    }

    def should_render_node(self, node):
        if getattr(node, "is_constructor", False):
            return False

        return super(DocFormatterPython, self).should_render_node(node)

    def is_method(self, node):
        if getattr(node, "is_method", False):
            return True

        if isinstance(node, (ast.VFunction)):
            return True

        return False

    def format_parameter_name(self, node, parameter):
        # Force "self" for the first parameter of a method
        if self.is_method(node) and parameter is node.instance_parameter:
            return "self"
        elif isinstance(parameter.type, ast.Varargs):
            return "..."
        else:
            return parameter.argname

    def format_fundamental_type(self, name):
        fundamental_types = {
            "utf8": "unicode",
            "gunichar": "unicode",
            "gchar": "str",
            "guchar": "str",
            "gboolean": "bool",
            "gint": "int",
            "guint": "int",
            "glong": "int",
            "gulong": "int",
            "gint64": "int",
            "guint64": "int",
            "gfloat": "float",
            "gdouble": "float",
            "gchararray": "str",
            "GParam": "GLib.Param",
            "PyObject": "object",
            "GStrv": "[str]",
            "GVariant": "GLib.Variant",
            }

        return fundamental_types.get(name, name)

    def format_type(self, type_):
        if isinstance(type_, (ast.List, ast.Array)):
            return '[' + self.format_type(type_.element_type) + ']'
        elif isinstance(type_, ast.Map):
            return '{%s: %s}' % (self.format_type(type_.key_type),
                                 self.format_type(type_.value_type))
        elif type_.target_giname is not None:
            return type_.target_giname
        else:
            return self.format_fundamental_type(type_.target_fundamental)

    def format_function_name(self, func):
        if func.parent is not None:
            return "%s.%s" % (func.parent.name, func.name)
        else:
            return func.name

    def get_parameters(self, node):
        return node.all_parameters

class DocFormatterGjs(DocFormatterIntrospectableBase):
    language = "Gjs"
    mime_type = "text/x-gjs"

    fundamentals = {
        "TRUE": "true",
        "FALSE": "false",
        "NULL": "null",
    }

    def is_method(self, node):
        if getattr(node, "is_method", False):
            return True

        if isinstance(node, (ast.VFunction)):
            return True

        return False

    def format_fundamental_type(self, name):
        fundamental_types = {
            "utf8": "String",
            "gunichar": "String",
            "gchar": "String",
            "guchar": "String",
            "gboolean": "Boolean",
            "gint": "Number",
            "guint": "Number",
            "glong": "Number",
            "gulong": "Number",
            "gint64": "Number",
            "guint64": "Number",
            "gfloat": "Number",
            "gdouble": "Number",
            "gchararray": "String",
            "GParam": "GLib.Param",
            "PyObject": "Object",
            "GStrv": "[String]",
            "GVariant": "GLib.Variant",
            }

        return fundamental_types.get(name, name)

    def format_type(self, type_):
        if isinstance(type_, (ast.List, ast.Array)):
            return '[' + self.format_type(type_.element_type) + ']'
        elif isinstance(type_, ast.Map):
            return '{%s: %s}' % (self.format_type(type_.key_type),
                                 self.format_type(type_.value_type))
        elif type_.target_fundamental == "none":
            return "void"
        elif type_.target_giname is not None:
            return type_.target_giname
        else:
            return self.format_fundamental_type(type_.target_fundamental)

    def format_function_name(self, func):
        if func.is_method:
            return "%s.prototype.%s" % (func.parent.name, func.name)
        elif func.is_constructor:
            return "%s.%s" % (func.parent.name, func.name)
        else:
            return func.name

    def get_parameters(self, node):
        skip = []
        for param in node.parameters:
            if param.direction == ast.PARAM_DIRECTION_OUT:
                skip.append(param)
            if param.closure_name is not None:
                skip.append(node.get_parameter(param.closure_name))
            if param.destroy_name is not None:
                skip.append(node.get_parameter(param.destroy_name))
            if isinstance(param.type, ast.Array) and param.type.length_param_name is not None:
                skip.append(node.get_parameter(param.type.length_param_name))

        params = []
        for param in node.parameters:
            if param not in skip:
                params.append(param)
        return params

LANGUAGES = {
    "c": DocFormatterC,
    "python": DocFormatterPython,
    "gjs": DocFormatterGjs,
}

class DocWriter(object):
    def __init__(self, transformer, language):
        self._transformer = transformer

        try:
            formatter_class = LANGUAGES[language.lower()]
        except KeyError:
            raise SystemExit("Unsupported language: %s" % (language, ))

        self._formatter = formatter_class(self._transformer)
        self._language = self._formatter.language

        self._lookup = self._get_template_lookup()

    def _get_template_lookup(self):
        if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
            top_srcdir = os.environ['UNINSTALLED_INTROSPECTION_SRCDIR']
            srcdir = os.path.join(top_srcdir, 'giscanner')
        else:
            srcdir = os.path.dirname(__file__)

        template_dir = os.path.join(srcdir, 'doctemplates')

        return TemplateLookup(directories=[template_dir],
                              module_directory=tempfile.mkdtemp(),
                              output_encoding='utf-8')

    def write(self, output):
        try:
            os.makedirs(output)
        except OSError:
            # directory already made
            pass

        nodes = [self._transformer.namespace]
        for node in self._transformer.namespace.itervalues():
            if isinstance(node, ast.Function) and node.moved_to is not None:
                continue
            if getattr(node, 'disguised', False):
                continue
            nodes.append(node)
            if isinstance(node, (ast.Class, ast.Interface, ast.Record)):
                nodes += getattr(node, 'methods', [])
                nodes += getattr(node, 'static_methods', [])
                nodes += getattr(node, 'virtual_methods', [])
                nodes += getattr(node, 'properties', [])
                nodes += getattr(node, 'signals', [])
                nodes += getattr(node, 'constructors', [])
        for node in nodes:
            if self._formatter.should_render_node(node):
                self._render_node(node, output)

    def _render_node(self, node, output):
        namespace = self._transformer.namespace

        node_kind = get_node_kind(node)
        template_name = '%s/%s.tmpl' % (self._language, node_kind)
        page_id = make_page_id(node)

        template = self._lookup.get_template(template_name)
        result = template.render(namespace=namespace,
                                 node=node,
                                 page_id=page_id,
                                 page_style=node_kind,
                                 formatter=self._formatter)

        output_file_name = os.path.join(os.path.abspath(output),
                                        page_id + '.page')
        fp = open(output_file_name, 'w')
        fp.write(result)
        fp.close()
