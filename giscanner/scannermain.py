#!/usr/bin/env python
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
# Copyright (C) 2009 Red Hat, Inc.
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

import subprocess
import optparse
import os
import sys

from giscanner.annotationparser import AnnotationParser, InvalidAnnotationError
from giscanner.ast import Include
from giscanner.cachestore import CacheStore
from giscanner.dumper import compile_introspection_binary
from giscanner.glibtransformer import GLibTransformer, IntrospectionBinary
from giscanner.minixpath import myxpath, xpath_assert
from giscanner.sourcescanner import SourceScanner
from giscanner.shlibs import resolve_shlibs
from giscanner.transformer import Transformer

def _get_option_parser():
    parser = optparse.OptionParser('%prog [options] sources')
    parser.add_option("", "--format",
                      action="store", dest="format",
                      default="gir",
                      help="format to use, one of gidl, gir")
    parser.add_option("-i", "--include",
                      action="append", dest="includes", default=[],
                      help="include types for other gidls")
    parser.add_option("", "--add-include-path",
                      action="append", dest="include_paths", default=[],
                      help="include paths for other GIR files")
    parser.add_option("", "--program",
                      action="store", dest="program", default=None,
                      help="program to execute")
    parser.add_option("", "--program-arg",
                      action="append", dest="program_args", default=[],
                      help="extra arguments to program")
    parser.add_option("", "--libtool",
                      action="store", dest="libtool_path", default=None,
                      help="full path to libtool")
    parser.add_option("", "--no-libtool",
                      action="store_true", dest="nolibtool", default=False,
                      help="do not use libtool")
    parser.add_option("-l", "--library",
                      action="append", dest="libraries", default=[],
                      help="libraries of this unit")
    parser.add_option("-L", "--library-path",
                      action="append", dest="library_paths", default=[],
                      help="directories to search for libraries")
    parser.add_option("-n", "--namespace",
                      action="store", dest="namespace_name",
                      help=("name of namespace for this unit, also "
                            "used as --strip-prefix default"))
    parser.add_option("", "--nsversion",
                      action="store", dest="namespace_version",
                      help="version of namespace for this unit")
    parser.add_option("", "--strip-prefix",
                      action="store", dest="strip_prefix", default=None,
                      help="remove this prefix from objects and functions")
    parser.add_option("", "--add-init-section",
                      action="append", dest="init_sections", default=[],
            help="add extra initialization code in the introspection program")
    parser.add_option("-o", "--output",
                      action="store", dest="output",
                      help="output to writeout, defaults to stdout")
    parser.add_option("", "--pkg",
                      action="append", dest="packages", default=[],
                      help="pkg-config packages to get cflags from")
    parser.add_option("", "--pkg-export",
                      action="append", dest="packages_export", default=[],
                      help="Associated pkg-config packages for this library")
    parser.add_option("-v", "--verbose",
                      action="store_true", dest="verbose",
                      help="be verbose")
    parser.add_option("", "--noclosure",
                      action="store_true", dest="noclosure",
                      help="do not delete unknown types")
    parser.add_option("", "--typelib-xml",
                      action="store_true", dest="typelib_xml",
                      help="Just convert GIR to typelib XML")
    parser.add_option("", "--inject",
                      action="store_true", dest="inject",
                      help="Inject additional components into GIR XML")
    parser.add_option("", "--xpath-assertions",
                      action="store", dest="xpath_assertions",
            help="Use given file to create assertions on GIR content")
    parser.add_option("", "--c-include",
                      action="append", dest="c_includes", default=[],
                      help="headers which should be included in C programs")

    group = optparse.OptionGroup(parser, "Preprocessor options")
    group.add_option("-I", help="Pre-processor include file",
                     action="append", dest="cpp_includes",
                     default=[])
    group.add_option("-D", help="Pre-processor define",
                     action="append", dest="cpp_defines",
                     default=[])
    group.add_option("-U", help="Pre-processor undefine",
                     action="append", dest="cpp_undefines",
                     default=[])
    group.add_option("-p", dest="", help="Ignored")
    parser.add_option_group(group)

    return parser


def _error(msg):
    raise SystemExit('ERROR: %s' % (msg, ))

def typelib_xml_strip(path):
    from giscanner.girparser import GIRParser
    from giscanner.girwriter import GIRWriter
    from giscanner.girparser import C_NS
    from xml.etree.cElementTree import parse

    c_ns_key = '{%s}' % (C_NS, )

    tree = parse(path)
    root = tree.getroot()
    for node in root.getiterator():
        for attrib in list(node.attrib):
            if attrib.startswith(c_ns_key):
                del node.attrib[attrib]
    parser = GIRParser()
    parser.parse_tree(tree)

    writer = GIRWriter(parser.get_namespace(),
                       parser.get_shared_libraries(),
                       parser.get_includes())
    sys.stdout.write(writer.get_xml())
    return 0

def inject(path, additions, outpath):
    from giscanner.girparser import GIRParser
    from giscanner.girwriter import GIRWriter
    from xml.etree.cElementTree import parse

    tree = parse(path)
    root = tree.getroot()
    injectDoc = parse(open(additions))
    for node in injectDoc.getroot():
        injectPath = node.attrib['path']
        target = myxpath(root, injectPath)
        if not target:
            raise ValueError("Couldn't find path %r" % (injectPath, ))
        for child in node:
            target.append(child)

    parser = GIRParser()
    parser.parse_tree(tree)
    writer = GIRWriter(parser.get_namespace(),
                       parser.get_shared_libraries(),
                       parser.get_includes())
    outf = open(outpath, 'w')
    outf.write(writer.get_xml())
    outf.close()
    return 0

