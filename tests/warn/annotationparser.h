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


/**
 * test_symbol_missing_colon
 *
 * Forgotten colon above will result in a warning.
 **/

// EXPECT:22: Warning: Test: missing ':' at column 29:
//+ * test_symbol_missing_colon
//+                            ^


/**
 * GtkWidget:test_property_missing_colon
 *
 * Forgotten colon above will result in a warning.
 **/

// EXPECT:33: Warning: Test: missing ':' at column 41:
//+ * GtkWidget:test_property_missing_colon
//+                                        ^


/**
 * GtkWidget::test_signal_missing_colon
 *
 * Forgotten colon above will result in a warning.
 **/

// EXPECT:44: Warning: Test: missing ':' at column 40:
//+ * GtkWidget::test_signal_missing_colon
//+                                       ^


/**
 * This is not a valid section identifier
 * SECTION:test_invalid_section_idetifier
 *
 * Above identifier will result in a warning.
 **/

// EXPECT:55: Warning: Test: ignoring unrecognized GTK-Doc comment block, identifier not found:
//+ * This is not a valid section identifier
//+   ^


/**
 * test_unexpected_parameter:
 * @param1: first parameter
 *
 * Parameters should come before the comment block description
 *
 * Returns: something
 * @param2: second parameter
 **/

// EXPECT:73: Warning: Test: '@param2' parameter unexpected at this location:
//+ * @param2: second parameter
//+    ^


/**
 * test_multiple_returns_tag_and_parameter:
 *
 * Multiple return value warnings are checked for when a returns
 * parameter is encountered.
 *
 * Return Value: something
 * @returns: something
 */

// EXPECT:88: Warning: Test: '@returns' parameter unexpected at this location:
//+ * @returns: something
//+    ^
// EXPECT:88: Warning: Test: encountered multiple 'Returns' parameters or tags for 'test_multiple_returns_tag_and_parameter'.


/**
 * test_multiple_parameters:
 * @param1: first parameter
 * @param1: first parameter
 **/

// EXPECT:100: Warning: Test: multiple '@param1' parameters for identifier 'test_multiple_parameters':
//+ * @param1: first parameter
//+    ^


/**
 * test_unexpected_tag:
 * @param1: first parameter
 * Returns: something
 *
 * Tags should go after the comment block description
 **/

// EXPECT:111: Warning: Test: 'Returns:' tag unexpected at this location:
//+ * Returns: something
//+   ^


/**
 * test_multiple_returns_tag:
 * @returns: something
 *
 * Multiple return value warnings are checked for when returns tag is used
 *
 * Returns: anything
 * Return value: whatever
 **/

// EXPECT:127: Warning: Test: encountered multiple 'Returns' parameters or tags for 'test_multiple_returns_tag'.
// EXPECT:128: Warning: Test: encountered multiple 'Returns' parameters or tags for 'test_multiple_returns_tag'.


/**
 * test_multiple_tags:
 *
 * Since: 3.0
 * Since: 3.0
 **/

// EXPECT:139: Warning: Test: multiple 'Since:' tags for identifier 'test_multiple_tags':
//+ * Since: 3.0
//+   ^


/**
 * test_tag_annotatable:
 *
 * There's currently 2 tags that can be annotated, so these don't emit warnings
 *
 * Returns: (allow-none): something
 * Attributes: (free) (form) (annotations)
 **/

/**
 * test_tag_not_annotatable:
 *
 * Tags (except Returns: and Attributes:) don't have annotations
 *
 * Since: (allow-none): 2.24
 **/

// EXPECT:161: Warning: Test: annotations not supported for tag 'Since:'.


/**
 * test_multiline_annotations_on_parameter:
 * @param1: (allow-none)
 * (transfer full): first parameter
 *
 * Annotations spanning multiple lines are not valid
 **/

// EXPECT:170: Warning: Test: ignoring invalid multiline annotation continuation:
//+ * (transfer full): first parameter
//+   ^


/**
 * test_multiline_annotations_on_tag:
 *
 * Annotations spanning multiple lines are not valid
 *
 * Returns: (allow-none)
 * (transfer full): something
 **/

// EXPECT:186: Warning: Test: ignoring invalid multiline annotation continuation:
//+ * (transfer full): something
//+   ^


/**

 * regress_test_invalid_comment:
 * @foo: a param
 *
 * invalid comment with a line without
 * https://bugzilla.gnome.org/show_bug.cgi?id=673806
 */

// EXPECT:195: Warning: Test: ignoring unrecognized GTK-Doc comment block, identifier not found:
//+
//+^

/**
 * regress_test_invalid_comment_end:
 * @foo: a param
 *
 * invalid comment with a line without
 * https://bugzilla.gnome.org/show_bug.cgi?id=689354 */

// EXPECT:212: Warning: Test: Comments should end with */ on a new line:
//+ * https://bugzilla.gnome.org/show_bug.cgi?id=689354 */
//+                                                    ^
