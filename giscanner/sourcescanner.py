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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

import os
import subprocess

from . import _giscanner


class SourceType(object):
    def __init__(self, scanner, stype):
        self._scanner = scanner
        self._stype = stype

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
    def child_list(self):
        for symbol in self._stype.child_list:
            if symbol is None:
                continue
            yield SourceSymbol(self._scanner, symbol)


class SourceSymbol(object):
    def __init__(self, scanner, symbol):
        self._scanner = scanner
        self._symbol = symbol

    def directives(self):
        mapping = {}
        for directive in self._scanner.get_directives(self._symbol.ident):
            mapping[directive.name] = directive.options
        return mapping

    @property
    def const_int(self):
        return self._symbol.const_int

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


class SourceScanner(object):
    def __init__(self):
        self._scanner = _giscanner.SourceScanner()
        self._filenames = []
        self._cpp_options = []

    # Public API

    def set_cpp_options(self, includes, defines, undefines):
        for prefix, args in [('-I', includes),
                             ('-D', defines),
                             ('-U', undefines)]:
            for arg in (args or []):
                opt = prefix + arg
                if not opt in self._cpp_options:
                    self._cpp_options.append(opt)

    def parse_files(self, filenames):
        headers = []
        for filename in filenames:
            if filename.endswith('.c'):
                filename = os.path.abspath(filename)
                self._scanner.lex_filename(filename)
            else:
                headers.append(filename)

        for filename in headers:
            self._parse_one(filename)
            self._filenames.append(filename)

    def parse_macros(self):
        self._scanner.set_macro_scan(True)
        for filename in self._filenames:
            self._parse_one(filename)
        self._scanner.set_macro_scan(False)

    def get_symbols(self):
        for symbol in self._scanner.get_symbols():
            yield SourceSymbol(self._scanner, symbol)

    def dump(self):
        print '-'*30
        for symbol in self._scanner.get_symbols():
            print symbol.ident, symbol.base_type.name, symbol.type

    # Private

    def _parse_one(self, filename):
        filename = os.path.abspath(filename)
        proc = self._preprocess(filename)
        fd = proc.stdout.fileno()
        if proc is None:
            return

        self._scanner.parse_file(fd, filename)

    def _preprocess(self, filename):
        cpp_args = [
            'cpp',
            '-C',
            '-U__GNUC__',
            '-I.',
            ]
        cpp_args += self._cpp_options
        proc = subprocess.Popen(
            cpp_args,
            bufsize=4096,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            )
        proc.stdin.write('#include <%s>\n' % (filename,))
        proc.stdin.close()
        return proc
