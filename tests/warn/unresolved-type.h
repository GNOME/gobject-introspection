#include "common.h"

typedef struct {
   int i;
} MyStruct;

// EXPECT:5: Warning: Test: symbol='MyStruct': Unknown namespace for identifier 'MyStruct'

typedef enum {
  TEST_MY_ENUM_A = 0
} MyEnum;

// EXPECT:11: Warning: Test: symbol='MyEnum': Unknown namespace for identifier 'MyEnum'

typedef enum {
  MY_ENUM_A = 0
} TestMyEnum2;

// EXPECT:17: Warning: Test: symbol='TestMyEnum2': Unknown namespace for symbol 'MY_ENUM_A'

/* Stub function here so namespace isn't empty */
void test_foo (void);

