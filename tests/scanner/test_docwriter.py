import unittest

from giscanner.docwriter import DocWriter
from giscanner.transformer import Transformer


class TestDocWriter(unittest.TestCase):

    def test_main(self):
        transformer = Transformer(None)
        DocWriter(transformer, "gjs", "devdocs")


if __name__ == '__main__':
    unittest.main()
