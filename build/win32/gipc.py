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

if __name__ == '__main__':
    sys.exit(main(sys.argv))
