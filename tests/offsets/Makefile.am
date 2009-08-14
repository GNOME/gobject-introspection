include $(top_srcdir)/common.mk

BUILT_SOURCES =
CLEANFILES =
EXTRA_DIST =

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

offsets-1.0.gir: liboffsets.la offsets.h $(SCANNER_BIN) $(SCANNER_LIBS) Makefile
	$(CHECK_DEBUG) $(SCANNER) \
	--include=GObject-2.0 \
        --libtool="$(SHAVE_SAVED_LIBTOOL)" \
	--library=liboffsets.la \
	--namespace=offsets \
	--nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/offsets.h $(srcdir)/offsets.c \
	 --output $@

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	LD_LIBRARY_PATH=$(top_builddir)/girepository/.libs:$(builddir)/.libs$${LD_LIBRARY_PATH:+:$$LD_LIBRARY_PATH} \
	 $(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@

CLEANFILES += offsets-1.0.gir offsets-1.0.typelib

############################################################

check_PROGRAMS += gitestoffsets

nodist_gitestoffsets_SOURCES = gitestoffsets.c
gitestoffsets_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestoffsets_LDADD = $(top_builddir)/girepository/libgirepository-1.0.la $(GIREPO_LIBS)

gitestoffsets.c: gen-gitestoffsets offsets.h
	$(PYTHON) $(srcdir)/gen-gitestoffsets $(srcdir)/offsets.h > $@ || ( rm -f $@ && false )

EXTRA_DIST += gen-gitestoffsets
BUILT_SOURCES += gitestoffsets.c
CLEANFILES += gitestoffsets.c

############################################################

check-local: offsets-1.0.typelib
	LD_LIBRARY_PATH=$(top_builddir)/girepository/.libs:$(builddir)/.libs$${LD_LIBRARY_PATH:+:$$LD_LIBRARY_PATH} \
	 GI_TYPELIB_PATH=:$(top_builddir)/gir gitestoffsets$(EXEEXT) offsets.compiled offsets.introspected
	diff -u offsets.compiled offsets.introspected

CLEANFILES += offsets.compiled offsets.introspected
