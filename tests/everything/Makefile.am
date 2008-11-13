include $(top_srcdir)/common.mk

LT_CURRENT = 1
LT_REVISION = 0
LT_AGE = 0
LT_VERSION = $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
TYPELIB_VERSION = $(LT_CURRENT).0

AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -version-info $(LT_VERSION)
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
TYPELIBS = $(GIRS:.gir=.typelib)
TXMLS = $(GIRS:.gir=.gir.txml)
CLEANFILES = $(TYPELIBS) $(TXMLS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(TXMLS) $(GIRS)

Everything-$(TYPELIB_VERSION).gir: libgirepository-everything.la gitesttypes.c gitesttypes.h $(SCANNER_BIN) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) \
	--include=GObject-2.0 \
	--library=girepository-everything \
	--namespace=Everything --nsversion=$(TYPELIB_VERSION) \
	--pkg gobject-2.0 \
	$(srcdir)/gitesttypes.h $(srcdir)/gitesttypes.c \
	--output $@
GIRS += Everything-$(TYPELIB_VERSION).gir

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@
	PYTHONPATH=$(SCANNER_PYTHONPATH) $(SCANNER) --add-include-path=$(top_builddir)/gir --typelib-xml $< > $<.tmp && mv $<.tmp $<.txml
