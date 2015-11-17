# Common NMake Makefile to set Build Environment for
# Building Introspection Files and Associated Tests

# Please do not change anything after this line

setgirbuildenv:
	@set UNINSTALLED_INTROSPECTION_SRCDIR=..\..
	@set UNINSTALLED_INTROSPECTION_BUILDDIR=..\..
	@set PYTHONPATH=..\..;$(BINDIR)
	@set PATH=$(BINDIR);$(BASEDIR)\bin;$(PATH)
	@set PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)
	@set LIB=win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin;$(BASEDIR)\lib;$(LIB)
