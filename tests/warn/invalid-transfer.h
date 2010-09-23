
/**
 * test_transfer_invalid:
 * @param: (transfer):
 * @param2: (transfer invalid):
 * @param3: (transfer full foo):
 */
void test_transfer_invalid(int param, int param2, int param3);

// EXPECT:4: Warning: Test: transfer annotation needs a value
// EXPECT:5: Warning: Test: invalid transfer annotation value: 'invalid'
// EXPECT:6: Warning: Test: transfer annotation needs one value, not 2
