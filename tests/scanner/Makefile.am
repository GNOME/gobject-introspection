NULL ?=

include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

INTROSPECTION_SCANNER_ARGS += --warn-all

check_LTLIBRARIES = \
	libsletter.la \
	libannotation.la \
	libtestinherit.la \
	libfoo.la \
	libutility.la \
	libgtkfrob.la \
	libgettype.la \
	libregress.la \
	libwarnlib.la \
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)/girepository
AM_CFLAGS = $(GIO_CFLAGS) $(GOBJECT_CFLAGS) $(GTHREAD_CFLAGS)
# -rpath needed to force libtool to build a shared library for a check_LTLIBRARIES
# target. See http://lists.gnu.org/archive/html/automake/2005-10/msg00107.html
AM_LDFLAGS = -rpath /unused -avoid-version
LIBS = $(GOBJECT_LIBS) $(GTHREAD_LIBS)

libsletter_la_SOURCES = $(srcdir)/sletter.c $(srcdir)/sletter.h
libsletter_la_LIBADD = $(GIO_LIBS)
libsletter_la_CFLAGS = $(AM_CFLAGS)
libsletter_la_LDFLAGS = $(AM_LDFLAGS)

libannotation_la_SOURCES = $(srcdir)/annotation.c $(srcdir)/annotation.h
libtestinherit_la_SOURCES = $(srcdir)/drawable.c $(srcdir)/drawable.h
libfoo_la_SOURCES = $(srcdir)/foo.c $(srcdir)/foo.h
libfoo_la_LIBADD = $(top_builddir)/libgirepository-1.0.la
libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h
libgtkfrob_la_SOURCES = $(srcdir)/gtkfrob.c $(srcdir)/gtkfrob.h
libregress_la_SOURCES = $(srcdir)/regress.c $(srcdir)/regress.h
libregress_la_LIBADD = $(GIO_LIBS) $(CAIRO_LIBS)
libwarnlib_la_CFLAGS = $(AM_CFLAGS)
libwarnlib_la_SOURCES = $(srcdir)/warnlib.c $(srcdir)/warnlib.h
libwarnlib_la_LIBADD = $(GIO_LIBS)
libwarnlib_la_LDFLAGS = -export-symbols-regex '^warnlib_' -no-undefined
libgettype_la_SOURCES = $(srcdir)/gettype.c $(srcdir)/gettype.h

testsdir = $(datadir)/gobject-introspection-1.0/tests
tests_DATA = $(libregress_la_SOURCES) $(libwarnlib_la_SOURCES)

libregress_la_CFLAGS = $(AM_CFLAGS) $(CAIRO_CFLAGS)
libregress_la_LDFLAGS = $(AM_LDFLAGS)


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
EXTRA_DIST = $(EXPECTEDGIRS)

SLetter-1.0.gir: $(top_builddir)/Gio-2.0.gir libsletter.la
SLetter_1_0_gir_LIBS = libsletter.la
SLetter_1_0_gir_INCLUDES = Gio-2.0
SLetter_1_0_gir_FILES = $(libsletter_la_SOURCES)
SLetter_1_0_gir_SCANNERFLAGS = --identifier-prefix=S --c-include="sletter.h" --warn-error
GIRS += SLetter-1.0.gir

Regress-1.0.gir: $(top_builddir)/Gio-2.0.gir libregress.la
Regress_1_0_gir_LIBS = libregress.la
Regress_1_0_gir_INCLUDES = cairo-1.0 Gio-2.0
Regress_1_0_gir_FILES = $(libregress_la_SOURCES)
Regress_1_0_gir_SCANNERFLAGS = --c-include="regress.h" --warn-error
GIRS += Regress-1.0.gir

WarnLib-1.0.gir: $(top_builddir)/Gio-2.0.gir libwarnlib.la
WarnLib_1_0_gir_LIBS = libwarnlib.la
WarnLib_1_0_gir_INCLUDES = Gio-2.0
WarnLib_1_0_gir_FILES = $(libwarnlib_la_SOURCES)
WarnLib_1_0_gir_SCANNERFLAGS = --c-include="warnlib.h"
GIRS += WarnLib-1.0.gir

