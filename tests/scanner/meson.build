
scanner_test_env = environment()
scanner_test_env.append('PYTHONPATH', join_paths(meson.current_build_dir(), '../../'))

scanner_test_files = [
  'test_sourcescanner.py',
  'test_transformer.py'
]

foreach f : scanner_test_files 
  test(f, python3, args: files(f), env: scanner_test_env)
endforeach

