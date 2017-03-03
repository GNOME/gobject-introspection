#!/usr/bin/python
#
# Utility script to generate .pc files for GLib
# for Visual Studio builds, to be used for
# building introspection files

# Author: Fan, Chun-wei
# Date: March 10, 2016

import os
import sys

from replace import replace_multi
from pc_base import BasePCItems

def main(argv):
    base_pc = BasePCItems()
    
    base_pc.setup(argv)
    pkg_replace_items = {'@bindir@': '${exec_prefix}/bin',
                         '@datarootdir@': '${exec_prefix}/share',
                         '@datadir@': '${datarootdir}',
                         '@EXEEXT@': '.exe',
                         '@FFI_PC_CFLAGS@': '',
                         '@FFI_PC_PACKAGES@': '',
                         '@FFI_PC_LIBS@': '',
                         '${bindir}/g-ir-scanner': 'python ${bindir}/g-ir-scanner'}

    pkg_replace_items.update(base_pc.base_replace_items)

    # Generate gobject-introspection-1.0.pc
    replace_multi(base_pc.top_srcdir + '/gobject-introspection-1.0.pc.in',
                  base_pc.srcdir + '/gobject-introspection-1.0.pc',
                  pkg_replace_items)

    # Generate gobject-introspection-no-export-1.0.pc
    replace_multi(base_pc.top_srcdir + '/gobject-introspection-no-export-1.0.pc.in',
                  base_pc.srcdir + '/gobject-introspection-no-export-1.0.pc',
                  pkg_replace_items)

    # Generate a generic .pc file for Cairo, that is just sufficient for our purposes
    cairo_version = '1.14.6' # Use the latest stable version, for now.
    cairo_pc = open(base_pc.srcdir + '/cairo.pc', 'w')
    cairo_pc.write('prefix=' + base_pc.prefix + '\n')
    cairo_pc.write('exec_prefix=${prefix}\n')
    cairo_pc.write('libdir=${prefix}/lib\n')
    cairo_pc.write('includedir=${prefix}/include\n\n')
    cairo_pc.write('Name: cairo\n')
    cairo_pc.write('Description: generic cairo pkg-config file\n')
    cairo_pc.write('Version: ' + cairo_version + '\n\n')
    cairo_pc.write('Requires.private:\n')
    cairo_pc.write('Libs: -L${libdir} -lcairo\n')
    cairo_pc.write('Libs.private:\n')
    cairo_pc.write('Cflags: -I${includedir}\n')
    cairo_pc.close()

    # Generate a generic .pc file for Cairo-Win32, that is just sufficient for our
    # purposes
    # Just make a copy of the cairo.pc we just generated and replace the items as needed
    cairo_win32_replace_items = \
	    {'generic cairo pkg-config file': 'generic cairo-win32 pkg-config file'}
    replace_multi(base_pc.srcdir + '/cairo.pc',
                  base_pc.srcdir + '/cairo-win32.pc',
                  cairo_win32_replace_items)

    # Generate a generic .pc file for Cairo-GObject, that is just sufficient for our
    # purposes
    # Just make a copy of the cairo.pc we just generated and replace the items as needed
    cairo_gobject_replace_items = \
	    {'Requires.private:': 'Requires.private: gobject-2.0,glib-2.0',
         'generic cairo pkg-config file': 'generic cairo-gobject pkg-config file',
		 '-lcairo': '-lcairo-gobject'}
    replace_multi(base_pc.srcdir + '/cairo.pc',
                  base_pc.srcdir + '/cairo-gobject.pc',
                  cairo_gobject_replace_items)

    # Generate a generic .pc file for libxml2, that is just sufficient for our purposes
    libxml2_version = '2.9.3' # Use the latest stable version, for now.
    libxml2_replace_items = \
	    {'Name: cairo': 'Name: libXML',
         'Version: ' + cairo_version: 'Version: ' + libxml2_version,
         'generic cairo pkg-config file': 'generic libXML2 pkg-config file',
         '-lcairo': 'libxml2.lib',
         'Cflags: -I${includedir}': 'Cflags: -I${includedir}/libxml2'}
    replace_multi(base_pc.srcdir + '/cairo.pc',
                  base_pc.srcdir + '/libxml-2.0.pc',
                  libxml2_replace_items)

    # Generate a generic .pc file for freetype2, that is just sufficient for our purposes
    ft2_version = '2.6.3' # Use the latest stable version, for now.
    ft2_replace_items = \
	    {'Name: cairo': 'Name: FreeType 2',
         'Version: ' + cairo_version: 'Version: ' + ft2_version,
         'generic cairo pkg-config file': 'generic FreeType2 pkg-config file',
         '-lcairo': '-lfreetype'}
    replace_multi(base_pc.srcdir + '/cairo.pc',
                  base_pc.srcdir + '/freetype2.pc',
                  ft2_replace_items)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
