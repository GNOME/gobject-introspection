NULL ?=

include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

SUBDIRS = . annotationparser

INTROSPECTION_SCANNER_ARGS += --warn-all --reparse-validate

CLEANFILES =

EXTRA_LTLIBRARIES = \
	libsletter.la \
	libutility.la \
	libgtkfrob.la \
	libgettype.la \
	libregress.la \
	libwarnlib.la \
	libtypedefs.la \
	$(NULL)
CLEANFILES += $(EXTRA_LTLIBRARIES)

GI_SCANNER_CFLAGS = -I$(top_srcdir)/tests
AM_CPPFLAGS = -I$(top_srcdir)/girepository -I$(top_builddir)/girepository
AM_CFLAGS = $(GIO_CFLAGS) $(GOBJECT_CFLAGS) $(GTHREAD_CFLAGS) $(GI_HIDDEN_VISIBILITY_CFLAGS) $(GI_SCANNER_CFLAGS) $(WARN_CFLAGS)
# -rpath needed to force libtool to build a shared library for a check_LTLIBRARIES
# target. See http://lists.gnu.org/archive/html/automake/2005-10/msg00107.html
AM_LDFLAGS = $(WARN_LDFLAGS) -rpath /unused -avoid-version
LIBS = $(GOBJECT_LIBS) $(GTHREAD_LIBS)

libsletter_la_SOURCES = sletter.c sletter.h
libsletter_la_LIBADD = $(GIO_LIBS)
libsletter_la_CFLAGS = $(AM_CFLAGS)
libsletter_la_LDFLAGS = $(AM_LDFLAGS)

libutility_la_SOURCES = utility.c utility.h
libgtkfrob_la_SOURCES = gtkfrob.c gtkfrob.h
libregress_la_SOURCES = \
	regress.c regress.h \
	annotation.c annotation.h \
	foo.c foo.h \
	drawable.c drawable.h \
	$(NULL)
REGRESS_PRINT_PREVIEW_COMMAND="evince --unlink-tempfile --preview --print-settings %s %f"
libregress_la_CPPFLAGS = -DREGRESS_PRINT_PREVIEW_COMMAND=\"$(REGRESS_PRINT_PREVIEW_COMMAND)\" \
                         -DREGRESS_SOME_CHAR=\'c\'
libregress_la_LIBADD = $(GIO_LIBS)
if HAVE_CAIRO
libregress_la_LIBADD += $(CAIRO_LIBS)
endif
libwarnlib_la_CFLAGS = $(AM_CFLAGS)
libwarnlib_la_SOURCES = warnlib.c warnlib.h
libwarnlib_la_LIBADD = $(GIO_LIBS)
libwarnlib_la_LDFLAGS = -export-symbols-regex '^warnlib_' -no-undefined
libgettype_la_SOURCES = gettype.c gettype.h
libtypedefs_la_SOURCES = typedefs.c typedefs.h

testsdir = $(datadir)/gobject-introspection-1.0/tests
tests_DATA = $(libregress_la_SOURCES) $(libwarnlib_la_SOURCES) $(libutility_la_SOURCES)

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
CHECKGIRS = $(GIRS)
EXPECTEDGIRS = $(GIRS:.gir=-expected.gir)
INTROSPECTION_GIRS = $(GIRS)
CLEANFILES += $(TYPELIBS) $(GIRS)
EXTRA_DIST = $(EXPECTEDGIRS)

SLetter-1.0.gir: $(top_builddir)/Gio-2.0.gir libsletter.la
SLetter_1_0_gir_LIBS = libsletter.la
SLetter_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
SLetter_1_0_gir_INCLUDES = Gio-2.0
SLetter_1_0_gir_FILES = $(libsletter_la_SOURCES)
SLetter_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --identifier-prefix=S --c-include="sletter.h" --warn-error
GIRS += SLetter-1.0.gir

Regress-1.0.gir: $(top_builddir)/Gio-2.0.gir Utility-1.0.gir libregress.la
Regress_1_0_gir_LIBS = libregress.la
Regress_1_0_gir_CFLAGS = $(libregress_la_CPPFLAGS) $(libregress_la_CFLAGS) -include "glib.h"
Regress_1_0_gir_INCLUDES = Gio-2.0 Utility-1.0
if HAVE_CAIRO
Regress_1_0_gir_INCLUDES += cairo-1.0 
endif
Regress_1_0_gir_FILES = $(libregress_la_SOURCES)
Regress_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --c-include="regress.h" --warn-error
GIRS += Regress-1.0.gir

