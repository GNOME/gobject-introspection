import unittest
import tempfile
import os

from giscanner.sourcescanner import SourceScanner


two_typedefs_source = """
/**
 * Spam:
 */
typedef struct _spam Spam;

/**
 * Eggs:
 */
typedef struct _eggs Eggs;
"""


class Test(unittest.TestCase):
    def setUp(self):
        self.ss = SourceScanner()
        tmp_fd, tmp_name = tempfile.mkstemp()
        file = os.fdopen(tmp_fd, 'wt')
        file.write(two_typedefs_source)
        file.close()

        self.ss.parse_files([tmp_name])

    def test_get_symbols_length_consistency(self):
        self.assertEqual(len(list(self.ss.get_symbols())), 2)
        self.assertEqual(len(list(self.ss.get_symbols())), 2)

    def test_get_comments_length_consistency(self):
        self.assertEqual(len(list(self.ss.get_comments())), 2)
        self.assertEqual(len(list(self.ss.get_comments())), 2)


if __name__ == '__main__':
    unittest.main()
