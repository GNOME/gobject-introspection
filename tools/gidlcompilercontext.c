/* GObject introspection: Metadata compiler context
 *
 * Copyright (C) 2008 Codethink Ltd
 *               2008 Johan Dahlin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <glib.h>

#include "gidlcompilercontext.h"
#include "gidlnode.h"
#include "gmetadata.h"

/* STATIC FUNCTIONS */
/* ---------------- */

/* Functions for writing final 'C' file */
/* ------------------------------------ */

extern char gmetadata_header[];

/* Parameters
 * -Struct name
 * -Number of directory entries
 * -Length of strings area.
 */
static const char struct_header[] =
  "%s\n"
  "{\n"
  " Header " SECTION (header) ";\n"
  " DirEntry " SECTION (directory) "[%d];\n"
  " char " SECTION (strings) "[%d];\n";

/* Parameters
 * -Namespace name
 * -Struct name
 */
static const char declarations[] =
  "const unsigned char *_G_METADATA = (unsigned char *) &_METADATA_%s;\n"
  "const gsize _G_METADATA_SIZE = sizeof(%s);\n\n";

/* Parameters
 * -Struct name
 * -Namespace name
 */
static const char init_header[] =
  "static const %s _METADATA_%s =\n" 
  "{\n";

/* Parameters
 * -Namespace name
 */
static const char file_footer[] =
  "__attribute__((constructor)) void\n"
  "register_metadata (void)\n"
  "{\n"
  "  GMetadata *metadata;\n"
  "  metadata = g_metadata_new_from_const_memory (_G_METADATA, _G_METADATA_SIZE);\n"
  "  g_irepository_register (NULL, metadata);\n"
  "}\n"
  "\n"
  "__attribute__((destructor)) void\n"
  "unregister_metadata (void)\n"
  "{\n"
  "  g_irepository_unregister (NULL, \"%s\");\n"
  "}\n";
                             

typedef struct
{
  guint entry_id;
  guint dir_id;
} SymbolEntry;

typedef struct
{
  GIdlNode *node;
  guint entry_id;
} DeferredEntry;

static void
symbol_entry_free (SymbolEntry *symbol_entry)
{
  g_slice_free (SymbolEntry, symbol_entry);
}
			     
static void
deferred_entry_free (DeferredEntry *deferred_entry)
{
  g_slice_free (DeferredEntry, deferred_entry);
}
			     
static void
include_file (const gchar *fname,
              FILE        *output)
{
  FILE *input;
  char c;

  input = fopen (fname, "r");

  c = fgetc (input);
  while (c != EOF)
    {
      fputc (c, output);
      c = fgetc (input);
    }

  fclose (input);
}

