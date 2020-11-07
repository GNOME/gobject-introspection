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

import operator
import os
import sys
from enum import Enum
from typing import TYPE_CHECKING, Callable, Iterable, Optional, TextIO, Tuple, Union

from . import utils

if TYPE_CHECKING:
    from .ast import Namespace, Node
    from .sourcescanner import SourceSymbol


class LogType(Enum):
    WARNING = 0
    ERROR = 1
    FATAL = 2


class Position(object):
    """
    Represents a position in the source file which we
    want to inform about.
    """

    __slots__ = ('filename', 'line', 'column', 'is_typedef')

    def __init__(
        self,
        filename: str,
        line: Optional[int] = None,
        column: Optional[int] = None,
        is_typedef: bool = False,
    ):
        self.filename = filename
        self.line = line
        self.column = column
        self.is_typedef = is_typedef

    def _compare(
        self,
        other: "Position",
        op: Callable[
            [
                Tuple[str, Optional[int], Optional[int]],
                Tuple[str, Optional[int], Optional[int]],
            ],
            bool,
        ],
    ) -> bool:
        return op(
            (self.filename, self.line, self.column),
            (other.filename, other.line, other.column),
        )

    def __lt__(self, other: "Position") -> bool:
        return self._compare(other, operator.lt)

    def __gt__(self, other: "Position") -> bool:
        return self._compare(other, operator.gt)

    def __ge__(self, other: "Position") -> bool:
        return self._compare(other, operator.ge)

    def __le__(self, other: "Position") -> bool:
        return self._compare(other, operator.le)

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Position):
            return False
        return self._compare(other, operator.eq)

    def __ne__(self, other: object) -> bool:
        if not isinstance(other, Position):
            return True
        return self._compare(other, operator.ne)

    def __hash__(self) -> int:
        return hash((self.filename, self.line, self.column))

    def __repr__(self) -> str:
        return '<Position %s:%d:%d>' % (os.path.basename(self.filename),
                                        self.line or -1,
                                        self.column or -1)

    def format(self, cwd: str) -> str:
        # Windows: We may be using different drives self.filename and cwd,
        #          which leads to a ValuError when using os.path.relpath().
        #          In that case, just use the entire path of self.filename
        try:
            filename = os.path.relpath(os.path.realpath(self.filename),
                                       os.path.realpath(cwd))
        except ValueError:
            filename = os.path.realpath(self.filename)

        if self.column is not None and self.line is not None:
            return '%s:%d:%d' % (filename, self.line, self.column)
        elif self.line is not None:
            return '%s:%d' % (filename, self.line, )
        else:
            return '%s:' % (filename, )


