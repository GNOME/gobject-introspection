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
import os
import subprocess
import tempfile

from .libtoolimporter import LibtoolImporter
from .message import Position

with LibtoolImporter(None, None):
    if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
        from _giscanner import SourceScanner as CSourceScanner
    else:
        from giscanner._giscanner import SourceScanner as CSourceScanner

HEADER_EXTS = ['.h', '.hpp', '.hxx']
SOURCE_EXTS = ['.c', '.cpp', '.cc', '.cxx']
ALL_EXTS = SOURCE_EXTS + HEADER_EXTS

(CSYMBOL_TYPE_INVALID,
 CSYMBOL_TYPE_ELLIPSIS,
 CSYMBOL_TYPE_CONST,
 CSYMBOL_TYPE_OBJECT,
 CSYMBOL_TYPE_FUNCTION,
 CSYMBOL_TYPE_STRUCT,
 CSYMBOL_TYPE_UNION,
 CSYMBOL_TYPE_ENUM,
 CSYMBOL_TYPE_TYPEDEF,
 CSYMBOL_TYPE_MEMBER) = range(10)

(CTYPE_INVALID,
 CTYPE_VOID,
 CTYPE_BASIC_TYPE,
 CTYPE_TYPEDEF,
 CTYPE_STRUCT,
 CTYPE_UNION,
 CTYPE_ENUM,
 CTYPE_POINTER,
 CTYPE_ARRAY,
 CTYPE_FUNCTION) = range(10)

STORAGE_CLASS_NONE = 0
STORAGE_CLASS_TYPEDEF = 1 << 1
STORAGE_CLASS_EXTERN = 1 << 2
STORAGE_CLASS_STATIC = 1 << 3
STORAGE_CLASS_AUTO = 1 << 4
STORAGE_CLASS_REGISTER = 1 << 5

TYPE_QUALIFIER_NONE = 0
TYPE_QUALIFIER_CONST = 1 << 1
TYPE_QUALIFIER_RESTRICT = 1 << 2
TYPE_QUALIFIER_VOLATILE = 1 << 3
TYPE_QUALIFIER_EXTENSION = 1 << 4

FUNCTION_NONE = 0
FUNCTION_INLINE = 1 << 1

(UNARY_ADDRESS_OF,
 UNARY_POINTER_INDIRECTION,
 UNARY_PLUS,
 UNARY_MINUS,
 UNARY_BITWISE_COMPLEMENT,
 UNARY_LOGICAL_NEGATION) = range(6)


def symbol_type_name(symbol_type):
    return {
        CSYMBOL_TYPE_INVALID: 'invalid',
        CSYMBOL_TYPE_ELLIPSIS: 'ellipsis',
        CSYMBOL_TYPE_CONST: 'const',
        CSYMBOL_TYPE_OBJECT: 'object',
        CSYMBOL_TYPE_FUNCTION: 'function',
        CSYMBOL_TYPE_STRUCT: 'struct',
        CSYMBOL_TYPE_UNION: 'union',
        CSYMBOL_TYPE_ENUM: 'enum',
        CSYMBOL_TYPE_TYPEDEF: 'typedef',
        CSYMBOL_TYPE_MEMBER: 'member'}.get(symbol_type)


def ctype_name(ctype):
    return {
        CTYPE_INVALID: 'invalid',
        CTYPE_VOID: 'void',
        CTYPE_BASIC_TYPE: 'basic',
        CTYPE_TYPEDEF: 'typedef',
        CTYPE_STRUCT: 'struct',
        CTYPE_UNION: 'union',
        CTYPE_ENUM: 'enum',
        CTYPE_POINTER: 'pointer',
        CTYPE_ARRAY: 'array',
        CTYPE_FUNCTION: 'function'}.get(ctype)


class SourceType(object):
    __members__ = ['type', 'base_type', 'name', 'type_qualifier',
                   'child_list', 'is_bitfield']

    def __init__(self, scanner, stype):
        self._scanner = scanner
        self._stype = stype

    def __repr__(self):
        return '<%s type=%r name=%r>' % (
            self.__class__.__name__,
            ctype_name(self.type),
            self.name)

    @property
    def type(self):
        return self._stype.type

    @property
    def base_type(self):
        if self._stype.base_type is not None:
            return SourceType(self._scanner, self._stype.base_type)

    @property
    def name(self):
        return self._stype.name

    @property
    def type_qualifier(self):
        return self._stype.type_qualifier

    @property
    def child_list(self):
        for symbol in self._stype.child_list:
            if symbol is None:
                continue
            yield SourceSymbol(self._scanner, symbol)

    @property
    def is_bitfield(self):
        return self._stype.is_bitfield


