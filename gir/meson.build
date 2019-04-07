cairo_conf = configuration_data()
if get_option('cairo_libname') != ''
  cairo_library_name = get_option('cairo_libname')
elif host_machine.system() == 'win32'
  cairo_library_name = 'libcairo-gobject-2.dll'
elif host_machine.system() == 'darwin'
  cairo_library_name = 'libcairo-gobject.2.dylib'
else
  cairo_library_name = 'libcairo-gobject.so.2'
endif

cairo_conf.set('CAIRO_SHARED_LIBRARY', cairo_library_name)
cairo_conf.set('CAIRO_GIR_PACKAGE', 'cairo-gobject')

cairo_gir = configure_file(
  input: 'cairo-1.0.gir.in',
  output: 'cairo-1.0.gir',
  configuration: cairo_conf,
)

gir_files = [
  cairo_gir,
  'DBus-1.0.gir',
  'DBusGLib-1.0.gir',
  'fontconfig-2.0.gir',
  'freetype2-2.0.gir',
  'GL-1.0.gir',
  'libxml2-2.0.gir',
  'xft-2.0.gir',
  'xlib-2.0.gir',
  'xfixes-4.0.gir',
  'xrandr-1.3.gir',
  'win32-1.0.gir',
]

typelibdir = join_paths(get_option('libdir'), 'girepository-1.0')
install_data(gir_files, install_dir: girdir)

scanner_command = [
  python,
  girscanner,
  '--output=@OUTPUT@',
  '--no-libtool',
  '--quiet',
  '--reparse-validate',
  '--add-include-path', join_paths(meson.current_build_dir()),
  '--add-include-path', join_paths(meson.current_source_dir()),
]

dep_type = glib_dep.type_name()
if dep_type == 'internal'
  # XXX: Instead of hard-coding the subproject directory, we should use
  # gnome.generate_gir() because that will take care of dependencies, include
  # paths, library paths, and more that we now have to handle manually when
  # building with subprojects.
  subprojdir = 'subprojects'
  scanner_command += ['--extra-library=gio-2.0', '--extra-library=gmodule-2.0',
                      '--extra-library=glib-2.0', '--extra-library=gobject-2.0']
endif

# Take a glob and print to newlines
globber = '''
from glob import glob

# Sort the glob for stable results. Also ensures that gmarshal.h is not
# #include-ed by scannerparser.y first because it does not include glib.h
# itself, which leaves several defines unresolved.
for f in sorted(glob('@0@')):
  print(f)
'''

# GLib
glib_files = []
glib_command = scanner_command + [
  '--identifier-prefix=G',
  '--symbol-prefix=g',
  '--symbol-prefix=glib',
  '--c-include=glib.h',
  '--namespace=GLib',
  '--nsversion=2.0',
  '--library=glib-2.0',
  '--library=gobject-2.0',
]

if dep_type == 'pkgconfig'
  glib_command += ['--external-library', '--pkg=glib-2.0']
  glib_libdir = glib_dep.get_pkgconfig_variable('libdir')
  glib_incdir = join_paths(glib_dep.get_pkgconfig_variable('includedir'), 'glib-2.0')
  glib_libincdir = join_paths(glib_libdir, 'glib-2.0', 'include')
  glib_files += join_paths(glib_incdir, 'gobject', 'glib-types.h')
  glib_files += join_paths(glib_libincdir, 'glibconfig.h')
  if giounix_dep.found()
    glib_files += join_paths(glib_incdir, 'glib-unix.h')
  endif
  # Parse glob to get installed header list
  ret = run_command(python, '-c', globber.format(join_paths(glib_incdir, 'glib', '*.h')))
  if ret.returncode() != 0
    error('Failed to get glib header list')
  endif
  glib_headers = ret.stdout().strip().split('\n')
  # Get a list of all source files
  glib_srcdir = get_option('glib_src_dir')
  if glib_srcdir != ''
    ret = run_command(python, '-c', globber.format(join_paths(glib_srcdir, 'glib', '*.c')))
    if ret.returncode() != 0
      error('Failed to get glib source list')
    endif
    glib_files += ret.stdout().strip().split('\n')
  endif
  glib_includes = ['-I' + glib_incdir, '-I' + glib_libincdir]
