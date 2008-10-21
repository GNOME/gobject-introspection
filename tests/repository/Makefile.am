AM_CFLAGS = $(GOBJECT_CFLAGS)
AM_LDFLAGS = -module -avoid-version
LIBS = $(GOBJECT_LIBS)

noinst_PROGRAMS = gitestrepo gitestthrows

gitestrepo_SOURCES = $(srcdir)/gitestrepo.c
gitestrepo_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestrepo_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

gitestthrows_SOURCES = $(srcdir)/gitestthrows.c
gitestthrows_CPPFLAGS = $(GIREPO_CFLAGS) -I$(top_srcdir)/girepository
gitestthrows_LDADD = $(GIREPO_LIBS) $(top_builddir)/girepository/libgirepository.la

TESTS = gitestrepo gitestthrows
TESTS_ENVIRONMENT=env top_builddir="$(top_builddir)" $(DEBUG)
