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
import subprocess

import sys
import distutils

from distutils.msvccompiler import MSVCCompiler
from distutils.cygwinccompiler import Mingw32CCompiler
from distutils.sysconfig import customize_compiler

from . import utils


class CCompiler(object):

    compiler_cmd = ''
    compiler = None
    _cflags_no_deprecation_warnings = ''

    def __init__(self, compiler_name=None):
        pass

    def get_internal_link_flags(self,
                                args,
                                libtool,
                                libraries,
                                libpaths,
                                pkgconfig_msvc_flags,
                                ns,
                                ns_version):
        # An "internal" link is where the library to be introspected
        # is being built in the current directory.

        # Search the current directory first
        # (This flag is not supported nor needed for Visual C++)
        if pkgconfig_msvc_flags == '':
            args.append('-L.')

        # https://bugzilla.gnome.org/show_bug.cgi?id=625195
        if not libtool:
            # We don't have -Wl,-rpath for Visual C++, and that's
            # going to cause a problem.  Instead, link to internal
            # libraries by deducing the .lib file name using
            # the namespace name and version
            if pkgconfig_msvc_flags:
                if ns_version:
                    args.append(str.lower(ns) +
                                '-' +
                                ns_version + '.lib')
                else:
                    args.append(str.lower(ns) + '.lib')
            else:
                args.append('-Wl,-rpath=.')

        # Ensure libraries are always linked as we are going to use ldd to work
        # out their names later
        if not libtool and pkgconfig_msvc_flags == '':
            args.append('-Wl,--no-as-needed')

        for library in libraries:
            # Visual C++: We have the needed .lib files now, and we need to link
            # to .lib files, not the .dll as the --library option specifies the
            # .dll(s) the .gir file refers to
            if pkgconfig_msvc_flags == '':
                if library.endswith(".la"):  # explicitly specified libtool library
                    args.append(library)
                else:
                    args.append('-l' + library)

        for library_path in libpaths:
            # Not used/needed on Visual C++, and -Wl,-rpath options
            # will cause grief
            if pkgconfig_msvc_flags == '':
                args.append('-L' + library_path)
                if os.path.isabs(library_path):
                    if libtool:
                        args.append('-rpath')
                        args.append(library_path)
                    else:
                        args.append('-Wl,-rpath=' + library_path)

    def get_external_link_flags(self, args, libraries, pkgconfig_msvc_flags):
        # An "external" link is where the library to be introspected
        # is installed on the system; this case is used for the scanning
        # of GLib in gobject-introspection itself.

        for library in libraries:
            # The --library option on Windows pass in the .dll file(s) the
            # .gir files refer to, so don't link to them on Visual C++
            if pkgconfig_msvc_flags == '':
                if library.endswith(".la"):  # explicitly specified libtool library
                    args.append(library)
                else:
                    args.append('-l' + library)

    def resolve_windows_libs(self, libraries, options):
        args = []
        compiler_cmd = os.environ.get('CC', 'cc')
        libsearch = []

        # When we are using Visual C++...
        if 'cl.exe' in compiler_cmd or 'cl' in compiler_cmd:
            # The search path of the .lib's on Visual C++
            # is dependent on the LIB environmental variable,
            # so just query for that
            is_msvc = True
            libpath = os.environ.get('LIB')
            libsearch = libpath.split(';')

            # Use the dumpbin utility that's included in
            # every Visual C++ installation to find out which
            # DLL the library gets linked to
            args.append('dumpbin.exe')
            args.append('-symbols')

        # When we are not using Visual C++ (i.e. we are using GCC)...
        else:
            is_msvc = False
            libtool = utils.get_libtool_command(options)
            if libtool:
                args.append(utils.which(os.environ.get('SHELL', 'sh.exe')))
                args.extend(libtool)
                args.append('--mode=execute')
            # FIXME: it could have prefix (i686-w64-mingw32-dlltool.exe)
            args.extend(['dlltool.exe', '--identify'])
            proc = subprocess.Popen([compiler_cmd, '-print-search-dirs'],
                                    stdout=subprocess.PIPE)
            o, e = proc.communicate()
            for line in o.splitlines():
                if line.startswith('libraries: '):
                    libsearch = line[len('libraries: '):].split(';')

        shlibs = []
        not_resolved = []
        for lib in libraries:
            found = False
            candidates = [
                'lib%s.dll.a' % lib,
                'lib%s.a' % lib,
                '%s.dll.a' % lib,
                '%s.a' % lib,
                '%s.lib' % lib,
            ]
            for l in libsearch:
                if found:
                    break
                if l.startswith('='):
                    l = l[1:]
                for c in candidates:
                    if found:
                        break
                    implib = os.path.join(l, c)
                    if os.path.exists(implib):
                        proc = subprocess.Popen(args + [implib],
                                                stdout=subprocess.PIPE)
                        o, e = proc.communicate()
                        for line in o.splitlines():
                            if is_msvc:
                                # On Visual Studio, dumpbin -symbols something.lib gives the
                                # filename of DLL without the '.dll' extension that something.lib
                                # links to, in the line that contains
                                # __IMPORT_DESCRIPTOR_<dll_filename_that_something.lib_links_to>

                                if '__IMPORT_DESCRIPTOR_' in line:
                                    line_tokens = line.split()
                                    for item in line_tokens:
                                        if item.startswith('__IMPORT_DESCRIPTOR_'):
                                            shlibs.append(item[20:] + '.dll')
                                            found = True
                                            break
                                if found:
                                    break
                            else:
                                shlibs.append(line)
                                found = True
                                break
            if not found:
                not_resolved.append(lib)
        if len(not_resolved) > 0:
            raise SystemExit(
                "ERROR: can't resolve libraries to shared libraries: " +
                ", ".join(not_resolved))
        return shlibs
