include $(top_srcdir)/common.mk
include $(top_srcdir)/Makefile.introspection

BUILT_SOURCES =
CLEANFILES =
EXTRA_DIST =
INTROSPECTION_GIRS =

check_LTLIBRARIES =
check_PROGRAMS =

############################################################

check_LTLIBRARIES += liboffsets.la

liboffsets_la_SOURCES = \
	offsets.h	\
	offsets.c
liboffsets_la_CPPFLAGS = $(GIREPO_CFLAGS)
# dummy rpath to get built dynamically (huh?)
liboffsets_la_LDFLAGS = -avoid-version -rpath $(libdir)

Offsets-1.0.gir: liboffsets.la offsets.h
Offsets_1_0_gir_INCLUDES = GObject-2.0
Offsets_1_0_gir_LIBS = liboffsets.la
Offsets_1_0_gir_PACKAGES = gobject-2.0
Offsets_1_0_gir_FILES = $(srcdir)/offsets.h $(srcdir)/offsets.c
Offsets_1_0_gir_SCANNERFLAGS = --warn-all --warn-error
INTROSPECTION_GIRS += Offsets-1.0.gir

CLEANFILES += Offsets-1.0.gir Offsets-1.0.typelib

############################################################

check_PROGRAMS += gitestoffsets

nodist_gitestoffsets_SOURCES = gitestoffsets.c
gitestoffsets_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestoffsets_LDADD = $(top_builddir)/libgirepository-1.0.la $(GIREPO_LIBS)

gitestoffsets.c: gen-gitestoffsets offsets.h
	$(AM_V_GEN) $(PYTHON) $(srcdir)/gen-gitestoffsets $(srcdir)/offsets.h > $@ || ( rm -f $@ && false )

EXTRA_DIST += gen-gitestoffsets
BUILT_SOURCES += gitestoffsets.c
CLEANFILES += gitestoffsets.c

############################################################

check-local: Offsets-1.0.typelib
	GI_TYPELIB_PATH=:$(top_builddir) ./gitestoffsets$(EXEEXT) offsets.compiled offsets.introspected
	diff -u offsets.compiled offsets.introspected

CLEANFILES += offsets.compiled offsets.introspected
