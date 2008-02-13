if GI_GCOV_ENABLED

.PHONEY: coverage-report
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

endif