static void
write_header (GIdlCompilerContext *ctx, 
                const gchar *shlib,
                FILE *stream)
{
  guint32 n_entries;
  guint32 n_local_entries;
  const gchar *header_prototype = 
    " {\n"
    /* Magic */
    "  \"%s\",\n" 
    /* Major version */
    "  %d,\n"                  
    /* Minor version */
    "  %d,\n"                  
    "  0,\n"
    /* n_entries */
    "  %d,\n"                  
    /* n_local_entries */
    "  %d,\n"                  
    /* directory */
    "  G_STRUCT_OFFSET(%s, " SECTION (directory) "),\n"        
    /* n_annotations */
    "  %d,\n"                  
    /* annotations */
    "  %d,\n"                  
    /* struct_name */
    "  sizeof(%s),\n"          
    /* struct_name, pointer to name string */
    "  G_STRUCT_OFFSET(%s, " SECTION (strings) ") + %d,\n";    

  fprintf (stream, header_prototype,
	   G_IDL_MAGIC_ESCAPED,
	   1,
	   0,
	   ctx->directory_entries,
	   ctx->directory_local_entries,
	   ctx->struct_name,
	   0,
	   0,
	   ctx->struct_name,
	   ctx->struct_name,
	   g_idl_compiler_write_string (ctx, ctx->namespace_name));


  /* Header */
  if (shlib)
    fprintf (stream, STRING_POINTER,
	     ctx->struct_name,
	     g_idl_compiler_write_string (ctx, shlib));
  else
    fprintf (stream, "0");
  fprintf (stream, ",\n");

  /* Header sizes */
  fprintf (stream,
	   "  sizeof(DirEntry),\n"
	   "  sizeof(FunctionBlob),\n"
	   "  sizeof(CallbackBlob),\n"
	   "  sizeof(SignalBlob),\n"
	   "  sizeof(VFuncBlob),\n"
	   "  sizeof(ArgBlob),\n"
	   "  sizeof(PropertyBlob),\n"
	   "  sizeof(FieldBlob),\n"
	   "  sizeof(ValueBlob),\n"
	   "  sizeof(AnnotationBlob),\n"
	   "  sizeof(ConstantBlob),\n"
	   "  sizeof(ErrorDomainBlob),\n"
	   "  sizeof(SignatureBlob),\n"
	   "  sizeof(EnumBlob),\n"
	   "  sizeof(StructBlob),\n"
	   "  sizeof(ObjectBlob),\n"
	   "  sizeof(InterfaceBlob),\n"
	   "  sizeof(UnionBlob),\n" 
	   "  {0,0,0,0,0,0,0},\n" " },\n\n");
}

void
write_compiled (GIdlCompilerContext *ctx, FILE *compiled, 
                const gchar *shlib,
                GError **err)
{
  const char file_header[] =
    "#include <stdlib.h>\n"
    "#include <glib.h>\n"
    "#include <girepository.h>\n";

  /* Before doing anything need to add the namespace string */
  g_idl_compiler_write_string (ctx, ctx->namespace_name);

  fprintf (compiled, file_header);
  fprintf (compiled, gmetadata_header);

  /* +1 is for the null byte right at the end of the strings section */
  fprintf (compiled, struct_header, ctx->struct_name,
           ctx->directory_entries, ctx->string_offset + 1);
  
  /* Include the struct file */
  include_file (ctx->mdata_struct_fn, compiled);
  fprintf (compiled, "};\n\n");
  fprintf (compiled, init_header, ctx->struct_name, ctx->namespace_name);

  write_header (ctx, shlib, compiled);

  /* Close all the temporary files */
  fclose (ctx->mdata_init);
  fclose (ctx->mdata_string);
  fclose (ctx->mdata_directory);

  /* Place directory here */
  fprintf (compiled, " {\n");
  include_file (ctx->mdata_directory_fn, compiled);
  fprintf (compiled, " },\n\n");

  /* Place string data here */
  fprintf (compiled, " {\n");
  include_file (ctx->mdata_string_fn, compiled);
  fprintf (compiled, " },\n\n");

  /* Include the initializer file */
  include_file (ctx->mdata_init_fn, compiled);

  fprintf (compiled, "};\n\n");

  /* Write out the metadata declarations */
  fprintf (compiled, declarations, ctx->namespace_name, ctx->struct_name);

  fprintf (compiled, file_footer, ctx->namespace_name);

  /* Remove the temporary files */
  g_remove (ctx->mdata_struct_fn);
  g_remove (ctx->mdata_init_fn);
  g_remove (ctx->mdata_string_fn);
  g_remove (ctx->mdata_directory_fn);
}

/* GLOBAL FUNCTIONS */
/* ---------------- */

