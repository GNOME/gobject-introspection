AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -module -avoid-version
LIBS = $(GOBJECT_LIBS)

noinst_PROGRAMS = gitestrepo

gitestrepo_SOURCES = $(srcdir)/gitestrepo.c
gitestrepo_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestrepo_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

TESTS = gitestrepo
TESTS_ENVIRONMENT=env top_builddir="$(top_builddir)"