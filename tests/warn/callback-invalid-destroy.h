#include "common.h"

typedef GDestroyNotify TestDestroy;

/**
 * test_callback_invalid:
 * @callback: (destroy):
 * @user_data:
 * @destroy:
 */
void test_callback_invalid(GCallback callback, gpointer user_data, TestDestroy destroy);

// EXPECT:7: Warning: Test: "destroy" annotation needs one option, none given

/**
 * test_callback_invalid2:
 * @callback: (destroy a b):
 * @user_data:
 * @destroy:
 */
void test_callback_invalid2(GCallback callback, gpointer user_data, TestDestroy destroy);

// EXPECT:17: Warning: Test: "destroy" annotation needs one option, 2 given

/**
 * test_callback_invalid3:
 * @callback:
 * @user_data: (destroy destroy):
 * @destroy:
 */
void test_callback_invalid3(GCallback callback, gpointer user_data, TestDestroy destroy);

// EXPECT:28: Warning: Test: invalid "destroy" annotation: only valid on callback parameters
