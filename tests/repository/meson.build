repository_tests = [
  'gitestrepo',
  'giteststructinfo',
  'gitestthrows',
  # FIXME: Requires Regress typelib which is not yet ported to meson.
  # 'gitypelibtest',
]

repository_test_env = environment()
repository_test_env.append(
  'GI_TYPELIB_PATH',
  join_paths(meson.build_root(), 'gir'),
  join_paths(meson.build_root(), 'tests')
)

if glib_dep.type_name() == 'pkgconfig'
  foreach test_name : repository_tests
    source = files(test_name + '.c')
    exe = executable(test_name, source, dependencies: [girepo_dep])
    test(test_name, exe, env: repository_test_env)
  endforeach
endif
