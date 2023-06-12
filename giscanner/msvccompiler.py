# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2014  Chun-wei Fan
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

import os
from typing import Type

from distutils.errors import DistutilsExecError, CompileError
from distutils.ccompiler import CCompiler, gen_preprocess_options, new_compiler
from distutils.dep_util import newer

# Distutil's MSVCCompiler does not provide a preprocess()
# Implementation, so do our own here.


DistutilsMSVCCompiler: Type = type(new_compiler(compiler="msvc"))


def get_msvc_compiler():
    return MSVCCompiler()


class MSVCCompiler(DistutilsMSVCCompiler):

    def __init__(self, verbose=0, dry_run=0, force=0):
        super(DistutilsMSVCCompiler, self).__init__()
        CCompiler.__init__(self, verbose, dry_run, force)
        self.__paths = []
        self.__arch = None  # deprecated name
        self.initialized = False
        self.preprocess_options = None
        if self.check_is_clang_cl():
            cc_cmd = os.environ.get('CC').split()
            self.cc = cc_cmd[0]
            self.linker = 'lld-link'
            self.compile_options = []
            # Add any arguments added to clang-cl to self.compile_options
            # such as cross-compilation flags
            if len(cc_cmd) > 1:
                self.compile_options.extend(cc_cmd[1:])
            self.initialized = True
        else:
            self.initialize()

    def _get_file_basename(self, filename):
        if filename is None:
            return None
        if filename.rfind('.') == -1:
            return filename[filename.rfind('\\') + 1:]
        else:
            return filename[filename.rfind('\\') + 1:filename.rfind('.')]

    def check_is_clang_cl(self):
        # To run g-ir-scanner under Windows using clang-cl, set both `CC` and
        # `CXX` to `clang-cl [<arch_args>]` and ensure that clang-cl.exe and
        # lld-link.exe are in the PATH in a Visual Studio command prompt.  Note
        # that the Windows SDK is still needed in this case.  This is in line
        # with what is done in Meson
        return (os.environ.get('CC') is not None and
                os.environ.get('CXX') is not None and
                os.environ.get('CC').split()[0] == 'clang-cl' and
                os.environ.get('CXX').split()[0] == 'clang-cl')
