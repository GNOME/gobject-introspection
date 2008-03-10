/* GObject introspection: Type node compilation
 *
 * Copyright (C) 2005 Matthias Clasen
 * Copyright (C) 2008 Codethink Ltd
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
#include <stdlib.h>
#include <string.h>

#include "gmetadata.h"

#include "gidlnode.h"
#include "gidlcompilercontext.h"
#include "gidlcompilertypenode.h"

/*TYPE BLOB COMPILATION*/
/*---------------------*/

const gchar *
g_idl_compiler_name_basic_type(guint type_tag)
{
  const gchar *basic[] = {
    "void",
    "gboolean",
    "gint8",
    "guint8",
    "gint16",
    "guint16",
    "gint32",
    "guint32",
    "gint64",
    "guint64",
    "gint",
    "guint",
    "glong",
    "gulong",
    "gssize",
    "gsize",
    "gfloat",
    "gdouble",
    "utf8",
    "filename"
  };

  return basic[type_tag];
}

void
g_idl_compiler_serialize_type (GIdlNodeType * node, GString * str)
{
  gint i;

  if (TYPE_IS_SIMPLE(node->tag))
    {
      g_string_append_printf (str, "%s%s",
			      g_idl_compiler_name_basic_type(node->tag),
			      node->is_pointer ? "*" : "");
    }
  else if (node->tag == TYPE_TAG_ARRAY)
    {
      g_idl_compiler_serialize_type (node->parameter_type1, str);
      g_string_append (str, "[");

      if (node->has_length)
	g_string_append_printf (str, "length=%d", node->length);

      if (node->zero_terminated)
	g_string_append_printf (str, "%szero-terminated=1",
				node->has_length ? "," : "");

      g_string_append (str, "]");
    }
  else if (node->tag == TYPE_TAG_SYMBOL)
    {
      g_string_append_printf (str, "%s%s", node->interface,
			      node->is_pointer ? "*" : "");
    }
  else if (node->tag == TYPE_TAG_LIST)
    {
      g_string_append (str, "GList");
      if (node->parameter_type1)
	{
	  g_string_append (str, "<");
	  g_idl_compiler_serialize_type (node->parameter_type1, str);
	  g_string_append (str, ">");
	}
    }
  else if (node->tag == TYPE_TAG_SLIST)
    {
      g_string_append (str, "GSList");
      if (node->parameter_type1)
	{
	  g_string_append (str, "<");
	  g_idl_compiler_serialize_type (node->parameter_type1, str);
	  g_string_append (str, ">");
	}
    }
  else if (node->tag == TYPE_TAG_HASH)
    {
      g_string_append (str, "GHashTable<");
      if (node->parameter_type1)
	{
	  g_string_append (str, "<");
	  g_idl_compiler_serialize_type (node->parameter_type1, str);
	  g_string_append (str, ",");
	  g_idl_compiler_serialize_type (node->parameter_type2, str);
	  g_string_append (str, ">");
	}
    }
  else if (node->tag == TYPE_TAG_ERROR)
    {
      g_string_append (str, "GError");
      if (node->errors)
	{
	  g_string_append (str, "<");
	  for (i = 0; node->errors[i]; i++)
	    {
	      if (i > 0)
		g_string_append (str, ",");
	      g_string_append (str, node->errors[i]);
	    }
	  g_string_append (str, ">");
	}
    }
}

/* Types below somewhat augment a more basic type that has
 * an entry in the direcory. An array type is an array of X.
 * A list is a list of X.
 */
static void
type_array_write (GIdlNode * node,
			   guint type_id, GIdlCompilerContext * ctx)
{
  GIdlNodeType *type = (GIdlNodeType *) node;

  const gchar *array_struct =
  " ArrayTypeBlob "ID_TO_ENTRY";\n";

  const gchar *array_initialiser =
  " {\n"
  "  {%d, 0, %d},\n"
  "  %d, %d, 0, %d,\n";

  fprintf(ctx->mdata_struct, array_struct, type_id);

  fprintf(ctx->mdata_init, array_initialiser,
	  1,
	  type->tag,
	  type->zero_terminated,
	  type->has_length,
	  type->length);

  g_idl_compiler_write_simple_type_blob ((GIdlNode*)type->parameter_type1, ctx);

  fprintf(ctx->mdata_init, " },\n\n");
}

