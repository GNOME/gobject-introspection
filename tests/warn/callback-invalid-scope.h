#include "common.h"

/**
 * test_callback_invalid:
 * @callback: (scope invalid):
 *
 */
void test_callback_invalid(GCallback *callback, gpointer user_data);

// EXPECT:5: Warning: Test: Invalid scope 'invalid' for parameter 'callback'
// EXPECT:3: Warning: Test: test_callback_invalid: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async)
