# Common NMake Makefile to set Build Environment for
# Building Introspection Files and Associated Tests

# Please do not change anything after this line

setgirbuildenv:
	@set UNINSTALLED_INTROSPECTION_SRCDIR=$(TOP_SRCDIR)
	@set UNINSTALLED_INTROSPECTION_BUILDDIR=$(TOP_SRCDIR)
	@set PYTHONPATH=$(TOP_SRCDIR);$(BINDIR)
	@set PATH=$(BINDIR);$(PREFIX)\bin;$(PATH)
	@set PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)
	@set LIB=vs$(VSVER)\$(CFG)\$(PLAT)\bin;$(PREFIX)\lib;$(LIB)
