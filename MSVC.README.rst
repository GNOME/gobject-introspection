Building GObject-Introspection (G-I) on Windows using Visual Studio
===================================================================

Building G-I on Windows with Visual Studio is now supported via the use
of the Meson build system, the Visual Studio 2008~2017 projects have been
dropped from the distribution.  This README.msvc file will outline the
steps of performing such a build on Visual Studio 2008~2017.

You will need the following, in addition to your Visual Studio installation:

- A Python installation that matches the build configuration that you are
  planning to build.  That is, you need the 32-bit Python installation for
  building 32-bit builds of G-I and the 64-bit (amd64) Python installation
  for building x64/x86_64/amd64 builds of G-I.  You need at least the version
  that is required for Meson, which is 3.4.x at the time of writing.  You will
  then need to install Meson using the pip tool.

- The Ninja build tool, which is optional on Visual Studio 2010, 2015 and 2017
  builds (if one chooses to generate Visual Studio projects with Meson), but is
  required for 2008, 2012 and 2013 builds.

- GIT for Windows is recommended, as Meson will download using GIT the sources
  of libraries that it depends on, if they cannot be found (such as GLib, please
  see below)

- A recent enough version of GLib, preferably built with the same compiler that
  is now being used to build G-I.  If none is found, the Meson build will fetch
  GLib from GIT master and build it first before continuing to build G-I.  Note
  that it will require a libintl implementation (must be installed beforehand, the
  headers and lib and DLL must be found in the paths specified by %INCLUDE, %LIB%
  and %PATH% respectively), along with ZLib and libffi (GLib's own Meson build will
  build  them if they are not found).  If a pre-existing copy of GLib is available,
  be sure to set PKG_CONFIG_PATH to where its .pc files can be found, and ensure
  that its DLLs/ executables can be first found in the paths specified in %PATH%.
  Note that libffi is needed both by GLib and G-I.

- A DLL build of Cairo with Cairo-GObject built, also preferably with the same
  compiler that is now used to build G-I.

- A recent version of winflex/flex and Bison. They can be obtained via MSYS/MSYS64
  or Cygwin installations.  Either the 32-bit or 64-bit version will work, as long
  as they run on your system.

Set PATH to contain your Python-3.4.x+ interpreter, Ninja build tool (if needed) and
winflex/flex and Bison executables towards its end.

Note that if you plan to use g-ir-scanner for other packages built using Meson, you
need to use the same Python release series (3.4, 3.5...) for running Meson there as
well.

Open a Visual Studio command prompt and create an empty build directory (which needs
to be on the same drive as the G-I sources).  In that directory, run the following::

  python $(PythonInstallationPath)\scripts\meson.py $(G-I_srcdir) --buildtype=<build_configuration> --prefix=$(PREFIX) -Dcairo-libname=<DLL filename of cairo-gobject>

When Meson completes configuring and generating the build files, proceed building
using Ninja or the generated Visual Studio projects.

Additional notes for building with Visual Studio 2008 only
----------------------------------------------------------
Due to its use of security manifests, after Meson completes configuring and
generating the build files, first build the giscanner\_giscanner.pyd target
using 'ninja giscanner\_giscanner.pyd'.  After doing so, embed the manifest
using the following command::

  mt /manifest giscanner\_giscanner.pyd.manifest /outputresource:giscanner\_giscanner.pyd;2

The .gir files cannot be successfully generated without this step.

On x64 builds, building girepository\girepository-1.0-1.dll may hang during compilation.
If this happens, terminate all 'cl.exe' processes, which will terminate the build process.
Open build.ninja and change the compiler flags by changing /O2 to /O1 for all the sources
that hang during compilation.  At this time of writing, girepository\girwriter.c,
girepository\girparser.c and girepository\girnode.c are affected--this is due to an issue
in Visual Studio 2008's x64 compiler in regards to optimization.  Re-attempt the build, and
the build should complete normally.  This does not affect Win32/x86 builds.

On all Visual Studio 2008 builds, after successfully completing/installing the build, run
the following so that we ensure the manifests are embedded to the built DLLs and EXEs::

  for /r %f in (*.dll.manifest) do if exist $(PREFIX)\bin\%~nf mt /manifest %f /outputresource:$(PREFIX)\bin\%~nf;2
  for /r %f in (*.exe.manifest) do if exist $(PREFIX)\bin\%~nf mt /manifest %f /outputresource:$(PREFIX)\bin\%~nf;1