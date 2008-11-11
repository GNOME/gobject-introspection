BUILT_SOURCES =
CLEANFILES =
EXTRA_DIST =

check_LTLIBRARIES =
check_PROGRAMS =

SCANNER = $(top_srcdir)/tools/g-ir-scanner
SCANNER_PYTHONPATH = $(top_builddir):$(top_srcdir):$$PYTHONPATH
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la

############################################################

check_LTLIBRARIES += liboffsets.la

liboffsets_la_SOURCES = \
	offsets.h	\
	offsets.c
liboffsets_la_CPPFLAGS = $(GIREPO_CFLAGS)
# dummy rpath to get built dynamically (huh?)
liboffsets_la_LDFLAGS = -module -avoid-version -rpath $(libdir)

offsets-1.0.gir: liboffsets.la offsets.h $(SCANNER) $(SCANNER_LIBS) Makefile
	PYTHONPATH=$(SCANNER_PYTHONPATH) $(CHECK_DEBUG) $(SCANNER) -v \
	--add-include-path=$(top_builddir)/gir --add-include-path=. \
	--library=offsets \
	--namespace=offsets \
	--nsversion=1.0 \
	--pkg gobject-2.0 \
	$(srcdir)/offsets.h $(srcdir)/offsets.c \
	 --output $@

%.typelib: %.gir $(top_builddir)/tools/g-ir-compiler$(EXEEXT) Makefile
	$(top_builddir)/tools/g-ir-compiler --includedir=. --includedir=$(top_builddir)/gir $< -o $@

CLEANFILES += offsets-1.0.gir offsets-1.0.typelib

############################################################

check_PROGRAMS += gitestoffsets

nodist_gitestoffsets_SOURCES = gitestoffsets.c
gitestoffsets_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestoffsets_LDADD = $(top_builddir)/girepository/libgirepository.la $(GIREPO_LIBS)

gitestoffsets.c: gen-gitestoffsets offsets.h
	$(PYTHON) $(srcdir)/gen-gitestoffsets offsets.h > $@ || ( rm -f $@ && false )

EXTRA_DIST += gen-gitestoffsets
BUILT_SOURCES += gitestoffsets.c
CLEANFILES += gitestoffsets.c

############################################################

check-local: offsets-1.0.typelib
	LD_LIBRARY_PATH=$${LD_LIBRARY_PATH:+$$LD_LIBRARY_PATH:}$(builddir) GI_TYPELIB_PATH=$(builddir) \
	  $(builddir)/gitestoffsets$(EXEEXT) offsets.compiled offsets.introspected
	diff -u offsets.compiled offsets.introspected

CLEANFILES += offsets.compiled offsets.introspected
