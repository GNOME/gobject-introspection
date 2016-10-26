GENERATED_ITEMS = \
	cmph.vcxproj		\
	cmph.vcxproj.filters		\
	girepository.vcxproj	\
	girepository.vcxproj.filters	\
	g-ir-compiler.vcxproj	\
	g-ir-compiler.vcxproj.filters	\
	gi-install.props

EXTRA_DIST = \
	gobject-introspection.sln	\
	gi-build-defines.props	\
	gi-gen-srcs.props	\
	gi-install.propsin	\
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
	gi-install.vcxproj	\
	gi-install.vcxproj.filters	\
	gi-introspect.vcxproj	\
	README.txt	\
	$(GENERATED_ITEMS)

gi-install.props: $(top_srcdir)/build/win32/vs10/gi-install.propsin girepository.vs10.headers giscanner.vs10.scripts
	-$(RM) $(top_builddir)/build/win32/vs11/gi-install.props
	-$(RM) $(top_builddir)/build/win32/vs12/gi-install.props
	-$(RM) $(top_builddir)/build/win32/vs14/gi-install.props
	$(CPP) -P - <$(top_srcdir)/build/win32/vs10/gi-install.propsin >$@
	$(RM) girepository.vs10.headers
	$(RM) giscanner.vs10.scripts

DISTCLEANFILES = $(GENERATED_ITEMS)
