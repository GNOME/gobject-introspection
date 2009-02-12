## Process this file with automake to produce Makefile.in
include $(top_srcdir)/gcov.mak

GCOVSOURCES =

if GI_GCOV_ENABLED
GCOV_DIRS = girepository tools

check-coverage: coverage-report.txt
	@cat $(top_builddir)/coverage-report.txt

else

check-coverage:
	@echo "ERROR: Need to reconfigure with --enable-gcov to run make check-coverage"

endif

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = girepository giscanner tools gir tests
DIST_SUBDIRS = m4 $(SUBDIRS)

man_MANS = 			\
	docs/g-ir-compiler.1	\
	docs/g-ir-generate.1	\
	docs/g-ir-scanner.1

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gobject-introspection-1.0.pc

EXTRA_DIST = 			\
	CONTRIBUTORS		\
	$(pkgconfig_DATA)	\
	$(man_MANS)		\
	m4/introspection.m4	\
	misc/pep8.py		\
	misc/pyflakes.py

release-tag:
	@TAG=`echo $(VERSION)|sed s/\\\./_/g`;\
	  echo "* Tagging $(VERSION)"; \
          git tag -m "Tag $$VERSION" -a \
              GOBJECT_INTROSPECTION_$$TAG && \
	      git push --tags ssh://git.gnome.org/git/gobject-introspection

upload-release: $(distdir).tar.gz
	scp $(distdir).tar.gz gnome.org:
	ssh gnome.org install-module $(distdir).tar.gz
