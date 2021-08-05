gidocgen_dep = dependency('gi-docgen',
  version: '>= 2021.7',
  fallback: ['gi-docgen', 'dummy_dep'],
  required: get_option('gtk_doc'),
)

gi_docgen = find_program('gi-docgen', required: get_option('gtk_doc'))

docs_dir = get_option('prefix') / get_option('datadir') / 'doc'

toml_conf = configuration_data()
toml_conf.set('version', meson.project_version())

expand_content_files = []

girepository_toml = configure_file(
  input: 'girepository.toml.in',
  output: 'girepository.toml',
  configuration: toml_conf,
  install: true,
  install_dir: docs_dir / 'girepository',
)

custom_target('girepsitory-doc',
  input: [girepository_toml, girepository_gir],
  output: 'girepository',
  command: [
    gi_docgen,
    'generate',
    '--quiet',
    '--fatal-warnings',
    '--add-include-path=@0@'.format(meson.current_build_dir() / '../../gir'),
    '--config=@INPUT0@',
    '--output-dir=@OUTPUT@',
    '--no-namespace-dir',
    '--content-dir=@0@'.format(meson.current_source_dir()),
    '@INPUT1@',
  ],
  depend_files: expand_content_files,
  build_by_default: true,
  install: true,
  install_dir: docs_dir,
)
