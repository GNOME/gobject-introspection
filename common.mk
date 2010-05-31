# -*- Mode: make -*-
# Copyright 2009-2010 Johan Dahlin
#
# This file defines variables that are compatible with
# Makefile.introspection, but for use within the gobject-introspection
# module itself.
#

INTROSPECTION_SCANNER = \
    env LPATH=.libs \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
	UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
	UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
    $(top_builddir)/tools/g-ir-scanner$(EXEEXT)
INTROSPECTION_SCANNER_ARGS = \
    --verbose \
    -I$(top_srcdir) \
    --add-include-path=$(srcdir) \
    --add-include-path=$(top_srcdir)/gir \
    --add-include-path=$(builddir) \
    --add-include-path=$(top_builddir)/gir

INTROSPECTION_COMPILER = $(top_builddir)/tools/g-ir-compiler$(EXEEXT)
INTROSPECTION_COMPILER_ARGS = \
    --includedir=$(srcdir) \
    --includedir=$(top_srcdir)/gir \
    --includedir=$(builddir) \
    --includedir=$(top_builddir)/gir