elif dep_type == 'internal'
  glib_command += ['--pkg-export=glib-2.0']
  # XXX: Assumes that the builddir layout is 'mirror'
  glib_libdir = join_paths(meson.build_root(), subprojdir, 'glib', 'glib')
  # XXX: Assumes the location of the glib subproject dir
  # We should add API to meson to get a specific file from a specific subproject
  glibproj_incdir = join_paths(meson.source_root(), subprojdir, 'glib')
  glib_incdir = join_paths(glibproj_incdir, 'glib')
  glib_libincdir = glib_libdir
  glib_files += join_paths(glibproj_incdir, 'gobject', 'glib-types.h')
  glib_files += join_paths(glib_libincdir, 'glibconfig.h')
  if giounix_dep.found()
    glib_files += join_paths(glib_incdir, 'glib-unix.h')
  endif
  # We know exactly what headers will be installed, so just fetch that
  glib_subproject = subproject('glib')
  glib_headers = glib_subproject.get_variable('glib_sub_headers')
  glib_files += glib_subproject.get_variable('glib_sources')
  # XXX: Assumes that the builddir layout is 'mirror'
  gobject_libdir = join_paths(meson.build_root(), subprojdir, 'glib', 'gobject')
  gmodule_libdir = join_paths(meson.build_root(), subprojdir, 'glib', 'gmodule')
  gio_libdir = join_paths(meson.build_root(), subprojdir, 'glib', 'gio')
  glib_libpaths = ['-L' + glib_libdir, '-L' + gobject_libdir,
                   '-L' + gmodule_libdir, '-L' + gio_libdir]
  # Includes that will be used to compile the scanner executable
  glib_buildinc = join_paths(meson.build_root(), subprojdir, 'glib')
  gmodule_incdir = join_paths(glibproj_incdir, 'gmodule')
  gio_incdir = join_paths(glibproj_incdir, 'gio')
  glib_includes = ['-I' + glibproj_incdir, '-I' + glib_incdir, '-I' + glib_libincdir,
                   '-I' + glib_buildinc, '-I' + gmodule_incdir, '-I' + gio_incdir]
  # XXX: We need include paths to all glib dependencies too. We assume that the
  # dependencies are only libffi and proxy-libintl, and that they are used as
  # subprojects. In the worst case we add paths to non-existent directories.
  ffi_incdir = join_paths(meson.build_root(), subprojdir, 'libffi', 'include')
  glib_includes += ['-I' + ffi_incdir]
  intl_incdir = join_paths(meson.source_root(), subprojdir, 'proxy-libintl')
  glib_includes += ['-I' + intl_incdir]

  ffi_libdir = join_paths(meson.build_root(), subprojdir, 'libffi', 'src')
  intl_libdir = join_paths(meson.build_root(), subprojdir, 'proxy-libintl')
  glib_libpaths = ['-L' + ffi_libdir, '-L' + intl_libdir] + glib_libpaths

  glib_command += glib_libpaths

else
  error('Unknown glib dependency type: ' + dep_type)
endif

foreach h : glib_headers
  hstr = '@0@'.format(h)
  if not hstr.endswith('autocleanups.h')
    glib_files += h
  endif
endforeach

# NOTE: Always add this last so that we prefer the annotations in the sources
# (if they are available) since it contains 'backup' annotations that can be
# out of date.
glib_files += files('glib-2.0.c')

glib_gir = custom_target('gir-glib',
  input: glib_files,
  output: 'GLib-2.0.gir',
  depends: giscanner_pymod,
  depend_files: giscanner_built_files,
  install: true,
  install_dir: girdir,
  command: glib_command + [
    '--cflags-begin'] + glib_includes + [
    '-DGLIB_COMPILATION',
    '-D__G_I18N_LIB_H__',
    '-DGETTEXT_PACKAGE=Dummy',
    '--cflags-end',
    '@INPUT@',
  ]
)

gir_files += glib_gir

# GObject
gobject_files = []
gobject_command = scanner_command + [
  '--identifier-prefix=G',
  '--c-include=glib-object.h',
  '--namespace=GObject',
  '--nsversion=2.0',
  '--library=gobject-2.0',
]

