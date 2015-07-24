#!/usr/bin/python
#
# Expand the bundled cairo-1.0.gir.in files
# for use in Visual C++ builds of G-I
#
# Author: Fan, Chun-wei
# Date: January 20, 2014
#
# (Adapted from setup.py in
# $(glib_src_root)/build/win32/setup.py written by Shixin Zeng)

import os
import sys
import re
import string
import subprocess
import optparse

def process_in(src, dest, vars):
    RE_VARS = re.compile(r'%(\w+?)%')
    with open(src, 'r') as s:
        with open(dest, 'w') as d:
            for i in s:
                i = RE_VARS.sub(lambda x: str(vars[x.group(1)]), i)
                d.write(i)

def parent_dir(path):
    if not os.path.isabs(path):
        path = os.path.abspath(path)
    if os.path.isfile(path):
        path = os.path.dirname(path)
    return os.path.split(path)[0]

def setup_vars_cairo(src, dest, dllname):
    vars = {}
    vars['CAIRO_GIR_PACKAGE'] = 'cairo-gobject'
    vars['CAIRO_SHARED_LIBRARY'] = '%s' % dllname
    process_in (src, dest, vars)

def main(argv):
    parser = optparse.OptionParser()
    parser.add_option('--dllname', dest='dllname', action='store', help='Full file name of the Cairo-GObject DLL for the Cairo Introspection File')
    opt, args = parser.parse_args(argv)
    if opt.dllname is None:
        print ('dllname must be specified.  Please refer to %s -h for more information' % os.path.basename(__file__))
        sys.exit()

    # Get the srcroot and the path where the bundled .gir files reside in the package
    srcroot = parent_dir(__file__)
    preset_gir_path = os.path.join(srcroot, 'gir')

    # Set up variables in cairo-1.0.gir.in to produce cairo-1.0.gir
    setup_vars_cairo(os.path.join(preset_gir_path, 'cairo-1.0.gir.in'),
                     'cairo-1.0.gir',
                     opt.dllname)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
