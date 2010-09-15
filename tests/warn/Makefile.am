include $(top_srcdir)/common.mk

TESTS = \
	callback-invalid-scope.h \
	callback-missing-scope.h \
	return-gobject.h \
	unknown-parameter.h \
	unresolved-element-type.h \
	unresolved-type.h

EXTRA_DIST = warningtester.py common.h $(TESTS)

TESTS_ENVIRONMENT = PYTHONPATH=$(top_builddir):$(top_srcdir) $(PYTHON) $(srcdir)/warningtester.py

