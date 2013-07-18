# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2012 Dieter Verfaillie <dieterv@optionexplicit.be>
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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#


'''
test_patterns.py

Tests ensuring the regular expression programs used
in annotationparser.py continue to function correctly.
Each regular expression program is tested on input that
should not match and input that should match. When input
should match, resulting symbolic groups are verified
against the expected output.
'''


from giscanner.annotationparser import (SECTION_RE, SYMBOL_RE, PROPERTY_RE,
                                        SIGNAL_RE, PARAMETER_RE, TAG_RE,
                                        COMMENT_END_RE)
from unittest import (TestCase, main)


identifier_section_tests = [
    (SECTION_RE, 'TSIEOCN',
         None),
    (SECTION_RE, 'section',
         None),
    (SECTION_RE, 'section:',
         None),
    (SECTION_RE, 'section:test',
         None),
    (SECTION_RE, 'SECTION',
         None),
    (SECTION_RE, 'SECTION  \t   ',
         None),
    (SECTION_RE, '   \t  SECTION  \t   ',
         None),
    (SECTION_RE, 'SECTION:   \t ',
         None),
    (SECTION_RE, 'SECTION   :   ',
         None),
    (SECTION_RE, '   SECTION : ',
         None),
    (SECTION_RE, 'SECTION:gtkwidget',
         {'delimiter': ':',
          'section_name': 'gtkwidget'}),
    (SECTION_RE, 'SECTION:gtkwidget  ',
         {'delimiter': ':',
          'section_name': 'gtkwidget'}),
    (SECTION_RE, '  SECTION:gtkwidget',
         {'delimiter': ':',
          'section_name': 'gtkwidget'}),
    (SECTION_RE, '  SECTION:gtkwidget\t  ',
         {'delimiter': ':',
          'section_name': 'gtkwidget'}),
    (SECTION_RE, 'SECTION:    gtkwidget   ',
         {'delimiter': ':',
          'section_name': 'gtkwidget'}),
    (SECTION_RE, 'SECTION   :  gtkwidget',
         {'delimiter': ':',
          'section_name': 'gtkwidget'}),
    (SECTION_RE, 'SECTION    gtkwidget \f  ',
         {'delimiter': '',
          'section_name': 'gtkwidget'})]

