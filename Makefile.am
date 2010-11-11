man_MANS =
EXTRA_DIST =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
BUILT_SOURCES =
CLEANFILES = $(BUILT_SOURCES)
INTROSPECTION_GIRS =
check_LTLIBRARIES =
check_PROGRAMS =
bin_PROGRAMS =
bin_SCRIPTS =
GTESTER_PROGS =
noinst_PROGRAMS = $(GTESTER_PROGS)

include common.mk
include Makefile.introspection

include Makefile-cmph.am
include Makefile-girepository.am
include Makefile-giscanner.am
include Makefile-examples.am
include Makefile-gir.am
include Makefile-tools.am

## Process this file with automake to produce Makefile.in
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = . docs tests

DIST_SUBDIRS = m4 $(SUBDIRS)
DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

man_MANS += 			\
	docs/g-ir-compiler.1	\
	docs/g-ir-generate.1	\
	docs/g-ir-scanner.1

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gobject-introspection-1.0.pc gobject-introspection-no-export-1.0.pc

m4dir = $(datadir)/aclocal
m4_DATA = m4/introspection.m4

makedir = $(datadir)/gobject-introspection-1.0
dist_make_DATA = Makefile.introspection

EXTRA_DIST += 			\
	COPYING.LGPL		\
	COPYING.GPL		\
	CONTRIBUTORS		\
	$(pkgconfig_DATA)	\
	$(man_MANS)		\
	$(m4_DATA)		\
	misc/pep8.py		\
	misc/pre-commit		\
	misc/pyflakes.py

release-tag:
	@TAG=`echo $(VERSION)|sed s/\\\./_/g`;\
	  echo "* Tagging $(VERSION)"; \
          git tag -m "Tag $$VERSION" -a \
              GOBJECT_INTROSPECTION_$$TAG && \
	      git push --tags ssh://git.gnome.org/git/gobject-introspection

upload-release: $(distdir).tar.bz2
	scp $(distdir).tar.bz2 gnome.org:
	ssh gnome.org install-module $(distdir).tar.bz2

check-local:
	gtester --verbose $(GTESTER_PROGS)
	@test ! -d $(top_srcdir)/.git || (test -f .git/hooks/pre-commit || (echo -e "ERROR: missing \
	pre-commit hook.\n\ncopy misc/pre-commit to .git/hooks"; false))
	@test ! -d $(top_srcdir)/.git || (test -x .git/hooks/pre-commit || (echo -e "ERROR: pre-commit \
	is not executable\n\nrun chmod +x .git/hooks/pre-commit"; false))
	@echo "  PEP-8 INQUISITION"
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pep8.py --repeat --exclude=config.py

check-pyflakes:
	@echo "  CHECK Pyflakes"
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pyflakes.py
