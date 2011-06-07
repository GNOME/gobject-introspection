#!/usr/bin/env python

import os
import sys

if __name__ == '__main__':
    srcdir = sys.argv[1]
    sources = []
    projname = 'gio'
    subdir = os.path.join(srcdir, projname)
    headersfile = os.path.join(subdir, projname + '-public-headers.txt')
    f = open(headersfile)
    line = f.read()
    f.close()
    for headername in line.split(' '):
        headername = headername.strip()
        sources.append(os.path.join(subdir, headername))
    for sourcename in os.listdir(subdir):
        if sourcename.endswith('.c'):
            sources.append(os.path.join(subdir, sourcename))
    os.execv('./g-ir-annotation-tool',
             ['./g-ir-annotation-tool', '--extract', '-DGOBJECT_COMPILATION',
              '-DGIO_COMPILATION',
              '-I' + srcdir,
              '-I' + os.path.join(srcdir, 'glib'),
              '-I' + os.path.join(srcdir, 'gobject'),
              '-I' + os.path.join(srcdir, 'gio'),
              '-I' + os.path.join(srcdir, 'gmodule')] + sources)
