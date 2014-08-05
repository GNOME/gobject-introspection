import unittest
import os
import sys

from distutils.cygwinccompiler import Mingw32CCompiler
from distutils.unixccompiler import UnixCCompiler
from distutils.msvccompiler import MSVCCompiler

os.environ['GI_SCANNER_DISABLE_CACHE'] = '1'
path = os.getenv('UNINSTALLED_INTROSPECTION_SRCDIR', None)
assert path is not None
sys.path.insert(0, path)

from giscanner.ccompiler import CCompiler


class TestCompiler(unittest.TestCase):

    def check_windows_default_compiler(self, compiler):
        if os.environ.get('MSYSTEM') == 'MINGW32':
            return isinstance(compiler.compiler, Mingw32CCompiler)
        else:
            return isinstance(compiler.compiler, MSVCCompiler)

    def check_default_compiler(self, compiler, osname=None):
        # If osname is defined and is not 'nt', we always return the default
        # compiler given for the running platform.  Otherwise, on Windows,
        # we see for the presence of MSYSTEM == MINGW32 to see we create a
        # Mingw32CCompiler or MSVCCompiler instance
        if os.name == 'nt':
            if osname is None or osname == os.name:
                return self.check_windows_default_compiler(compiler)
            else:
                return isinstance(compiler.compiler, MSVCCompiler)
        else:
            return (isinstance(compiler.compiler, UnixCCompiler) and
                    not isinstance(compiler.compiler, Mingw32CCompiler))

    def test_compiler_creation(self):
        osname = 'nt'
        # Test distutils compiler detection when forcing osname = 'nt'
        compiler = CCompiler(osname=osname, environ={'MSYSTEM': 'MINGW32'})
        self.assertTrue(isinstance(compiler.compiler, Mingw32CCompiler))

        compiler = CCompiler(osname=osname, compiler_name='mingw32')
        self.assertTrue(isinstance(compiler.compiler, Mingw32CCompiler))

        compiler = CCompiler(osname=osname, compiler_name='msvc')
        self.assertTrue(isinstance(compiler.compiler, MSVCCompiler))

        with self.assertRaises(SystemExit):
            CCompiler(osname=osname, compiler_name='bad_compiler_name')

        if os.name == 'nt':
            compiler = CCompiler(osname=osname)
            self.assertTrue(self.check_windows_default_compiler(compiler))
        else:
            with self.assertRaises(SystemExit):
                CCompiler(osname=osname, compiler_name='bad_compiler_name')

        # Test distutils compiler detection when forcing osname != 'nt'
        osname = 'posix'
        compiler = CCompiler(osname=osname, environ={'MSYSTEM': 'MINGW32'})
        self.assertTrue(self.check_default_compiler(compiler, osname))

        compiler = CCompiler(osname=osname, compiler_name='mingw32')
        self.assertTrue(self.check_default_compiler(compiler, osname))

        compiler = CCompiler(osname=osname, compiler_name='msvc')
        self.assertTrue(self.check_default_compiler(compiler, osname))

        compiler = CCompiler(osname=osname, compiler_name='blah')
        self.assertTrue(self.check_default_compiler(compiler, osname))

        # Test default distutils compiler with ccompiler.py
        compiler = CCompiler()
        self.assertTrue(self.check_default_compiler(compiler))

if __name__ == '__main__':
    unittest.main()