if dep_type == 'pkgconfig'
  gobject_command += ['--external-library', '--pkg=gobject-2.0']
  # Get the installed header list
  ret = run_command(python, '-c', globber.format(join_paths(glib_incdir, 'gobject', '*.h')))
  if ret.returncode() != 0
    error('Failed to get gobject header list')
  endif
  gobject_headers = ret.stdout().strip().split('\n')
  if glib_srcdir != ''
    ret = run_command(python, '-c', globber.format(join_paths(glib_srcdir, 'gobject', '*.c')))
    if ret.returncode() != 0
      error('Failed to get gobject source list')
    endif
    gobject_files += ret.stdout().strip().split('\n')
  endif
else
  gobject_command += ['--pkg-export=gobject-2.0']
  gobject_headers = glib_subproject.get_variable('gobject_install_headers')
  gobject_files += glib_subproject.get_variable('gobject_sources')
  gobject_command += glib_libpaths
endif

foreach h : gobject_headers
  hstr = '@0@'.format(h)
  if not hstr.endswith('autocleanups.h') and not hstr.endswith('glib-types.h') and not hstr.endswith('gvaluecollector.h') and not hstr.endswith('glib-enumtypes.h')
    gobject_files += h
  endif
endforeach

# NOTE: Always add this last so that we prefer the annotations in the sources
# (if they are available) since it contains 'backup' annotations that can be
# out of date.
gobject_files += files('gobject-2.0.c')

gobject_gir = custom_target('gir-gobject',
  input: gobject_files,
  output: 'GObject-2.0.gir',
  depends: [glib_gir, giscanner_pymod],
  depend_files: giscanner_built_files,
  install: true,
  install_dir: girdir,
  command: gobject_command + [
    '--include-uninstalled=' + glib_gir.full_path(),
    '--cflags-begin'] + glib_includes + [
    '-DGOBJECT_COMPILATION',
    '--cflags-end',
    '@INPUT@',
  ]
)

gir_files += gobject_gir

# GModule
gmodule_files = []
gmodule_command = scanner_command + [
  '--identifier-prefix=G',
  '--symbol-prefix=g',
  '--c-include=gmodule.h',
  '--namespace=GModule',
  '--nsversion=2.0',
  '--library=gmodule-2.0',
]

if dep_type == 'pkgconfig'
  gmodule_command += ['--external-library', '--pkg=gmodule-2.0']
  gmodule_files += join_paths(glib_incdir, 'gmodule.h')
  if glib_srcdir != ''
    gmodule_files += join_paths(glib_srcdir, 'gmodule', 'gmodule.c')
  endif
else
  gmodule_command += ['--pkg-export=gmodule-2.0']
  gmodule_command += glib_libpaths
  gmodule_files += [join_paths(glibproj_incdir, 'gmodule', 'gmodule.h'),
                    join_paths(glibproj_incdir, 'gmodule', 'gmodule.c')]
endif

# NOTE: Always add this last so that we prefer the annotations in the sources
# (if they are available) since it contains 'backup' annotations that can be
# out of date.
gmodule_files += files('gmodule-2.0.c')

gir_files += custom_target('gir-gmodule',
  input: gmodule_files,
  output: 'GModule-2.0.gir',
  depends: [glib_gir, giscanner_pymod],
  depend_files: giscanner_built_files,
  install: true,
  install_dir: girdir,
  command: gmodule_command + [
    '--include-uninstalled=' + glib_gir.full_path(),
    '--cflags-begin'] + glib_includes + [
    '--cflags-end',
    '@INPUT@',
  ]
)

## Gio
gio_files = []
gio_command = scanner_command + [
  '--identifier-prefix=G',
  '--symbol-prefix=g',
  '--c-include=gio/gio.h',
  '--namespace=Gio',
  '--nsversion=2.0',
  '--library=gio-2.0',
]

if dep_type == 'pkgconfig'
  gio_command += ['--external-library', '--pkg=gio-2.0']
  # Get the installed header list
  ret = run_command(python, '-c', globber.format(join_paths(glib_incdir, 'gio', '*.h')))
  if ret.returncode() != 0
    error('Failed to get gio header list')
  endif
  gio_headers = ret.stdout().strip().split('\n')
  # Get all gio (and gio-unix) sources. This is not entirely correct, but it's
  # probably fine since it matches what Autotools does. We are more exact in
  # the subproject case.
  if glib_srcdir != ''
    ret = run_command(python, '-c', globber.format(join_paths(glib_srcdir, 'gio', '*.c')))
    if ret.returncode() != 0
      error('Failed to get gio source list')
    endif
    gio_files += ret.stdout().strip().split('\n')
  endif
