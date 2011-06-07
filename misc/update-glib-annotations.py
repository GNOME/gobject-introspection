#!/usr/bin/env python

import os
import sys

if __name__ == '__main__':
    srcdir = sys.argv[1]
    sources = []
    projname = 'glib'
    subdir = os.path.join(srcdir, projname)
    headersfile = os.path.join(subdir, projname + '-public-headers.txt')
    f = open(headersfile)
    line = f.read()
    f.close()
    for headername in line.split(' '):
        headername = headername.strip()
        if headername == 'gi18n-lib.h':
            continue
        sources.append(os.path.join(subdir, headername))
    for sourcename in os.listdir(subdir):
        if sourcename.endswith('.c'):
            sources.append(os.path.join(subdir, sourcename))
    os.execv('./g-ir-annotation-tool',
             ['./g-ir-annotation-tool', '--extract',
              '-DGLIB_COMPILATION',
              '-I' + srcdir,
              '-I' + os.path.join(srcdir, 'glib'),
              '-I' + os.path.join(srcdir, 'gmodule')] + sources)
