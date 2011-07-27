import difflib
import os
import os.path
import sys
from StringIO import StringIO
import __builtin__

path=os.getenv('UNINSTALLED_INTROSPECTION_SRCDIR', None)
assert path is not None
sys.path.insert(0, path)

# Not correct, but enough to get the tests going uninstalled
__builtin__.__dict__['DATADIR'] = path

from giscanner.annotationparser import AnnotationParser
from giscanner.ast import Include, Namespace
from giscanner.introspectablepass import IntrospectablePass
from giscanner.maintransformer import MainTransformer
from giscanner.message import MessageLogger
from giscanner.sourcescanner import SourceScanner
from giscanner.transformer import Transformer
from giscanner.scannermain import process_packages

currentdir = os.path.dirname(os.path.abspath(sys.argv[0]))
current_name = os.path.basename(currentdir)
path = os.path.abspath(os.path.join(currentdir, '..', ''))
top_srcdir = os.environ['UNINSTALLED_INTROSPECTION_SRCDIR']
top_builddir = os.environ['TOP_BUILDDIR']

class Options:
    def __init__(self):
        self.cpp_includes = []
        self.cpp_defines = []
        self.cpp_undefines = []
        self.library_paths = []

def _diff(orig, new, short):
    def _tolines(s):
        return [s + '\n' for line in s.split('\n')]
    lines = difflib.unified_diff(_tolines(orig),
                                 _tolines(new))
    if not lines:
        return

    diff = False
    try:
        first = lines.next()
        diff = True
    except StopIteration:
        pass
    else:
        print 'ERROR: while comparing %s:' % (short, )
        for line in list(lines)[2:]:
            print '%s: %r' % (short, line[:-1])

    return diff

def _extract_expected(filename):
    fd = open(filename)
    data = fd.read()

    retval = []
    for line in data.split('\n'):
        if line.startswith('// EXPECT:'):
            sort_key = None
            if ":" in line:
                try:
                    sort_key = int(line.split(":")[1])
                except ValueError:
                    pass
            retval.append((sort_key, line[10:]))
    return retval

def check(args):
    filename = args[0]

    output = StringIO()
    namespace = Namespace("Test", "1.0")
    logger = MessageLogger.get(namespace=namespace,
                               output=output)
    logger.enable_warnings(True)
    transformer = Transformer(namespace)
    transformer.set_include_paths([os.path.join(top_srcdir, 'gir'), top_builddir])
    transformer.register_include(Include.from_string("GObject-2.0"))

    ss = SourceScanner()

    options = Options()
    exit_code = process_packages(options, ['gobject-2.0'])
    if exit_code:
        sys.exit(exit_code)
    ss.set_cpp_options(options.cpp_includes,
                       options.cpp_defines,
                       options.cpp_undefines)
    ss.parse_files([filename])
    ss.parse_macros([filename])
    transformer.parse(ss.get_symbols())

    ap = AnnotationParser()
    blocks = ap.parse(ss.get_comments())

    main = MainTransformer(transformer, blocks)
    main.transform()

    final = IntrospectablePass(transformer, blocks)
    final.validate()

    raw = output.getvalue()
    if raw.endswith('\n'):
        raw = raw[:-1]
    warnings = raw.split('\n')

    failed_tests = 0
    expected_warnings = _extract_expected(filename)
    if '' in warnings:
        warnings.remove('')
    if len(expected_warnings) != len(warnings):
        raise SystemExit(
            "ERROR in %r: expected %d warnings, but got %d:\n"
            "----\nexpected:\n%s\n----\ngot:\n%s\n----" % (
            os.path.basename(filename),
            len(expected_warnings), len(warnings),
            '\n'.join([w[1] for w in expected_warnings]),
            '\n'.join([w.split(':', 2)[2][1:] for w in warnings])))
    for warning, (sort_key, expected) in zip(warnings, expected_warnings):
        actual = warning.split(":", 1)[1]
        if _diff(expected, actual, filename):
            raise SystemExit("ERROR: tests %r failed" % (filename, ))

sys.exit(check(sys.argv[1:]))
