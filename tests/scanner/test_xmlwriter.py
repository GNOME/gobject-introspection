import unittest

from giscanner.xmlwriter import XMLWriter


class TestXMLWriter(unittest.TestCase):

    def test_various(self):
        w = XMLWriter()
        w.push_tag('repository')
        w.push_tag('namespace')
        w.push_tag('enumeration')
        w.push_tag('member',
                   [('name', 'west'),
                    ('value', '7'),
                    ('c:identifier', 'GTK_ANCHOR_WEST'),
                    ('glib:nick', 'west')])

        w.pop_tag()
        w.pop_tag()
        w.pop_tag()
        x = w.get_xml()
        self.assertTrue('GTK_ANCHOR_WEST' in x)
        lines = x.split('\n')
        self.assertTrue(len(lines[3]) < 80)


if __name__ == '__main__':
    unittest.main()