static void
type_list_write (GIdlNode * node,
			  guint type_id,
			  GIdlCompilerContext * ctx)
{
  GIdlNodeType *type = (GIdlNodeType *) node;
  guint n_types = 1;

  const gchar *array_struct =
  " struct {\n"
  "  ParamTypeBlob fixed;\n"
  "  SimpleTypeBlob type[%d];\n"
  " } "ID_TO_ENTRY";\n";

  const gchar *array_initialiser =
  " {\n"
  "  {\n"
  "   {%d, 0, %d},\n"
  "   0, %d,\n"
  "  },\n";

  fprintf(ctx->mdata_struct, array_struct, n_types, type_id);

  fprintf(ctx->mdata_init, array_initialiser,
	  1,
	  type->tag,
	  n_types);

  fprintf(ctx->mdata_init, "  {\n");
  if (type->parameter_type1)
    {
      g_idl_compiler_write_simple_type_blob ((GIdlNode*)type->parameter_type1, ctx);
    }
  fprintf(ctx->mdata_init, "  },\n");

  fprintf(ctx->mdata_init, " },\n\n");
}

static void
type_hash_write (GIdlNode * node,
			  guint type_id, GIdlCompilerContext * ctx)
{
  GIdlNodeType *type = (GIdlNodeType *) node;
  guint n_types = 2;

  const gchar *hash_struct =
  " struct {\n"
  "  ParamTypeBlob fixed;\n"
  "  SimpleTypeBlob type[%d];\n"
  " } "ID_TO_ENTRY";\n";

  const gchar *hash_initialiser =
  " {\n"
  "  {\n"
  "   {%d, 0, %d},\n"
  "   0, %d,\n"
  "  },\n";

  fprintf(ctx->mdata_struct, hash_struct, n_types, type_id);

  fprintf(ctx->mdata_init, hash_initialiser,
	  1,
	  type->tag,
	  n_types);

  fprintf(ctx->mdata_init, "  {\n");
  if (type->parameter_type1)
    {
      g_idl_compiler_write_simple_type_blob ((GIdlNode*)type->parameter_type1, ctx);
    }
  if (type->parameter_type2)
    {
      g_idl_compiler_write_simple_type_blob ((GIdlNode*)type->parameter_type2, ctx);
    }
  fprintf(ctx->mdata_init, "  },\n");

  fprintf(ctx->mdata_init, " },\n\n");
}

static void
type_error_write (GIdlNode * node,
			   guint type_id, GIdlCompilerContext * ctx)
{
  GIdlNodeType *type = (GIdlNodeType *) node;
  guint n_domains = 0;
  guint i;

  const gchar *error_struct =
  " struct {\n"
  "  ErrorTypeBlob fixed;\n"
  "  guint16 domains[%d];\n"
  " } "ID_TO_ENTRY";\n";

  const gchar *error_initialiser =
  " {\n"
  "  {\n"
  "   {%d, 0, %d},\n"
  "   %d,\n"
  "  },\n";

  const gchar *error_domain_entry =
  "   %d,\n";

  if (type->errors)
    {
       n_domains = g_strv_length(type->errors);
    }

  fprintf(ctx->mdata_struct, error_struct, n_domains, type_id);

  fprintf(ctx->mdata_init, error_initialiser,
	  1,
	  type->tag,
	  n_domains);

  fprintf(ctx->mdata_init, "  {\n");
  for (i=0; i < n_domains; i++)
    {
      fprintf(ctx->mdata_init, error_domain_entry,
	      g_idl_compiler_get_entry_dirid (ctx, type->errors[i]));
    }
  fprintf(ctx->mdata_init, "  },\n");

  fprintf(ctx->mdata_init, " },\n\n");
}

