include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

# We need to build a shared library, which can be dlopened
# it does not work with noinst_LTLIBRARIES
testlib_LTLIBRARIES = \
	libannotation.la \
	libdrawable.la \
	libfoo.la \
	libutility.la \
	libgtkfrob.la
testlibdir = $(prefix)/unused
install-testlibLTLIBRARIES: # prevent it from being installed

AM_CPPFLAGS = -I$(top_srcdir)/girepository
AM_CFLAGS = $(GIO_CFLAGS) $(GOBJECT_CFLAGS) $(GTHREAD_CFLAGS)
AM_LDFLAGS = -avoid-version
LIBS = $(GOBJECT_LIBS) $(GTHREAD_LIBS)

libannotation_la_SOURCES = $(srcdir)/annotation.c $(srcdir)/annotation.h
libdrawable_la_SOURCES = $(srcdir)/drawable.c $(srcdir)/drawable.h
libfoo_la_SOURCES = $(srcdir)/foo.c $(srcdir)/foo.h
libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h
libgtkfrob_la_SOURCES = $(srcdir)/gtkfrob.c $(srcdir)/gtkfrob.h

if OS_WIN32
AM_LDFLAGS += -no-undefined
endif

# .gir --[scanner]-> .typelib --[generate]-> .tgir
GIRS =
TYPELIBS = $(GIRS:.gir=.typelib)
CHECKGIRS = $(GIRS:.gir=.gir.check)
EXPECTEDGIRS = $(GIRS:.gir=-expected.gir)
TGIRS = $(GIRS:.gir=.tgir)
CHECKTGIRS = $(GIRS:.gir=.tgir.check)
EXPECTEDTGIRS = $(GIRS:.gir=-expected.tgir)
INTROSPECTION_GIRS = $(GIRS)
CLEANFILES = $(TYPELIBS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(GIRS) $(TGIRS)
EXTRA_DIST = $(EXPECTEDGIRS) $(EXPECTEDTGIRS)

annotation-1.0.gir: utility-1.0.gir libannotation.la
annotation_1_0_gir_PACKAGES = gobject-2.0
annotation_1_0_gir_LIBS = libannotation.la
annotation_1_0_gir_INCLUDES = GObject-2.0 utility-1.0
annotation_1_0_gir_FILES = $(libannotation_la_SOURCES)
GIRS += annotation-1.0.gir

drawable-1.0.gir: utility-1.0.gir libdrawable.la
drawable_1_0_gir_PACKAGES = gobject-2.0
drawable_1_0_gir_LIBS = libdrawable.la
drawable_1_0_gir_INCLUDES = GObject-2.0 utility-1.0
drawable_1_0_gir_FILES = $(libdrawable_la_SOURCES)
GIRS += drawable-1.0.gir

foo-1.0.gir: utility-1.0.gir libfoo.la
foo_1_0_gir_PACKAGES = gobject-2.0
foo_1_0_gir_LIBS = libfoo.la
foo_1_0_gir_INCLUDES = GObject-2.0 Gio-2.0 utility-1.0
foo_1_0_gir_FILES = $(srcdir)/foo.h $(srcdir)/foo.c
foo_1_0_gir_SCANNERFLAGS = --c-include="foo.h"
GIRS += foo-1.0.gir

utility-1.0.gir: libutility.la
utility_1_0_gir_PACKAGES = gobject-2.0
utility_1_0_gir_LIBS = libutility.la
utility_1_0_gir_INCLUDES = GObject-2.0
utility_1_0_gir_FILES = $(libutility_la_SOURCES)
GIRS += utility-1.0.gir

# This one tests different --namespace and --strip-prefix
GtkFrob-1.0.gir: libgtkfrob.la
GtkFrob_1_0_gir_PACKAGES = gobject-2.0
GtkFrob_1_0_gir_LIBS = libgtkfrob.la
GtkFrob_1_0_gir_INCLUDES = GObject-2.0
GtkFrob_1_0_gir_FILES = $(libgtkfrob_la_SOURCES)
GtkFrob_1_0_gir_SCANNERFLAGS = --strip-prefix=Gtk
GIRS += GtkFrob-1.0.gir

noinst_PROGRAMS = barapp

barapp_SOURCES = $(srcdir)/barapp.c $(srcdir)/barapp.h
barapp_LDADD = $(top_builddir)/girepository/libgirepository-1.0.la
barapp_LDFLAGS = -export-dynamic

BarApp-1.0.gir: barapp
BarApp_1_0_gir_PACKAGES = gobject-2.0
BarApp_1_0_gir_PROGRAM = ./barapp
BarApp_1_0_gir_INCLUDES = GObject-2.0
BarApp_1_0_gir_FILES = $(barapp_SOURCES)
BarApp_1_0_gir_SCANNERFLAGS = --strip-prefix=Bar
GIRS += BarApp-1.0.gir

pre-check:
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   cp -f $(top_srcdir)/giscanner/*.py $(top_builddir)/giscanner; \
	fi

post-check:
	@echo "========================"
	@echo "All scanner tests passed"
	@echo "========================"
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	   rm -f $(top_builddir)/giscanner/*.py*; \
	fi

%.gir.check: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "  TEST  $*.gir"

# stop %.typelib rule from building %-expected.tgir (via %-expected.typelib)
%-expected.typelib:
	@true

%.tgir: %.typelib $(top_builddir)/tools/g-ir-generate$(EXEEXT) Makefile
	$(AM_V_GEN) $(top_builddir)/tools/g-ir-generate --includedir=. --includedir=$(top_builddir)/gir $< -o $@

%.tgir.check: %.tgir
	@diff -u -U 10 $(srcdir)/$*-expected.tgir $*.tgir; \
	if test "$$?" = "0"; then \
	    echo "  TEST  $*.tgir"; \
	    rm -f $*.tgir; \
	else \
	    exit 1; \
	fi

distclean-local:
	@if test "$(top_builddir)" != "$(top_srcdir)"; then \
	    rm -f $(top_builddir)/tests/scanner/*.tgir; \
	fi

check-local: pre-check
check-local: $(CHECKGIRS) $(CHECKTGIRS) $(TYPELIBS)

check-local: post-check
