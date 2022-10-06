Introspection scanner
---------------------

- If you add a new warning to `annotationparser.py`, you should add new
  tests for it in `tests/scanner/annotationparser/gi`

- In case there are changes to the gir expected test files, the script
  `tests/scanner/update-expected-results.sh` can be used to update them in this
  way:

  ```
  tests/scanner/update-expected-results.sh <build-path>
  ```

- If you add a new warning elsewhere (`maintransformer.py`, etc), you
  should add a new test for it in `tests/warn/`

- Before pushing code to the repository, make sure to run `meson test`
