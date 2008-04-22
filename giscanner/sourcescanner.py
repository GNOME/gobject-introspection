import os
import subprocess

import giscanner

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

    def parse_file(self, filename):
        self._parse_one(filename)
        self._filenames.append(filename)

    def parse_macros(self):
        self._scanner.set_macro_scan(True)
        for filename in self._filenames:
            self._parse_one(filename)
        self._scanner.set_macro_scan(False)

    def get_symbols(self):
        for symbol in self._scanner.get_symbols():
            yield symbol

    def dump(self):
        print '-'*30
        for symbol in self._scanner.get_symbols():
            print symbol.ident, symbol.base_type.name, symbol.type

    # Private

    def _parse_one(self, filename):
        if filename.endswith('.c'):
            # FIXME lex only
            return

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
