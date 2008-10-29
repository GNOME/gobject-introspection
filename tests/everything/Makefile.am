AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -version-info 1:0:0
LIBS = $(GOBJECT_LIBS)

typelibsdir = $(libdir)/girepository
typelibs_DATA = $(TYPELIBS)

girsdir = $(datadir)/gir
girs_DATA = $(GIRS)

lib_LTLIBRARIES = libgirepository-everything.la

libgirepository_everything_la_SOURCES = $(srcdir)/gitesttypes.c $(srcdir)/gitesttypes.h

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

Everything-1.0.gir: libgirepository-everything.la gitesttypes.c gitesttypes.h $(SCANNER) $(SCANNER_LIBS)
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(CHECK_DEBUG) $(SCANNER) -v \
	--add-include-path=$(top_builddir)/gir \
	--include=GObject-2.0 \
	--library=girepository-everything \
	--namespace=Everything --nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/gitesttypes.h $(srcdir)/gitesttypes.c \
	--output $@
GIRS += Everything-1.0.gir

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@
	PYTHONPATH=$(top_builddir):$$PYTHONPATH $(SCANNER) --add-include-path=$(top_builddir)/gir --typelib-xml $< > $<.tmp && mv $<.tmp $<.txml
