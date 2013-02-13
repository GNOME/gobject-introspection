# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008 Colin Walters
# Copyright (C) 2008 Johan Dahlin
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
import sys
import subprocess
import shutil
import tempfile

from .gdumpparser import IntrospectionBinary
from . import utils

# bugzilla.gnome.org/558436
# Compile a binary program which is then linked to a library
# we want to introspect, in order to call its get_type functions.

_PROGRAM_TEMPLATE = """/* This file is generated, do not edit */
#include <glib.h>
#include <string.h>
#include <stdlib.h>

%(gdump_include)s

int
main(int argc, char **argv)
{
  GError *error = NULL;
  const char *introspect_dump_prefix = "--introspect-dump=";

#if !GLIB_CHECK_VERSION(2,35,0)
  g_type_init ();
#endif

  %(init_sections)s

  if (argc != 2 || !g_str_has_prefix (argv[1], introspect_dump_prefix))
    {
      g_printerr ("Usage: %%s --introspect-dump=input,output", argv[0]);
      exit (1);
    }

  if (!dump_irepository (argv[1] + strlen(introspect_dump_prefix), &error))
    {
      g_printerr ("%%s\\n", error->message);
      exit (1);
    }
  exit (0);
}
"""


class CompilerError(Exception):
    pass


class LinkerError(Exception):
    pass


