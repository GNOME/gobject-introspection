## Process this file with automake to produce Makefile.in

bin_PROGRAMS = invoke
noinst_LTLIBRARIES = testfns.la


testfns_la_SOURCES =				\
	testfns.c				\
	testfns-metadata.c
testfns_la_CFLAGS = $(GIREPO_CFLAGS)
testfns_la_LDFLAGS = -module -avoid-version

testfns-metadata.c: testfns.xml
	../../src/g-idl-compiler $(srcdir)/testfns.xml -o testfns-metadata.c


invoke_SOURCES = invoke.c
invoke_CFLAGS = $(GIREPO_CFLAGS) -I ../../src
invoke_LDADD = $(GIREPO_LIBS) -ldl ../../src/libgirepository.la

