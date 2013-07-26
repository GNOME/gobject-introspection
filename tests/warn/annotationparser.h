#include "common.h"

/**
 * test_symbol_twice_documented:
 *
 * Documenting the same thing multiple times can lead to subtle bugs.
 * For example, one comment block might have correct annotations...
 **/
void test_symbol_twice_documented();

/**
 * test_symbol_twice_documented:
 *
 * ...and a different comment block (out of sync with the above) might have
 * no annotations at all. The last comment block seen by the parser "wins".
 **/

// EXPECT:12: Warning: Test: multiple comment blocks documenting 'test_symbol_twice_documented:' identifier.
