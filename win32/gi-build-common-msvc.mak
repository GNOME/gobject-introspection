# Common NMake Makefile to Build Introspection Files and Tests for G-I

# Please do not change anything after this line

!include detectenv-msvc.mak

GI_APIVERSION = 1.0
GLIB_APIVERSION = 2.0

CHECK_PACKAGE = gio-$(GLIB_APIVERSION)

!include introspection-msvc.mak

BINDIR = vs$(VSVER)\$(CFG)\$(PLAT)\bin
TOP_SRCDIR = ..

G_IR_SCANNER_CURRENT = $(TOP_SRCDIR)\tools\g-ir-scanner
G_IR_DOC_TOOL_CURRENT = $(TOP_SRCDIR)\tools\g-ir-doc-tool
G_IR_COMPILER_CURRENT = $(BINDIR)\g-ir-compiler.exe
