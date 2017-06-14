Please do not compile this package (gobject-introspection) in paths that contain
spaces in them-as strange problems may occur during compilation or during
the use of the library.

Please refer to the following GNOME Live! page for more detailed
instructions on building gobject-introsecption and its dependencies
with Visual C++:

https://live.gnome.org/GTK%2B/Win32/MSVCCompilationOfGTKStack

This VS9 solution and the projects it includes are intented to be used
in a gobject-introspection source tree unpacked from a tarball. In a git checkout you
first need to use some Unix-like environment, which will do the work for you.

The required dependencies are Python 2.7 (2.7) or 3.3 (3.x) or later, GLib and LibFFI.
It is recommended that GLib is built with Visual C++ 2008 to avoid problems cause by
usage of different CRTs.

Please refer to the README.txt file in $(GLib_src_root)\build\win32\vs9 on how to build
GLib using Visual C++ 2008

For LibFFI, please use the Centricular fork of it, which can be found at
https://github.com/centricular/libffi.  Please refer there on building--please
note that this will involve the use of the Meson build system and the Ninja
build tool.

For Python, retrieving the official Windows binaries for 2.7 (2.x) or 3.3 (3.x) or later
from http://www.python.org will do the job-be sure that the Python version that
you downloaded matches the configuration of your build (win32 or x64/amd64).  Ensure that
the correct path for your Python interpretor is set in gi-extra-paths.vsprops prior to
opening the project files, or close the project files and delete all the *.user, *.ncb and
*.suo files and reopening the project files.

For building the Regress test project, cairo (and possibly cairo-gobject support)
is needed.

Set up the source tree as follows under some arbitrary top
folder <root>:

<root>\<this-gobject-introspection-source-tree>
<root>\vs9\<PlatformName>

*this* file you are now reading is thus located at
<root>\<this-glib-source-tree>\build\win32\vs9\README.

<PlatformName> is either Win32 or x64, as in VS9 project files.

For LibFFI, one should also put the generated ffi.h and ffitarget.h
into <root>\vs9\<PlatformName>\include\ and the compiled static libffi.lib
(or copy libffi-convenience.lib into libffi.lib) into
<root>\vs9\<PlatformName>\lib\.

The libintl.h that is used for building GLib needs to be in
<root>\vs9\<PlatformName>\include, if not already done so

A working pkg-config tool is also required-it may be obtained from
http://www.gtk.org/download/win32.php [32-bit]
http://www.gtk.org/download/win64.php [64-bit]

*** Note! ***
The build of G-I is now done within the project files, although it is still possible to
do it in two stages by using the NMake Makefiles after building the projects.

As there are numerous possible configurations on Python and PKG_CONFIG_PATH, note that:
-For both methods PKG_CONFIG_PATH is by default $(PREFIX)\lib\pkgconfig, where $(PREFIX)
 is by default <parent_dir_of_G-I_srcroot>\vs9\<PlatformName>.  If searching from
 more directories is desired, set the PKG_CONFIG_PATH environment variable before using
 the NMake Makefile or opening the projects, but note that $(PREFIX)\lib\pkgconfig will
 precede the set paths.
-For the Python Path using the project files: check whether the directory settings in
 gi-version-paths.vsprops under PythonDir (32-bit) or PythonDirX64 (x64) is correct.
 If the projects have been loaded by Visual Studio, close the projects and re-open them.
 You may need to delete all the *.suo, *.user and *.ncb files in this directory for
 the changes to take effect.
-For the Python Path using the NMake Makefiles: pass in PYTHON=<full_path_to_python> to
 the NMake Makefile or set it in the environment.  The bit-ness of your Python installation
 must match the configuration that you are building for.

The use of Visual Studio Projects will no longer require the setting of environmental
variables, but the following environmental variables are needed (either by using "set xxx=yyy"
or by nmake -f gi-introspection-msvc.mak xxx=yyy) for building the introspection files (which
should be done after successfully building the Project Files):

Please see $(srcroot)\build\win32\gi-introspection-msvc.mak for more details.  Doing
"nmake -f gi-introspection-msvc.mak (options omitted)" will build the various introspection files,
and "nmake -f gi-introspection-msvc.mak (options omitted) install-introspection" will copy the introspection
files to <root>\vs9\<PlatformName>\share\gir-1.0 (.gir files) and <root>\vs9\<PlatformName>\lib\girepository-1.0
(.typelib files)

*** End of Note! ***

The "install" project will copy build results and headers into their
appropriate location under <root>\vs9\<PlatformName>. For instance,
built DLLs go into <root>\vs9\<PlatformName>\bin, built LIBs into
<root>\vs9\<PlatformName>\lib and gobject-introspection headers into
<root>\vs9\<PlatformName>\include\gobject-introsection-1.0.

This is then from where
project files higher in the stack are supposed to look for them, not
from a specific gobject-introspection source tree.

--Tor Lillqvist <tml@iki.fi>
--Updated by Chun-wei Fan <fanc999@gmail.com>
