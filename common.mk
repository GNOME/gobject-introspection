SCANNER_BIN = $(top_builddir)/tools/g-ir-scanner
SCANNER_PYTHONPATH = $(top_builddir):$(top_srcdir):$$PYTHONPATH
SCANNER_ENV = env PYTHONPATH=$(SCANNER_PYTHONPATH) \
	UNINSTALLED_INTROSPECTION_SRCDIR=$(top_srcdir) \
	UNINSTALLED_INTROSPECTION_BUILDDIR=$(top_builddir)
SCANNER_ARGS = -v --add-include-path=$(top_builddir)/gir --add-include-path=.
SCANNER = $(AM_V_GEN) env LPATH=.libs $(CHECK_DEBUG) $(SCANNER_ENV) $(SCANNER_BIN) $(SCANNER_ARGS)
SCANNER_LIBS = \
	$(top_srcdir)/giscanner/*.py \
	$(top_builddir)/giscanner/libgiscanner.la \
	$(top_builddir)/girepository/libgirepository-1.0.la

INTROSPECTION_SCANNER = $(SCANNER)
INTROSPECTION_SCANNER_ARGS = $(SCANNER_ARGS)
INTROSPECTION_COMPILER = $(top_builddir)/tools/g-ir-compiler$(EXEEXT)
INTROSPECTION_COMPILER_ARGS = \
	--includedir=$(srcdir) \
	--includedir=$(top_srcdir)/gir \
    --includedir=$(top_builddir)/gir
