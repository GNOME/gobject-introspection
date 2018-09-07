test_regress_sources = files('scanner/regress.c')
test_regress_headers = files('scanner/regress.h')
test_marshalling_sources = files('gimarshallingtests.c')
test_marshalling_headers = files('gimarshallingtests.h')

test_regress_incdirs = include_directories(['.', 'scanner'])

installed_sources = [
  'scanner/regress.c',
  'scanner/regress.h',
  'scanner/warnlib.c',
  'scanner/warnlib.h',
  'gimarshallingtests.c',
  'gimarshallingtests.h',
  'gitestmacros.h',
]

install_data(installed_sources, install_dir: join_paths(get_option('datadir'), 'gobject-introspection-1.0', 'tests'))

### TODO: actually test
subdir('warn')
subdir('scanner')
