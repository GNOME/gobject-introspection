project('gobject-introspection', 'c',
  version: '1.55.0',
  meson_version: '>= 0.42.0',
  default_options: [
    'warning_level=1',
    'buildtype=debugoptimized',
  ],
)

host_system = host_machine.system()
gi_versions = meson.project_version().split('.')

configinc = include_directories('.')

py3 = import('python3')
python3 = py3.find_python()

cc = meson.get_compiler('c')
config = configuration_data()
config.set_quoted('GIR_SUFFIX', 'gir-1.0')
config.set_quoted('GIR_DIR', join_paths(get_option('prefix'), get_option('datadir'), 'gir-1.0'))
config.set_quoted('GOBJECT_INTROSPECTION_LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))

foreach type : ['char', 'short', 'int', 'long']
  size = cc.sizeof(type)
  if size == -1
    error('Failed to get size of @0@'.format(type))
  endif
  config.set('SIZEOF_@0@'.format(type.to_upper()), size)
endforeach

add_project_arguments(['-DHAVE_CONFIG_H'], language: 'c')

gi_hidden_visibility_cflags = []
if host_system == 'windows'
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

# Always bumped to match our version
glib_version = '>=2.@0@.@1@'.format(gi_versions[1], gi_versions[2])

glib_dep = dependency('glib-2.0', version : glib_version,
  fallback: ['glib', 'libglib_dep'])
gobject_dep = dependency('gobject-2.0', version : glib_version,
  fallback: ['glib', 'libgobject_dep'])
gio_dep = dependency('gio-2.0', version : glib_version,
  fallback: ['glib', 'libgio_dep'])
gmodule_dep = dependency('gmodule-2.0', version : glib_version,
  fallback: ['glib', 'libgmodule_dep'])
if host_system != 'windows'
  giounix_dep = dependency('gio-unix-2.0', version : glib_version,
    fallback: ['glib', 'libgiounix_dep'])
else
  # Don't even try to look for gio-unix-2.0 on Windows because Meson will
  # fruitlessly try to find it in the glib subproject even when we don't want
  # it to look in the subproject at all. Just use a not-found dependency.
  giounix_dep = dependency('', required : false)
  # XXX: Autotools doesn't build girs for gio-win32-2.0, but maybe we should?
endif
libffi_dep = dependency('libffi',
  fallback : ['libffi', 'ffi_dep'])

subdir('girepository')
subdir('tools')
subdir('giscanner')
subdir('gir')
subdir('examples')
subdir('docs')
### TODO
### subdir('tests')

install_data('Makefile.introspection', install_dir: join_paths(get_option('datadir'), 'gobject-introspection-1.0'))
install_data('m4/introspection.m4', install_dir: join_paths(get_option('datadir'), 'aclocal'))

prefix = get_option('prefix')
pkgconfig_conf = configuration_data()
pkgconfig_conf.set('prefix', prefix)
pkgconfig_conf.set('exec_prefix', '${prefix}')
pkgconfig_conf.set('bindir', join_paths('${prefix}', get_option('bindir')))
pkgconfig_conf.set('libdir', join_paths('${prefix}', get_option('libdir')))
pkgconfig_conf.set('datarootdir', join_paths('${prefix}', get_option('datadir')))
pkgconfig_conf.set('datadir', '${datarootdir}')
pkgconfig_conf.set('includedir', join_paths('${prefix}', get_option('includedir')))
if host_system == 'windows' or host_system == 'cygwin'
  pkgconfig_conf.set('EXEEXT', '.exe')
else
  pkgconfig_conf.set('EXEEXT', '')
endif
pkgconfig_conf.set('VERSION', meson.project_version())
pkgconfig_conf.set('FFI_PC_PACKAGES', 'libffi')
if libffi_dep.type_name() == 'pkgconfig'
  pkgconfig_conf.set('FFI_PC_CFLAGS', libffi_dep.get_pkgconfig_variable('Cflags'))
  pkgconfig_conf.set('FFI_PC_LIBS', libffi_dep.get_pkgconfig_variable('Libs'))
else
  # XXX: We can't know the correct values for these, needs meson API. Maybe we
  # should use meson's pkgconfig module to generate the whole file.
  pkgconfig_conf.set('FFI_PC_CFLAGS', '')
  pkgconfig_conf.set('FFI_PC_LIBS', '-lffi')
endif

configure_file(
  input: 'gobject-introspection-no-export-1.0.pc.in',
  output: 'gobject-introspection-no-export-1.0.pc',
  configuration: pkgconfig_conf,
  install: true,
  install_dir: join_paths(get_option('libdir'), 'pkgconfig'),
)

configure_file(
  input: 'gobject-introspection-1.0.pc.in',
  output: 'gobject-introspection-1.0.pc',
  configuration: pkgconfig_conf,
  install: true,
  install_dir: join_paths(get_option('libdir'), 'pkgconfig'),
)
