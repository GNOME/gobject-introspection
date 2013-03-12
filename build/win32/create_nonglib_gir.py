#!/usr/bin/python
#
# Expand the bundled *.gir.in files
# for use in Visual C++ builds of G-I
#
# Author: Fan, Chun-wei
# Date: January 21, 2013
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

def get_vsver(vsver):
    return {
        '9': '9',
        '10': '10',
        '11': '11',
        '2008': '9',
        '2010': '10',
        '2012': '11',
        }.get(vsver, '0')

def parent_dir(path):
    if not os.path.isabs(path):
        path = os.path.abspath(path)
    if os.path.isfile(path):
        path = os.path.dirname(path)
    return os.path.split(path)[0]

def setup_vars_cairo(src, dest, vsver):
    vars = {}
    vars['CAIRO_GIR_PACKAGE'] = 'cairo-gobject'
    vars['CAIRO_SHARED_LIBRARY'] = '%s-vs%s.dll' % (vars['CAIRO_GIR_PACKAGE'], vsver)
    process_in (src, dest, vars)

def main(argv):
    parser = optparse.OptionParser()
    parser.add_option('--vsver', dest='vsver', action='store', help='Version of Visual Studio used, 9 or 2008 for VS 2008, 10 or 2010 for VS2010, 11 or 2012 for VS2012')
    opt, args = parser.parse_args(argv)
    if opt.vsver is None:
        print ('vsver must be specified.  Please use %s -h to see the valid values' % os.path.basename(__file__))
        sys.exit()
    vsver = get_vsver(opt.vsver)
    if vsver is '0':
        print ('You must specify a valid vsver.  Please use %s -h to see the valid values' % os.path.basename(__file__))
        sys.exit()

    # Get the srcroot and the path where the bundled .gir files reside in the package
    srcroot = parent_dir(parent_dir(__file__))
    preset_gir_path = os.path.join(srcroot, 'gir')

    # Set up variables in cairo-1.0.gir.in to produce cairo-1.0.gir
    setup_vars_cairo(os.path.join(preset_gir_path, 'cairo-1.0.gir.in'),
                     os.path.join(preset_gir_path, 'cairo-1.0.gir'),
                     vsver)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
