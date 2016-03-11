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
import argparse

import replace

from gi_msvc_build_utils import parent_dir

def main(argv):
    parser = argparse.ArgumentParser(description='Generate the complete cairo-1.0.gir')
    parser.add_argument('--dllname',
                        required=True,
                        help='Full file name of the Cairo-GObject DLL for the Cairo Introspection File')
    args = parser.parse_args()

    # Get the srcroot and the path where the bundled .gir files reside in the package
    srcroot = parent_dir(parent_dir(__file__))
    preset_gir_path = os.path.join(srcroot, 'gir')

    # Set up variables in cairo-1.0.gir.in to produce cairo-1.0.gir
    cairo_replace_items = {'%CAIRO_GIR_PACKAGE%': 'cairo-gobject',
                           '%CAIRO_SHARED_LIBRARY%': args.dllname}
    replace.replace_multi(os.path.join(preset_gir_path, 'cairo-1.0.gir.in'),
                          'cairo-1.0.gir',
                          cairo_replace_items)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
