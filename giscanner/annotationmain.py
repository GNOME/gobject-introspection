# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2010 Johan Dahlin
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

import optparse

from giscanner import message
from giscanner.annotationparser import AnnotationParser
from giscanner.scannermain import (get_preprocessor_option_group,
                                   create_source_scanner,
                                   process_packages)


def annotation_main(args):
    parser = optparse.OptionParser('%prog [options] sources')

    group = optparse.OptionGroup(parser, "Tool modes, one is required")
    group.add_option("-e", "--extract",
                     action="store_true", dest="extract",
                     help="Extract annotations from the input files")
    parser.add_option_group(group)

    group = get_preprocessor_option_group(parser)
    group.add_option("-L", "--library-path",
                     action="append", dest="library_paths", default=[],
                     help="directories to search for libraries")
    group.add_option("", "--pkg",
                     action="append", dest="packages", default=[],
                     help="pkg-config packages to get cflags from")
    parser.add_option_group(group)

    options, args = parser.parse_args(args)

    if not options.extract:
        raise SystemExit("ERROR: Nothing to do")

    if options.packages:
        process_packages(options, options.packages)

    logger = message.MessageLogger.get(namespace=None)

    ss = create_source_scanner(options, args)

    if options.extract:
        ap = AnnotationParser()
        blocks = ap.parse(ss.get_comments())
        print '/' + ('*' * 60) + '/'
        print '/* THIS FILE IS GENERATED DO NOT EDIT */'
        print '/' + ('*' * 60) + '/'
        print
        for block in sorted(blocks.values()):
            print block.to_gtk_doc()
            print
        print
        print '/' + ('*' * 60) + '/'
        print '/* THIS FILE IS GENERATED DO NOT EDIT */'
        print '/' + ('*' * 60) + '/'

    return 0
