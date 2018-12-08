#!/usr/bin/env python3
# Scan glib sources.
# e.g.:
#   ./update-glib-annotations.py ../../glib ../../glib/_build

import os
import sys

import subprocess

path=os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
for k in ['UNINSTALLED_INTROSPECTION_SRCDIR',
          'UNINSTALLED_INTROSPECTION_BUILDDIR']:
    if k not in os.environ:
        os.environ[k] = path

possible_builddirs = ['../_build/', '..', '../../build/']


def directory_includes(dirs, srcdir, builddir):
    result = []
    result.append('-I' + srcdir)

    if srcdir != builddir:
        result.append('-I' + builddir)

    for name in dirs:
        result.append('-I' + os.path.join(srcdir, name))
        if srcdir != builddir:
            result.append('-I' + os.path.join(builddir, name))

    return result


def extract_annotations(module, srcdir, builddir, outfile):
    sources = []
    subdir = os.path.join(srcdir, module['name'])
    includes = directory_includes(module['includes'],
                                  srcdir, builddir)

    for sourcename in os.listdir(subdir):
        if sourcename.endswith('.c'):
            sources.append(os.path.join(subdir, sourcename))

    annotation_tool_base_args = [
        os.path.join(builddir, 'g-ir-annotation-tool'), '--extract']

    return subprocess.check_call(annotation_tool_base_args +
                                 module['defines'] +
                                 includes +
                                 sources,
                                 stdout=outfile)


if __name__ == '__main__':
    srcdir = sys.argv[1]
    if len(sys.argv) == 3:
        builddir = sys.argv[2]
    else:
        for d in possible_builddirs:
            if os.path.isfile(os.path.join(d, 'g-ir-annotation-tool')):
                builddir = d
                break
        assert builddir is not None

    print("Using source directory: '%s' build directory: '%s'" % (srcdir, builddir))

    modules = [{'name':         'glib',
                'srcname':      '../gir/glib-2.0.c',
                'includes':     ['glib', 'gmodule'],
                'defines':      ['-DGLIB_COMPILATION']},

               {'name':         'gmodule',
                'srcname':      '../gir/gmodule-2.0.c',
                'includes':     ['glib', 'gmodule'],
                'defines':      ['-DGLIB_COMPILATION']},

               {'name':         'gobject',
                'srcname':      '../gir/gobject-2.0.c',
                'includes':     ['glib', 'gobject', 'gmodule'],
                'defines':      ['-DGOBJECT_COMPILATION']},

               {'name':         'gio',
                'srcname':      '../gir/gio-2.0.c',
                'includes':     ['glib', 'gmodule', 'gobject', 'gio'],
                'defines':      ['-DGOBJECT_COMPILATION', '-DGIO_COMPILATION', '-DG_SETTINGS_ENABLE_BACKEND']}]

    for module in modules:
        srcname = module['srcname']
        tmpname = module['srcname'] + '.tmp'

        if os.path.isfile(tmpname):
            os.unlink(tmpname)

        if os.path.isfile(srcname):
            os.unlink(srcname)

        # Extract annotations into a file opened in binary mode.
        # Since g-ir-scanner-tool outputs utf-8 encoded data, we simply pass
        # that directly into this file via. the underlying subprocess call.
        srcfile = open(tmpname, 'wb')
        extract_annotations(module, srcdir, builddir, srcfile)
        srcfile.close()
        os.rename(tmpname, srcname)

        print("Updated '%s'" % (srcname, ))

    print("Done; run \"git diff\" to see any changes.")
