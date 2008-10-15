# -*- Mode: makefile -*-
if GI_GCOV_ENABLED

clean-gcov:
	find . -name "*.gcda" -o -name "*.gcov" -delete

clean-gcno:
	find . -name "*.gcno" -delete

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

coverage-report:
	@total_covered=0; total_lines=0; \
	for file in $(GCOVSOURCES); do \
	  if test -f $$file.gcov; then \
	    covered=`grep -e '[0-9]\+:' $$file.gcov | wc -l` ; \
	    uncovered=`grep '#####:' $$file.gcov | wc -l`; \
	    lines=$$(($$covered + $$uncovered)); \
	    total_covered=$$((total_covered + covered)); \
	    total_lines=$$((total_lines + lines)); \
	    echo -n "    $$file: $$covered / $$lines"; \
	    echo " ($$((($$covered * 100) / $$lines))%)"; \
	  fi \
	done >> $(top_builddir)/coverage-report.txt; \
	echo -e "  Total coverage:"\
	  "$$((($$total_covered * 100) / $$total_lines))%\n" \
	  >> $(top_builddir)/coverage-report.txt

.PHONEY: coverage-report gcov-all coverage-report.txt

endif
