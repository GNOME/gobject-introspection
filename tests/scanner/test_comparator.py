#!/usr/bin/python
# -*- coding: utf-8 -*-
# TODO: copyright

import unittest
import tempfile
import os
import sys
import __builtin__


os.environ['GI_SCANNER_DISABLE_CACHE'] = '1'
path = os.getenv('UNINSTALLED_INTROSPECTION_SRCDIR', None)
assert path is not None
sys.path.insert(0, path)

# Not correct, but enough to get the tests going uninstalled
__builtin__.__dict__['DATADIR'] = path

from giscanner.girparser import GIRParser
from giscanner.gircomparator import GIRComparator
from giscanner.message import MessageLogger, WARNING, ERROR, FATAL


class TestComparatorErrors(unittest.TestCase):
    def _create_temp_gir_file(self, xml):
        tmp_fd, tmp_name = tempfile.mkstemp(suffix='.gir', text=True)
        file = os.fdopen(tmp_fd, 'wt')
        file.write(xml)
        file.close()

        return tmp_name

    def _test_comparator(self, old_xml, new_xml, wrap=True):
        # Wrap the files in a repository and namespace for convenience.
        if wrap:
            old_xml = self._wrap_gir(old_xml)
            new_xml = self._wrap_gir(new_xml)

        old_tmpfile = self._create_temp_gir_file(old_xml)
        new_tmpfile = self._create_temp_gir_file(new_xml)

        old_parser = GIRParser()
        new_parser = GIRParser()

        old_parser.parse(old_tmpfile)
        new_parser.parse(new_tmpfile)

        old_namespace = old_parser.get_namespace()
        new_namespace = new_parser.get_namespace()

        os.unlink(new_tmpfile)
        os.unlink(old_tmpfile)

        self.assertNotEqual(old_namespace, None)
        self.assertNotEqual(new_namespace, None)

        return GIRComparator(old_namespace, new_namespace)

    def _wrap_gir(self, xml):
        return ('<?xml version="1.0"?>'
                '<repository version="1.2" '
                        'xmlns="http://www.gtk.org/introspection/core/1.0" '
                        'xmlns:c="http://www.gtk.org/introspection/c/1.0">'
                    '<include name="GObject" version="2.0"/>'
                    '<include name="Gio" version="2.0"/>'
                    '<namespace name="N" '
                               'version="1.0" '
                               'shared-library="libtest-1.0.so.0" '
                               'c:identifier-prefixes="Test" '
                               'c:symbol-prefixes="test">'
                        '%s'
                    '</namespace>'
                '</repository>') % xml

    def assertSuccess(self, old_xml, new_xml, wrap=True):
        comparator = self._test_comparator(old_xml, new_xml, wrap)
        self.assertEqual(comparator.compare(), 0)

    def assertErrors(self, old_xml, new_xml, errors, wrap=True):
        comparator = self._test_comparator(old_xml, new_xml, wrap)
        self.assertNotEqual(comparator.compare(), 0)

        output = comparator.get_output()
        self.assertEqual(output, errors)

    def assertInfos(self, old_xml, new_xml, infos, wrap=True):
        comparator = self._test_comparator(old_xml, new_xml, wrap)
        self.assertEqual(comparator.compare(), 0)

        output = comparator.get_output()
        self.assertEqual(output, infos)

    def test_alias_type_changed(self):
        self.assertErrors(
            '<alias name="A"><type name="GObject.Object"/></alias>',
            '<alias name="A"><type name="Gio.InputStream"/></alias>',
            [
                (GIRComparator.OUTPUT_FORWARDS_INCOMPATIBLE,
                 'Alias ‘N.A’ has changed type from ‘GObject.Object’ to its '
                 'subtype ‘Gio.InputStream’.'),
            ])
        self.assertErrors(
            '<alias name="A"><type name="Gio.InputStream"/></alias>',
            '<alias name="A"><type name="GObject.Object"/></alias>',
            [
                (GIRComparator.OUTPUT_BACKWARDS_INCOMPATIBLE,
                 'Alias ‘N.A’ has changed type from ‘Gio.InputStream’ to '
                 '‘GObject.Object’.'),
            ])


if __name__ == '__main__':
    unittest.main()
