#include "common.h"

typedef GCallback TestCallback;

/**
 * test_invalid_closure:
 * @callback: (closure a b):
 * @user_data:
 */
void test_invalid_closure(TestCallback callback, gpointer user_data);

// EXPECT:7: Warning: Test: "closure" annotation takes at most one option, 2 given

/**
 * test_invalid_closure2:
 * @callback:
 * @user_data: (closure callback):
 */
void test_invalid_closure2(TestCallback callback, gpointer user_data);

// EXPECT:17: Warning: Test: invalid "closure" annotation: only valid on callback parameters

/**
 * test_invalid_closure3:
 * @callback: (closure user_data):
 * @user_data:
 */
void test_invalid_closure3(TestCallback callback, int user_data);

// EXPECT:25: Warning: Test: invalid "closure" annotation: only valid on gpointer parameters


/**
 * TestInvalidCallbackClosure:
 * @foo:
 * @user_data: (closure a):
 */
typedef void (* TestInvalidCallbackClosure) (int foo, gpointer user_data);

// EXPECT:36: Warning: Test: invalid "closure" annotation with argument on a callback type

/**
 * TestInvalidCallbackClosure2:
 * @foo: (closure):
 * @user_data:
 */
typedef void (* TestInvalidCallbackClosure2) (int foo, gpointer user_data);

// EXPECT:44: Warning: Test: invalid "closure" annotation: only valid on gpointer parameters

// EXPECT:5: Warning: Test: test_invalid_closure: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
// EXPECT:14: Warning: Test: test_invalid_closure2: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
// EXPECT:23: Warning: Test: test_invalid_closure3: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
