SUBDIRS = . invoke scanner

EXTRA_DIST = \
	roundtrips.sh	\
	array.gir	\
	boxed.gir	\
	constant.gir	\
	enum.gir	\
	errors.gir	\
	function.gir	\
	gobject.gir	\
	interface.gir	\
	object.gir	\
	struct.gir	\
	types.gir	\
	union.gir	\
	xref1.gir	\
	xref2.gir

TESTS = #roundtrips.sh

check-local:
	find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs echo $(PYTHON) $(top_srcdir)/misc/pep8.py --repeat
