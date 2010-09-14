include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

INTROSPECTION_SCANNER_ARGS += --warn-all --warn-error

# We need to build a shared library, which can be dlopened
# it does not work with noinst_LTLIBRARIES
testlib_LTLIBRARIES = \
	libannotation.la \
	libtestinherit.la \
	libfoo.la \
	libutility.la \
	libgtkfrob.la
if HAVE_CAIRO
testlib_LTLIBRARIES += libregress.la
endif

testlibdir = $(prefix)/unused
install-testlibLTLIBRARIES: # prevent it from being installed

AM_CPPFLAGS = -I$(top_srcdir)/girepository
AM_CFLAGS = $(GIO_CFLAGS) $(GOBJECT_CFLAGS) $(GTHREAD_CFLAGS)
AM_LDFLAGS = -avoid-version
LIBS = $(GOBJECT_LIBS) $(GTHREAD_LIBS)

libannotation_la_SOURCES = $(srcdir)/annotation.c $(srcdir)/annotation.h
libtestinherit_la_SOURCES = $(srcdir)/drawable.c $(srcdir)/drawable.h
libfoo_la_SOURCES = $(srcdir)/foo.c $(srcdir)/foo.h
libfoo_la_LIBADD = $(top_builddir)/girepository/libgirepository-1.0.la
libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h
libgtkfrob_la_SOURCES = $(srcdir)/gtkfrob.c $(srcdir)/gtkfrob.h
libregress_la_SOURCES = $(srcdir)/regress.c $(srcdir)/regress.h

testsdir = $(datadir)/gobject-introspection-1.0/tests
tests_DATA = $(libregress_la_SOURCES)

libregress_la_CFLAGS = $(AM_CFLAGS) $(CAIRO_CFLAGS)
libregress_la_LDFLAGS = $(AM_LDFLAGS) $(CAIRO_LIBS) 


if OS_WIN32
AM_LDFLAGS += -no-undefined
endif

# .gir --[scanner]-> .typelib
GIRS =
TYPELIBS = $(GIRS:.gir=.typelib)
CHECKGIRS = $(GIRS:.gir=.gir.check)
EXPECTEDGIRS = $(GIRS:.gir=-expected.gir)
INTROSPECTION_GIRS = $(GIRS)
CLEANFILES = $(TYPELIBS) $(GIRS)
BUILT_SOURCES = $(TYPELIBS) $(GIRS)
EXTRA_DIST = $(EXPECTEDGIRS)

Regress-1.0.gir: $(top_builddir)/gir/Gio-2.0.gir libregress.la
Regress_1_0_gir_LIBS = libregress.la
Regress_1_0_gir_INCLUDES = cairo-1.0 Gio-2.0
Regress_1_0_gir_FILES = $(libregress_la_SOURCES)
if HAVE_CAIRO
GIRS += Regress-1.0.gir
endif

Annotation-1.0.gir: Utility-1.0.gir libannotation.la
Annotation_1_0_gir_PACKAGES = gobject-2.0
Annotation_1_0_gir_LIBS = libannotation.la
Annotation_1_0_gir_INCLUDES = GObject-2.0 Utility-1.0
Annotation_1_0_gir_FILES = $(libannotation_la_SOURCES)
GIRS += Annotation-1.0.gir

TestInherit-1.0.gir: Utility-1.0.gir libtestinherit.la
TestInherit_1_0_gir_PACKAGES = gobject-2.0
TestInherit_1_0_gir_LIBS = libtestinherit.la
TestInherit_1_0_gir_INCLUDES = GObject-2.0 Utility-1.0
TestInherit_1_0_gir_FILES = $(libtestinherit_la_SOURCES)
GIRS += TestInherit-1.0.gir

Foo-1.0.gir: Utility-1.0.gir libfoo.la
Foo_1_0_gir_PACKAGES = gobject-2.0
Foo_1_0_gir_LIBS = libfoo.la
Foo_1_0_gir_INCLUDES = GObject-2.0 Gio-2.0 Utility-1.0
Foo_1_0_gir_FILES = $(srcdir)/foo.h $(srcdir)/foo.c
Foo_1_0_gir_SCANNERFLAGS = --c-include="foo.h"
GIRS += Foo-1.0.gir

Utility-1.0.gir: libutility.la
Utility_1_0_gir_PACKAGES = gobject-2.0
Utility_1_0_gir_LIBS = libutility.la
Utility_1_0_gir_INCLUDES = GObject-2.0
Utility_1_0_gir_FILES = $(libutility_la_SOURCES)
GIRS += Utility-1.0.gir

# This one tests different --namespace and --strip-prefix
GtkFrob-1.0.gir: libgtkfrob.la
GtkFrob_1_0_gir_PACKAGES = gobject-2.0
GtkFrob_1_0_gir_LIBS = libgtkfrob.la
GtkFrob_1_0_gir_INCLUDES = GObject-2.0
GtkFrob_1_0_gir_FILES = $(libgtkfrob_la_SOURCES)
GtkFrob_1_0_gir_SCANNERFLAGS = --identifier-prefix=Gtk --symbol-prefix=gtk_frob
GIRS += GtkFrob-1.0.gir

noinst_PROGRAMS = barapp

barapp_SOURCES = $(srcdir)/barapp.c $(srcdir)/barapp.h
barapp_LDADD = $(top_builddir)/girepository/libgirepository-1.0.la
barapp_LDFLAGS = -export-dynamic

Bar-1.0.gir: barapp
Bar_1_0_gir_PACKAGES = gobject-2.0
Bar_1_0_gir_PROGRAM = ./barapp
Bar_1_0_gir_INCLUDES = GObject-2.0
Bar_1_0_gir_FILES = $(barapp_SOURCES)
Bar_1_0_gir_SCANNERFLAGS = --accept-unprefixed
GIRS += Bar-1.0.gir

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

check-local: pre-check
check-local: $(CHECKGIRS) $(TYPELIBS)

check-local: post-check
