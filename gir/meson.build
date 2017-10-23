cairo_conf = configuration_data()
if host_machine.system() == 'win32'
  # TODO: Might not use libtool name
  cairo_library_name = 'libcairo-gobject-2.dll'
elif host_machine.system() == 'darwin'
  cairo_library_name = 'libcairo-gobject.2.dylib'
else
  cairo_library_name = 'libcairo-gobject.so.2'
# TODO: OpenBSD = libcairo-gobject.so
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
girdir = join_paths(get_option('datadir'), 'gir-1.0')
install_data(gir_files, install_dir: girdir)

scanner_command = [
  find_program('env'),
  'UNINSTALLED_INTROSPECTION_SRCDIR=' + meson.source_root(),
  'UNINSTALLED_INTROSPECTION_BUILDDIR=' + meson.build_root(),
  girscanner,
  '--output=@OUTPUT@',
  '--warn-all',
  '--no-libtool',
  '--external-library',
  '--reparse-validate',
]

# GLib
glib_includedir = join_paths(gobject_dep.get_pkgconfig_variable('includedir'), 'glib-2.0')
glib_libincludedir = join_paths(gobject_dep.get_pkgconfig_variable('libdir'), 'glib-2.0/include')
glib_srcdir = get_option('glib-src-dir')

glib_glob = glib_includedir + '/glib/*.h'
if glib_srcdir != ''
  glib_glob += ',' + glib_srcdir + '/glib/*.c'
endif

glib_sources_file = custom_target('glib-sources-file',
  input: 'glib-2.0.c',
  output: 'glib-sources.list',
  command: [
    find_program('generate_source_list.py'),
    '@OUTPUT@',
    glib_glob,
    'glib-autocleanups.h',
    glib_libincludedir + '/glibconfig.h',
    glib_includedir + '/gobject/glib-types.h',
    '@INPUT@',
  ]
)

glib_gir = custom_target('gir-glib',
  input: glib_sources_file,
  output: 'GLib-2.0.gir',
  install: true,
  install_dir: girdir,
  command: scanner_command + [
    '--identifier-prefix=G',
    '--symbol-prefix=g',
    '--symbol-prefix=glib',
    '--c-include=glib.h',
    '--namespace=GLib',
    '--nsversion=2.0',
    '--pkg=glib-2.0',
    '--library=glib-2.0',
    '--library=gobject-2.0',
    '--cflags-begin',
    '-I' + glib_includedir,
    '-I' + glib_libincludedir,
    '-DGLIB_COMPILATION',
    '-D__G_I18N_LIB_H__',
    '-DGETTEXT_PACKAGE=Dummy',
    '--cflags-end',
    '--filelist=@INPUT@',
  ]
)

gir_files += glib_gir

# GObject
gobject_glob = glib_includedir + '/gobject/*.h'
if glib_srcdir != ''
  gobject_glob += ',' + glib_srcdir + '/gobject/*.c'
endif

gobject_sources_file = custom_target('gobject-sources-file',
  input: 'gobject-2.0.c',
  output: 'gobject-sources.list',
  command: [
    find_program('generate_source_list.py'),
    '@OUTPUT@',
    gobject_glob,
    'glib-types.h',
    '@INPUT@',
  ]
)

gobject_gir = custom_target('gir-gobject',
  input: gobject_sources_file,
  output: 'GObject-2.0.gir',
  depends: glib_gir,
  install: true,
  install_dir: girdir,
  command: scanner_command + [
    '--identifier-prefix=G',
    '--symbol-prefix=g',
    '--c-include=glib-object.h',
    '--namespace=GObject',
    '--nsversion=2.0',
    '--pkg=gobject-2.0',
    '--library=gobject-2.0',
    '--include-uninstalled=' + glib_gir.full_path(),
    '--cflags-begin',
    '-I' + glib_includedir,
    '-I' + glib_libincludedir,
    '-DGOBJECT_COMPILATION',
    '--cflags-end',
    '--filelist=@INPUT@',
  ]
)

