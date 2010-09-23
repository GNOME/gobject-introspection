include $(top_srcdir)/common.mk

TESTS = \
	callback-invalid-scope.h \
	callback-missing-scope.h \
	return-gobject.h \
	invalid-option.h \
	invalid-transfer.h \
	unknown-parameter.h \
	unresolved-element-type.h \
	unresolved-type.h

EXTRA_DIST = warningtester.py common.h $(TESTS)

TESTS_ENVIRONMENT = PYTHONPATH=$(top_builddir):$(top_srcdir) TOP_BUILDDIR=$(top_builddir) $(PYTHON) $(srcdir)/warningtester.py

