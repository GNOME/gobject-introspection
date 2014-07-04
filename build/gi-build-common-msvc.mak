# Common NMake Makefile to Build Introspection Files and Tests for G-I

# Please do not change anything after this line

!include detectenv_msvc.mak

GI_APIVERSION = 1.0
GLIB_APIVERSION = 2.0

CHECK_PACKAGE = gio-$(GLIB_APIVERSION)

!include introspection-msvc.mak

BINDIR = ..\build\win32\vs$(VSVER)\$(CFG)\$(PLAT)\bin
G_IR_SCANNER_CURRENT = ..\tools\g-ir-scanner
G_IR_DOC_TOOL_CURRENT = ..\tools\g-ir-doc-tool
G_IR_COMPILER_CURRENT = $(BINDIR)\g-ir-compiler.exe

!if "$(VALID_GCC_INSTPATH)" == "TRUE"
!if "$(PLAT)" == "x64"
TIME_T_DEFINE = -Dtime_t=long long
!else
TIME_T_DEFINE = -Dtime_t=long
!endif
!endif
