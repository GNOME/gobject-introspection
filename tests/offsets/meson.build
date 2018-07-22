offsets_sources = [
  'offsets.c',
]

offsets_headers = [
  'offsets.h',
]

offsets_lib = library(
  'offsets',
  offsets_sources,
  include_directories: [include_directories('..'), configinc],
  dependencies: [glib_dep, gobject_dep, gio_dep, gmodule_dep],
  install: false,
)

gnome = import('gnome')
offsets_gir = gnome.generate_gir(
  offsets_lib,
  sources: offsets_sources + offsets_headers,
  namespace: 'Offsets',
  nsversion: '1.0',
  includes: ['GObject-2.0'],
  install: false,
  build_by_default: true,
  extra_args: ['--warn-all', '--warn-error'],
)

gitestoffsets_sources = custom_target(
  'gen-offsets',
  command: [
    python, join_paths(meson.current_source_dir(), 'gen-gitestoffsets'),
    join_paths(meson.current_source_dir(), 'offsets.h'),
  ],
  capture: true,
  output: ['gitestoffsets.c'],
  build_by_default: true)

gitestoffsets = executable(
    'gitestoffsets',
    gitestoffsets_sources,
    dependencies: [glib_dep, gobject_dep, gmodule_dep,
                   gio_dep, girepo_dep],
    include_directories: [include_directories('..'), configinc])

test_env = environment()
test_env.set('GI_TYPELIB_PATH', meson.current_build_dir())

test(
  'gitestoffsets', python,
  args: [
    join_paths(meson.current_source_dir(), 'test-offsets'),
    gitestoffsets,
  ],
  env: test_env,
)
