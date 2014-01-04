include $(top_srcdir)/common.mk

SUBDIRS = . scanner repository offsets warn

EXTRA_DIST=
BUILT_SOURCES=
CLEANFILES=

AM_CFLAGS = $(GOBJECT_CFLAGS)
LIBADD = $(GOBJECT_LIBS)

testsdir = $(datadir)/gobject-introspection-1.0/tests
tests_DATA =		    \
    everything.c	    \
    everything.h	    \
    gimarshallingtests.c    \
    gimarshallingtests.h

EXTRA_LTLIBRARIES = libeverything-1.0.la libgimarshallingtests-1.0.la

libeverything_1_0_la_SOURCES = everything.c
libgimarshallingtests_1_0_la_SOURCES = gimarshallingtests.c

EXTRA_DIST += \
	gimarshallingtests.h \
	gi-tester

BUILT_SOURCES += everything.c everything.h

CLEANFILES += \
    $(BUILT_SOURCES) \
    $(EXTRA_LTLIBRARIES) \
    everything-stamp.h \
    Everything-1.0.gir \
    Everything-1.0.typelib \
    GIMarshallingTests-1.0.gir \
    GIMarshallingTests-1.0.typelib

everything-stamp.h: Makefile
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) --generate-typelib-tests=Everything,everything.h,everything.c
	touch $@

everything.c: everything-stamp.h
	@true

everything.h: everything-stamp.h
	@true

Everything-1.0.gir: libeverything-1.0.la Makefile
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) --warn-all --warn-error --reparse-validate \
	--namespace=Everything --nsversion=1.0 \
	--libtool="$(LIBTOOL)" \
	--add-include-path=$(top_builddir) --include=Gio-2.0 \
	--library=libeverything-1.0.la --output=$@ \
	everything.h everything.c

GIMarshallingTests-1.0.gir: libgimarshallingtests-1.0.la Makefile
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) --warn-all --warn-error --reparse-validate \
	--namespace=GIMarshallingTests --symbol-prefix=gi_marshalling_tests --nsversion=1.0 \
	--libtool="$(LIBTOOL)" \
	--add-include-path=$(top_builddir) --include=Gio-2.0 \
	--library=libgimarshallingtests-1.0.la  --output=$@ \
	--c-include="tests/gimarshallingtests.h" \
	$(srcdir)/gimarshallingtests.h $(srcdir)/gimarshallingtests.c

%.typelib: %.gir
	$(AM_V_GEN) $(INTROSPECTION_COMPILER) $(INTROSPECTION_COMPILER_ARGS) $< -o $@

TESTS=Everything-1.0.typelib GIMarshallingTests-1.0.typelib
LOG_COMPILER=$(srcdir)/gi-tester
