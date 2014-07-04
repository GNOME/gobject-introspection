EXTRA_DIST = \
	gobject-introspection.sln	\
	gi-build-defines.props	\
	gi-extra-paths.props	\
	gi-gen-srcs.props	\
	gi-install.propsin	\
	gi-install.props	\
	gi-version-paths.props	\
	gi-prebuild.vcxproj	\
	girepository.vcxprojin	\
	girepository.vcxproj.filtersin	\
	cmph-bdz-test.vcxproj	\
	cmph-bdz-test.vcxproj.filters	\
	cmph.vcxprojin	\
	cmph.vcxproj.filtersin	\
	g-ir-compiler.vcxprojin	\
	g-ir-compiler.vcxproj.filtersin	\
	g-ir-generate.vcxproj	\
	g-ir-generate.vcxproj.filters	\
	glib-print.vcxproj	\
	glib-print.vcxproj.filters	\
	_giscanner.vcxproj	\
	_giscanner.vcxproj.filters	\
	install.vcxproj	\
	README.txt

gi-install.props: $(top_srcdir)/build/win32/vs10/gi-install.propsin gir.vs10.install
	$(CPP) -P - <$(top_srcdir)/build/win32/vs10/gi-install.propsin >$@
	rm gir.vs10.install

CLEANFILES = gi-install.props
