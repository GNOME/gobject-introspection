# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008-2011 Johan Dahlin
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

import os
import optparse

from .docbookwriter import DocBookWriter
from .docbookwriter import DocBookFormatterC
from .docbookwriter import DocBookFormatterPython
from .mallardwriter import MallardWriter
from .mallardwriter import MallardFormatterC
from .mallardwriter import MallardFormatterPython
from .transformer import Transformer

class GIDocGenerator(object):

    def parse(self, filename):
        if 'UNINSTALLED_INTROSPECTION_SRCDIR' in os.environ:
            top_srcdir = os.environ['UNINSTALLED_INTROSPECTION_SRCDIR']
            top_builddir = os.environ['UNINSTALLED_INTROSPECTION_BUILDDIR']
            extra_include_dirs = [os.path.join(top_srcdir, 'gir'), top_builddir]
        else:
            extra_include_dirs = []
        self.transformer = Transformer.parse_from_gir(filename, extra_include_dirs)

    def generate(self, writer, output):
        writer.add_transformer(self.transformer)
        writer.write(output)

def doc_main(args):
    parser = optparse.OptionParser('%prog [options] GIR-file')

    parser.add_option("-o", "--output",
                      action="store", dest="output",
                      help="Filename to write output")
    parser.add_option("-f", "--format",
                      action="store", dest="format",
                      default="docbook",
                      help="Output format")
    parser.add_option("-l", "--language",
                      action="store", dest="language",
                      default="Python",
                      help="Output language")

    options, args = parser.parse_args(args)
    if not options.output:
        raise SystemExit("missing output parameter")

    if len(args) < 2:
        raise SystemExit("Need an input GIR filename")

    if options.format == "docbook":
        if options.language == "Python":
            formatter = DocBookFormatterPython()
        elif options.language == "C":
            formatter = DocBookFormatterC()
        else:
            raise SystemExit("Unsupported language: %s" % (options.language, ))
        writer = DocBookWriter(formatter)
    elif options.format == "mallard":
        if options.language == "Python":
            formatter = MallardFormatterPython()
        elif options.language == "C":
            formatter = MallardFormatterC()
        else:
            raise SystemExit("Unsupported language: %s" % (options.language, ))
        writer = MallardWriter(formatter)
    else:
        raise SystemExit("Unsupported output format: %s" % (options.format, ))

    generator = GIDocGenerator()
    generator.parse(args[1])

    generator.generate(writer, options.output)

    return 0