gir_files += gobject_gir

# GModule
gir_files += custom_target('gir-gmodule',
  input: 'gmodule-2.0.c', # TODO: glib sources
  output: 'GModule-2.0.gir',
  depends: glib_gir,
  install: true,
  install_dir: girdir,
  command: scanner_command + [
    '--identifier-prefix=G',
    '--symbol-prefix=g',
    '--c-include=gmodule.h',
    '--namespace=GModule',
    '--nsversion=2.0',
    '--pkg=gmodule-2.0',
    '--library=gmodule-2.0',
    '--include-uninstalled=' + glib_gir.full_path(),
    '--cflags-begin',
    '-I' + glib_includedir,
    '-I' + glib_libincludedir,
    '--cflags-end',
    glib_includedir + '/gmodule.h',
    '@INPUT@',
  ]
)

# Gio
gio_command = scanner_command + [
  '--identifier-prefix=G',
  '--symbol-prefix=g',
  '--c-include=gio/gio.h',
  '--namespace=Gio',
  '--nsversion=2.0',
  '--pkg=gio-2.0',
  '--library=gio-2.0',
  '--include-uninstalled=' + gobject_gir.full_path(),
  '--cflags-begin',
  '-DGIO_COMPILATION',
  '-DG_SETTINGS_ENABLE_BACKEND',
  '-I' + glib_includedir,
  '--cflags-end',
  '--filelist=@INPUT@',
]

gio_glob = glib_includedir + '/gio/*.h'
if glib_srcdir != ''
  gio_glob += ',' + glib_srcdir + '/gio/*.c'
endif

if giounix_dep.found()
  giounix_includedir = giounix_dep.get_pkgconfig_variable('includedir') + '/gio-unix-2.0'
  gio_glob += ',' + giounix_includedir + '/gio/*.h'

  get_header_list = '''
from glob import glob
from os.path import basename

print(','.join(basename(f) for f in glob('@0@/gio/*.h')))
'''.format(giounix_includedir)

  ret = run_command(py3.find_python(), '-c', get_header_list)
  if ret.returncode() != 0
    error('Failed to get gio header list')
  endif
  gio_headers = ret.stdout().strip().split(',')
  foreach header : gio_headers
    gio_command += '--c-include=gio/' + header
  endforeach

  gio_command += '--pkg=gio-unix-2.0'
endif

gio_sources_file = custom_target('gio-sources-file',
  input: 'gio-2.0.c',
  output: 'gio-sources.list',
  command: [
    find_program('generate_source_list.py'),
    '@OUTPUT@',
    gio_glob,
    ' ',
    '@INPUT@',
  ]
)

gir_files += custom_target('gir-gio',
  input: gio_sources_file,
  output: 'Gio-2.0.gir',
  depends: gobject_gir,
  install: true,
  install_dir: girdir,
  command: gio_command,
)

# GIRepository
gir_files += custom_target('gir-girepository',
  input: girepo_gir_sources,
  output: 'GIRepository-2.0.gir',
  depends: gobject_gir,
  install: true,
  install_dir: girdir,
  command: scanner_command + [
    '--identifier-prefix=GI',
    '--symbol-prefix=g',
    '--c-include=girepository.h',
    '--namespace=GIRepository',
    '--nsversion=2.0',
    '--pkg=gobject-introspection-1.0',
    '--library=girepository-1.0',
    '--include-uninstalled=' + gobject_gir.full_path(),
    '--cflags-begin',
    '-DGI_COMPILATION',
    '-I' + meson.source_root() + '/girepository',
    '--cflags-end',
    '@INPUT@',
  ]
)

foreach gir : gir_files
  custom_target('generate-typelib-@0@'.format(gir).underscorify(),
    input: gir,
    output: '@BASENAME@.typelib',
    command: [gircompiler, '-o', '@OUTPUT@', '@INPUT@'],
    install: true,
    install_dir: typelibdir,
  )
endforeach
