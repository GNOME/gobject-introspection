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

man_MANS = docs/g-ir-scanner.1

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gobject-introspection-1.0.pc

EXTRA_DIST = $(pkgconfig_DATA)

