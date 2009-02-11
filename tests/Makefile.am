SUBDIRS = . scanner everything repository invoke offsets

EXTRA_DIST = \
	array.gir	\
	boxed.gir	\
	constant.gir	\
	enum.gir	\
	errors.gir	\
	extended.gir \
	function.gir	\
	interface.gir	\
	object.gir	\
	struct.gir	\
	types.gir	\
	union.gir	\
	xref1.gir	\
	xref2.gir

GIRTESTS =				\
	boxed.gir.test		\
	constant.gir.test	\
	enum.gir.test		\
	object.gir.test		\
	struct.gir.test

CLEANFILES = $(GIRTESTS:%.gir.test=%.1) $(GIRTESTS:%.gir.test=%.2) extended.gir.test

extended.gir.test: extended.gir Makefile
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler --includedir=$(top_builddir)/gir extended.gir -o extended.gir.test

%.gir.test: %.gir Makefile
	@echo Testing $<:
	$(DEBUG) $(top_builddir)/tools/g-ir-compiler --includedir=$(top_builddir)/gir $< > $*.1
	$(DEBUG) $(top_builddir)/tools/g-ir-generate --includedir=$(top_builddir)/gir $*.1 > $*.2
	diff -u $(srcdir)/$*.gir $*.2 && rm $*.1 $*.2


check-local: $(GIRTESTS) extended.gir.test
	@echo Running PEP8 on Python sources
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pep8.py --repeat
	@echo Running Pyflakes on Python sources
	@find $(top_srcdir)/giscanner -name \*.py | sort | uniq | xargs $(PYTHON) $(top_srcdir)/misc/pyflakes.py
