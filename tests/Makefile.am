SUBDIRS = . scanner repository offsets

BUILT_SOURCES=
CLEANFILES=

INCLUDES = $(GOBJECT_CFLAGS)
LIBADD = $(GOBJECT_LIBS)

noinst_LTLIBRARIES = libeverything-1.0.la

libeverything_1_0_la_SOURCES = everything.c

BUILT_SOURCES += everything.c everything.h

CLEANFILES += $(BUILT_SOURCES) everything-stamp.h
everything-stamp.h: Makefile
	$(AM_V_GEN) $(top_builddir)/tools/g-ir-scanner --generate-typelib-tests=Everything,everything.h,everything.c
	touch $@

everything.c: everything-stamp.h
	@true

everything.h: everything-stamp.h
	@true

Everything-1.0.gir: libeverything-1.0.la
	$(AM_V_GEN) $(top_builddir)/tools/g-ir-scanner --warn-all --reparse-validate --namespace=Everything --version=1.0 --library=libeverything-1.0.la everything.h everything.c --output=$@

Everything-1.0.typelib: Everything-1.0.gir
	$(AM_V_GEN) $(top_builddir)/tools/g-ir-compiler $< -o $@

install-data-local:
	for src in everything.c everything.h; do \
	  install -m 644 -D $$src $(datadir)/gobject-introspection-1.0/tests/$$src; \
	done