else
  gio_command += ['--pkg-export=gio-2.0']
  gio_headers = glib_subproject.get_variable('gio_headers')
  gio_files += glib_subproject.get_variable('gio_sources')
  gio_command += glib_libpaths
endif

foreach h : gio_headers
  hstr = '@0@'.format(h)
  if not hstr.endswith('autocleanups.h')
    gio_files += h
  endif
endforeach

if giounix_dep.found()
  if dep_type == 'pkgconfig'
    gio_command += ['--pkg=gio-unix-2.0']
    giounix_includedir = join_paths(giounix_dep.get_pkgconfig_variable('includedir'), 'gio-unix-2.0')
    # Get the installed gio-unix header list
    ret = run_command(python, '-c', globber.format(join_paths(giounix_includedir, 'gio', '*.h')))
    if ret.returncode() != 0
      error('Failed to get gio-unix header list')
    endif
    giounix_headers = ret.stdout().strip().split('\n')
  else
    gio_command += ['--pkg-export=gio-unix-2.0']
    giounix_headers = glib_subproject.get_variable('gio_unix_include_headers')
  endif
  # No filtering needed
  gio_files += giounix_headers
  # GIO Unix headers must be included explicitly since there is no catch-all
  # header that includes all of them unlike gio/gio.h above
  foreach header : giounix_headers
    hstr = '@0@'.format(header)
    hbase = hstr.split('/')[-1]
    gio_command += '--c-include=gio/@0@'.format(hbase)
  endforeach
endif

# NOTE: Always add this last so that we prefer the annotations in the sources
# (if they are available) since it contains 'backup' annotations that can be
# out of date.
gio_files += files('gio-2.0.c')

gio_gir = custom_target('gir-gio',
  input: gio_files,
  output: 'Gio-2.0.gir',
  depends: [gobject_gir, giscanner_pymod],
  depend_files: giscanner_built_files,
  install: true,
  install_dir: girdir,
  command: gio_command + [
    '--include-uninstalled=' + gobject_gir.full_path(),
    '--cflags-begin'] + glib_includes + [
    '-DGIO_COMPILATION',
    '-DG_SETTINGS_ENABLE_BACKEND',
    '--cflags-end',
    '@INPUT@',
  ]
)

gir_files += gio_gir

# GIRepository

girepository_command = scanner_command + [
  '--identifier-prefix=GI',
  '--symbol-prefix=g',
  '--symbol-prefix=gi',
  '--c-include=girepository.h',
  '--namespace=GIRepository',
  '--nsversion=2.0',
  '--library=girepository-1.0',
  '--pkg-export=gobject-introspection-1.0',
  '-L' + meson.current_build_dir() + '/../girepository',
]

if dep_type != 'pkgconfig'
  girepository_command += glib_libpaths
endif

gir_files += custom_target('gir-girepository',
  input: girepo_gir_sources,
  output: 'GIRepository-2.0.gir',
  depends: [gobject_gir, giscanner_pymod, girepo_lib],
  depend_files: giscanner_built_files,
  install: true,
  install_dir: girdir,
  command: girepository_command + [
    '--include-uninstalled=' + gobject_gir.full_path(),
    '--cflags-begin'] + glib_includes + [
    '-I' + meson.current_source_dir() + '/../girepository',
    '-I' + meson.current_build_dir() + '/../girepository',
    '-DGI_COMPILATION',
    '--cflags-end',
    '@INPUT@',
  ]
)

typelibs = []
foreach gir : gir_files
  typelibs += custom_target('generate-typelib-@0@'.format(gir).underscorify(),
    input: gir,
    output: '@BASENAME@.typelib',
    depends: [gobject_gir, ],
    command: [gircompiler, '-o', '@OUTPUT@', '@INPUT@',
              '--includedir', meson.current_build_dir(),
              '--includedir', meson.current_source_dir(),
    ],
    install: true,
    install_dir: typelibdir,
  )
endforeach
