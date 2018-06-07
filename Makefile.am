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
noinst_PROGRAMS =
EXTRA_LTLIBRARIES =
EXTRA_PROGRAMS =
TESTS =

include common.mk
include Makefile.introspection

include Makefile-cmph.am
include Makefile-girepository.am
include Makefile-giscanner.am
include Makefile-examples.am
include Makefile-gir.am
include Makefile-tools.am

## Process this file with automake to produce Makefile.in
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = . docs tests

DIST_SUBDIRS = $(SUBDIRS)
DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc --enable-doctool

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
	autogen.sh		\
	CONTRIBUTORS		\
	$(pkgconfig_DATA)	\
	$(man_MANS)		\
	$(m4_DATA)		\
	misc/pep8.py		\
	misc/pyflakes.py	\
	misc/update-glib-annotations.py	\
	misc/update-gtkdoc-tests.py	\
	misc/verbump.py		\
	README.msvc

# Default pep8.py --exclude + emacs backup files
PEP8_EXCLUDES=--exclude='.svn,CVS,.bzr,.hg,.git,__pycache__,.\#*'

check-local:
	@echo "TEST: PEP-8 INQUISITION"
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs \
		$(PYTHON) $(top_srcdir)/misc/pep8.py --max-line-length=99 --ignore=E128,W503 $(PEP8_EXCLUDES)
	@find $(top_srcdir)/tests -name \*.py | sort | uniq | xargs \
		$(PYTHON) $(top_srcdir)/misc/pep8.py --ignore=E127,E402,E501,E731 $(PEP8_EXCLUDES)

check-pyflakes:
	@echo "  CHECK Pyflakes"
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pyflakes.py


# Colin's handy Makefile bits for:
# 1) stuffing tarballs with pre-generated scripts from your workstation
# 2) bumping configure.ac version post-release
# 3) tagging correctly in git
# 4) uploading to gnome.org
# To use:
#  $ make check
#  $ make dist
#  $ make prepare-minor-release

# Customize to taste
TAG_PREFIX=GOBJECT_INTROSPECTION_
COMPRESSION=.xz


PACKAGE=@PACKAGE@
VERSION=@VERSION@
DISTNAME=$(PACKAGE)-$(VERSION).tar$(COMPRESSION)
TAG_VERSION=$(shell echo $(VERSION) |sed s/\\\./_/g)

prepare-release-tag: Makefile
	git tag -m "Tag $(TAG_VERSION)" -a $(TAG_PREFIX)$(TAG_VERSION)

prepare-minor-release: $(DISTNAME) prepare-release-tag Makefile
	env top_srcdir=$(top_srcdir) python $(top_srcdir)/misc/verbump.py

upload-release: $(DISTNAME) Makefile
	git log origin/master..master
	@echo -n "Ok to push? [y/N] "; read ans; test x$$ans == xy || exit 1
	git push --tags origin master:master
	scp $(DISTNAME) master.gnome.org:
	ssh master.gnome.org install-module $(DISTNAME)