identifier_symbol_tests = [
    (SYMBOL_RE, 'GBaseFinalizeFunc:',
         {'delimiter': ':',
          'symbol_name': 'GBaseFinalizeFunc',
          'annotations': ''}),
    (SYMBOL_RE, 'gtk_widget_show  ',
         {'delimiter': '',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, '  gtk_widget_show',
         {'delimiter': '',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, '  gtk_widget_show  ',
         {'delimiter': '',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, 'gtk_widget_show:',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, 'gtk_widget_show :',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, 'gtk_widget_show:  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, 'gtk_widget_show :  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, '  gtk_widget_show:',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, '  gtk_widget_show :',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, '  gtk_widget_show:  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, '  gtk_widget_show :  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': ''}),
    (SYMBOL_RE, 'gtk_widget_show (skip)',
         {'delimiter': '',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, 'gtk_widget_show: (skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, 'gtk_widget_show : (skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, 'gtk_widget_show:  (skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, 'gtk_widget_show :  (skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, '  gtk_widget_show:(skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, '  gtk_widget_show :(skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, '  gtk_widget_show:  (skip)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)'}),
    (SYMBOL_RE, '  gtk_widget_show :  (skip)    \t    ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)    \t    '}),
    (SYMBOL_RE, '  gtk_widget_show  :  (skip)   \t    ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)   \t    '}),
    (SYMBOL_RE, 'gtk_widget_show:(skip)(test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)(test1)'}),
    (SYMBOL_RE, 'gtk_widget_show (skip)(test1)',
         {'delimiter': '',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)(test1)'}),
    (SYMBOL_RE, 'gtk_widget_show: (skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, 'gtk_widget_show : (skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, 'gtk_widget_show:  (skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, 'gtk_widget_show :  (skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, '  gtk_widget_show:(skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, '  gtk_widget_show :(skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, '  gtk_widget_show:  (skip) (test1)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)'}),
    (SYMBOL_RE, '  gtk_widget_show :  (skip) (test1)  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1)  '}),
    (SYMBOL_RE, 'gtk_widget_show: (skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, 'gtk_widget_show : (skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, 'gtk_widget_show:  (skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, 'gtk_widget_show :  (skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, '  gtk_widget_show:(skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, '  gtk_widget_show :(skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, '  gtk_widget_show:  (skip) (test1) (test-2)',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)'}),
    (SYMBOL_RE, '  gtk_widget_show :  (skip) (test1) (test-2)  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip) (test1) (test-2)  '}),
    (SYMBOL_RE, '  gtk_widget_show  :  (skip)  (test1)  (test-2)  ',
         {'delimiter': ':',
          'symbol_name': 'gtk_widget_show',
          'annotations': '(skip)  (test1)  (test-2)  '}),
    # constants
    (SYMBOL_RE, 'MY_CONSTANT:',
         {'delimiter': ':',
          'symbol_name': 'MY_CONSTANT',
          'annotations': ''}),
    # structs
    (SYMBOL_RE, 'FooWidget:',
         {'delimiter': ':',
          'symbol_name': 'FooWidget',
          'annotations': ''}),
    # enums
    (SYMBOL_RE, 'Something:',
         {'delimiter': ':',
          'symbol_name': 'Something',
          'annotations': ''})]

identifier_property_tests = [
    # simple property name
    (PROPERTY_RE, 'GtkWidget:name (skip)',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': '',
          'annotations': '(skip)'}),
    (PROPERTY_RE, 'GtkWidget:name',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, ' GtkWidget :name',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, 'GtkWidget: name ',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, '  GtkWidget  :  name  ',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, 'GtkWidget:name:',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'GtkWidget:name:  ',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, '  GtkWidget:name:',
         {'class_name': 'GtkWidget',
          'property_name': 'name',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'Something:name:',
         {'class_name': 'Something',
          'property_name': 'name',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'Something:name:  ',
         {'class_name': 'Something',
          'property_name': 'name',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, '  Something:name:',
         {'class_name': 'Something',
          'property_name': 'name',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'Weird-thing:name:',
         None),
    (PROPERTY_RE, 'really-weird_thing:name:',
         None),
    (PROPERTY_RE, 'GWin32InputStream:handle:',
         {'class_name': 'GWin32InputStream',
          'property_name': 'handle',
          'delimiter': ':',
          'annotations': ''}),
    # property name that contains a dash
    (PROPERTY_RE, 'GtkWidget:double-buffered (skip)',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': '',
          'annotations': '(skip)'}),
    (PROPERTY_RE, 'GtkWidget:double-buffered',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, ' GtkWidget :double-buffered',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, 'GtkWidget: double-buffered ',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, '  GtkWidget  :  double-buffered  ',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': '',
          'annotations': ''}),
    (PROPERTY_RE, 'GtkWidget:double-buffered:',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'GtkWidget:double-buffered:  ',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, '  GtkWidget:double-buffered:',
         {'class_name': 'GtkWidget',
          'property_name': 'double-buffered',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'Something:double-buffered:',
         {'class_name': 'Something',
          'property_name': 'double-buffered',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'Something:double-buffered:  ',
         {'class_name': 'Something',
          'property_name': 'double-buffered',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, '  Something:double-buffered:',
         {'class_name': 'Something',
          'property_name': 'double-buffered',
          'delimiter': ':',
          'annotations': ''}),
    (PROPERTY_RE, 'Weird-thing:double-buffered:',
         None),
    (PROPERTY_RE, 'really-weird_thing:double-buffered:',
         None),
    (PROPERTY_RE, ' GMemoryOutputStream:realloc-function: (skip)',
         {'class_name': 'GMemoryOutputStream',
          'property_name': 'realloc-function',
          'delimiter': ':',
          'annotations': '(skip)'})]

identifier_signal_tests = [
    # simple property name
    (SIGNAL_RE, 'GtkWidget::changed: (skip)',
         {'class_name': 'GtkWidget',
          'signal_name': 'changed',
          'delimiter': ':',
          'annotations': '(skip)'}),
    (SIGNAL_RE, 'GtkWidget::changed:',
         {'class_name': 'GtkWidget',
          'signal_name': 'changed',
          'delimiter': ':',
          'annotations': ''}),
    (SIGNAL_RE, 'Something::changed:',
         {'class_name': 'Something',
          'signal_name': 'changed',
          'delimiter': ':',
          'annotations': ''}),
    (SIGNAL_RE, 'Weird-thing::changed:',
         None),
    (SIGNAL_RE, 'really-weird_thing::changed:',
         None),
    # signal name that contains a dash
    (SIGNAL_RE, 'GtkWidget::hierarchy-changed: (skip)',
         {'class_name': 'GtkWidget',
          'signal_name': 'hierarchy-changed',
          'delimiter': ':',
          'annotations': '(skip)'}),
    (SIGNAL_RE, 'GtkWidget::hierarchy-changed:',
         {'class_name': 'GtkWidget',
          'signal_name': 'hierarchy-changed',
          'delimiter': ':',
          'annotations': ''}),
    (SIGNAL_RE, 'Something::hierarchy-changed:',
         {'class_name': 'Something',
          'signal_name': 'hierarchy-changed',
          'delimiter': ':',
          'annotations': ''}),
    (SIGNAL_RE, 'Weird-thing::hierarchy-changed:',
         None),
    (SIGNAL_RE, 'really-weird_thing::hierarchy-changed:',
         None)]

parameter_tests = [
    (PARAMETER_RE, '@Short_description: Base class for all widgets  ',
         {'parameter_name': 'Short_description',
          'annotations': '',
          'delimiter': '',
          'description': 'Base class for all widgets'}),
    (PARAMETER_RE, '@...: the value of the first property, followed optionally by more',
         {'parameter_name': '...',
          'annotations': '',
          'delimiter': '',
          'description': 'the value of the first property, followed optionally by more'}),
    (PARAMETER_RE, '@widget: a #GtkWidget',
         {'parameter_name': 'widget',
          'annotations': '',
          'delimiter': '',
          'description': 'a #GtkWidget'}),
    (PARAMETER_RE, '@widget_pointer: (inout) (transfer none): '
                   'address of a variable that contains @widget',
         {'parameter_name': 'widget_pointer',
          'annotations': '(inout) (transfer none)',
          'delimiter': ':',
          'description': 'address of a variable that contains @widget'}),
    (PARAMETER_RE, '@weird_thing: (inout) (transfer none) (allow-none) (attribute) (destroy) '
                   '(foreign) (inout) (out) (transfer) (skip) (method): some weird @thing',
         {'parameter_name': 'weird_thing',
          'annotations': '(inout) (transfer none) (allow-none) (attribute) (destroy) '
                            '(foreign) (inout) (out) (transfer) (skip) (method)',
          'delimiter': ':',
          'description': 'some weird @thing'}),
    (PARAMETER_RE, '@data: a pointer to the element data. The data may be moved as elements '
                   'are added to the #GByteArray.',
         {'parameter_name': 'data',
          'annotations': '',
          'delimiter': '',
          'description': 'a pointer to the element data. The data may be moved as elements '
                            'are added to the #GByteArray.'}),
    (PARAMETER_RE, '@a: a #GSequenceIter',
         {'parameter_name': 'a',
          'annotations': '',
          'delimiter': '',
          'description': 'a #GSequenceIter'}),
    (PARAMETER_RE, '@keys: (array length=n_keys) (element-type GQuark) (allow-none):',
         {'parameter_name': 'keys',
          'annotations': '(array length=n_keys) (element-type GQuark) (allow-none)',
          'delimiter': ':',
          'description': ''})]

tag_tests = [
    (TAG_RE, 'Since 3.0',
         None),
    (TAG_RE, 'Since: 3.0',
         {'tag_name': 'Since',
          'annotations': '',
          'delimiter': '',
          'description': '3.0'}),
    (TAG_RE, 'Attributes: (inout) (transfer none): some note about attributes',
         {'tag_name': 'Attributes',
          'annotations': '(inout) (transfer none)',
          'delimiter': ':',
          'description': 'some note about attributes'}),
    (TAG_RE, 'Rename to: something_else',
         {'tag_name': 'Rename to',
          'annotations': '',
          'delimiter': '',
          'description': 'something_else'}),
    (TAG_RE, '@Deprecated: Since 2.8, reference counting is done atomically',
         None),
    (TAG_RE, 'Returns %TRUE and does weird things',
         None),
    (TAG_RE, 'Returns: a #GtkWidget',
         {'tag_name': 'Returns',
          'annotations': '',
          'delimiter': '',
          'description': 'a #GtkWidget'}),
    (TAG_RE, 'Return value: (transfer none): The binary data that @text responds. '
             'This pointer',
         {'tag_name': 'Return value',
          'annotations': '(transfer none)',
          'delimiter': ':',
          'description': 'The binary data that @text responds. This pointer'}),
    (TAG_RE, 'Return value: (transfer full) (array length=out_len) (element-type guint8):',
         {'tag_name': 'Return value',
          'annotations': '(transfer full) (array length=out_len) (element-type guint8)',
          'delimiter': ':',
          'description': ''}),
    (TAG_RE, 'Returns: A boolean value, but let me tell you a bit about this boolean.  It',
         {'tag_name': 'Returns',
          'annotations': '',
          'delimiter': '',
          'description': 'A boolean value, but let me tell you a bit about this boolean.  '
                         'It'}),
    (TAG_RE, 'Returns: (transfer container) (element-type GObject.ParamSpec): a',
         {'tag_name': 'Returns',
          'annotations': '(transfer container) (element-type GObject.ParamSpec)',
          'delimiter': ':',
          'description': 'a'}),
    (TAG_RE, 'Return value: (type GLib.HashTable<utf8,GLib.HashTable<utf8,utf8>>) '
             '(transfer full):',
         {'tag_name': 'Return value',
          'annotations': '(type GLib.HashTable<utf8,GLib.HashTable<utf8,utf8>>) '
                         '(transfer full)',
          'delimiter': ':',
          'description': ''})]

comment_end_tests = [
    (COMMENT_END_RE, '*/',
         {'description': ''}),
    (COMMENT_END_RE, '   */',
         {'description': ''}),
    (COMMENT_END_RE, ' */ ',
         {'description': ''}),
    (COMMENT_END_RE, '**/',
         {'description': ''}),
    (COMMENT_END_RE, ' **/',
         {'description': ''}),
    (COMMENT_END_RE, ' **/ ',
         {'description': ''}),
    (COMMENT_END_RE, 'test */',
         {'description': 'test'}),
    (COMMENT_END_RE, ' test*/',
         {'description': 'test'}),
    (COMMENT_END_RE, 'test **/',
         {'description': 'test'}),
    (COMMENT_END_RE, ' test**/',
         {'description': 'test'}),
    (COMMENT_END_RE, 'test *****/',
         {'description': 'test'}),
    (COMMENT_END_RE, ' test*****/',
         {'description': 'test'})]


def create_tests(tests_name, testcases):
    for (index, testcase) in enumerate(testcases):
        real_test_name = '%s_%03d' % (tests_name, index)

        test_method = TestProgram.__create_test__(testcase)
        test_method.__name__ = real_test_name
        setattr(TestProgram, real_test_name, test_method)


class TestProgram(TestCase):
    @classmethod
    def __create_test__(cls, testcase):
        def do_test(self):
            (program, text, expected) = testcase

            match = program.match(text)

            if match is not None:
                msg = 'Test matched pattern but specifies no expected named groups.'
                self.assertTrue(isinstance(expected, dict), msg)

                for group in match.groupdict().keys():
                    msg = 'Test case is missing expected results for named group "%s".' % (group)
                    self.assertTrue(group in expected.keys(), msg)

            if expected is None:
                msg = 'Program matched text but shouldn\'t:\n"%s"'
                self.assertTrue(match is None, msg % (text, ))
            else:
                msg = 'Program should match text but didn\'t:\n"%s"'
                self.assertTrue(match is not None, msg % (text, ))

                for key, value in expected.items():
                    msg = 'expected "%s" for "%s" but match returned "%s"'
                    msg = msg % (value, key, match.group(key))
                    self.assertEqual(match.group(key), value, msg)

        return do_test


if __name__ == '__main__':
    # Create tests from data
    create_tests('test_identifier_section', identifier_section_tests)
    create_tests('test_identifier_symbol', identifier_symbol_tests)
    create_tests('test_identifier_property', identifier_property_tests)
    create_tests('test_identifier_signal', identifier_signal_tests)
    create_tests('test_parameter', parameter_tests)
    create_tests('test_tag', tag_tests)
    create_tests('test_comment_end', comment_end_tests)

    # Run test suite
    main()
