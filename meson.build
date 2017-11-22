project('gobject-introspection', 'c',
  version: '1.55.0',
  meson_version: '>= 0.40.0',
  default_options: [
    'warning_level=1',
    'buildtype=debugoptimized',
  ],
)

py3 = import('python3')

gi_prefix = get_option('prefix')
gi_bindir = join_paths(gi_prefix, get_option('bindir'))
gi_libdir = join_paths(gi_prefix, get_option('libdir'))
gi_datadir = join_paths(gi_prefix, get_option('datadir'))
gi_includedir = join_paths(gi_prefix, get_option('includedir'))

cc = meson.get_compiler('c')
config = configuration_data()
config.set_quoted('GIR_SUFFIX', 'gir-1.0')
config.set_quoted('GIR_DIR', join_paths(gi_datadir, 'gir-1.0'))
config.set_quoted('GOBJECT_INTROSPECTION_LIBDIR', gi_libdir)

foreach type : ['char', 'short', 'int', 'long']
  size = cc.sizeof(type)
  if size == -1
    error('Failed to get size of @0@'.format(type))
  endif
  config.set('SIZEOF_@0@'.format(type.to_upper()), size)
endforeach

add_project_arguments([
    '-I' + meson.build_root(),
    '-DHAVE_CONFIG_H',
  ], language: 'c',
)

gi_hidden_visibility_cflags = []
if host_machine.system() == 'windows'
  config.set('DLL_EXPORT', true)
  config.set('_GI_EXTERN', '__declspec(dllexport) extern')
  if cc.get_id() != 'msvc'
    gi_hidden_visibility_cflags += '-fvisibility=hidden'
  endif
else
  config.set('_GI_EXTERN', '__attribute__((visibility("default"))) extern')
  gi_hidden_visibility_cflags += '-fvisibility=hidden'
endif

configure_file(
  configuration: config,
  output: 'config.h'
)

gobject_dep = dependency('gobject-2.0', version: '>= 2.52.0')
gio_dep = dependency('gio-2.0')
giounix_dep = dependency('gio-unix-2.0', required: false)
gmodule_dep = dependency('gmodule-2.0')
libffi_dep = dependency('libffi')

gir_build = get_option('gir_build')
subdir('girepository')
subdir('tools')
subdir('giscanner')
if gir_build
  ### To do in a second time
  subdir('gir')
endif
subdir('examples')
subdir('docs')

### Missing meson.build file
### subdir('tests')

install_data('Makefile.introspection', install_dir: join_paths(gi_datadir, 'gobject-introspection-1.0'))
install_data('m4/introspection.m4', install_dir: join_paths(gi_datadir, 'aclocal'))

pkgconfig_conf = configuration_data()
pkgconfig_conf.set('prefix', prefix)
pkgconfig_conf.set('exec_prefix', '${prefix}')
pkgconfig_conf.set('bindir', gi_bindir)
pkgconfig_conf.set('libdir', gi_libdir)
pkgconfig_conf.set('datarootdir', gi_datadir)
pkgconfig_conf.set('datadir', '${datarootdir}')
pkgconfig_conf.set('includedir', gi_includedir)
pkgconfig_conf.set('EXEEXT', '') # TODO?
pkgconfig_conf.set('VERSION', meson.project_version())
pkgconfig_conf.set('FFI_PC_CFLAGS', libffi_dep.get_pkgconfig_variable('Cflags'))
pkgconfig_conf.set('FFI_PC_LIBS', libffi_dep.get_pkgconfig_variable('Libs'))
pkgconfig_conf.set('FFI_PC_PACKAGES', 'libffi')

configure_file(
  input: 'gobject-introspection-1.0.pc.in',
  output: 'gobject-introspection-1.0.pc',
  configuration: pkgconfig_conf,
  install: true,
  install_dir: join_paths(gi_libdir, 'pkgconfig'),
)
