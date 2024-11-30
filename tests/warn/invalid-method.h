#include "common.h"

struct _TestMethod {
    GObject parent;
};
typedef struct _TestMethod TestMethod;

/**
 * test_method_no_parameters: (method)
 *
 */
void test_method_no_parameters();

// EXPECT:12: Warning: Test: test_method_no_parameters: Methods must have parameters

/**
 * test_method_invalid_first_parameter: (method)
 *
 */
void test_method_invalid_first_parameter(int param);

// EXPECT:20: Warning: Test: test_method_invalid_first_parameter: Methods must have a pointer as their first parameter

/**
 * test_method_invalid_namespace: (method)
 *
 */
void test_method_invalid_namespace(GClosure *param);

// EXPECT:28: Warning: Test: test_method_invalid_namespace: Methods must belong to the same namespace as the class they belong to

/**
 * test_method_out_instance_param: (method)
 * @self: (out):
 */
void test_method_out_instance_param(TestMethod *self);

// EXPECT:36: Error: Test: test_method_out_instance_param: The first argument of a method cannot be an out-argument

/**
 * test_method_inout_instance_param: (method)
 * @self: (inout):
 */
void test_method_inout_instance_param(TestMethod *self);

// EXPECT:44: Error: Test: test_method_inout_instance_param: The first argument of a method cannot be an inout-argument

/**
 * test_method_nullable_instance_param: (method)
 * @self: (nullable):
 */
void test_method_nullable_instance_param(TestMethod *self);

// EXPECT:52: Warning: Test: "nullable" annotation on instance parameter of test_method_nullable_instance_param: did you really intend that?

/**
 * test_method_transfer_full_instance_param: (method)
 * @self: (transfer full):
 */
void test_method_transfer_full_instance_param(TestMethod *self);

// EXPECT:60: Warning: Test: "transfer" annotation of "full" on instance parameter of test_method_transfer_full_instance_param: should not be applied to a method's instance parameter unless this is a free() or destroy() method

/**
 * test_method_free: (method)
 * @self: (transfer full):
 *
 * Should not warn because it's named "free"
 */
void test_method_free_data(TestMethod *self);
