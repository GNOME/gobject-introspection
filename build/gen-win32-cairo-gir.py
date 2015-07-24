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
import optparse

from gi_msvc_build_utils import process_in
from gi_msvc_build_utils import parent_dir

def setup_vars_cairo(src, dest, dllname):
    vars = {}
    vars['CAIRO_GIR_PACKAGE'] = 'cairo-gobject'
    vars['CAIRO_SHARED_LIBRARY'] = '%s' % dllname
    process_in (src, dest, vars, 1)

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
