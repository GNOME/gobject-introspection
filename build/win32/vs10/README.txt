Please do not compile this package (gobject-introspection) in paths that contain
spaces in them-as strange problems may occur during compilation or during
the use of the library.

Please refer to the following GNOME Live! page for more detailed
instructions on building gobject-introsecption and its dependencies
with Visual C++:

https://live.gnome.org/GTK%2B/Win32/MSVCCompilationOfGTKStack

This VS10 solution and the projects it includes are intented to be used
in a gobject-introspection source tree unpacked from a tarball. In a git checkout you
first need to use some Unix-like environment, which will do the work for you.

The required dependencies are Python 2.7 (2.7) or 3.3 (3.x) or later, GLib and LibFFI.
It is recommended that GLib is built with Visual C++ 2010 to avoid problems cause by
usage of different CRTs.

Please refer to the README.txt file in $(GLib_src_root)\build\win32\vs10 on how to build
GLib using Visual C++ 2010

For LibFFI, please get version 3.0.10 or later, as Visual C++ build support
was added in the 3.0.10 release series.  Please see the README file that
comes with the LibFFI source package for more details on how to build LibFFI
on Visual C++-please note that the mozilla-build package from Mozilla is needed
in order to build LibFFI on Windows.

For Python, retrieving the official Windows binaries for 2.7 (2.x) or 3.3 (3.x) or later
from http://www.python.org will do the job-be sure that the Python version that
you downloaded matches the configuration of your build (win32 or x64/amd64).  Ensure that
the correct path for your Python interpretor is set in gi-extra-paths.vsprops prior to
opening the project files, or close the project files and delete all the *.user, *.sdf and
*.suo files and reopening the project files.

For building the Regress test project, cairo (and possibly cairo-gobject support)
is needed.

Set up the source tree as follows under some arbitrary top
folder <root>:

<root>\<this-gobject-introspection-source-tree>
<root>\vs10\<PlatformName>

*this* file you are now reading is thus located at
<root>\<this-glib-source-tree>\build\win32\vs10\README.

<PlatformName> is either Win32 or x64, as in VS10 project files.

For LibFFI, one should also put the generated ffi.h and ffitarget.h
into <root>\vs10\<PlatformName>\include\ and the compiled static libffi.lib
(or copy libffi-convenience.lib into libffi.lib) into
<root>\vs10\<PlatformName>\lib\.

The libintl.h that is used for building GLib needs to be in
<root>\vs10\<PlatformName>\include, if not already done so.

A working pkg-config tool is also required-it may be obtained from
http://www.gtk.org/download/win32.php [32-bit]
http://www.gtk.org/download/win64.php [64-bit]

*** Note! ***
Please note that due to numerous possible configurations on Python, PKG_CONFIG_PATH,
the build of G-I is now a 2-step process: one with the Visual Studio Projects that
will build the libraries, tools, Python Module and test DLLs (except for the everything
test), and the other one with NMake Makefiles for building the introspection files.
Please note that if one needs to change the installation location
of Python, one needs to change the values of PythonDir (for x86/Win32 builds) and/or
PythonDirX64 (for x64 builds) in gi-extra-paths.props

The use of Visual Studio Projects will no longer require the setting of environmental
variables, but the following environmental variables are needed (either by using "set xxx=yyy"
or by nmake -f gi-introspection-msvc.mak xxx=yyy) for building the introspection files (which
should be done after successfully building the Project Files):

PYTHON: Full path to your Python 2.7.x/3.3.x+ interpretor (python.exe) if it is
        not in your PATH.  Please note that only 2.7.x and 3.3.x and later works.
        You need to use an x64/amd64 version of Python for x64 builds, and a Win32/x86
        version of Python for Win32/x86 builds
PKG_CONFIG_PATH: Location of the .pc (pkg-config) files, especially for the GLib .pc files.

Please see $(srcroot)\build\win32\gi-introspection-msvc.mak for more details.  Doing
"nmake -f gi-introspection-msvc.mak (options omitted)" will build the various introspection files,
and "nmake -f gi-introspection-msvc.mak (options omitted) install-introspection" will copy the introspection
files to <root>\vs10\<PlatformName>\share\gir-1.0 (.gir files) and
<root>\vs10\<PlatformName>\lib\girepository-1.0 (.typelib files)

*** End of Note! ***

The "install" project will copy build results and headers into their
appropriate location under <root>\vs10\<PlatformName>. For instance,
built DLLs go into <root>\vs10\<PlatformName>\bin, built LIBs into
<root>\vs10\<PlatformName>\lib and gobject-introspection headers into
<root>\vs10\<PlatformName>\include\gobject-introsection-1.0.

This is then from where
project files higher in the stack are supposed to look for them, not
from a specific gobject-introspection source tree.

--Tor Lillqvist <tml@iki.fi>
--Updated by Chun-wei Fan <fanc999@gmail.com>
