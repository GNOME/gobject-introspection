## Process this file with automake to produce Makefile.in
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = gidl girepository tools tests
DIST_SUBDIRS = m4 $(SUBDIRS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gobject-introspection.pc
EXTRA_DIST = $(pkgconfig_DATA)

if GI_GCOV_ENABLED
GCOV_DIRS = girepository tools

clean-gcov:
	find  -name "*.gcda" -o -name "*.gcov" -delete

clean-gcno:
	find  -name "*.gcno" -delete

gcov-all:
	@for dir in $(GCOV_DIRS); do \
		cd $(abs_srcdir)/$$dir && \
		for file in *.c; do \
			gcov -f -p -o `find $(abs_builddir)/$$dir -newer $$file -name "*-$${file/.c/.gcda}" -print0 | sed -e 's/\.gcda/\.o/'` $$file > /dev/null; \
		done \
	done

coverage-report.txt: clean clean-gcov all check gcov-all
	@rm  -f $(top_builddir)/coverage-report.txt
	@echo -e "=== Coverage Report ===\n" >> $(top_builddir)/coverage-report.txt
	@for dir in $(GCOV_DIRS); do \
		echo "Module '$$dir':" >> $(top_builddir)/coverage-report.txt; \
		$(MAKE) -C $$dir coverage-report; \
	done

check-coverage: coverage-report.txt
	@cat $(top_builddir)/coverage-report.txt

.PHONEY: gcov-all coverage-report.txt

else

check-coverage:
	@echo "Need to reconfigure with --enable-gcov"

endif
