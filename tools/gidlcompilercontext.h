
#ifndef __G_IDL_COMPILER_CONTEXT_H__
#define __G_IDL_COMPILER_CONTEXT_H__

#include <stdio.h>
#include <glib.h>

#include "gidlnode.h"

typedef struct _GIdlCompilerContext GIdlCompilerContext;

struct _GIdlCompilerContext
{
  gchar *namespace_name;
  gchar *struct_name;

  gchar *mdata_struct_fn;
  FILE *mdata_struct;

  gchar *mdata_init_fn;
  FILE *mdata_init;

  guint32 string_offset;
  gchar *mdata_string_fn;
  FILE *mdata_string;
  GHashTable *strings;

  guint32 directory_local_entries;
  guint32 directory_entries;
  gchar *mdata_directory_fn;
  FILE *mdata_directory;

  /* The entriesdb contains all the
   * types that have a directory entry.
   *
   * It must be filled in before beginning to write
   * out the data. This is because it is used
   * to decide whether a type is available or
   * needs an external reference
   */
  GHashTable *entriesdb;

  /* The typesdb is used to store type names to
   * entry ids, so that multiple similar type blobs are
   * not written out
   */
  GHashTable *typesdb;

  /* Type blobs are accessed in the middle of writing another
   * entry. Writing them needs to be deferred until after
   * that entry is finished.
   */
  GList *dtypelist;

  /* Signature blobs are accessed in the middle of writing
   * other entries, and so need to be deferred.
   *
   * There is no signature node, so the function / callback
   * nodes are stored instead.
   */
  GList *dsignaturelist;

  /* Constants have values that are of a variable size,
   * and have to be written out after the entry has finished,
   * so are stored as a variant in this list until the time comes.
   */
  GList *dconstantlist;
};

GIdlCompilerContext *g_idl_compiler_context_new (const gchar * namespace,
						 GError ** err);

void
g_idl_compiler_context_finalize (GIdlCompilerContext *ctx,
				 FILE *stream,
				 const gchar *shlib,
				 GError **err);

void g_idl_compiler_context_destroy (GIdlCompilerContext * ctx);

guint32 g_idl_compiler_write_string (GIdlCompilerContext * ctx,
				     const gchar * str);

gint32 g_idl_compiler_get_unique_id (void);

void g_idl_compiler_add_entry (GIdlCompilerContext *ctx,
			       GIdlNode *node);

guint g_idl_compiler_get_entry_id (GIdlCompilerContext * ctx,
				   const gchar * name);

guint g_idl_compiler_get_entry_dirid (GIdlCompilerContext * ctx,
				      const gchar * name);

void g_idl_compiler_push_deferred_type_node (GIdlCompilerContext * ctx,
					     GIdlNode * node,
					     guint entry_id);

GIdlNode *g_idl_compiler_pop_deferred_type_node (GIdlCompilerContext * ctx,
						 guint * entry_id);

void g_idl_compiler_push_deferred_signature_node (GIdlCompilerContext * ctx,
						  GIdlNode * node,
						  guint entry_id);

GIdlNode *g_idl_compiler_pop_deferred_signature_node (GIdlCompilerContext * ctx,
						      guint * entry_id);

void g_idl_compiler_push_deferred_constant (GIdlCompilerContext * ctx,
					    GIdlNode * node,
					    guint entry_id);

GIdlNode * g_idl_compiler_pop_deferred_constant (GIdlCompilerContext * ctx,
						 guint * entry_id);

#define SECTION(sEC) "info_" #sEC
#define ID_TO_ENTRY   "entry_%d"

/* Parameters (To the string)
 * Metadata struct name
 * Offset into string buffer - Given by g_idl_compiler_write_string()
 */
#define STRING_POINTER "G_STRUCT_OFFSET(%s," SECTION(strings) ") + %d"

/* Parameters(To the string)
 * Metatada struct name
 * Type name
 */
#define TYPE_POINTER   "G_STRUCT_OFFSET(%s,"ID_TO_ENTRY")"

#endif /*__G_IDL_COMPILER_CONTEXT_H__*/
