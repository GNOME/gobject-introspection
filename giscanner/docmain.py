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

import optparse

from .docbookwriter import DocBookWriter
from .girparser import GIRParser

class GIDocGenerator(object):

    def parse(self, filename):
        self.parser = GIRParser()
        self.parser.parse(filename)

    def generate(self, writer, output):
        ns = self.parser.get_namespace()
        writer.add_namespace(ns)
        writer.write(output)


def doc_main(args):
    parser = optparse.OptionParser('%prog [options] sources')

    parser.add_option("-o", "--output",
                      action="store", dest="output",
                      help="Filename to write output")
    parser.add_option("-f", "--format",
                      action="store", dest="format",
                      default="docbook",
                      help="Output format")

    options, args = parser.parse_args(args)
    if not options.output:
        raise SystemExit("missing output parameter")

    if len(args) < 2:
        raise SystemExit("Need an input gir filename")

    if options.format == "docbook":
        writer = DocBookWriter()
    else:
        raise SystemExit("Unsupported output format: %s" % (options.format, ))

    generator = GIDocGenerator()
    generator.parse(args[1])

    generator.generate(writer, options.output)

    return 0
