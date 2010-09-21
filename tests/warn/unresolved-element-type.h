#include "common.h"

/**
 * test_unresolved_element_type:
 *
 * Returns: (element-type Unresolved) (transfer full):
 */

GList* test_unresolved_element_type(void);

// EXPECT:6: Warning: Test: test_unresolved_element_type: Unknown type: 'Unresolved'