class DumpCompiler(object):

    def __init__(self, options, get_type_functions, error_quark_functions):
        self._options = options
        self._get_type_functions = get_type_functions
        self._error_quark_functions = error_quark_functions

        self._compiler_cmd = os.environ.get('CC', 'gcc')
        self._linker_cmd = os.environ.get('CC', self._compiler_cmd)
        self._pkgconfig_cmd = os.environ.get('PKG_CONFIG', 'pkg-config')
        self._pkgconfig_msvc_flags = ''
        # Enable the --msvc-syntax pkg-config flag when
        # the Microsoft compiler is used
        # (This is the other way to check whether Visual C++ is used subsequently)
        if 'cl' in self._compiler_cmd:
            self._pkgconfig_msvc_flags = '--msvc-syntax'
        self._uninst_srcdir = os.environ.get(
            'UNINSTALLED_INTROSPECTION_SRCDIR')
        self._packages = ['gio-2.0 gmodule-2.0']
        self._packages.extend(options.packages)

    # Public API

    def run(self):
        # We have to use the current directory to work around Unix
        # sysadmins who mount /tmp noexec
        tmpdir = tempfile.mkdtemp('', 'tmp-introspect', dir=os.getcwd())

        tpl_args = {}
        if self._uninst_srcdir is not None:
            gdump_path = os.path.join(self._uninst_srcdir, 'girepository', 'gdump.c')
        else:
            gdump_path = os.path.join(os.path.join(DATADIR), 'gobject-introspection-1.0',
                                      'gdump.c')
        if not os.path.isfile(gdump_path):
            raise SystemExit("Couldn't find %r" % (gdump_path, ))
        gdump_file = open(gdump_path)
        gdump_contents = gdump_file.read()
        gdump_file.close()
        tpl_args['gdump_include'] = gdump_contents
        tpl_args['init_sections'] = "\n".join(self._options.init_sections)

        c_path = self._generate_tempfile(tmpdir, '.c')
        f = open(c_path, 'w')
        f.write(_PROGRAM_TEMPLATE % tpl_args)

        # We need to reference our get_type and error_quark functions
        # to make sure they are pulled in at the linking stage if the
        # library is a static library rather than a shared library.
        if len(self._get_type_functions) > 0:
            for func in self._get_type_functions:
                f.write("extern GType " + func + "(void);\n")
            f.write("GType (*GI_GET_TYPE_FUNCS_[])(void) = {\n")
            first = True
            for func in self._get_type_functions:
                if first:
                    first = False
                else:
                    f.write(",\n")
                f.write("  " + func)
            f.write("\n};\n")
        if len(self._error_quark_functions) > 0:
            for func in self._error_quark_functions:
                f.write("extern GQuark " + func + "(void);\n")
            f.write("GQuark (*GI_ERROR_QUARK_FUNCS_[])(void) = {\n")
            first = True
            for func in self._error_quark_functions:
                if first:
                    first = False
                else:
                    f.write(",\n")
                f.write("  " + func)
            f.write("\n};\n")
        f.close()

        # Microsoft compilers generate intermediate .obj files
        # during compilation, unlike .o files like GCC and others
        if self._pkgconfig_msvc_flags:
            o_path = self._generate_tempfile(tmpdir, '.obj')
        else:
            o_path = self._generate_tempfile(tmpdir, '.o')

        if os.name == 'nt':
            ext = 'exe'
        else:
            ext = ''

        bin_path = self._generate_tempfile(tmpdir, ext)

        try:
            self._compile(o_path, c_path)
        except CompilerError, e:
            if not utils.have_debug_flag('save-temps'):
                shutil.rmtree(tmpdir)
            raise SystemExit('compilation of temporary binary failed:' + str(e))

        try:
            self._link(bin_path, o_path)
        except LinkerError, e:
            if not utils.have_debug_flag('save-temps'):
                shutil.rmtree(tmpdir)
            raise SystemExit('linking of temporary binary failed: ' + str(e))

        return IntrospectionBinary([bin_path], tmpdir)

    # Private API

    def _generate_tempfile(self, tmpdir, suffix=''):
        tmpl = '%s-%s%s' % (self._options.namespace_name,
                            self._options.namespace_version, suffix)
        return os.path.join(tmpdir, tmpl)

    def _run_pkgconfig(self, flag):
        # Enable the --msvc-syntax pkg-config flag when
        # the Microsoft compiler is used
        if self._pkgconfig_msvc_flags:
            cmd = [self._pkgconfig_cmd, self._pkgconfig_msvc_flags, flag]
        else:
            cmd = [self._pkgconfig_cmd, flag]
        proc = subprocess.Popen(
            cmd + self._packages,
            stdout=subprocess.PIPE)
        return proc.communicate()[0].split()

    def _compile(self, output, *sources):
        # Not strictly speaking correct, but easier than parsing shell
        args = self._compiler_cmd.split()
        # Do not add -Wall when using init code as we do not include any
        # header of the library being introspected
        if self._compiler_cmd == 'gcc' and not self._options.init_sections:
            args.append('-Wall')
        args.append("-Wno-deprecated-declarations")
        pkgconfig_flags = self._run_pkgconfig('--cflags')
        args.extend(pkgconfig_flags)
        cflags = os.environ.get('CFLAGS', '')
        for cflag in cflags.split():
            args.append(cflag)
        for include in self._options.cpp_includes:
            args.append('-I' + include)
        # The Microsoft compiler uses different option flags for
        # compilation result output
        if self._pkgconfig_msvc_flags:
            args.extend(['-c', '-Fe'+output, '-Fo'+output])
        else:
            args.extend(['-c', '-o', output])
        for source in sources:
            if not os.path.exists(source):
                raise CompilerError(
                    "Could not find c source file: %s" % (source, ))
        args.extend(list(sources))
        if not self._options.quiet:
            print "g-ir-scanner: compile: %s" % (
                subprocess.list2cmdline(args), )
            sys.stdout.flush()
        try:
            subprocess.check_call(args)
        except subprocess.CalledProcessError, e:
            raise CompilerError(e)

    def _link(self, output, *sources):
        args = []
        libtool = utils.get_libtool_command(self._options)
        if libtool:
            args.extend(libtool)
            args.append('--mode=link')
            args.append('--tag=CC')
            if self._options.quiet:
                args.append('--silent')

        args.extend(self._linker_cmd.split())
        # We can use -o for the Microsoft compiler/linker,
        # but it is considered deprecated usage with that
        if self._pkgconfig_msvc_flags:
            args.extend(['-Fe'+output])
        else:
            args.extend(['-o', output])
        if libtool:
            if os.name == 'nt':
                args.append('-export-all-symbols')
            else:
                args.append('-export-dynamic')

        cflags = os.environ.get('CFLAGS', '')
        for cflag in cflags.split():
            args.append(cflag)
        ldflags = os.environ.get('LDFLAGS', '')
        for ldflag in ldflags.split():
            args.append(ldflag)

        # Make sure to list the library to be introspected first since it's
        # likely to be uninstalled yet and we want the uninstalled RPATHs have
        # priority (or we might run with installed library that is older)

        for source in sources:
            if not os.path.exists(source):
                raise CompilerError(
                    "Could not find object file: %s" % (source, ))
        args.extend(list(sources))

        if not self._options.external_library:
            self._add_link_internal_args(args, libtool)
        else:
            self._add_link_external_args(args)

        if not self._options.quiet:
            print "g-ir-scanner: link: %s" % (
                subprocess.list2cmdline(args), )
            sys.stdout.flush()
        try:
            subprocess.check_call(args)
        except subprocess.CalledProcessError, e:
            raise LinkerError(e)

    def _add_link_internal_args(self, args, libtool):
        # An "internal" link is where the library to be introspected
        # is being built in the current directory.

        # Search the current directory first
        # (This flag is not supported nor needed for Visual C++)
        if self._pkgconfig_msvc_flags == '':
            args.append('-L.')

        # https://bugzilla.gnome.org/show_bug.cgi?id=625195
        if not libtool:
            # We don't have -Wl,-rpath for Visual C++, and that's
            # going to cause a problem.  Instead, link to internal
            # libraries by deducing the .lib file name using
            # the namespace name and version
            if self._pkgconfig_msvc_flags:
                if self._options.namespace_version:
                    args.append(str.lower(self._options.namespace_name) +
                                '-' +
                                self._options.namespace_version+'.lib')
                else:
                    args.append(str.lower(self._options.namespace_name)+'.lib')
            else:
                args.append('-Wl,-rpath=.')

        for library in self._options.libraries:
            # Visual C++: We have the needed .lib files now, and we need to link
            # to .lib files, not the .dll as the --library option specifies the
            # .dll(s) the .gir file refers to
            if self._pkgconfig_msvc_flags == '':
                if library.endswith(".la"): # explicitly specified libtool library
                    args.append(library)
                else:
                    args.append('-l' + library)

        for library_path in self._options.library_paths:
            # Not used/needed on Visual C++, and -Wl,-rpath options
            # will cause grief
            if self._pkgconfig_msvc_flags == '':
                args.append('-L' + library_path)
                if os.path.isabs(library_path):
                    if libtool:
                        args.append('-rpath')
                        args.append(library_path)
                    else:
                        args.append('-Wl,-rpath=' + library_path)

        args.extend(self._run_pkgconfig('--libs'))

    def _add_link_external_args(self, args):
        # An "external" link is where the library to be introspected
        # is installed on the system; this case is used for the scanning
        # of GLib in gobject-introspection itself.

        args.extend(self._run_pkgconfig('--libs'))
        for library in self._options.libraries:
            # The --library option on Windows pass in the .dll file(s) the
            # .gir files refer to, so don't link to them on Visual C++
            if self._pkgconfig_msvc_flags == '':
                if library.endswith(".la"): # explicitly specified libtool library
                    args.append(library)
                else:
                    args.append('-l' + library)

def compile_introspection_binary(options, get_type_functions,
                                 error_quark_functions):
    dc = DumpCompiler(options, get_type_functions, error_quark_functions)
    return dc.run()
