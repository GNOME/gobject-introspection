EXTRA_DIST = \
	gobject-introspection.sln	\
	girepository.vcxprojin	\
	girepository.vcxproj.filtersin	\
	gir.propsin	\
	gir.props	\
	annotation.vcxproj	\
	annotation.vcxproj.filters	\
	cmph-bdz-test.vcxproj	\
	cmph-bdz-test.vcxproj.filters	\
	cmph.vcxprojin	\
	cmph.vcxproj.filtersin	\
	everything.vcxproj	\
	everything.vcxproj.filters	\
	foo.vcxproj	\
	foo.vcxproj.filters	\
	g-ir-compiler.vcxprojin	\
	g-ir-compiler.vcxproj.filtersin	\
	g-ir-generate.vcxproj	\
	g-ir-generate.vcxproj.filters	\
	gettype.vcxproj	\
	gettype.vcxproj.filters	\
	gimarshallingtests.vcxproj	\
	gimarshallingtests.vcxproj.filters	\
	glib-print.vcxproj	\
	glib-print.vcxproj.filters	\
	gtkfrob.vcxproj	\
	gtkfrob.vcxproj.filters	\
	regress.vcxproj	\
	regress.vcxproj.filters	\
	sletter.vcxproj	\
	sletter.vcxproj.filters	\
	testinherit.vcxproj	\
	testinherit.vcxproj.filters	\
	utility.vcxproj	\
	utility.vcxproj.filters	\
	_giscanner.vcxproj	\
	_giscanner.vcxproj.filters	\
	generate_typelibs.vcxproj	\
	install.vcxproj	\
	README.txt

gir.props: $(top_srcdir)/build/win32/vs10/gir.propsin gir.vs10.install
	$(CPP) -P - <$(top_srcdir)/build/win32/vs10/gir.propsin >$@
	rm gir.vs10.install

CLEANFILES = gir.props
