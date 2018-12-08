from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import unittest
import tempfile
import os

from giscanner.sourcescanner import SourceScanner


class Test(unittest.TestCase):

    def _parse_files(self, code, header=True):
        scanner = SourceScanner()
        tmp_fd, tmp_name = tempfile.mkstemp(suffix=".h" if header else ".c")
        fileobj = os.fdopen(tmp_fd, 'wb')
        with fileobj:
            fileobj.write(code.encode("utf-8"))
        scanner.parse_files([tmp_name])
        os.unlink(tmp_name)
        return scanner

    def test_length_consistency(self):
        scanner = self._parse_files("""
/**
 * Spam:
 */
typedef struct _spam Spam;

/**
 * Eggs:
 */
typedef struct _eggs Eggs;
""")

        self.assertEqual(len(list(scanner.get_symbols())), 2)
        self.assertEqual(len(list(scanner.get_symbols())), 2)
        self.assertEqual(len(list(scanner.get_comments())), 2)
        self.assertEqual(len(list(scanner.get_comments())), 2)
        self.assertFalse(scanner.get_errors())

    def test_parser_error(self):
        scanner = self._parse_files("""
void foo() {
    a =
}""")

        errors = scanner.get_errors()
        self.assertEqual(len(errors), 1)
        self.assertTrue("syntax error" in errors[0])

    def test_ignore_typeof(self):
        # https://gitlab.gnome.org/GNOME/gobject-introspection/merge_requests/71
        scanner = self._parse_files("""
/**
* foo:
*/
void foo(int bar) {
    bar = ((__typeof__(bar)) (foo) (bar));
}
""")
        self.assertEqual(len(list(scanner.get_comments())), 1)
        self.assertFalse(scanner.get_errors())


if __name__ == '__main__':
    unittest.main()
