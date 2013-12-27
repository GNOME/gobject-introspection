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

from giscanner import ast
from giscanner.sourcescanner import SourceScanner
from giscanner.transformer import Transformer
from giscanner.message import MessageLogger, WARNING, ERROR, FATAL


def create_scanner_from_source_string(source):
    ss = SourceScanner()
    tmp_fd, tmp_name = tempfile.mkstemp(suffix='.h', text=True)
    file = os.fdopen(tmp_fd, 'wt')
    file.write(source)
    file.close()

    ss.parse_files([tmp_name])
    return ss


def load_namespace_from_source_string(namespace, source):
    ss = create_scanner_from_source_string(source)
    xformer = Transformer(namespace)
    xformer.parse(ss.get_symbols())


class TestStructTypedefs(unittest.TestCase):
    def setUp(self):
        # Hack to set logging singleton
        self.namespace = ast.Namespace('Test', '1.0')
        logger = MessageLogger.get(namespace=self.namespace)
        logger.enable_warnings((WARNING, ERROR, FATAL))

    def test_anonymous_typedef(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                int value;
            } TestStruct;
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)

    def test_typedef_before(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct _TestStruct TestStruct;
            struct _TestStruct {
                int value;
            };
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)

    @unittest.expectedFailure
    def test_typedef_after(self):
        load_namespace_from_source_string(self.namespace, """
            struct _TestStruct {
                int value;
            };
            typedef struct _TestStruct TestStruct;
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)

    @unittest.expectedFailure
    def test_tag_and_typedef(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct _TestStruct {
                int value;
            } TestStruct;
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)

    def test_struct_tag_only(self):
        load_namespace_from_source_string(self.namespace, """
            struct TestStruct {
                int value;
            };
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)

    def test_struct_aliases(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                int value;
            } TestStruct;
            typedef TestStruct TestStructAlias1;
            typedef TestStruct TestStructAlias2;
            """)
        self.assertEqual(len(self.namespace.names), 3)

        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)

        alias = self.namespace.get('StructAlias1')
        self.assertTrue(isinstance(alias, ast.Alias))
        self.assertEqual(alias.target, node)
        self.assertEqual(alias.ctype, 'TestStructAlias1')

        alias = self.namespace.get('StructAlias2')
        self.assertTrue(isinstance(alias, ast.Alias))
        self.assertEqual(alias.target, node)
        self.assertEqual(alias.ctype, 'TestStructAlias2')

    def test_struct_tag_aliases_before(self):
        # This test is similar to how GObject and GInitiallyUnowned are setup
        load_namespace_from_source_string(self.namespace, """
            typedef struct _TestStruct TestStruct;
            typedef struct _TestStruct TestStructAlias;
            struct _TestStruct {
                int value;
            };
            """)
        self.assertEqual(len(self.namespace.names), 2)

        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)
        self.assertEqual(node.ctype, 'TestStruct')

        shared = self.namespace.get('StructAlias')
        self.assertTrue(shared is not None)
        self.assertTrue(isinstance(shared, ast.Record))
        self.assertTrue(shared.disguised)
        self.assertEqual(len(shared.fields), 0)
        self.assertEqual(shared.ctype, 'TestStructAlias')

    @unittest.expectedFailure
    def test_struct_tag_aliases_after(self):
        load_namespace_from_source_string(self.namespace, """
            struct _TestStruct {
                int value;
            };
            typedef struct _TestStruct TestStruct;
            typedef struct _TestStruct TestStructAlias;
            """)
        self.assertEqual(len(self.namespace.names), 2)

        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(len(node.fields), 1)
        self.assertEqual(node.ctype, 'TestStruct')

        shared = self.namespace.get('StructAlias')
        self.assertTrue(shared is not None)
        self.assertTrue(isinstance(shared, ast.Record))
        self.assertTrue(shared.disguised)
        self.assertEqual(len(shared.fields), 0)
        self.assertEqual(shared.ctype, 'TestStructAlias')

    def test_struct_pointer(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                int value;
            } TestStruct;
            typedef TestStruct* TestStructPtr;
            """)
        self.assertEqual(len(self.namespace.names), 2)

        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertEqual(len(node.fields), 1)
        self.assertEqual(node.ctype, 'TestStruct')

        ptr = self.namespace.get('StructPtr')
        self.assertTrue(ptr is not None)
        self.assertTrue(isinstance(ptr, ast.Alias))
        self.assertEqual(ptr.ctype, 'TestStructPtr')
        # This loses type information about the struct which seems broken.
        self.assertEqual(ptr.target, ast.TYPE_ANY)

    def test_struct_tag_pointer(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct _TestStruct TestStruct;
            struct _TestStruct{
                int value;
            };
            typedef struct _TestStruct* TestStructPtr;
            """)
        self.assertEqual(len(self.namespace.names), 2)

        node = self.namespace.get('Struct')
        self.assertTrue(node is not None)
        self.assertTrue(isinstance(node, ast.Record))
        self.assertFalse(node.disguised)
        self.assertEqual(node.ctype, 'TestStruct')
        self.assertEqual(len(node.fields), 1)

        ptr = self.namespace.get('StructPtr')
        self.assertTrue(ptr is not None)
        # This currently gives a disguised Record instead of an Alias
        self.assertTrue(isinstance(ptr, ast.Record))
        self.assertTrue(ptr.disguised)
        self.assertEqual(len(ptr.fields), 0)
        self.assertEqual(ptr.ctype, 'TestStructPtr')


class TestNestedStructs(unittest.TestCase):
    def setUp(self):
        # Hack to set logging singleton
        self.namespace = ast.Namespace('Test', '1.0')
        logger = MessageLogger.get(namespace=self.namespace)
        logger.enable_warnings((WARNING, ERROR, FATAL))

    def test_nested_named(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                int value;
            } TestSimpleStruct;

            typedef struct {
                TestSimpleStruct nested_struct;
            } TestStructWithNested;
            """)
        self.assertEqual(len(self.namespace.names), 2)
        node = self.namespace.get('StructWithNested')
        self.assertEqual(len(node.fields), 1)

        simple = self.namespace.get('SimpleStruct')
        self.assertTrue(node is not None)

        field = node.fields[0]
        self.assertTrue(field is not None)
        self.assertTrue(isinstance(field, ast.Field))
        self.assertEqual(field.type, simple)
        self.assertEqual(field.name, 'nested_struct')

    def test_nested_anonymous(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                struct {
                    int value;
                };
            } TestStructWithNestedAnon;
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('StructWithNestedAnon')
        self.assertEqual(len(node.fields), 1)

        field = node.fields[0]
        self.assertTrue(field is not None)
        self.assertTrue(isinstance(field, ast.Field))
        self.assertEqual(field.name, None)

        anon = field.anonymous_node
        self.assertTrue(isinstance(anon, ast.Record))
        self.assertEqual(len(anon.fields), 1)

        anon_field = anon.fields[0]
        self.assertTrue(anon_field is not None)
        self.assertTrue(isinstance(anon_field, ast.Field))
        self.assertEqual(anon_field.name, 'value')

    def test_nested(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                struct {
                    int value;
                } nested;
            } TestStructWithNested;
            """)
        self.assertEqual(len(self.namespace.names), 1)
        node = self.namespace.get('StructWithNested')
        self.assertEqual(len(node.fields), 1)

        field = node.fields[0]
        self.assertTrue(field is not None)
        self.assertTrue(isinstance(field, ast.Field))
        self.assertEqual(field.name, 'nested')

        nested = field.anonymous_node
        self.assertTrue(isinstance(nested, ast.Record))
        self.assertEqual(len(nested.fields), 1)
        self.assertEqual(nested.name, 'nested')

        nested_field = nested.fields[0]
        self.assertTrue(nested_field is not None)
        self.assertTrue(isinstance(nested_field, ast.Field))
        self.assertEqual(nested_field.name, 'value')

    def test_struct_ptr(self):
        load_namespace_from_source_string(self.namespace, """
            typedef struct {
                int value;
            } TestSimpleStruct;

            typedef struct {
                TestSimpleStruct *struct_ptr;
            } TestStructWithNestedPtr;
            """)
        self.assertEqual(len(self.namespace.names), 2)
        node = self.namespace.get('StructWithNestedPtr')
        self.assertEqual(len(node.fields), 1)

        simple = self.namespace.get('SimpleStruct')
        self.assertTrue(node is not None)

        field = node.fields[0]
        self.assertTrue(field is not None)
        self.assertTrue(isinstance(field, ast.Field))
        self.assertEqual(field.type.ctype, 'TestSimpleStruct*')
        self.assertEqual(field.name, 'struct_ptr')


if __name__ == '__main__':
    unittest.main()
