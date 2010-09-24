#include "common.h"

/**
 * test_invalid_list_element_type:
 * @l1: (element-type):
 * @l2: (element-type int int):
 */

void test_invalid_list_element_type(GList *l1, GList *l2);

// EXPECT:5: Warning: Test: element-type annotation needs a value
// EXPECT:5: Warning: Test: element-type takes at least one value, none given

/**
 * test_invalid_array_element_type:
 * @a1: (element-type):
 * @a2: (element-type int int):
 */

void test_invalid_array_element_type(const char *a1, const char *a2);

// EXPECT:16: Warning: Test: element-type annotation needs a value
// EXPECT:16: Warning: Test: element-type takes at least one value, none given

/**
 * test_invalid_hash_element_type:
 * @h1: (element-type):
 * @h2: (element-type int):
 * @h3: (element-type int int int):
 */

void test_invalid_hash_element_type(GHashTable *h1, GHashTable *h2, GHashTable *h3);

// EXPECT:27: Warning: Test: element-type annotation needs a value
// EXPECT:27: Warning: Test: element-type takes at least one value, none given
// EXPECT:29: Warning: Test: element-type takes at maximium 2 values, 3 given

/**
 * test_unresolved_element_type:
 *
 * Returns: (element-type Unresolved) (transfer full):
 */

GList* test_unresolved_element_type(void);


// EXPECT:5: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:6: Warning: Test: element-type annotation for a list must have exactly one option, not 2 options
// EXPECT:16: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:20: Warning: Test: Unknown container Type(target_fundamental=utf8, ctype=char*) for element-type annotation
// EXPECT:27: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:28: Warning: Test: element-type annotation for a hash table must have exactly two options, not 1 option(s)
// EXPECT:29: Warning: Test: element-type annotation for a hash table must have exactly two options, not 3 option(s)
// EXPECT:41: Warning: Test: test_unresolved_element_type: Unknown type: 'Unresolved'
