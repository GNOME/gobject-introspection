## Process this file with automake to produce Makefile.in

check_PROGRAMS = invoke
testlib_LTLIBRARIES = testfns.la
testlibdir = /tmp
install-testlibLTLIBRARIES: # prevent it from being installed


testfns_la_SOURCES =				\
	testfns.c				\
	testfns-metadata.c
testfns_la_CFLAGS = $(GIREPO_CFLAGS) -I ../../src
testfns_la_LDFLAGS = -module -avoid-version
testfns_la_LIBADD = $(GIREPO_LIBS) ../../src/libgirepository.la

BUILT_SOURCES = testfns-metadata.c test.repo
CLEANFILES = testfns-metadata.c test.repo

testfns-metadata.c: testfns.xml
	../../src/g-idl-compiler $(srcdir)/testfns.xml -o testfns-metadata.c

test.repo: testfns.xml
	../../src/g-idl-compiler --shared-library testfns.la $< --raw -o $@

invoke_SOURCES = invoke.c
invoke_CFLAGS = $(GIREPO_CFLAGS) -I ../../src
invoke_LDADD = $(GIREPO_LIBS) ../../src/libgirepository.la

TESTS = invoke invoke-namespace-find.sh

EXTRA_DIST = invoke-namespace-find.sh

TESTS_ENVIRONMENT = GIREPOPATH="."
