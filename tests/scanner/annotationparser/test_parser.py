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
test_parser.py

Tests ensuring the "parse tree" built by annotationparser.py
continues to function correctly.
'''


import difflib
import os
import xml.etree.ElementTree as etree
import unittest

from giscanner.annotationparser import AnnotationParser
from giscanner.ast import Namespace
from giscanner.message import MessageLogger


def parsed2tree(docblock):
    parsed = ''

    if docblock is not None:
        parsed += '<docblock>\n'

        parsed += '  <identifier>\n'
        # An identifier name is always required, but we can't trust our
        # own parser to ensure this when testing so fall back to an empty
        # string when no name has been parsed...
        parsed += '    <name>%s</name>\n' % (docblock.name or '', )
        if docblock.options.values:
            parsed += '    <annotations>\n'
            for key, value in docblock.options.values:
                parsed += '      <annotation>\n'
                parsed += '        <name>%s</name>\n' % (key, )
                if value is not None:
                    options = value.all()
                    parsed += '        <options>\n'
                    for option in options:
                        parsed += '          <option>\n'
                        parsed += '            <name>%s</name>\n' % (option, )
                        if options[option] is not None:
                            parsed += '            <value>%s</value>\n' % (options[option], )
                        parsed += '          </option>\n'
                    parsed += '        </options>\n'
                parsed += '      </annotation>\n'
            parsed += '    </annotations>\n'
        parsed += '  </identifier>\n'

        if docblock.params:
            parsed += '  <parameters>\n'
            for param_name in docblock.params:
                param = docblock.params.get(param_name)
                parsed += '    <parameter>\n'
                parsed += '      <name>%s</name>\n' % (param_name, )
                if param.options.values:
                    parsed += '      <annotations>\n'
                    for key, value in param.options.values:
                        parsed += '        <annotation>\n'
                        parsed += '          <name>%s</name>\n' % (key, )
                        if value is not None:
                            options = value.all()
                            parsed += '          <options>\n'
                            for option in options:
                                parsed += '            <option>\n'
                                parsed += '              <name>%s</name>\n' % (option, )
                                if options[option] is not None:
                                    parsed += '              <value>%s</value>\n' % (options[option], )
                                parsed += '            </option>\n'
                            parsed += '          </options>\n'
                        parsed += '        </annotation>\n'
                    parsed += '      </annotations>\n'
                if param.comment or param.value:
                    parsed += '      <description>%s</description>\n' % (param.comment or param.value, )
                parsed += '    </parameter>\n'
            parsed += '  </parameters>\n'

        if docblock.comment or docblock.value:
            parsed += '  <description>%s</description>\n' % (docblock.comment or docblock.value, )

        if docblock.tags:
            parsed += '  <tags>\n'
            for tag_name in docblock.tags:
                tag = docblock.tags.get(tag_name)
                parsed += '    <tag>\n'
                parsed += '      <name>%s</name>\n' % (tag_name, )
                if tag.options.values:
                    parsed += '      <annotations>\n'
                    for key, value in tag.options.values:
                        parsed += '        <annotation>\n'
                        parsed += '          <name>%s</name>\n' % (key, )
                        if value is not None:
                            options = value.all()
                            parsed += '          <options>\n'
                            for option in options:
                                parsed += '            <option>\n'
                                parsed += '              <name>%s</name>\n' % (option, )
                                if options[option] is not None:
                                    parsed += '              <value>%s</value>\n' % (options[option], )
                                parsed += '            </option>\n'
                            parsed += '          </options>\n'
                        parsed += '        </annotation>\n'
                    parsed += '      </annotations>\n'
                if tag.comment or tag.value:
                    parsed += '      <description>%s</description>\n' % (tag.comment or tag.value, )
                parsed += '    </tag>\n'
            parsed += '  </tags>\n'

        parsed += '<docblock>'

    return parsed


def expected2tree(docblock):
    # Note: this sucks, but we can't rely on etree.tostring() to generate useable output :(

    expected = ''

    if docblock is not None:
        expected += '<docblock>\n'

        if docblock.find('identifier') is not None:
            expected += '  <identifier>\n'
            # Expecting an identifier name is required, don't bother checking if it's there or not
            expected += '    <name>%s</name>\n' % (docblock.find('identifier/name').text, )
            annotations = docblock.find('identifier/annotations')
            if annotations is not None:
                expected += '    <annotations>\n'
                for annotation in annotations.findall('annotation'):
                    expected += '      <annotation>\n'
                    expected += '        <name>%s</name>\n' % (annotation.find('name').text, )
                    if annotation.find('options') is not None:
                        expected += '        <options>\n'
                        for option in annotation.findall('options/option'):
                            expected += '          <option>\n'
                            expected += '            <name>%s</name>\n' % (option.find('name').text, )
                            if option.find('value') is not None:
                                expected += '            <value>%s</value>\n' % (option.find('value').text, )
                            expected += '          </option>\n'
                        expected += '        </options>\n'
                    expected += '      </annotation>\n'
                expected += '    </annotations>\n'
            expected += '  </identifier>\n'

        parameters = docblock.find('parameters')
        if parameters is not None:
            expected += '  <parameters>\n'
            for parameter in parameters.findall('parameter'):
                expected += '    <parameter>\n'
                expected += '      <name>%s</name>\n' % (parameter.find('name').text, )
                annotations = parameter.find('annotations')
                if annotations is not None:
                    expected += '      <annotations>\n'
                    for annotation in parameter.findall('annotations/annotation'):
                        expected += '        <annotation>\n'
                        expected += '          <name>%s</name>\n' % (annotation.find('name').text, )
                        if annotation.find('options') is not None:
                            expected += '          <options>\n'
                            for option in annotation.findall('options/option'):
                                expected += '            <option>\n'
                                expected += '              <name>%s</name>\n' % (option.find('name').text, )
                                if option.find('value') is not None:
                                    expected += '              <value>%s</value>\n' % (option.find('value').text, )
                                expected += '            </option>\n'
                            expected += '          </options>\n'
                        expected += '        </annotation>\n'
                    expected += '      </annotations>\n'
                if parameter.find('description') is not None:
                    expected += '      <description>%s</description>\n' % (parameter.find('description').text, )
                expected += '    </parameter>\n'
            expected += '  </parameters>\n'

        description = docblock.find('description')
        if description is not None:
            expected += '  <description>%s</description>\n' % (description.text, )

        tags = docblock.find('tags')
        if tags is not None:
            expected += '  <tags>\n'
            for tag in tags.findall('tag'):
                expected += '    <tag>\n'
                expected += '      <name>%s</name>\n' % (tag.find('name').text, )
                annotations = tag.find('annotations')
                if annotations is not None:
                    expected += '      <annotations>\n'
                    for annotation in tag.findall('annotations/annotation'):
                        expected += '        <annotation>\n'
                        expected += '          <name>%s</name>\n' % (annotation.find('name').text, )
                        if annotation.find('options') is not None:
                            expected += '          <options>\n'
                            for option in annotation.findall('options/option'):
                                expected += '            <option>\n'
                                expected += '              <name>%s</name>\n' % (option.find('name').text, )
                                if option.find('value') is not None:
                                    expected += '              <value>%s</value>\n' % (option.find('value').text, )
                                expected += '            </option>\n'
                            expected += '          </options>\n'
                        expected += '        </annotation>\n'
                    expected += '      </annotations>\n'
                if tag.find('description') is not None:
                    expected += '      <description>%s</description>\n' % (tag.find('description').text, )
                expected += '    </tag>\n'
            expected += '  </tags>\n'

        expected += '<docblock>'

    return expected


def create_tests(tests_dir, tests_file):
    tests_name = os.path.relpath(tests_file[:-4], tests_dir)
    tests_name = tests_name.replace('/', '.').replace('\\', '.')

    tests_tree = etree.parse(tests_file).getroot()

    fix_cdata_elements = tests_tree.findall('test/commentblock')
    fix_cdata_elements += tests_tree.findall('.//description')

    for element in fix_cdata_elements:
        if element.text:
            element.text = element.text.replace('{{?', '<!')
            element.text = element.text.replace('}}', '>')

    for counter, test in enumerate(tests_tree.findall('test')):
        test_name = 'test_%s.%03d' % (tests_name, counter + 1)
        test_method = TestCommentBlock.__create_test__(test)
        setattr(TestCommentBlock, test_name, test_method)


class TestCommentBlock(unittest.TestCase):
    @classmethod
    def __create_test__(cls, testcase):
        def do_test(self):
            # Parse GTK-Doc comment block
            commentblock = testcase.find('commentblock').text
            parsed_docblock = AnnotationParser().parse_comment_block((commentblock, 'test.c', 1))
            parsed_tree = parsed2tree(parsed_docblock).split('\n')

            # Get expected output
            expected_docblock = testcase.find('docblock')
            expected_tree = expected2tree(expected_docblock).split('\n')

            # Construct a meaningful message
            msg = 'Parsed DocBlock object tree does not match expected output:\n\n'
            msg += '%s\n\n' % (commentblock, )

            diff = difflib.unified_diff(expected_tree, parsed_tree,
                                        'Expected DocBlock', 'Parsed DocBlock',
                                        n=max(len(expected_tree), len(parsed_tree)),
                                        lineterm='')
            for line in diff:
                msg += '%s\n' % (line, )

            # Compare parsed with expected DocBlock tree
            self.assertEqual(parsed_tree, expected_tree, msg)

        return do_test


if __name__ == '__main__':
    # Initialize message logger
    # TODO: at some point it might be a good idea to test warnings emitted
    # by annotationparser here, instead of having them in tests/warn/annotationparser.h?
    namespace = Namespace('Test', '1.0')
    logger = MessageLogger.get(namespace=namespace)
    logger.enable_warnings(False)

    # Load test cases from disc
    tests_dir = os.path.dirname(os.path.abspath(__file__))

    for dirpath, dirnames, filenames in os.walk(tests_dir):
        for filename in filenames:
            tests_file = os.path.join(dirpath, filename)
            if os.path.basename(tests_file).endswith('.xml'):
                create_tests(tests_dir, tests_file)

    # Run test suite
    unittest.main()
