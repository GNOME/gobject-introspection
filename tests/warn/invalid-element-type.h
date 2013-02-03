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
// EXPECT:29: Warning: Test: element-type takes at most 2 values, 3 given

/**
 * test_invalid_bytearray_element_type:
 * @b1: (element-type):
 * @b2: (element-type int):
 */

void test_invalid_bytearray_element_type(GByteArray *b1, GByteArray *b2);

// EXPECT:40: Warning: Test: element-type annotation needs a value
// EXPECT:40: Warning: Test: element-type takes at least one value, none given

/**
 * test_invalid_ptrarray_element_type:
 * @p1: (element-type):
 * @p2: (element-type int):
 */

void test_invalid_ptrarray_element_type(GPtrArray *p1, GPtrArray *p2);

// EXPECT:51: Warning: Test: element-type annotation needs a value
// EXPECT:51: Warning: Test: element-type takes at least one value, none given

/**
 * test_unresolved_element_type:
 *
 * Returns: (element-type Unresolved) (transfer full):
 */

GList* test_unresolved_element_type(void);

/**
 * test_unresolved_value_element_type:
 *
 * Returns: (element-type GLib.Value) (transfer full):
 */

GPtrArray* test_unresolved_value_element_type(void);


// EXPECT:5: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:6: Warning: Test: element-type annotation for a list must have exactly one option, not 2 options
// EXPECT:16: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:20: Warning: Test: Unknown container Type(target_fundamental=utf8, ctype=char*) for element-type annotation
// EXPECT:27: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:28: Warning: Test: element-type annotation for a hash table must have exactly two options, not 1 option(s)
// EXPECT:29: Warning: Test: element-type annotation for a hash table must have exactly two options, not 3 option(s)
// EXPECT:40: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:41: Warning: Test: invalid (element-type) for a GByteArray, must be one of guint8, gint8 or gchar
// EXPECT:51: Warning: Test: element-type annotation takes at least one option, none given
// EXPECT:52: Warning: Test: invalid (element-type) for a GPtrArray, must be a pointer
// EXPECT:63: Warning: Test: test_unresolved_element_type: Unknown type: 'Unresolved'
// EXPECT:71: Warning: Test: test_unresolved_value_element_type: Unknown type: 'GLib.Value'
// EXPECT:4: Warning: Test: test_invalid_list_element_type: argument l1: Missing (element-type) annotation
// EXPECT:4: Warning: Test: test_invalid_list_element_type: argument l2: Missing (element-type) annotation
// EXPECT:50: Warning: Test: test_invalid_ptrarray_element_type: argument p1: Missing (element-type) annotation