static void
type_complex_write (GIdlNode * node,
			     guint type_id, GIdlCompilerContext * ctx)
{
  GIdlNodeType *type = (GIdlNodeType *) node;

  switch (type->tag)
    {
    case TYPE_TAG_ARRAY:
      {
	type_array_write (node, type_id, ctx);
      }
      break;

    case TYPE_TAG_LIST:
    case TYPE_TAG_SLIST:
      {
	type_list_write (node, type_id, ctx);
      }
      break;

    case TYPE_TAG_HASH:
      {
	type_hash_write (node, type_id, ctx);
      }
      break;

    case TYPE_TAG_ERROR:
      {
	type_error_write (node, type_id, ctx);
      }
      break;

    default:
      g_error ("Unknown type tag %d\n", type->tag);
      break;
    }
}

/* This is called at the end of any entries that may have
 * added complex type blobs to the type list.
 *
 * These can only be written out to the metadata at the end of a previous
 * entry and so are deffered until the entry is finished.
 */
void
g_idl_compiler_write_deferred_type_blobs (GIdlCompilerContext *ctx)
{
  GIdlNodeType *type;
  guint entry_id;
  type = (GIdlNodeType *) g_idl_compiler_pop_deferred_type_node (ctx, &entry_id);

  while (type)
    {
      fprintf(ctx->mdata_init, " /*Entry - %d*/\n",
              entry_id);
      type_complex_write ((GIdlNode *) type, entry_id, ctx);
      type = (GIdlNodeType *) g_idl_compiler_pop_deferred_type_node (ctx, &entry_id);
    }
}

/*
 * This function writes out a simple type blob initializer.
 * Simple type blobs are only included in other entries.
 */
void
g_idl_compiler_write_simple_type_blob (GIdlNode * node, GIdlCompilerContext * ctx)
{
  GIdlNodeType *type = (GIdlNodeType *) node;

  const gchar *simple_initialiser =
  "   {\n"
  "    {%d, 0, %d}, 0\n"
  "   },\n";
  const gchar *symbol_initialiser =
  "   {\n"
  "    {%d, 0, %d}, %d,\n"
  "   },\n";
  const gchar *complex_initialiser =
  "   {\n"
  "    {%d, 0, %d}, "TYPE_POINTER",\n"
  "   },\n";

  /* If this is a simple type */
  /* Simple types are not given their own entry
   * into the global structure. They are a member of
   * another entry.
   */
  if (TYPE_IS_SIMPLE(type->tag))
    {
      fprintf (ctx->mdata_init, simple_initialiser,
	       type->is_pointer, type->tag);
    }
  else if (TYPE_IS_SYMBOL(type->tag))
    {
      guint dir_id;

      dir_id = g_idl_compiler_get_entry_dirid(ctx, type->interface);

      fprintf (ctx->mdata_init, symbol_initialiser,
	       type->is_pointer, type->tag,
	       dir_id);
    }
  else
    {
      gpointer type_id;
      GString *str;
      gchar *s;

      str = g_string_new (0);
      g_idl_compiler_serialize_type (type, str);
      s = g_string_free (str, FALSE);

      type_id = g_hash_table_lookup (ctx->typesdb, s);
      if (type_id)
        {
          g_free (s);
        }
      else
        {
          type_id = GINT_TO_POINTER (g_idl_compiler_get_unique_id ());
          g_hash_table_insert (ctx->typesdb, s, type_id);
          g_idl_compiler_push_deferred_type_node (ctx, node, GPOINTER_TO_INT(type_id));
        }

      fprintf (ctx->mdata_init, complex_initialiser,
	       type->is_pointer, type->tag,
	       ctx->struct_name, GPOINTER_TO_INT(type_id));
    }
}
