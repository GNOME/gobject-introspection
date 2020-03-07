project('gobject-introspection', 'c',
  version: '1.64.0',
  meson_version: '>= 0.50.1',
  default_options: [
    'warning_level=1',
    'buildtype=debugoptimized',
  ],
)

host_system = host_machine.system()
gi_versions = meson.project_version().split('.')

configinc = include_directories('.')

pymod = import('python')
python = pymod.find_installation(get_option('python'))

python_version = python.language_version()
python_version_req = '>=3.4'
if not python_version.version_compare(python_version_req)
  error('Requires Python @0@, @1@ found.'.format(python_version_req, python_version))
endif

cc = meson.get_compiler('c')

project_c_args = []
if cc.get_id() != 'msvc'
    project_c_args += [
      '-Wall',
      '-Warray-bounds',
      '-Wcast-align',
      '-Wdeclaration-after-statement',
      '-Wduplicated-branches',
      '-Wextra',
      '-Wformat=2',
      '-Wformat-nonliteral',
      '-Wformat-security',
      '-Wimplicit-function-declaration',
      '-Winit-self',
      '-Wjump-misses-init',
      '-Wlogical-op',
      '-Wmissing-declarations',
      '-Wmissing-format-attribute',
      '-Wmissing-include-dirs',
      '-Wmissing-noreturn',
      '-Wmissing-prototypes',
      '-Wnested-externs',
      '-Wnull-dereference',
      '-Wold-style-definition',
      '-Wpacked',
      '-Wpointer-arith',
      '-Wrestrict',
      '-Wreturn-type',
      '-Wshadow',
      '-Wsign-compare',
      '-Wstrict-aliasing',
      '-Wstrict-prototypes',
      '-Wundef',
      '-Wunused-but-set-variable',
      '-Wwrite-strings',
    ]

    project_c_args += [
      '-fno-strict-aliasing',
    ]
else
    project_c_args += [
      '-FImsvc_recommended_pragmas.h',
      '-utf-8',
    ]
endif

project_c_args = cc.get_supported_arguments(project_c_args)
add_project_arguments(project_c_args, language: 'c')

if cc.get_id() == 'msvc' and project_c_args.contains('-utf-8')
  extra_giscanner_cflags = ['-utf-8']
  extra_giscanner_args = ['--cflags-begin'] + extra_giscanner_cflags + ['--cflags-end']
else
  extra_giscanner_cflags = []
  extra_giscanner_args = []
endif

config = configuration_data()

config.set('GI_MAJOR_VERSION', gi_versions[0])
config.set('GI_MINOR_VERSION', gi_versions[1])
config.set('GI_MICRO_VERSION', gi_versions[2])

config.set_quoted('GIR_SUFFIX', 'gir-1.0')
gir_dir_prefix = get_option('gir_dir_prefix')
if gir_dir_prefix == ''
    gir_dir_prefix = join_paths(get_option('prefix'), get_option('datadir'))
    gir_dir_pc_prefix = '${datadir}'
else
    gir_dir_prefix = join_paths(get_option('prefix'), gir_dir_prefix)
    gir_dir_pc_prefix = join_paths('${prefix}', gir_dir_prefix)
endif
girdir = join_paths(gir_dir_prefix, 'gir-1.0')
config.set_quoted('GIR_DIR', girdir)
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

# FIXME: Always bumped to match our version
#glib_version = '>=2.@0@.@1@'.format(gi_versions[1], gi_versions[2])
glib_version = '>= 2.58.0'

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

# cairo
cairo_option = get_option('cairo')
if cc.get_id() == 'msvc'
  if cairo_option.disabled()
    req = cairo_option
  else
    req = false
  endif

  cairo_dep = dependency('cairo', required: req)
  cairo_gobject_dep = dependency('cairo-gobject', required: req)

  if not cairo_gobject_dep.found() or not cairo_dep.found()
    if cc.has_header('cairo.h') and cc.has_header ('cairo-gobject.h')
      cairo_dep = cc.find_library('cairo', required: cairo_option)
      cairo_gobject_dep = cc.find_library('cairo-gobject', required: cairo_option)
    endif
  endif
else
  cairo_dep = dependency('cairo', required: cairo_option)
  cairo_gobject_dep = dependency('cairo-gobject', required: cairo_option)
endif
cairo_deps_found = cairo_gobject_dep.found() and cairo_dep.found()

if not cairo_deps_found
  warning('Not building with cairo support, not all tests will be run')
endif

# doctool
doctool_option = get_option('doctool')

with_doctool = true
if doctool_option.disabled()
  with_doctool = false
else
  has_mako = run_command(python, ['-c', 'import mako']).returncode() == 0
  has_markdown = run_command(python, ['-c', 'import markdown']).returncode() == 0
  if not has_mako or not has_markdown
    if doctool_option.enabled()
      error('doctool requires markdown and mako')
    else
      with_doctool = false
    endif
  endif
endif

if not with_doctool
  warning('Not building with doctool support, not all tests will be run')
endif

subdir('girepository')
subdir('tools')
subdir('giscanner')

# Not building gir data might be useful in cross-compilation
# scenarios where running target binaries through software emulation
# is not possible (due to the SW emulation missing support for target HW).
if get_option('build_introspection_data') == true
    subdir('gir')
endif
subdir('docs')

# The tests will also run, which is not possible if they
# were built for a different architecture.
if not meson.is_cross_build()
    subdir('tests')
endif

install_data('Makefile.introspection', install_dir: join_paths(get_option('datadir'), 'gobject-introspection-1.0'))
install_data('m4/introspection.m4', install_dir: join_paths(get_option('datadir'), 'aclocal'))

prefix = join_paths(get_option('prefix'))
pkgconfig_conf = configuration_data()
pkgconfig_conf.set('prefix', prefix)
pkgconfig_conf.set('exec_prefix', '${prefix}')
pkgconfig_conf.set('bindir', join_paths('${exec_prefix}', get_option('bindir')))
pkgconfig_conf.set('libdir', join_paths('${exec_prefix}', get_option('libdir')))
pkgconfig_conf.set('datarootdir', join_paths('${prefix}', get_option('datadir')))
pkgconfig_conf.set('datadir', '${datarootdir}')
pkgconfig_conf.set('includedir', join_paths('${prefix}', get_option('includedir')))
pkgconfig_conf.set('GIR_PC_DIR', join_paths(gir_dir_pc_prefix, 'gir-1.0'))
if host_system == 'windows' or host_system == 'cygwin'
  pkgconfig_conf.set('EXEEXT', '.exe')
else
  pkgconfig_conf.set('EXEEXT', '')
endif
pkgconfig_conf.set('VERSION', meson.project_version())
pkgconfig_conf.set('FFI_PC_PACKAGES', 'libffi')
if libffi_dep.type_name() == 'pkgconfig'
  prog_pkgconfig = find_program('pkg-config')
  pkgconfig_conf.set('FFI_PC_CFLAGS', run_command(prog_pkgconfig, ['libffi', '--cflags-only-I']).stdout())
  pkgconfig_conf.set('FFI_PC_LIBS', run_command(prog_pkgconfig, ['libffi', '--libs-only-l']).stdout())
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
  install_dir: join_paths(get_option('libdir'), 'pkgconfig'),
)

configure_file(
  input: 'gobject-introspection-1.0.pc.in',
  output: 'gobject-introspection-1.0.pc',
  configuration: pkgconfig_conf,
  install_dir: join_paths(get_option('libdir'), 'pkgconfig'),
)
