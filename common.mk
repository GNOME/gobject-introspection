# -*- Mode: make -*-
# Copyright 2009-2010 Johan Dahlin
#
# This file defines variables that are compatible with
# Makefile.introspection, but for use within the gobject-introspection
# module itself.
#

INTROSPECTION_SCANNER = \
    env PATH=.libs:$(PATH) \
        LPATH=.libs \
        CC=$(CC) \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
        $(top_builddir)/g-ir-scanner

INTROSPECTION_SCANNER_ARGS = \
    --verbose \
    -I$(top_srcdir) \
    --add-include-path=$(srcdir) \
    --add-include-path=$(top_srcdir)/gir \
    --add-include-path=$(builddir) \
    --add-include-path=$(top_builddir)

INTROSPECTION_COMPILER = \
    env PATH=.libs:$(PATH) \
        $(top_builddir)/g-ir-compiler$(EXEEXT)

INTROSPECTION_COMPILER_ARGS = \
    --includedir=$(srcdir) \
    --includedir=$(top_srcdir)/gir \
    --includedir=$(builddir) \
    --includedir=$(top_builddir)

INTROSPECTION_DOCTOOL = \
    env PATH=.libs:$(PATH) \
        LPATH=.libs \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
        $(top_builddir)/g-ir-doc-tool
