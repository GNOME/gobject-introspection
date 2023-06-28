Building GObject-Introspection (G-I) on Windows using Visual Studio
===================================================================

Building G-I on Windows with Visual Studio is now supported via the use
of the Meson build system.  This `MSVC.README.rst` file will outline the
steps of performing such a build on Visual Studio 2015 and later.

You will need the following, in addition to your Visual Studio installation:

- A Python installation that matches the build configuration that you are
  planning to build.  That is, you need the 32-bit Python installation for
  building 32-bit builds of G-I and the 64-bit (amd64) Python installation
  for building x64/x86_64/amd64 builds of G-I.  You need at least the version
  that is required for Meson, which is 3.7.x at the time of writing.  You will
  then need to install Meson using the pip tool.

- The Ninja build tool, unless using the `--backend=[vs|vsXXXX]` option in
  the Meson command line.  Note that using the `--backend=[vs|vsXXXX]` option
  may not work that well as it is not as well maintained as the standard Ninja
  backend.

- GIT for Windows is recommended, as Meson will download using GIT the sources
  of libraries that it depends on, if they cannot be found (such as GLib, please
  see below)

- A recent enough version of GLib, preferably built with the same compiler that
  is now being used to build G-I.  If none is found, the Meson build will fetch
  GLib from the tip of the main branch and build it first before continuing to
  build G-I.  Note that it will require a libintl implementation (must be
  installed beforehand, the headers and lib and DLL must be found in the paths
  specified by `%INCLUDE%`, `%LIB%` and `%PATH%` respectively), along with ZLib
  and libffi (GLib's own Meson build will build  them if they are not found).
  If a pre-existing copy of GLib is available, be sure to set `PKG_CONFIG_PATH`
  to where its .pc files can
  be found, and ensure that its DLLs/ executables can be first found in the
  paths specified in `%PATH%`. Note that libffi is needed both by GLib and G-I.

- A DLL build of Cairo with Cairo-GObject built, also preferably with the same
  compiler that is now used to build G-I.

- A recent version of `winflex`/`flex` and `winbison`/`bison`. They can be
obtained via MSYS/MSYS64 or Cygwin installations, or from the winflex project.
Either the 32-bit or 64-bit version will work, as long as they run on your
system.

Set `%PATH%` to contain your Python-3.7.x+ interpreter, Ninja build tool (if
needed) and `winflex`/`flex` and `winbison`/`bison` executables towards its 
end.  Please note that building against MSYS2 or Cygwin Python with Visual
Studio builds is not (and will likely never be) supported.

Open a Visual Studio command prompt and create an empty build directory (which needs
to be on the same drive as the G-I sources).  In that directory, run the following:
```
meson setup $(G-I_srcdir) --buildtype=... --prefix=$(PREFIX) -Dcairo_libname=<cairo-gobject-dll> -Dpython=<full path to Python interpreter to build _giscanner[cpXX-winYYY].pyd>
```

The `-Dcairo-libname` is likely necessary as the default DLL file name for
Cairo-GObject may likely not match the default `libcairo-gobject-2.dll`, which
is the default DLL filename for Cairo-GObject that is built with
MinGW/mingw-w64.

The `-Dpython` is likely necessary when using multiple Python installations on 
the system. Note that for this setting, Python-3.7.x or later is supported. This
will be the Python installation that will be used for invoking 
`g-ir-[doctool|annotation-tool|scanner]`.

When Meson completes configuring and generating the build files, proceed building using Ninja or the generated Visual Studio projects.

Additional notes for building and running against Python 3.8.x and later
------------------------------------------------------------------------
Python 3.8.x and later made restrictions on where DLLs are searched for
third-party modules, which will therefore affect how the Python tools in
`tools/` look for dependent DLLs, as they rely on a C Python module,
`_giscanner[-cpXX-winYYY].pyd`, as the paths in
`%PATH%` are no longer referred to, except for system-supplied DLLs in their
designated locations on the system.

In order to cope with this, DLLs are being searched for in the locations
indicated by the `bindir` entry in the pkg-config files that are being
required for the individual packages, followed by locations (note the plural
form-multiple paths are supported by `GI_EXTRA_BASE_DLL_DIRS`, separated by
Python's `os.pathsep`, which is `;` on Windows `cmd.exe` used for the Visual
Studio builds) that are indicated through the envvar `GI_EXTRA_BASE_DLL_DIRS`.
This means, if there are any DLLs required (including their dependent
non-system DLLs) for the `.gir` files being generated or queried, they must be
in the locations indicated by the `bindir` entries in the dependent packages'
`.pc` files of the current package, and/or i the locations indicated by
`GI_EXTRA_BASE_DLL_DIRS`.

Additional notes on using `clang-cl` (LLVM/CLang's Visual Studio compiler emulation)
----------------------------------------------------------------------------------
Support has been added to build GObject-Introspection with clang-cl,
specifically for running `g-ir-scanner` with `clang-cl` and `lld-link` as the
compiler and linker.  To enable such support, you need to set *both* the
environment variables `CC` and `CXX` to `clang-cl` prior to building 
GObject-Introspection or running `g-ir-scanner`.  This is in line with
building with `clang-cl` in place of using the stock Visual Studio compiler to 
perform builds with the Meson build system.

Additional notes on using `g-ir-scanner` on C++ items
---
It is recommended that when `g-ir-scanner` is run when building introspection
files for C++ items, such as HarfBuzz, that the latest Visual Studio 2019 
version (or later Visual Studio releases) is used during the build, as their
preprocessor would handle things better than the Visual Studio 2015 or 2017
ones.  In this case, G-I can still be *built* with Visual Studio 2015 or 2017
without problems.
