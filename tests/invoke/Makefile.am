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
testfns_la_LIBADD = $(top_builddir)/girepository/libgirepository.la $(GIREPO_LIBS)

if OS_WIN32
testfns_la_LDFLAGS += -no-undefined
endif

BUILT_SOURCES = testfns-metadata.c
CLEANFILES = testfns-metadata.c 

testfns-metadata.c: testfns-1.0.gir $(top_builddir)/tools/g-ir-compiler Makefile
	$(CHECK_DEBUG) $(top_builddir)/tools/g-ir-compiler $(srcdir)/testfns-1.0.gir --code -o testfns-metadata.c

invoke_SOURCES = invoke.c
invoke_CFLAGS = $(GIREPO_CFLAGS)  -I$(top_srcdir)/girepository
invoke_LDADD = $(top_builddir)/girepository/libgirepository.la $(GIREPO_LIBS)

TESTS = invoke invoke-namespace-find.sh

EXTRA_DIST = invoke-namespace-find.sh testfns-1.0.gir