class SourceSymbol(object):
    __members__ = ['const_int', 'const_double', 'const_string', 'const_boolean',
                   'ident', 'type', 'base_type']

    def __init__(self, scanner, symbol):
        self._scanner = scanner
        self._symbol = symbol

    def __repr__(self):
        src = self.source_filename
        if src:
            line = self.line
            if line:
                src += ':%r' % (line, )
        return '<%s type=%r ident=%r src=%r>' % (
            self.__class__.__name__,
            symbol_type_name(self.type),
            self.ident,
            src)

    @property
    def const_int(self):
        return self._symbol.const_int

    @property
    def const_double(self):
        return self._symbol.const_double

    @property
    def const_string(self):
        return self._symbol.const_string

    @property
    def const_boolean(self):
        return self._symbol.const_boolean

    @property
    def ident(self):
        return self._symbol.ident

    @property
    def type(self):
        return self._symbol.type

    @property
    def base_type(self):
        if self._symbol.base_type is not None:
            return SourceType(self._scanner, self._symbol.base_type)

    @property
    def source_filename(self):
        return self._symbol.source_filename

    @property
    def line(self):
        return self._symbol.line

    @property
    def private(self):
        return self._symbol.private

    @property
    def position(self):
        return Position(self._symbol.source_filename,
                        self._symbol.line)


class SourceScanner(object):

    def __init__(self):
        self._scanner = CSourceScanner()
        self._filenames = []
        self._cpp_options = []

    # Public API

    def set_cpp_options(self, includes, defines, undefines, cflags=[]):
        self._cpp_options.extend(cflags)
        for prefix, args in [('-I', [os.path.realpath(f) for f in includes]),
                             ('-D', defines),
                             ('-U', undefines)]:
            for arg in (args or []):
                opt = prefix + arg
                if opt not in self._cpp_options:
                    self._cpp_options.append(opt)

    def parse_files(self, filenames):
        for filename in filenames:
            # self._scanner expects file names to be canonicalized and symlinks to be resolved
            filename = os.path.realpath(filename)
            self._scanner.append_filename(filename)
            self._filenames.append(filename)

        headers = []
        for filename in self._filenames:
            if os.path.splitext(filename)[1] in SOURCE_EXTS:
                self._scanner.lex_filename(filename)
            else:
                headers.append(filename)

        self._parse(headers)

    def parse_macros(self, filenames):
        self._scanner.set_macro_scan(True)
        # self._scanner expects file names to be canonicalized and symlinks to be resolved
        self._scanner.parse_macros([os.path.realpath(f) for f in filenames])
        self._scanner.set_macro_scan(False)

    def get_symbols(self):
        for symbol in self._scanner.get_symbols():
            yield SourceSymbol(self._scanner, symbol)

    def get_comments(self):
        return self._scanner.get_comments()

    def dump(self):
        print '-' * 30
        for symbol in self._scanner.get_symbols():
            print symbol.ident, symbol.base_type.name, symbol.type

    # Private

    def _parse(self, filenames):
        if not filenames:
            return

        defines = ['__GI_SCANNER__']
        undefs = []
        cpp_args = os.environ.get('CC', 'cc').split()  # support CC="ccache gcc"
        if 'cl' in cpp_args:
            # The Microsoft compiler/preprocessor (cl) does not accept
            # source input from stdin (the '-' flag), so we need
            # some help from gcc from MinGW/Cygwin or so.
            # Note that the generated dumper program is
            # still built and linked by Visual C++.
            cpp_args = ['gcc']
        cpp_args += os.environ.get('CPPFLAGS', '').split()
        cpp_args += os.environ.get('CFLAGS', '').split()
        cpp_args += ['-E', '-C', '-I.', '-']
        cpp_args += self._cpp_options

        # We expect the preprocessor to remove macros. If debugging is turned
        # up high enough that won't happen, so strip these out. Bug #720504
        for flag in ['-g3', '-ggdb3', '-gstabs3', '-gcoff3', '-gxcoff3', '-gvms3']:
            try:
                cpp_args.remove(flag)
            except ValueError:
                pass

        proc = subprocess.Popen(cpp_args,
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE)

        for define in defines:
            proc.stdin.write('#ifndef %s\n' % (define, ))
            proc.stdin.write('# define %s\n' % (define, ))
            proc.stdin.write('#endif\n')
        for undef in undefs:
            proc.stdin.write('#undef %s\n' % (undef, ))
        for filename in filenames:
            proc.stdin.write('#include <%s>\n' % (filename, ))
        proc.stdin.close()

        tmp_fd, tmp_name = tempfile.mkstemp()
        fp = os.fdopen(tmp_fd, 'w+b')
        while True:
            data = proc.stdout.read(4096)
            if data is None:
                break
            fp.write(data)
            if len(data) < 4096:
                break
        fp.seek(0, 0)

        assert proc, 'Proc was none'
        proc.wait()
        if proc.returncode != 0:
            raise SystemExit('Error while processing the source.')

        self._scanner.parse_file(fp.fileno())
        fp.close()
        os.unlink(tmp_name)
