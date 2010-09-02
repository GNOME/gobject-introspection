import difflib
import os
import os.path
import sys
from StringIO import StringIO

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
        print repr(orig), repr(new)
        print 'ERROR: while comparing %s:' % (short, )
        for line in list(lines)[2:]:
            print '%s: %s' % (short, line[:-1])

    return diff

def check(args):
    filenames = args

    output = StringIO()
    namespace = Namespace("Test", "1.0")
    logger = MessageLogger.get(namespace=namespace,
                               output=output)
    logger.enable_warnings(True)
    transformer = Transformer(namespace)
    transformer.register_include(Include.from_string("GObject-2.0"))

    ss = SourceScanner()

    options = Options()
    exit_code = process_packages(options, ['gobject-2.0'])
    if exit_code:
        sys.exit(exit_code)
    ss.set_cpp_options(options.cpp_includes,
                       options.cpp_defines,
                       options.cpp_undefines)
    ss.parse_files(filenames)
    ss.parse_macros(filenames)
    transformer.parse(ss.get_symbols())

    ap = AnnotationParser()
    blocks = ap.parse(ss.get_comments())

    main = MainTransformer(transformer, blocks)
    main.transform()

    final = IntrospectablePass(transformer)
    final.validate()

    warnings = output.getvalue()[:-1].split('\n')

    failed_tests = 0
    for warning in warnings:
        filename, actual = warning.split(":", 1)
        fd = open(filename)
        data = fd.read()
        pos = data.find("EXPECT:")
        if pos == -1:
            raise SystemExit("%s: unexpected warning %s" % (filename, warning,))
        expected = data[pos+7:]
        while expected.endswith('\n'):
            expected = expected[:-1]
        if _diff(actual, expected, filename):
            failed_tests += 1

    print 'PASS: %d of %d tested passed' % (len(filenames) - failed_tests,
                                            len(filenames))

    if failed_tests:
        raise SystemExit("ERROR: some tests failed")

sys.exit(check(sys.argv[1:]))