def validate(assertions, path):
    from xml.etree.cElementTree import parse
    doc = parse(open(path))
    root = doc.getroot()
    f = open(assertions)
    assertions_list = f.readlines()
    for assertion in assertions_list:
        assertion = assertion.strip()
        xpath_assert(root, assertion)
    f.close()
    return 0

def process_options(output, allowed_flags):
    for option in output.split():
        for flag in allowed_flags:
            if not option.startswith(flag):
                continue
            yield option
            break

def process_packages(parser, options, packages):
    args = ['pkg-config', '--cflags']
    args.extend(packages)
    output = subprocess.Popen(args,
                              stdout=subprocess.PIPE).communicate()[0]
    if output is None:
        # the error output should have already appeared on our stderr,
        # so we just exit
        sys.exit(1)
    # Some pkg-config files on Windows have options we don't understand,
    # so we explicitly filter to only the ones we need.
    options_whitelist = ['-I', '-D', '-U', '-l', '-L']
    filtered_output = list(process_options(output, options_whitelist))
    pkg_options, unused = parser.parse_args(filtered_output)
    options.cpp_includes.extend(pkg_options.cpp_includes)
    options.cpp_defines.extend(pkg_options.cpp_defines)
    options.cpp_undefines.extend(pkg_options.cpp_undefines)

    args = ['pkg-config', '--libs-only-L']
    args.extend(packages)
    output = subprocess.Popen(args,
                              stdout=subprocess.PIPE).communicate()[0]
    if output is None:
        sys.exit(1)
    filtered_output = list(process_options(output, options_whitelist))
    pkg_options, unused = parser.parse_args(filtered_output)
    options.library_paths.extend(pkg_options.library_paths)

def scanner_main(args):
    parser = _get_option_parser()
    (options, args) = parser.parse_args(args)

    if len(args) <= 1:
        _error('Need at least one filename')

    if options.typelib_xml:
        return typelib_xml_strip(args[1])

    if options.inject:
        if len(args) != 4:
            _error('Need three filenames; e.g. g-ir-scanner '
                   '--inject Source.gir Additions.xml SourceOut.gir')
        return inject(*args[1:4])

    if options.xpath_assertions:
        return validate(options.xpath_assertions, args[1])

    if not options.namespace_name:
        _error('Namespace name missing')

    if options.format == 'gir':
        from giscanner.girwriter import GIRWriter as Writer
    else:
        _error("Unknown format: %s" % (options.format, ))

    if not (options.libraries or options.program):
        _error("Must specify --program or --library")
    libraries = options.libraries

    filenames = []
    for arg in args:
        if (arg.endswith('.c') or
            arg.endswith('.h')):
            if not os.path.exists(arg):
                _error('%s: no such a file or directory' % (arg, ))
            # Make absolute, because we do comparisons inside scannerparser.c
            # against the absolute path that cpp will give us
            filenames.append(os.path.abspath(arg))

    cachestore = CacheStore()
    transformer = Transformer(cachestore,
                              options.namespace_name,
                              options.namespace_version)
    if options.strip_prefix:
        transformer.set_strip_prefix(options.strip_prefix)
    else:
        transformer.set_strip_prefix(options.namespace_name)
    transformer.set_include_paths(options.include_paths)
    shown_include_warning = False
    for include in options.includes:
        if os.sep in include:
            raise ValueError("Invalid include path %r" % (include, ))
        try:
            include_obj = Include.from_string(include)
        except:
            sys.stderr.write("Malformed include %r\n" % (include, ))
            sys.exit(1)
        transformer.register_include(include_obj)

    packages = set(options.packages)
    packages.update(transformer.get_pkgconfig_packages())
    process_packages(parser, options, packages)

    # Run the preprocessor, tokenize and construct simple
    # objects representing the raw C symbols
    ss = SourceScanner()
    ss.set_cpp_options(options.cpp_includes,
                       options.cpp_defines,
                       options.cpp_undefines)
    ss.parse_files(filenames)
    ss.parse_macros(filenames)

    # Transform the C symbols into AST nodes
    transformer.set_source_ast(ss)

    # Transform the C AST nodes into higher level
    # GLib/GObject nodes
    glibtransformer = GLibTransformer(transformer,
                                      noclosure=options.noclosure)

    # Do enough parsing that we have the get_type() functions to reference
    # when creating the introspection binary
    glibtransformer.init_parse()

    if options.program:
        args=[options.program]
        args.extend(options.program_args)
        binary = IntrospectionBinary(args)
    else:
        binary = compile_introspection_binary(options,
                            glibtransformer.get_get_type_functions())

    shlibs = resolve_shlibs(options, binary, libraries)

    glibtransformer.set_introspection_binary(binary)

    namespace = glibtransformer.parse()

    ap = AnnotationParser(namespace, ss, transformer)
    try:
        ap.parse()
    except InvalidAnnotationError, e:
        raise SystemExit("ERROR in annotation: %s" % (str(e), ))

    # Write out AST
    if options.packages_export:
        exported_packages = options.packages_export
    else:
        exported_packages = options.packages
    writer = Writer(namespace, shlibs, transformer.get_includes(),
                    exported_packages, options.c_includes,
                    transformer.get_strip_prefix())
    data = writer.get_xml()
    if options.output:
        fd = open(options.output, "w")
        fd.write(data)
    else:
        print data

    return 0