GIdlCompilerContext *
g_idl_compiler_context_new (const gchar  *namespace,
			    GError      **error)
{
  gint struct_fd, init_fd, string_fd, directory_fd;
  GIdlCompilerContext *ctx;
  GError *tmp_error = NULL;

  ctx = g_slice_new0 (GIdlCompilerContext);
  if (!ctx)
    {
      /* FIXME Put proper error quark here */
      g_set_error (error, G_FILE_ERROR, G_FILE_ERROR_NOENT,
                   "Could not create output context");
      goto out;
    }
  ctx->strings = g_hash_table_new (g_str_hash, g_str_equal);
  ctx->namespace_name = g_strdup (namespace);
  ctx->struct_name = g_strdup_printf ("struct mdata_%s", namespace);

  ctx->entriesdb = g_hash_table_new_full (g_str_hash, g_str_equal,
					  (GDestroyNotify)g_free,
					  (GDestroyNotify)symbol_entry_free);
  ctx->typesdb = g_hash_table_new (g_str_hash, g_str_equal);

  /* Structure definition file */
  struct_fd = g_file_open_tmp ("gicomp-XXXXXX", &ctx->mdata_struct_fn,
			       &tmp_error);
  if (tmp_error)
    goto error4;

  /* Structure initialization file */
  init_fd = g_file_open_tmp ("gicomp-XXXXXX", &ctx->mdata_init_fn,
			     &tmp_error);
  if (tmp_error)
    goto error3;
  
  /* String file */
  string_fd = g_file_open_tmp ("gicomp-XXXXXX", &ctx->mdata_string_fn,
			       &tmp_error);
  if (tmp_error)
    goto error2;

  /* Directory file */
  directory_fd = g_file_open_tmp ("gicomp-XXXXXX", &ctx->mdata_directory_fn,
				  &tmp_error);
  if (tmp_error)
      goto error1;

  ctx->mdata_struct = fdopen (struct_fd, "w");
  ctx->mdata_init = fdopen (init_fd, "w");
  ctx->mdata_string = fdopen (string_fd, "w");
  ctx->mdata_directory = fdopen (directory_fd, "w");
      
  goto out;
  
 error1:
  close (directory_fd);
  g_remove (ctx->mdata_directory_fn);
 error2:
  close (string_fd);
  g_remove (ctx->mdata_string_fn);
 error3:
  close (init_fd);
  g_remove (ctx->mdata_init_fn);
 error4:
  close (struct_fd);
  g_remove (ctx->mdata_struct_fn);
 error:
  g_propagate_error (error, tmp_error);

  g_free (ctx);
  ctx = NULL;
 out:
  return ctx;
}

void
g_idl_compiler_context_finalize (GIdlCompilerContext  *ctx,
                                 FILE                 *stream,
                                 const gchar          *shlib,
                                 GError              **error)
{
  fclose (ctx->mdata_struct);
  write_compiled (ctx, stream, shlib, error);
}

void
g_idl_compiler_context_destroy (GIdlCompilerContext *ctx)
{
  g_free (ctx->mdata_struct_fn);
  g_free (ctx->mdata_init_fn);
  g_free (ctx->mdata_string_fn);
  g_free (ctx->mdata_directory_fn);

  g_free (ctx->struct_name);
  g_free (ctx->namespace_name);

  g_list_foreach (ctx->dtypelist, (GFunc)deferred_entry_free, NULL);
  g_list_free (ctx->dtypelist);

  g_list_foreach (ctx->dconstantlist, (GFunc)deferred_entry_free, NULL);
  g_list_free (ctx->dconstantlist);
  
  g_hash_table_destroy (ctx->entriesdb);
  g_hash_table_destroy (ctx->typesdb);
  g_hash_table_destroy (ctx->strings);
  g_slice_free (GIdlCompilerContext, ctx);
}


/**
 * g_idl_compiler_write_string:
 * @ctx:
 * @str:
 * String specific functions
 *
 * If string is already in the pool, return previous location,
 * otherwise write string to the metadata at offset, put it
 * in the pool and update offset.
 */
guint32
g_idl_compiler_write_string (GIdlCompilerContext *ctx,
			     const gchar         *str)
{
  gpointer value;
  guint32 orig = ctx->string_offset;
  
  g_return_val_if_fail (str != NULL, 0);

  if (g_hash_table_lookup_extended (ctx->strings, str, NULL, &value))
    return GPOINTER_TO_INT (value);

  g_hash_table_insert (ctx->strings, (gpointer) str,
                       GINT_TO_POINTER (ctx->string_offset));
  
  /* +1 is for the null byte that is added at the end of each string */
  ctx->string_offset += strlen (str) + 1;

  fprintf (ctx->mdata_string, "  \"%s\\0\"\n", str);

  return orig;
}

