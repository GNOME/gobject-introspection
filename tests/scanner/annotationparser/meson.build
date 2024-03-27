annotationparser_test_env = environment()
annotationparser_test_env.prepend('PYTHONPATH', test_env_common_pypath)
if test_env_common_path.length() > 0
    annotationparser_test_env.prepend('PATH', test_env_common_path)
endif

# Needed on Windows for Python 3.8.x+ if project is configured with
# --pkg-config-path or -Dpkg_config_path
if pkg_config_path_win.length() > 0
  annotationparser_test_env.prepend('PKG_CONFIG_PATH', pkg_config_path_win)
endif

annotationparser_test_files = [
  'test_patterns.py',
  'test_parser.py',
]

foreach f : annotationparser_test_files
  test(f, python, args: files(f), env: annotationparser_test_env, depends: [giscanner_pymod])
endforeach
