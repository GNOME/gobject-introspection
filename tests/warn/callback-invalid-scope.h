#include "common.h"

typedef GCallback TestCallback;

/**
 * test_callback_invalid:
 * @callback: (scope invalid):
 * @user_data:
 */
void test_callback_invalid(TestCallback callback, gpointer user_data);

// EXPECT:7: Warning: Test: invalid "scope" annotation option: "invalid"

/**
 * test_callback_invalid2:
 * @callback: (scope):
 * @user_data:
 *
 */
void test_callback_invalid2(TestCallback callback, gpointer user_data);

// EXPECT:16: Warning: Test: "scope" annotation needs one option, none given

/**
 * test_callback_invalid3:
 * @callback: (scope call async):
 * @user_data:
 */
void test_callback_invalid3(TestCallback callback, gpointer user_data);

// EXPECT:26: Warning: Test: "scope" annotation needs one option, 2 given

/**
 * test_callback_invalid4:
 * @callback:
 * @user_data: (scope call):
 */
void test_callback_invalid4(TestCallback callback, gpointer user_data);

// EXPECT:36: Warning: Test: invalid "scope" annotation: only valid on callback parameters

// EXPECT:14: Warning: Test: test_callback_invalid2: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
// EXPECT:24: Warning: Test: test_callback_invalid3: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
// EXPECT:33: Warning: Test: test_callback_invalid4: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
