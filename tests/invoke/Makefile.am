## Process this file with automake to produce Makefile.in

check_PROGRAMS = invoke
testlib_LTLIBRARIES = testfns.la
testlibdir = /tmp
install-testlibLTLIBRARIES: # prevent it from being installed


testfns_la_SOURCES =				\
	testfns.c				\
	testfns-metadata.c
testfns_la_CFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
testfns_la_LDFLAGS = -module -avoid-version
testfns_la_LIBADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

BUILT_SOURCES = testfns-metadata.c test.repo
CLEANFILES = testfns-metadata.c test.repo

testfns-metadata.c: testfns.xml $(top_builddir)/tools/g-idl-compiler
	$(top_builddir)/tools/g-idl-compiler $(srcdir)/testfns.xml -o testfns-metadata.c

test.repo: testfns.xml
	$(top_builddir)/tools/g-idl-compiler --shared-library testfns.la $< --raw -o $@

invoke_SOURCES = invoke.c
invoke_CFLAGS = $(GIREPO_CFLAGS)  -I$(top_srcdir)/girepository
invoke_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

TESTS = invoke invoke-namespace-find.sh

EXTRA_DIST = invoke-namespace-find.sh testfns.xml

TESTS_ENVIRONMENT = GIREPOPATH="."
