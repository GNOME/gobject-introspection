
/**
 * test_invalid_closure:
 * @param: (closure a b):
 */
void test_invalid_closure(int param);

// EXPECT:4: Warning: Test: "closure" annotation takes at most one option, 2 given

/**
 * TestInvalidCallbackClosure:
 * @data: (closure data):
 */
typedef void (* TestInvalidCallbackClosure) (void* data);

// EXPECT:12: Warning: Test: TestInvalidCallbackClosure: "closure" annotation takes no option in callback types
