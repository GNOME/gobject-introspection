AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -module -avoid-version
LIBS = $(GOBJECT_LIBS)

testprefix = $(pkglibdir)/test

testlibdir = $(testprefix)
testlib_LTLIBRARIES = libgitesttypes.la

girdir = $(testprefix)/gir
dist_gir_DATA = $(GIRS)

typelibdir = $(testprefix)/girepository
typelib_DATA = $(TYPELIBS)

libgitesttypes_la_SOURCES = $(srcdir)/gitesttypes.c $(srcdir)/gitesttypes.h

if OS_WIN32
AM_LDFLAGS += -no-undefined
endif

GIRS =
SCANNER = $(top_srcdir)/tools/g-ir-scanner
SCANNER_LIBS = $(top_srcdir)/giscanner/*.py \
	       $(top_builddir)/giscanner/libgiscanner.la
TYPELIBS = $(GIRS:.gir=.typelib)
TXMLS = $(GIRS:.gir=.gir.txml)
CLEANFILES = $(TYPELIBS) $(TXMLS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(TXMLS) $(GIRS)

gitesttypes-1.0.gir: libgitesttypes.la gitesttypes.c gitesttypes.h $(SCANNER) $(SCANNER_LIBS)
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(CHECK_DEBUG) $(SCANNER) -v \
	--include=$(top_srcdir)/gir/GObject-2.0.gir \
	--library=gitesttypes \
	--namespace=gitesttypes --nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/gitesttypes.h $(srcdir)/gitesttypes.c \
	--output $@
GIRS += gitesttypes-1.0.gir

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@
	$(SCANNER) --typelib-xml $< > $<.tmp && mv $<.tmp $<.txml
