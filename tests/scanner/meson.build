
scanner_test_env = environment()
scanner_test_env.append('PYTHONPATH', join_paths(meson.current_build_dir(), '../../'))

scanner_test_files = [
  'test_shlibs.py',
  'test_sourcescanner.py',
]

# FIXME: Windows
if host_system != 'windows'
  scanner_test_files += ['test_transformer.py']
endif

foreach f : scanner_test_files 
  test(
    f, python,
    args: files(f),
    env: scanner_test_env,
    depends: [giscanner_pymod])
endforeach

