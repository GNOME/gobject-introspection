#!/usr/bin/env python
# Scan glib sources.
# e.g.:
#   ./update-glib-annotations.py ../../glib ../../glib/_build


import os
import sys

import subprocess


possible_builddirs = ['../_build/', '..', '../../build/']
builddir = None
for d in possible_builddirs:
    if os.path.isfile(os.path.join(d, 'g-ir-annotation-tool')):
        builddir = d
        break
assert builddir is not None
annotation_tool_base_args = [os.path.join(builddir, 'g-ir-annotation-tool'),
                             '--extract']


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
    headersfile = os.path.join(builddir,
                               module['name'],
                               module['name'] + '-public-headers.txt')
    includes = directory_includes(module['includes'],
                                  srcdir, builddir)

    f = open(headersfile)
    line = f.read()
    f.close()

    for headername in line.split(' '):
        headername = headername.strip()
        if headername in module['skip_headers']:
            continue
        sources.append(os.path.join(subdir, headername))

    for sourcename in os.listdir(subdir):
        if sourcename.endswith('.c'):
            sources.append(os.path.join(subdir, sourcename))

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
        builddir = srcdir

    print "Using source directory: %r build directory: %r" % (srcdir, builddir)

    modules = [{'name':         'glib',
                'srcname':      '../gir/glib-2.0.c',
                'skip_headers': ['gi18n-lib.h'],
                'includes':     ['glib', 'gmodule'],
                'defines':      ['-DGLIB_COMPILATION']},

               {'name':         'gobject',
                'srcname':      '../gir/gobject-2.0.c',
                'skip_headers': [],
                'includes':     ['glib', 'gobject', 'gmodule'],
                'defines':      ['-DGOBJECT_COMPILATION']},

               {'name':         'gio',
                'srcname':      '../gir/gio-2.0.c',
                'skip_headers': [],
                'includes':     ['glib', 'gmodule', 'gobject', 'gio'],
                'defines':      ['-DGOBJECT_COMPILATION', '-DGIO_COMPILATION']}]

    for module in modules:
        srcname = module['srcname']
        tmpname = module['srcname'] + '.tmp'

        if os.path.isfile(tmpname):
            os.unlink(tmpname)

        if os.path.isfile(srcname):
            os.unlink(srcname)

        srcfile = open(tmpname, 'w')
        extract_annotations(module, srcdir, builddir, srcfile)
        srcfile.close()
        os.rename(tmpname, srcname)

        print "Updated %r" % (srcname, )

    print "Done; run \"git diff\" to see any changes."
