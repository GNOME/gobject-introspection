## Process this file with automake to produce Makefile.in
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = girepository giscanner tools gir docs tests examples
DIST_SUBDIRS = m4 $(SUBDIRS)
DISTCHECK_CONFIGURE_FLAGS = --enable-gtk-doc

man_MANS = 			\
	docs/g-ir-compiler.1	\
	docs/g-ir-generate.1	\
	docs/g-ir-scanner.1

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gobject-introspection-1.0.pc gobject-introspection-no-export-1.0.pc

m4dir = $(datadir)/aclocal
m4_DATA = m4/introspection.m4

makedir = $(datadir)/gobject-introspection-1.0
dist_make_DATA = Makefile.introspection

EXTRA_DIST = 			\
	COPYING.LGPL		\
	COPYING.GPL		\
	CONTRIBUTORS		\
	$(pkgconfig_DATA)	\
	$(man_MANS)		\
	$(m4_DATA)		\
	misc/pep8.py		\
	misc/pyflakes.py

release-tag:
	@TAG=`echo $(VERSION)|sed s/\\\./_/g`;\
	  echo "* Tagging $(VERSION)"; \
          git tag -s -m "Tag $$VERSION" -a \
              GOBJECT_INTROSPECTION_$$TAG && \
	      git push --tags ssh://git.gnome.org/git/gobject-introspection

upload-release: $(distdir).tar.gz
	scp $(distdir).tar.gz gnome.org:
	ssh gnome.org install-module $(distdir).tar.gz

check-local:
	@echo "  PEP-8 INQUISITION"
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pep8.py --repeat --exclude=config.py
	@echo "  CHECK Pyflakes"
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pyflakes.py
