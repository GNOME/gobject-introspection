NULL ?=

include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

INTROSPECTION_SCANNER_ARGS += --warn-all

check_LTLIBRARIES = \
	libsletter.la \
	libtestinherit.la \
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

libtestinherit_la_SOURCES = $(srcdir)/drawable.c $(srcdir)/drawable.h
libutility_la_SOURCES = $(srcdir)/utility.c $(srcdir)/utility.h
libgtkfrob_la_SOURCES = $(srcdir)/gtkfrob.c $(srcdir)/gtkfrob.h
libregress_la_SOURCES = \
	$(srcdir)/regress.c $(srcdir)/regress.h \
	$(srcdir)/annotation.c $(srcdir)/annotation.h \
	$(srcdir)/foo.c $(srcdir)/foo.h \
	$(NULL)
libregress_la_LIBADD = $(GIO_LIBS)
if HAVE_CAIRO
libregress_la_LIBADD += $(CAIRO_LIBS)
endif
libwarnlib_la_CFLAGS = $(AM_CFLAGS)
libwarnlib_la_SOURCES = $(srcdir)/warnlib.c $(srcdir)/warnlib.h
libwarnlib_la_LIBADD = $(GIO_LIBS)
libwarnlib_la_LDFLAGS = -export-symbols-regex '^warnlib_' -no-undefined
libgettype_la_SOURCES = $(srcdir)/gettype.c $(srcdir)/gettype.h

testsdir = $(datadir)/gobject-introspection-1.0/tests
tests_DATA = $(libregress_la_SOURCES) $(libwarnlib_la_SOURCES)

libregress_la_CPPFLAGS =
if !HAVE_CAIRO
libregress_la_CPPFLAGS += -D_GI_DISABLE_CAIRO
endif
libregress_la_CFLAGS = $(AM_CFLAGS)
if HAVE_CAIRO
libregress_la_CFLAGS += $(CAIRO_CFLAGS)
endif
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

Regress-1.0.gir: $(top_builddir)/Gio-2.0.gir Utility-1.0.gir libregress.la
Regress_1_0_gir_LIBS = libregress.la
Regress_1_0_gir_INCLUDES = Gio-2.0 Utility-1.0
if HAVE_CAIRO
Regress_1_0_gir_INCLUDES += cairo-1.0 
endif
Regress_1_0_gir_FILES = $(libregress_la_SOURCES)
Regress_1_0_gir_SCANNERFLAGS = --c-include="regress.h" --warn-error $(libregress_la_CPPFLAGS)
GIRS += Regress-1.0.gir

WarnLib-1.0.gir: $(top_builddir)/Gio-2.0.gir libwarnlib.la
WarnLib_1_0_gir_LIBS = libwarnlib.la
WarnLib_1_0_gir_INCLUDES = Gio-2.0
WarnLib_1_0_gir_FILES = $(libwarnlib_la_SOURCES)
WarnLib_1_0_gir_SCANNERFLAGS = --c-include="warnlib.h" --symbol-prefix=warnlib_
GIRS += WarnLib-1.0.gir

TestInherit-1.0.gir: Utility-1.0.gir libtestinherit.la
TestInherit_1_0_gir_PACKAGES = gobject-2.0
TestInherit_1_0_gir_LIBS = libtestinherit.la
TestInherit_1_0_gir_INCLUDES = GObject-2.0 Utility-1.0
TestInherit_1_0_gir_FILES = $(libtestinherit_la_SOURCES)
TestInherit_1_0_gir_SCANNERFLAGS = --c-include="drawable.h" --warn-error
GIRS += TestInherit-1.0.gir

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

EXTRA_DIST += \
	annotationparser/README					\
	annotationparser/test_parser.py				\
	annotationparser/test_patterns.py			\
	annotationparser/gi/annotation_allow_none.xml		\
	annotationparser/gi/annotation_array.xml		\
	annotationparser/gi/annotation_closure.xml		\
	annotationparser/gi/annotation_constructor.xml		\
	annotationparser/gi/annotation_destroy.xml		\
	annotationparser/gi/annotation_element_type.xml		\
	annotationparser/gi/annotation_foreign.xml		\
	annotationparser/gi/annotation_get_value_func.xml	\
	annotationparser/gi/annotation_in.xml			\
	annotationparser/gi/annotation_in_out.xml		\
	annotationparser/gi/annotation_method.xml		\
	annotationparser/gi/annotation_out.xml			\
	annotationparser/gi/annotation_ref_func.xml		\
	annotationparser/gi/annotation_rename_to.xml		\
	annotationparser/gi/annotation_scope.xml		\
	annotationparser/gi/annotation_set_value_func.xml	\
	annotationparser/gi/annotation_skip.xml			\
	annotationparser/gi/annotation_transfer.xml		\
	annotationparser/gi/annotation_type.xml			\
	annotationparser/gi/annotation_unref_func.xml		\
	annotationparser/gi/annotation_value.xml		\
	annotationparser/gi/annotation_virtual.xml		\
	annotationparser/gi/syntax.xml				\
	annotationparser/gi/syntax_identifier.xml		\
	annotationparser/gi/syntax_nested_tags.xml		\
	annotationparser/gi/syntax_paragraph_breaks.xml		\
	annotationparser/gi/tag_deprecated.xml			\
	annotationparser/gi/tag_description.xml			\
	annotationparser/gi/tag_returns.xml			\
	annotationparser/gi/tag_since.xml			\
	annotationparser/gi/tag_stability.xml			\
	annotationparser/gtkdoc/gobject/gtypes.h.xml		\
	annotationparser/gtkdoc/gobject/gtypes.c.xml		\
	annotationparser/gtkdoc/gobject/giface.h.xml		\
	annotationparser/gtkdoc/gobject/giface.c.xml		\
	annotationparser/gtkdoc/fail/tester.h.xml		\
	annotationparser/gtkdoc/fail/tester.c.xml		\
	annotationparser/gtkdoc/empty/tester.c.xml		\
	annotationparser/gtkdoc/bugs/tester.h.xml		\
	annotationparser/gtkdoc/bugs/tester.c.xml		\
	annotationparser/gtkdoc/annotations/tester.h.xml	\
	annotationparser/gtkdoc/annotations/tester.c.xml	\
	annotationparser/gtkdoc/gobject/gobject.h.xml		\
	annotationparser/gtkdoc/gobject/gobject.c.xml
