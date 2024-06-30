#include "common.h"

typedef GCallback TestCallback;

void test_callback(TestCallback callback, gpointer user_data);

// EXPECT:5: Warning: Test: test_callback: argument callback: Missing (scope) annotation for callback without GDestroyNotify (valid: call, async, forever)
