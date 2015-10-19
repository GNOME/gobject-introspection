# -*- Mode: make -*-
# Copyright 2009-2010 Johan Dahlin
#
# This file defines variables that are compatible with
# Makefile.introspection, but for use within the gobject-introspection
# module itself.
#

if USE_HOST_GI
INTROSPECTION_SCANNER = \
    env PATH="$(PATH)" \
        LPATH=.libs \
        CC="$(CC)" \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
        g-ir-scanner
else
INTROSPECTION_SCANNER = \
    env PATH=".libs:$(PATH)" \
        LPATH=.libs \
        CC="$(CC)" \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
        $(top_builddir)/g-ir-scanner
endif

if USE_CROSS_WRAPPER
CROSS_WRAPPER_ARG = --use-binary-wrapper=$(GI_CROSS_WRAPPER)
else
CROSS_WRAPPER_ARG =
endif

if USE_LDD_WRAPPER
LDD_WRAPPER_ARG = --use-ldd-wrapper=$(GI_LDD_WRAPPER)
else
LDD_WRAPPER_ARG =
endif

INTROSPECTION_SCANNER_ARGS = \
    --verbose \
    $(CROSS_WRAPPER_ARG) \
    $(LDD_WRAPPER_ARG) \
    -I$(top_srcdir) \
    --add-include-path=$(srcdir) \
    --add-include-path=$(top_srcdir)/gir \
    --add-include-path=$(builddir) \
    --add-include-path=$(top_builddir) \
    --add-include-path=$(top_builddir)/gir

if USE_CROSS_WRAPPER
INTROSPECTION_COMPILER = \
    env PATH=".libs:$(PATH)" \
        $(GI_CROSS_WRAPPER) $(top_builddir)/.libs/g-ir-compiler$(EXEEXT)
else
INTROSPECTION_COMPILER = \
    env PATH=".libs:$(PATH)" \
        $(top_builddir)/g-ir-compiler$(EXEEXT)
endif

INTROSPECTION_COMPILER_ARGS = \
    --includedir=$(srcdir) \
    --includedir=$(top_srcdir)/gir \
    --includedir=$(builddir) \
    --includedir=$(top_builddir) \
    --includedir=$(top_builddir)/gir

if USE_HOST_GI
INTROSPECTION_DOCTOOL = \
    env PATH="$(PATH)" \
        LPATH=.libs \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
        g-ir-doc-tool
else
INTROSPECTION_DOCTOOL = \
    env PATH=".libs:$(PATH)" \
        LPATH=.libs \
        PYTHONPATH=$(top_builddir):$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
        UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir) \
        $(top_builddir)/g-ir-doc-tool
endif

INTROSPECTION_DOCTOOL_ARGS = \
    --add-include-path=$(srcdir) \
    --add-include-path=$(top_srcdir)/gir \
    --add-include-path=$(builddir) \
    --add-include-path=$(top_builddir) \
    --add-include-path=$(top_builddir)/gir
