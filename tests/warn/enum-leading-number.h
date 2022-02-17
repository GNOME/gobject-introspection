#include "common.h"

/**
 * TestEnum:
 * @TEST_ENUM_BUTTON_PRESS: ...
 * @TEST_ENUM_2BUTTON_PRESS: ...
 * @TEST_ENUM_DOUBLE_BUTTON_PRESS: ...
 *
 * ...
 */
typedef enum {
  TEST_ENUM_BUTTON_PRESS,
  TEST_ENUM_2BUTTON_PRESS,
  TEST_ENUM_DOUBLE_BUTTON_PRESS
} TestEnum;

// EXPECT:15: Warning: Test: Member TEST_ENUM_2BUTTON_PRESS for enumeration TestEnum starts with a number