Annotation-1.0.gir: Utility-1.0.gir libannotation.la
Annotation_1_0_gir_PACKAGES = gobject-2.0
Annotation_1_0_gir_LIBS = libannotation.la
Annotation_1_0_gir_INCLUDES = GObject-2.0 Utility-1.0
Annotation_1_0_gir_FILES = $(libannotation_la_SOURCES)
Annotation_1_0_gir_SCANNERFLAGS = --c-include="annotation.h" --warn-error
GIRS += Annotation-1.0.gir

TestInherit-1.0.gir: Utility-1.0.gir libtestinherit.la
TestInherit_1_0_gir_PACKAGES = gobject-2.0
TestInherit_1_0_gir_LIBS = libtestinherit.la
TestInherit_1_0_gir_INCLUDES = GObject-2.0 Utility-1.0
TestInherit_1_0_gir_FILES = $(libtestinherit_la_SOURCES)
TestInherit_1_0_gir_SCANNERFLAGS = --c-include="drawable.h" --warn-error
GIRS += TestInherit-1.0.gir

Foo-1.0.gir: Utility-1.0.gir libfoo.la
Foo_1_0_gir_PACKAGES = gobject-2.0
Foo_1_0_gir_LIBS = libfoo.la
Foo_1_0_gir_INCLUDES = GObject-2.0 Gio-2.0 Utility-1.0
Foo_1_0_gir_FILES = $(srcdir)/foo.h $(srcdir)/foo.c
Foo_1_0_gir_SCANNERFLAGS = --c-include="foo.h" --warn-error
GIRS += Foo-1.0.gir

Utility-1.0.gir: libutility.la
Utility_1_0_gir_PACKAGES = gobject-2.0
Utility_1_0_gir_LIBS = libutility.la
Utility_1_0_gir_INCLUDES = GObject-2.0
Utility_1_0_gir_FILES = $(libutility_la_SOURCES)
Utility_1_0_gir_SCANNERFLAGS = --c-include="utility.h" --warn-error
GIRS += Utility-1.0.gir

# This one tests different --namespace and --strip-prefix
GtkFrob-1.0.gir: libgtkfrob.la
GtkFrob_1_0_gir_PACKAGES = gobject-2.0
GtkFrob_1_0_gir_LIBS = libgtkfrob.la
GtkFrob_1_0_gir_INCLUDES = GObject-2.0
GtkFrob_1_0_gir_FILES = $(libgtkfrob_la_SOURCES)
GtkFrob_1_0_gir_SCANNERFLAGS = --identifier-prefix=Gtk --symbol-prefix=gtk_frob --warn-error
GIRS += GtkFrob-1.0.gir

# This tests that functions called _get_type are only matched if they have no
# arguments and return GType
GetType-1.0.gir: libgettype.la
GetType_1_0_gir_PACKAGES = gobject-2.0
GetType_1_0_gir_LIBS = libgettype.la
GetType_1_0_gir_INCLUDES = GObject-2.0
GetType_1_0_gir_FILES = $(libgettype_la_SOURCES)
GetType_1_0_gir_SCANNERFLAGS = --c-include="gettype.h" --identifier-prefix=GetType --symbol-prefix=gettype
GIRS += GetType-1.0.gir

if !OS_WIN32
check_PROGRAMS = barapp

barapp_SOURCES = $(srcdir)/barapp.c $(srcdir)/barapp.h
barapp_LDADD = $(top_builddir)/libgirepository-1.0.la
barapp_LDFLAGS = -export-dynamic

Bar-1.0.gir: barapp
Bar_1_0_gir_PACKAGES = gobject-2.0
Bar_1_0_gir_PROGRAM = ./barapp
Bar_1_0_gir_INCLUDES = GObject-2.0
Bar_1_0_gir_FILES = $(barapp_SOURCES)
Bar_1_0_gir_SCANNERFLAGS = --accept-unprefixed
GIRS += Bar-1.0.gir
endif

EXTRA_DIST += headeronly.h

Headeronly-1.0.gir: headeronly.h
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) --warn-all --warn-error --reparse-validate --namespace=Headeronly --nsversion=1.0 --header-only --output=$@ $<

%.gir.check: %.gir
	@diff -u -U 10 $(srcdir)/$*-expected.gir $*.gir && echo "  TEST  $*.gir"

check-local: Headeronly-1.0.gir $(CHECKGIRS) $(TYPELIBS)
