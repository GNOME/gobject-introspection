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

BUILT_SOURCES = testfns-metadata.c
CLEANFILES = testfns-metadata.c 

testfns-metadata.c: testfns.gir $(top_builddir)/tools/g-ir-compiler Makefile
	$(CHECK_DEBUG) $(top_builddir)/tools/g-ir-compiler $(srcdir)/testfns.gir --code -o testfns-metadata.c

invoke_SOURCES = invoke.c
invoke_CFLAGS = $(GIREPO_CFLAGS)  -I$(top_srcdir)/girepository
invoke_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

TESTS = invoke invoke-namespace-find.sh

EXTRA_DIST = invoke-namespace-find.sh testfns.gir

