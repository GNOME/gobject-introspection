
/**
 * test_transfer_invalid:
 * @param: (transfer):
 * @param2: (transfer invalid):
 * @param3: (transfer full foo):
 */
void test_transfer_invalid(int param, int param2, int param3);

// EXPECT:4: Warning: Test: "transfer" annotation needs one option, none given
// EXPECT:5: Warning: Test: invalid "transfer" annotation option: "invalid"
// EXPECT:6: Warning: Test: "transfer" annotation needs one option, 2 given