static guint16
g_idl_compiler_write_dir_entry (GIdlCompilerContext *ctx,
				guint16              blob_type,
				const gchar         *name,
				gint                 entry_id)
{
  const char *entry_prototype =
    "  {\n" "   %d,\n"
    "   %d,\n"
    "   0,\n"
    "   " STRING_POINTER ",\n"
    "   " TYPE_POINTER ",\n"
    "  },\n";
  guint orig = ctx->directory_entries;

  fprintf (ctx->mdata_directory, entry_prototype,
           blob_type,
           TRUE,
           ctx->struct_name, g_idl_compiler_write_string (ctx, name),
           ctx->struct_name, entry_id);

  ctx->directory_local_entries += 1;
  ctx->directory_entries += 1;
  return orig;
}

static guint16
g_idl_compiler_write_xref_entry (GIdlCompilerContext *ctx,
                             guint16 blob_type,
                             const gchar *name,
                             const gchar *namespace)
{
  const char *entry_prototype =
    "  {\n" "   %d,\n"
    "   %d,\n"
    "   0,\n"
    "   " STRING_POINTER ",\n"
    "   " STRING_POINTER ",\n"
    "  },\n";
  guint dir_id_res = ctx->directory_entries;

  fprintf (ctx->mdata_directory, entry_prototype,
           blob_type,
           FALSE,
           ctx->struct_name, g_idl_compiler_write_string (ctx, name),
           ctx->struct_name, g_idl_compiler_write_string (ctx, namespace));

  ctx->directory_entries += 1;
  return dir_id_res;
}

/* This is a unique id for each entry in the
 * metadata that may need to be referenced elsewhere.
 * Essentially anything that has to be given a
 * name in the metadata struct.
 */
gint32
g_idl_compiler_get_unique_id (void)
{
  static gint32 i = 0;
  return ++i;
}

void
g_idl_compiler_add_entry (GIdlCompilerContext *ctx, GIdlNode *node)
{
  guint entry_id;
  guint dir_id;
  SymbolEntry *entry;

  entry = g_slice_new0 (SymbolEntry);
  entry_id = g_idl_compiler_get_unique_id ();
  dir_id = g_idl_compiler_write_dir_entry (ctx, node->type,
					   node->name, entry_id);
  
  entry->entry_id = entry_id;
  /* The directory array is indexed from 1 upwards. Just to confuse us */
  entry->dir_id = dir_id + 1;

  g_hash_table_insert (ctx->entriesdb, g_strdup (node->name), entry);
}

static guint
g_idl_compiler_add_xref (GIdlCompilerContext *ctx,
			 const gchar         *name)
{
  gint dir_id;
  guint n_names;
  gchar **names;
  gchar *symbol;
  gchar *namespace;
  SymbolEntry *entry;

  names = g_strsplit (name, ".", 0);
  n_names = g_strv_length (names);

  if (n_names < 2)
    {
      g_warning ("External reference with no namespace");
      symbol = g_strjoinv ("", &names[0]);
      namespace = NULL;
    }
  else
    {
      symbol = g_strjoinv (".", &names[1]);
      namespace = names[0];
    }

  fprintf (ctx->mdata_directory,
	   "  {\n" 
	   "   0,\n"
	   "   0,\n"
	   "   0,\n"
	   "   " STRING_POINTER ",\n",
	   ctx->struct_name,
	   g_idl_compiler_write_string (ctx, symbol));
  
  if (namespace)
    fprintf (ctx->mdata_directory, "   " STRING_POINTER ",\n",
	     ctx->struct_name, g_idl_compiler_write_string (ctx, namespace));
  else
      fprintf (ctx->mdata_directory, "   0,\n");
  fprintf (ctx->mdata_directory, "  },\n");

  dir_id = ctx->directory_entries;
  ctx->directory_entries += 1;

  /* The Directory array is indexed from 1 upwards. Just to confuse us */
  entry = g_slice_new0 (SymbolEntry);
  entry->dir_id = dir_id + 1;
  g_hash_table_insert (ctx->entriesdb, g_strdup (name), entry);

  g_free(symbol);
  g_strfreev (names);
  return dir_id + 1;
}

