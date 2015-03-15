#!@PYTHON@
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
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

from __future__ import with_statement

import optparse
import os
import sys
import __builtin__

__builtin__.__dict__['DATADIR'] = '@datarootdir@'

if 'GI_SCANNER_DEBUG' in os.environ:
    def on_exception(exctype, value, tb):
        print 'Caught exception: %r %r' % (exctype, value)
        import pdb
        pdb.pm()
    sys.excepthook = on_exception

srcdir=os.getenv('UNINSTALLED_INTROSPECTION_SRCDIR', None)
if srcdir is not None:
    path = srcdir
else:
    # This is a private directory, we don't want to pollute the global
    # namespace.
    path = os.path.join('@libdir@', 'gobject-introspection')
sys.path.insert(0, path)

from giscanner.annotationparser import (COMMENT_BLOCK_START_RE, COMMENT_BLOCK_END_RE,
                                        GtkDocCommentBlockParser, GtkDocCommentBlockWriter)
from giscanner.message import MessageLogger, ERROR, FATAL


(CHUNK_DOC,
 CHUNK_DATA) = range(2)


if __name__ == '__main__':
    parser = optparse.OptionParser('%prog [options]')

    parser.add_option('-f', '--file',
                      action='store', dest='input',
                      help='Parse GTK-Doc comment blocks from the specified file')
    parser.add_option('--fix',
                      action="store_true", dest="fix", default=False,
                      help='Write back fixed GTK-Doc comment blocks')

    options, args = parser.parse_args(sys.argv)
    if not options.input:
        raise SystemExit('missing input file')
    elif not os.path.isfile(options.input):
        raise SystemExit('%s is not a file' % (options.input, ))

    logger = MessageLogger.get(namespace=None)
    parser = GtkDocCommentBlockParser()
    writer = GtkDocCommentBlockWriter(indent=True)
    logger.enable_warnings((ERROR, FATAL))

    with open(options.input, 'rU') as f:
        lines = f.readlines()

    chunks = []
    in_comment = False
    chunk_start = 0
    chunk_end = 0

    for line_index, line in enumerate(lines):
        if not in_comment:
            if COMMENT_BLOCK_START_RE.match(line):
                # We are at a line that starts a GTK-Doc comment block
                in_comment = True
                # Store everything before the GTK-Doc comment block as data
                chunks.append([CHUNK_DATA,
                               ''.join(lines[chunk_start:line_index])])
                # Store where this GTK-Doc comment block starts
                chunk_start = line_index
        else:
            if COMMENT_BLOCK_END_RE.match(line):
                # We are at a line that closes a GTK-Doc comment block
                in_comment = False
                # Store the GTK-Doc comment block
                chunks.append([CHUNK_DOC,
                               ''.join(lines[chunk_start:line_index+1]),
                               chunk_start + 1])
                # Data chunk after the GTK-Doc comment block starts at the next line
                chunk_start = line_index + 1
                # Store where the GTK-Doc comment block ends
                chunk_end = line_index
    else:
        # Store everything after the last GTK-Doc comment block (if any) as data
        chunks.append([CHUNK_DATA,
                       ''.join(lines[chunk_end if chunk_end == 0 else chunk_end + 1:])])

    # We cannot use a for loop here as chunks is modified from within the loop
    fixed = False
    for i in range(len(chunks)):
        chunk = chunks[i]
        if chunk[0] == CHUNK_DOC:
            docblock = parser.parse_comment_block(chunk[1].rstrip(), options.input, chunk[2])
            if docblock:
                fixed = True
                chunk[1] = writer.write(docblock)

    if options.fix:
        error_count = logger.get_error_count()
        if error_count > 0:
            raise SystemExit('ERROR: %s will not be rewritten, please fix above %s and try again.\n' %
                             (options.input, 'error' if error_count == 1 else 'errors'))

        if fixed:
            with open(options.input, 'wb') as f:
                for chunk in chunks:
                    f.write(chunk[1])

