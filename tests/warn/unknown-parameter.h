/* See https://bugzilla.gnome.org/show_bug.cgi?id=629708 */

/**
 * test_param_mismatch:
 * @wrong_name: (out):
 *
 */
void test_param_mismatch(int *out);

// EXPECT:: Warning: Test: test_param_mismatch: unknown parameter 'wrong_name' in documentation comment, should be 'out'

/**
 * test_param_mismatch2:
 * @wrong_name2: (out):
 *
 */
void test_param_mismatch2(int a, int *out2);

// EXPECT:: Warning: Test: test_param_mismatch2: unknown parameter 'wrong_name2' in documentation comment, should be one of 'a', 'out2'

/**
 * test_param_missing:
 * @missing: (out):
 *
 */
void test_param_missing(void);

// EXPECT:: Warning: Test: test_param_missing: unknown parameter 'missing' in documentation comment


/**
 * test_param_vargs:
 * @...: The varargs
 *
 */
void test_param_varargs(int i, ...);

// Should not warn