WarnLib-1.0.gir: $(top_builddir)/Gio-2.0.gir libwarnlib.la
WarnLib_1_0_gir_LIBS = libwarnlib.la
WarnLib_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
WarnLib_1_0_gir_INCLUDES = Gio-2.0
WarnLib_1_0_gir_FILES = $(libwarnlib_la_SOURCES)
WarnLib_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --c-include="warnlib.h" --symbol-prefix=warnlib_
GIRS += WarnLib-1.0.gir

Utility-1.0.gir: libutility.la
Utility_1_0_gir_PACKAGES = gobject-2.0
Utility_1_0_gir_LIBS = libutility.la
Utility_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
Utility_1_0_gir_INCLUDES = GObject-2.0
Utility_1_0_gir_FILES = $(libutility_la_SOURCES)
Utility_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --c-include="utility.h" --warn-error
GIRS += Utility-1.0.gir

# This one tests different --namespace and --strip-prefix
GtkFrob-1.0.gir: libgtkfrob.la
GtkFrob_1_0_gir_PACKAGES = gobject-2.0
GtkFrob_1_0_gir_LIBS = libgtkfrob.la
GtkFrob_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
GtkFrob_1_0_gir_INCLUDES = GObject-2.0
GtkFrob_1_0_gir_FILES = $(libgtkfrob_la_SOURCES)
GtkFrob_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --identifier-prefix=Gtk --symbol-prefix=gtk_frob --warn-error
GIRS += GtkFrob-1.0.gir

# This tests that functions called _get_type are only matched if they have no
# arguments and return GType
GetType-1.0.gir: libgettype.la
GetType_1_0_gir_PACKAGES = gobject-2.0
GetType_1_0_gir_LIBS = libgettype.la
GetType_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
GetType_1_0_gir_INCLUDES = GObject-2.0
GetType_1_0_gir_FILES = $(libgettype_la_SOURCES)
GetType_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --c-include="gettype.h" --identifier-prefix=GetType --symbol-prefix=gettype
GIRS += GetType-1.0.gir

Typedefs-1.0.gir: libtypedefs.la
Typedefs_1_0_gir_PACKAGES = gobject-2.0
Typedefs_1_0_gir_LIBS = libtypedefs.la
Typedefs_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
Typedefs_1_0_gir_INCLUDES = GObject-2.0
Typedefs_1_0_gir_FILES = $(libtypedefs_la_SOURCES)
Typedefs_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --c-include="typedefs.h" --identifier-prefix=Typedefs --symbol-prefix=typedefs
GIRS += Typedefs-1.0.gir

if !OS_WIN32
EXTRA_PROGRAMS = barapp
CLEANFILES += $(EXTRA_PROGRAMS)

barapp_SOURCES = barapp.c barapp.h
barapp_LDADD = $(top_builddir)/libgirepository-1.0.la
barapp_LDFLAGS = -export-dynamic

Bar-1.0.gir: barapp
Bar_1_0_gir_PACKAGES = gobject-2.0
Bar_1_0_gir_PROGRAM = ./barapp
Bar_1_0_gir_CFLAGS = $(GI_SCANNER_CFLAGS)
Bar_1_0_gir_INCLUDES = GObject-2.0
Bar_1_0_gir_FILES = $(barapp_SOURCES)
Bar_1_0_gir_SCANNERFLAGS = $(INTROSPECTION_SCANNER_ARGS) --accept-unprefixed
GIRS += Bar-1.0.gir
endif

EXTRA_DIST += \
	headeronly.h \
	Headeronly-1.0-expected.gir
CLEANFILES += Headeronly-1.0.gir
CHECKGIRS += Headeronly-1.0.gir

Headeronly-1.0.gir: headeronly.h
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) --warn-all --warn-error --reparse-validate --namespace=Headeronly --nsversion=1.0 --header-only --output=$@ $<

