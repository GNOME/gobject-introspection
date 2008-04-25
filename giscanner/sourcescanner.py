import os
import subprocess

import giscanner


class SourceSymbol(object):
    def __init__(self, symbol, directives):
        self._symbol = symbol
        self._directives = directives

    def directives(self):
        mapping = {}
        for directive in self._directives:
            mapping[directive.name] = directive.options
        return mapping

    @property
    def ident(self):
        return self._symbol.ident

    @property
    def type(self):
        return self._symbol.type

    @property
    def base_type(self):
        return self._symbol.base_type


class SourceScanner(object):
    def __init__(self):
        self._scanner = giscanner.SourceScanner()
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
            yield SourceSymbol(
                symbol, self._scanner.get_directives(symbol.ident))

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