guint
g_idl_compiler_get_entry_id (GIdlCompilerContext *ctx,
			     const gchar         *name)
{
  SymbolEntry *entry;

  entry = g_hash_table_lookup (ctx->entriesdb, name);
  return entry->entry_id;
}

guint
g_idl_compiler_get_entry_dirid (GIdlCompilerContext *ctx,
				const gchar         *name)
{
  SymbolEntry *entry;

  entry = g_hash_table_lookup (ctx->entriesdb, name);
  if (entry)
    return entry->dir_id;

  /* If no entry found assume its an external reference */
  return g_idl_compiler_add_xref (ctx, name);
}

void
g_idl_compiler_push_deferred_type_node (GIdlCompilerContext *ctx,
					GIdlNode            *node,
					guint                entry_id)
{
  DeferredEntry *entry;

  entry = g_slice_new (DeferredEntry);
  entry->node = node;
  entry->entry_id = entry_id;
  ctx->dtypelist = g_list_prepend (ctx->dtypelist, entry);
}

GIdlNode *
g_idl_compiler_pop_deferred_type_node (GIdlCompilerContext *ctx,
				       guint               *entry_id)
{
  DeferredEntry *entry;
  GIdlNode *node;

  if (!ctx->dtypelist)
    return NULL;

  entry = (DeferredEntry *) ctx->dtypelist->data;
  ctx->dtypelist = g_list_remove (ctx->dtypelist, (gpointer) entry);
  *entry_id = entry->entry_id;
  node = entry->node;
  deferred_entry_free (entry);
  return node;
}

void
g_idl_compiler_push_deferred_signature_node (GIdlCompilerContext * ctx,
                                   GIdlNode * node, guint entry_id)
{
  DeferredEntry *entry;

  entry = g_slice_new (DeferredEntry);
  entry->node = node;
  entry->entry_id = entry_id;
  ctx->dsignaturelist = g_list_prepend (ctx->dsignaturelist, entry);
}

GIdlNode*
g_idl_compiler_pop_deferred_signature_node (GIdlCompilerContext *ctx,
					    guint               *entry_id)
{
  DeferredEntry *entry;
  GIdlNode *node;

  if (!ctx->dsignaturelist)
    return NULL;

  entry = (DeferredEntry *) ctx->dsignaturelist->data;
  ctx->dsignaturelist = g_list_remove (ctx->dsignaturelist, entry);
  *entry_id = entry->entry_id;
  node = entry->node;
  deferred_entry_free (entry);
  return node;
}

void
g_idl_compiler_push_deferred_constant (GIdlCompilerContext *ctx,
				       GIdlNode            *node,
				       guint                entry_id)
{
  DeferredEntry *constant;

  constant = g_slice_new (DeferredEntry);
  constant->node = node;
  constant->entry_id = entry_id;
  ctx->dconstantlist = g_list_prepend (ctx->dconstantlist, constant);
}

GIdlNode *
g_idl_compiler_pop_deferred_constant (GIdlCompilerContext *ctx,
				      guint               *entry_id)
{
  DeferredEntry *deferred_entry;
  GIdlNode *node;

  if (!ctx->dconstantlist)
    return NULL;

  deferred_entry = (DeferredEntry *) ctx->dconstantlist->data;
  ctx->dconstantlist = g_list_remove (ctx->dconstantlist, deferred_entry);
  *entry_id = deferred_entry->entry_id;
  node = deferred_entry->node;
  deferred_entry_free (deferred_entry);
  return node;
}
