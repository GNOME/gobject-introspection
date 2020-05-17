custom_c_args = []
if cc.get_id() != 'msvc'
  custom_c_args = cc.get_supported_arguments(['-Wno-missing-field-initializers'])
endif


gircompiler = executable('g-ir-compiler', 'compiler.c',
  dependencies: [
    girepo_internals_dep,
    girepo_dep,
  ],
  install: true,
  c_args: custom_c_args,
)

girgenerate = executable('g-ir-generate', 'generate.c',
  dependencies: [
    girepo_internals_dep,
    girepo_dep,
  ],
  install: true,
  c_args: custom_c_args,
)

girinspect = executable('g-ir-inspect', 'g-ir-inspect.c',
  dependencies: girepo_dep,
  install: true,
  c_args: custom_c_args,
)

if not get_option('gi_cross_use_prebuilt_gi')
  meson.override_find_program('g-ir-compiler', gircompiler)
  meson.override_find_program('g-ir-generate', girgenerate)
  meson.override_find_program('g-ir-inspect', girinspect)
endif
