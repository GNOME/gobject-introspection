#!/usr/bin/env python
# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
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

import os
import platform
import re
import subprocess

from .utils import get_libtool_command, extract_libtool_shlib, which


# For .la files, the situation is easy.
def _resolve_libtool(options, binary, libraries):
    shlibs = []
    for library in libraries:
        shlib = extract_libtool_shlib(library)
        if shlib:
            shlibs.append(shlib)

    return shlibs


# Assume ldd output is something vaguely like
#
#  libpangoft2-1.0.so.0 => /usr/lib/libpangoft2-1.0.so.0 (0x006c1000)
#
# We say that if something in the output looks like libpangoft2<blah>
# then the *first* such in the output is the soname. We require <blah>
# to start with [^A-Za-z0-9_-] to avoid problems with libpango vs libpangoft2
#
# The negative lookbehind at the start is to avoid problems if someone
# is crazy enough to name a library liblib<foo> when lib<foo> exists.
#
# Match absolute paths on OS X to conform to how libraries are usually
# referenced on OS X systems.
def _ldd_library_pattern(library_name):
    pattern = "(?<![A-Za-z0-9_-])(lib*%s[^A-Za-z0-9_-][^\s\(\)]*)"
    if platform.system() == 'Darwin':
        pattern = "([^\s]*lib*%s[^A-Za-z0-9_-][^\s\(\)]*)"
    return re.compile(pattern % re.escape(library_name))


# This is a what we do for non-la files. We assume that we are on an
# ELF-like system where ldd exists and the soname extracted with ldd is
# a filename that can be opened with dlopen().
#
# On OS X this will need a straightforward alternate implementation
# in terms of otool.
#
# Windows is more difficult, since there isn't always a straightforward
# translation between library name (.lib) and the name of the .dll, so
# extracting the dll names from the compiled app may not be sufficient.
# We might need to hunt down the .lib in the compile-time path and
# use that to figure out the name of the DLL.
#
def _resolve_non_libtool(options, binary, libraries):
    if not libraries:
        return []

    if platform.platform().startswith('OpenBSD'):
        # Hack for OpenBSD when using the ports' libtool which uses slightly
        # different directories to store the libraries in. So rewite binary.args[0]
        # by inserting '.libs/'.
        old_argdir = binary.args[0]
        new_libsdir = os.path.join(os.path.dirname(binary.args[0]), '.libs/')
        new_lib = new_libsdir + os.path.basename(binary.args[0])
        if os.path.exists(new_lib):
            binary.args[0] = new_lib
            os.putenv('LD_LIBRARY_PATH', new_libsdir)
        else:
            binary.args[0] = old_argdir

    if os.name == 'nt':
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
            libtool = get_libtool_command(options)
            if libtool:
                args.append(which(os.environ.get('SHELL', 'sh.exe')))
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

    else:
        args = []
        libtool = get_libtool_command(options)
        if libtool:
            args.extend(libtool)
            args.append('--mode=execute')
        platform_system = platform.system()
        if platform_system == 'Darwin':
            args.extend(['otool', '-L', binary.args[0]])
        else:
            args.extend(['ldd', binary.args[0]])
        proc = subprocess.Popen(args, stdout=subprocess.PIPE)
        patterns = {}
        for library in libraries:
            patterns[library] = _ldd_library_pattern(library)

        shlibs = []
        for line in proc.stdout:
            for library, pattern in patterns.iteritems():
                m = pattern.search(line)
                if m:
                    del patterns[library]
                    shlibs.append(m.group(1))
                    break

        if len(patterns) > 0:
            raise SystemExit(
                "ERROR: can't resolve libraries to shared libraries: " +
                ", ".join(patterns.keys()))

    return shlibs


# We want to resolve a set of library names (the <foo> of -l<foo>)
# against a library to find the shared library name. The shared
# library name is suppose to be what you pass to dlopen() (or
# equivalent). And we want to do this using the libraries that 'binary'
# is linking against.
#
def resolve_shlibs(options, binary, libraries):
    libtool = filter(lambda x: x.endswith(".la"), libraries)
    non_libtool = filter(lambda x: not x.endswith(".la"), libraries)

    return (_resolve_libtool(options, binary, libtool) +
            _resolve_non_libtool(options, binary, non_libtool))
