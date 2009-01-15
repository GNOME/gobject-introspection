include $(top_srcdir)/common.mk

LT_CURRENT = 1
LT_REVISION = 0
LT_AGE = 0
LT_VERSION = $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
TYPELIB_VERSION = $(LT_CURRENT).0

AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -version-info $(LT_VERSION)
LIBS = $(GOBJECT_LIBS)

typelibsdir = $(libdir)/girepository-1.0
typelibs_DATA = $(TYPELIBS)

girsdir = $(datadir)/gir-1.0
girs_DATA = $(GIRS)

lib_LTLIBRARIES = libgirepository-everything-1.0.la

libgirepository_everything_1_0_la_SOURCES = $(srcdir)/everything.c $(srcdir)/everything.h

if OS_WIN32
AM_LDFLAGS += -no-undefined
endif

GIRS =
TYPELIBS = $(GIRS:.gir=.typelib)
TXMLS = $(GIRS:.gir=.tgir)
CLEANFILES = $(TYPELIBS) $(TXMLS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(TXMLS) $(GIRS)

Everything-$(TYPELIB_VERSION).gir: libgirepository-everything-1.0.la everything.c everything.h $(SCANNER_BIN) $(SCANNER_LIBS)
	$(CHECK_DEBUG) $(SCANNER) \
	--include=GObject-2.0 \
        --libtool="$(LIBTOOL)" \
	--library=girepository-everything-1.0 \
	--namespace=Everything --nsversion=$(TYPELIB_VERSION) \
	--pkg gobject-2.0 \
	$(srcdir)/everything.h $(srcdir)/everything.c \
	--output $@
GIRS += Everything-$(TYPELIB_VERSION).gir

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@

%.tgir: %.typelib $(top_builddir)/tools/g-ir-generate$(EXEEXT) Makefile
	 $(DEBUG) $(top_builddir)/tools/g-ir-generate --includedir=. --includedir=$(top_builddir)/gir $< -o $@
