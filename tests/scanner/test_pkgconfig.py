# -*- coding: UTF-8 -*-
#
# GObject-Introspection - a framework for introspecting GObject libraries
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

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import contextlib
import os
import sys
import tempfile
import tempfile
import textwrap
import time
import unittest

from giscanner import pkgconfig


def get_pkg_config():
    """Return value of PKG_CONFIG environment variable or None if unset."""
    return os.environ.get('PKG_CONFIG', None)


def set_pkg_config(value):
    """Set value of PKG_CONFIG environment variable or unsets it when value is None."""
    if value is None:
        del os.environ['PKG_CONFIG']
    else:
        os.environ['PKG_CONFIG'] = value


@contextlib.contextmanager
def pkg_config_script(code):
    """Points PKG_CONFIG environment variable to an executable file with given python code.
    Common leading whitespace is removed from code for convenience."""

    with tempfile.NamedTemporaryFile(mode='wt', suffix='.py', delete=False) as file:
        file.write('#!{}\n'.format(sys.executable))
        file.write(textwrap.dedent(code))
        os.chmod(file.name, 0o777)

    try:
        pkg_config = get_pkg_config()
        set_pkg_config(file.name)
        yield
    finally:
        os.unlink(file.name)
        set_pkg_config(pkg_config)


class PkgConfigTest(unittest.TestCase):
    def test_non_zero_exit_code(self):
        """Checks that non-zero exit code from pkg-config results in exception."""
        s = """
        import sys
        sys.exit(1)
        """
        with self.assertRaises(pkgconfig.PkgConfigError):
            with pkg_config_script(s):
                pkgconfig.cflags(['foo'])

    def test_cflags(self):
        """Checks arguments passed to pkg-config when asking for --cflags."""
        s = """
        import sys
        args = sys.argv[1:]
        assert len(args) == 4
        assert args[0] == '--cflags'
        assert args[1] == 'foo-1.0'
        assert args[2] == 'bar-2.0'
        assert args[3] == 'baz'
        """
        with pkg_config_script(s):
            pkgconfig.cflags(['foo-1.0', 'bar-2.0', 'baz'])

    def test_libs(self):
        """Checks arguments passed to pkg-config when asking for --libs."""
        s = """
        import sys
        args = sys.argv[1:]
        assert len(args) == 3
        assert args[0] == '--libs'
        assert args[1] == 'a'
        assert args[2] == 'b-42.0'
        """
        with pkg_config_script(s):
            pkgconfig.libs(['a', 'b-42.0'])

    @unittest.skipIf(
        sys.version_info < (3, 0),
        "Python 2 defaults to ascii encoding in text file I/O and nothing is done to change that")
    def test_non_ascii_output(self):
        with pkg_config_script("""print("-L'zażółć gęślą jaźń'")"""):
            flags = pkgconfig.cflags(['test-1.0'])
            self.assertEqual(flags, ["-Lzażółć gęślą jaźń"])

        with pkg_config_script("""print('-Lé')"""):
            flags = pkgconfig.cflags(['test-1.0'])
            self.assertEqual(flags, ['-Lé'])

    def test_shell_word_spliting_rules(self):
        # Regression test for issue #171.
        with pkg_config_script("""print('-L"/usr/lib64" -lgit2')"""):
            flags = pkgconfig.cflags(['foo-2.0'])
            self.assertEqual(flags, ['-L/usr/lib64', '-lgit2'])

        # Macro define for a C string literal.
        with pkg_config_script('''print("""-DLOG='"HELLO"'""")'''):
            flags = pkgconfig.cflags(['bar-3.0'])
            self.assertEqual(flags, ['-DLOG="HELLO"'])


if __name__ == '__main__':
    unittest.main()
