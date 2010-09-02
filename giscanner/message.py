#!/usr/bin/env python
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2010 Red Hat, Inc.
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

import os
import sys

from . import ast

(WARNING,
 ERROR,
 FATAL) = range(3)

class MessageLogger(object):
    _instance = None

    def __init__(self, namespace, output=None):
        if output is None:
            output = sys.stderr
        self._cwd = os.getcwd() + os.sep
        self._output = output
        self._namespace = namespace
        self._enable_warnings = False
        self._warned = False

    @classmethod
    def get(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = cls(*args, **kwargs)
        return cls._instance

    def enable_warnings(self, enable):
        self._enable_warnings = enable

    def did_warn(self):
        return self._warned

    def log(self, log_type, text, file_positions=None, prefix=None):
        """Log a warning, using optional file positioning information.
If the warning is related to a ast.Node type, see log_node_warning()."""
        if not self._enable_warnings:
            return

        self._warned = True

        if file_positions is None or len(file_positions) == 0:
            target_file_positions = [('<unknown>', -1, -1)]
        else:
            target_file_positions = file_positions

        position_strings = []
        for (filename, line, column) in target_file_positions:
            if filename.startswith(self._cwd):
                filename = filename[len(self._cwd):]
            if column != -1:
                position = '%s:%d:%d' % (filename, line, column)
            elif line != -1:
                position = '%s:%d' % (filename, line, )
            else:
                position = '%s:' % (filename, )
            position_strings.append(position)

        for position in position_strings[:-1]:
            self._output.write("%s:\n" % (position, ))
        last_position = position_strings[-1]

        if log_type == WARNING:
            error_type = "Warning"
        elif log_type == ERROR:
            error_type = "Error"
        elif log_type == FATAL:
            error_type = "Fatal"
        if prefix:
            self._output.write(
'''%s: %s: %s: %s: %s\n''' % (last_position, error_type, self._namespace.name,
                            prefix, text))
        else:
            self._output.write(
'''%s: %s: %s: %s\n''' % (last_position, error_type, self._namespace.name, text))


        if log_type == FATAL:
            raise SystemExit

    def log_node(self, log_type, node, text, context=None):
        """Log a warning, using information about file positions from
the given node.  The optional context argument, if given, should be
another ast.Node type which will also be displayed.  If no file position
information is available from the node, the position data from the
context will be used."""
        if hasattr(node, 'file_positions'):
            if (len(node.file_positions) == 0 and
                (context is not None) and len(context.file_positions) > 0):
                file_positions = context.file_positions
            else:
                file_positions = node.file_positions
        else:
            file_positions = None
            if not context:
                text = "context=%r %s" % (node, text)

        if context:
            if isinstance(context, ast.Function):
                name = context.symbol
            else:
                name = context.name
            text = "%s: %s" % (name, text)
        elif len(file_positions) == 0 and hasattr(node, 'name'):
            text = "(%s)%s: %s" % (node.__class__.__name__, node.name, text)

        self.log(log_type, text, file_positions)

    def log_symbol(self, log_type, symbol, text, **kwargs):
        """Log a warning in the context of the given symbol."""
        if symbol.source_filename:
            file_positions = [(symbol.source_filename, symbol.line, -1)]
        else:
            file_positions = None
        prefix = "symbol=%r" % (symbol.ident, )
        self.log(log_type, text, file_positions, prefix=prefix, **kwargs)


def log_node(log_type, node, text, context=None):
    ml = MessageLogger.get()
    ml.log_node(log_type, node, text, context=context)

def warn(text, file_positions=None, prefix=None):
    ml = MessageLogger.get()
    ml.log(WARNING, text, file_positions, prefix)

def warn_node(node, text, context=None):
    log_node(WARNING, node, text, context=context)

def warn_symbol(symbol, text):
    ml = MessageLogger.get()
    ml.log_symbol(WARNING, symbol, text)

def fatal(text, file_positions=None, prefix=None):
    ml = MessageLogger.get()
    ml.log(FATAL, text, file_positions, prefix)