EXTRA_DIST += \
	identfilter.py \
	identfilter.h \
	Identfilter-1.0-expected.gir
CLEANFILES += Identfilter-1.0.gir
CHECKGIRS += Identfilter-1.0.gir

Identfilter-1.0.gir: identfilter.h
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) \
		--namespace=Identfilter --accept-unprefixed --nsversion=1.0 --header-only \
		--identifier-filter-cmd="$(PYTHON) $(srcdir)/identfilter.py" \
		--output=$@ $<

EXTRA_DIST += \
	symbolfilter.py \
	symbolfilter.h \
	Symbolfilter-1.0-expected.gir
CLEANFILES += Symbolfilter-1.0.gir
CHECKGIRS += Symbolfilter-1.0.gir

Symbolfilter-1.0.gir: symbolfilter.h
	$(AM_V_GEN) $(INTROSPECTION_SCANNER) $(INTROSPECTION_SCANNER_ARGS) \
		--warn-all --reparse-validate \
		--namespace=Symbolfilter --accept-unprefixed --nsversion=1.0 --header-only \
		--symbol-filter-cmd="$(PYTHON) $(srcdir)/symbolfilter.py" \
		--output=$@ $<

if BUILD_DOCTOOL
DOCGIRS = Regress-1.0.gir
CHECKDOCS = $(DOCGIRS:.gir=-C) $(DOCGIRS:.gir=-Python) $(DOCGIRS:.gir=-Gjs) $(DOCGIRS:.gir=-sections.txt)
MALLARD_DIRS = $(DOCGIRS:.gir=-C) $(DOCGIRS:.gir=-Python) $(DOCGIRS:.gir=-Gjs)
MALLARD_CLEAN = $(DOCGIRS:.gir=-C)/* $(DOCGIRS:.gir=-Python)/* $(DOCGIRS:.gir=-Gjs)/* $(DOCGIRS:.gir=-sections.txt)
EXPECTED_MALLARD_DIRS = $(MALLARD_DIRS:=-expected)
CLEANFILES += $(MALLARD_CLEAN)

%-C: %.gir
	$(AM_V_GEN)rm -rf $(builddir)/$*-C
	$(AM_V_at)$(INTROSPECTION_DOCTOOL) $(INTROSPECTION_DOCTOOL_ARGS) --language C $*.gir -o $(builddir)/$*-C/

%-Python: %.gir
	$(AM_V_GEN)rm -rf $(builddir)/$*-Python
	$(AM_V_at)$(INTROSPECTION_DOCTOOL) $(INTROSPECTION_DOCTOOL_ARGS) --language Python $*.gir -o $(builddir)/$*-Python/

%-Gjs: %.gir
	$(AM_V_GEN)rm -rf $(builddir)/$*-Gjs
	$(AM_V_at)$(INTROSPECTION_DOCTOOL) $(INTROSPECTION_DOCTOOL_ARGS) --language Gjs $*.gir -o $(builddir)/$*-Gjs/

%-sections.txt: %.gir
	$(AM_V_GEN)$(INTROSPECTION_DOCTOOL) $(INTROSPECTION_DOCTOOL_ARGS) --write-sections-file $*.gir -o $@

else
CHECKDOCS =
endif

PYTESTS = \
	test_ccompiler.py \
	test_shlibs.py \
	test_pkgconfig.py \
	test_sourcescanner.py \
	test_transformer.py \
	test_xmlwriter.py \
	test_docwriter.py \
	test_scanner.py

TESTS = $(CHECKGIRS) $(CHECKDOCS) $(TYPELIBS) $(PYTESTS)
TESTS_ENVIRONMENT = env srcdir=$(srcdir) top_srcdir=$(top_srcdir) builddir=$(builddir) top_builddir=$(top_builddir) \
	CC="$(CC)" \
	PYTHON=$(PYTHON) UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir)
LOG_COMPILER = $(PYTHON) $(top_srcdir)/tests/gi-tester

EXTRA_DIST += \
	meson.build \
	$(PYTESTS) \
	Regress-1.0-C-expected					\
	Regress-1.0-Gjs-expected				\
	Regress-1.0-Python-expected				\
	Regress-1.0-sections-expected.txt			\
	$(NULL)