class MessageLogger(object):
    _instance = None

    def __init__(self, namespace: Optional["Namespace"] = None, output: TextIO = None):
        if output is None:
            output = sys.stderr
        self._cwd = os.getcwd()
        self._output = output
        self._namespace = namespace
        self._enable_warnings = False
        self._warning_count = 0

    @classmethod
    def get(cls, *args, **kwargs) -> "MessageLogger":
        if cls._instance is None:
            cls._instance = cls(*args, **kwargs)
        return cls._instance

    def enable_warnings(self, value: bool) -> None:
        self._enable_warnings = value

    def get_warning_count(self) -> int:
        return self._warning_count

    def log(
        self,
        log_type: LogType,
        text: str,
        positions: Optional[Union[Iterable[Position], Position]] = None,
        prefix: str = None,
        marker_pos: Optional[int] = None,
        marker_line: Optional[str] = None,
    ) -> None:
        """
        Log a warning, using optional file positioning information.
        If the warning is related to a ast.Node type, see log_node().
        """
        utils.break_on_debug_flag('warning')

        self._warning_count += 1

        if not self._enable_warnings and log_type in (LogType.WARNING, LogType.ERROR):
            return

        if not positions:
            positions = [Position("<unknown>")]
        elif isinstance(positions, Position):
            positions = [positions]
        elif not isinstance(positions, list):
            positions = list(positions)

        for position in positions[:-1]:
            self._output.write("%s:\n" % (position.format(cwd=self._cwd), ))
        last_position = positions[-1].format(cwd=self._cwd)

        error_type = "Warning"
        if log_type == LogType.ERROR:
            error_type = "Error"
        elif log_type == LogType.FATAL:
            error_type = "Fatal"

        if marker_pos is not None and marker_line is not None:
            text = '%s\n%s\n%s' % (text, marker_line, ' ' * marker_pos + '^')

        if prefix:
            if self._namespace:
                text = ('%s: %s: %s: %s: %s\n' % (last_position, error_type,
                                                  self._namespace.name, prefix, text))
            else:
                text = ('%s: %s: %s: %s\n' % (last_position, error_type,
                                              prefix, text))
        else:
            if self._namespace:
                text = ('%s: %s: %s: %s\n' % (last_position, error_type,
                                              self._namespace.name, text))
            else:
                text = ('%s: %s: %s\n' % (last_position, error_type, text))

        self._output.write(text)

        if log_type == LogType.FATAL:
            utils.break_on_debug_flag('fatal')
            raise SystemExit(text)

    def log_node(
        self,
        log_type: LogType,
        node: "Node",
        text: str,
        context=None,
        positions: Optional[Union[Iterable[Position], Position]] = None,
    ) -> None:
        """
        Log a warning, using information about file positions from
        the given node.  The optional context argument, if given, should be
        another ast.Node type which will also be displayed.  If no file position
        information is available from the node, the position data from the
        context will be used.
        """
        if positions:
            pass
        elif getattr(node, 'file_positions', None):
            positions = node.file_positions
        elif context and context.file_positions:
            positions = context.file_positions
        else:
            positions = set()

        if context:
            text = "%s: %s" % (getattr(context, 'symbol', context.name), text)
        elif not positions and hasattr(node, 'name'):
            text = "(%s)%s: %s" % (node.__class__.__name__, node.name, text)

        self.log(log_type, text, positions)

    def log_symbol(self, log_type: LogType, symbol: "SourceSymbol", text: str) -> None:
        """Log a warning in the context of the given symbol."""
        self.log(log_type, text, symbol.position,
                 prefix="symbol='%s'" % (symbol.ident, ))


def log_node(
    log_type: LogType,
    node: "Node",
    text: str,
    context=None,
    positions: Optional[Union[Iterable[Position], Position]] = None,
):
    ml = MessageLogger.get()
    ml.log_node(log_type, node, text, context=context, positions=positions)


def warn(
    text: str,
    positions: Optional[Union[Iterable[Position], Position]] = None,
    prefix: str = None,
    marker_pos: Optional[int] = None,
    marker_line: Optional[str] = None,
):
    ml = MessageLogger.get()
    ml.log(LogType.WARNING, text, positions, prefix, marker_pos, marker_line)


def warn_node(
    node,
    text: str,
    context=None,
    positions: Optional[Union[Iterable[Position], Position]] = None,
) -> None:
    log_node(LogType.WARNING, node, text, context=context, positions=positions)


def error_node(
    node,
    text: str,
    context=None,
    positions: Optional[Union[Iterable[Position], Position]] = None,
) -> None:
    log_node(LogType.ERROR, node, text, context=context, positions=positions)


def warn_symbol(symbol: "SourceSymbol", text: str) -> None:
    ml = MessageLogger.get()
    ml.log_symbol(LogType.WARNING, symbol, text)


def error(
    text: str,
    positions: Optional[Union[Iterable[Position], Position]] = None,
    prefix: str = None,
    marker_pos: Optional[int] = None,
    marker_line: Optional[str] = None,
) -> None:
    ml = MessageLogger.get()
    ml.log(LogType.ERROR, text, positions, prefix, marker_pos, marker_line)


def fatal(
    text: str,
    positions: Optional[Union[Iterable[Position], Position]] = None,
    prefix: str = None,
    marker_pos: Optional[int] = None,
    marker_line: Optional[str] = None,
) -> None:
    ml = MessageLogger.get()
    ml.log(LogType.FATAL, text, positions, prefix, marker_pos, marker_line)
