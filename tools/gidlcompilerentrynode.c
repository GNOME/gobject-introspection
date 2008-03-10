/* GObject introspection: Node compilation
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
#include "gidlmodule.h"
#include "gidlcompilercontext.h"
#include "gidlcompilertypenode.h"

/* PARAMETER BLOB COMPILATION */
/*----------------------------*/
/* Blobs in this section do not get a directory entry.
 * They are not types in themselves but are just information 
 * about types, such as the signals of an object or the fields
 * of a struct.
 */

/*VALUE*/
/* Used in enums and flags */
static void
include_value (GIdlNode * node, GIdlCompilerContext * ctx)
{
  GIdlNodeValue *value = (GIdlNodeValue *) node;
  const gchar *value_prototype = "   {%d, %d, " STRING_POINTER ", %d},\n";

  fprintf (ctx->mdata_init, value_prototype,
	   value->deprecated,
	   0,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   value->value);
}

/*PARAM*/
/* Used in signatures */
static void
include_param (GIdlNode * node, GIdlCompilerContext * ctx)
{
  GIdlNodeParam *param = (GIdlNodeParam *) node;

  const gchar *param_header =
  "   {\n"
  "    "STRING_POINTER",\n"
  "    %d, %d, %d, %d, %d, %d, %d, %d, 0,\n";

  fprintf (ctx->mdata_init, param_header,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   param->in,
	   param->out,
	   param->dipper,
	   param->null_ok,
	   param->optional,
	   param->transfer,
	   param->shallow_transfer,
	   param->retval);

  g_idl_compiler_write_simple_type_blob ((GIdlNode *)param->type, ctx);

  fprintf(ctx->mdata_init, "   },\n");
}

/*V FUNC*/
/* Used in objects and interfaces */
static void
include_vfunc (GIdlNode * node, GIdlCompilerContext * ctx)
{
  guint signature_id;
  GIdlNodeVFunc *vfunc = (GIdlNodeVFunc *) node;
  const char *vfunc_header =
  "  {\n"
  "   "STRING_POINTER",\n"
  "   %d, %d, %d, %d, 0, %d,\n"
  "   %d, 0,\n"
  "   "TYPE_POINTER",\n"
  "  },\n";

  signature_id = g_idl_compiler_get_unique_id();

  g_idl_compiler_push_deferred_signature_node(ctx, node, signature_id);

  fprintf(ctx->mdata_init, vfunc_header,
	  ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	  0, /*FIXME*/
	  0, /*FIXME*/
	  0, /*FIXME*/
	  0, /*FIXME*/
	  0, /*FIXME*/
	  vfunc->offset,
	  ctx->struct_name, signature_id);
}

/*PROPERTY*/
/* Used in objects and interfaces */
static void
include_property (GIdlNode * node, GIdlCompilerContext * ctx)
{
  GIdlNodeProperty *property = (GIdlNodeProperty *) node;

  const gchar *property_header =
  "   {\n"
  "    "STRING_POINTER", %d, %d, %d, %d, %d, 0,\n";

  fprintf (ctx->mdata_init, property_header,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   property->deprecated,
	   property->readable,
	   property->writable,
	   property->construct,
	   property->construct_only);

  /*Insert simple type blob here */
  g_idl_compiler_write_simple_type_blob ((GIdlNode *)property->type, ctx);

  fprintf (ctx->mdata_init, "   },\n");
}

/*FIELD*/
/* Used in struct */
static void
include_field (GIdlNode * node, GIdlCompilerContext * ctx)
{
  GIdlNodeField *field = (GIdlNodeField *) node;

  const gchar *field_header =
  "   {\n"
  "    "STRING_POINTER", %d, %d, %d, %d, %d,\n";

  fprintf (ctx->mdata_init, field_header,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   field->readable, field->writable, 0, 0, field->offset);

  /*Insert simple type blob here */
  g_idl_compiler_write_simple_type_blob ((GIdlNode *)field->type, ctx);

  fprintf (ctx->mdata_init, "   },\n");
}

 /*SIGNAL*/
/* Used in interface and object */
static void
include_signal (GIdlNode * node, GIdlCompilerContext * ctx)
{
  guint signature_id;
  GIdlNodeSignal *signal = (GIdlNodeSignal *) node;
  const char *signal_header =
  "  {\n"
  "   %d, %d, %d, %d, %d,\n"
  "   %d, %d, %d, %d, %d,\n"
  "   0,\n"
  "   %d,\n"
  "   "STRING_POINTER",\n"
  "   "TYPE_POINTER",\n"
  "  },\n";

  signature_id = g_idl_compiler_get_unique_id();

  g_idl_compiler_push_deferred_signature_node(ctx, node, signature_id);

  fprintf(ctx->mdata_init, signal_header,
	  signal->deprecated,
	  signal->run_first,
	  signal->run_last,
	  signal->run_cleanup,
	  signal->no_recurse,
	  signal->detailed,
	  signal->action,
	  signal->no_hooks,
	  0, /*FIXME*/
	  0, /*FIXME*/
	  0, /*FIXME*/
	  ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	  ctx->struct_name, signature_id);
}

/*METHOD*/
/*Used in struct object interface, uses the FunctionBlob*/
static void
include_method (GIdlNode * node,
	GIdlCompilerContext * ctx)
{
  guint signature_id;
  GIdlNodeFunction *function = (GIdlNodeFunction *) node;
  const char *function_header =
  "  {\n"
  "   %d, %d, %d, %d, %d, %d, 0, %d,\n"
  "   "STRING_POINTER",\n"
  "   "STRING_POINTER",\n"
  "   "TYPE_POINTER",\n"
  "  },\n";

  signature_id = g_idl_compiler_get_unique_id();

  g_idl_compiler_push_deferred_signature_node(ctx, node, signature_id);

  fprintf(ctx->mdata_init, function_header,
          BLOB_TYPE_FUNCTION,
	  function->deprecated,
	  function->is_setter,
	  function->is_getter,
	  function->is_constructor,
	  function->wraps_vfunc,
	  0, /*index??*/
	  ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	  ctx->struct_name, g_idl_compiler_write_string (ctx, function->symbol),
	  ctx->struct_name, signature_id);
}

/*CONSTANT*/
static void
include_constant (GIdlNode * node,
	GIdlCompilerContext * ctx)
{
  GIdlNodeConstant *constant = (GIdlNodeConstant *)node;
  guint entry_id;
  const gchar *constant_header =
  " {\n"
  "   %d, %d, 0,\n"        /*type/deprecated/reserved */
  "   "STRING_POINTER",\n";    /*name */

  const gchar *constant_footer =
  "   %d, "TYPE_POINTER"\n" /*size/offset*/
  " },\n";

  fprintf (ctx->mdata_init, constant_header,
	   BLOB_TYPE_CONSTANT,
	   constant->deprecated,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name));

  g_idl_compiler_write_simple_type_blob ((GIdlNode *)constant->type, ctx);

  entry_id = g_idl_compiler_get_unique_id();

  g_idl_compiler_push_deferred_constant(ctx, node, entry_id);

  fprintf (ctx->mdata_init, constant_footer,
	   0, /*FIXME I'm excluding the size, where is this used?*/
	   ctx->struct_name, entry_id);
}

/*ENTRY BLOB COMPILATION*/
/*----------------------*/
/* Blobs in this section are given a directory entry
 * and can be used as a type
 */

/*ENUM / FLAGS*/
static void
write_enum (GIdlNode * node,
				guint entry_id,
				GIdlCompilerContext * ctx)
{
  GIdlNodeEnum *enum_ = (GIdlNodeEnum *) node;
  guint16 blob_type;
  guint32 gtype_name = 0;
  guint32 gtype_init = 0;
  guint unregistered;
  GList *c;

  const gchar *enum_flags_struct =
  " struct\n"
  " {\n"
  "  EnumBlob fixed;\n"
  "  ValueBlob values[%d];\n"
  " } " ID_TO_ENTRY ";\n";

  const gchar *enum_flags_header = 
  " {\n"
  "  {\n"
  "   %d, %d, %d, %d,\n"        /*type/deprecated/unregistered/reserved */
  "   " STRING_POINTER ",\n"    /*name */
  "   " STRING_POINTER ",\n"    /*gtype-name */
  "   " STRING_POINTER ",\n"    /*gtype-init */
  "   %d, %d\n" "  },\n";       /*n_values/reserved */

  if (node->type == G_IDL_NODE_ENUM)
    blob_type = BLOB_TYPE_ENUM;
  else
    blob_type = BLOB_TYPE_FLAGS;

  if (enum_->gtype_name)
    {
      unregistered = FALSE;
      gtype_name = g_idl_compiler_write_string (ctx, enum_->gtype_name);
      gtype_init = g_idl_compiler_write_string (ctx, enum_->gtype_init);
    }
  else
    {
      unregistered = TRUE;
      gtype_name = 0;
      gtype_init = 0;
    }

  fprintf (ctx->mdata_struct, enum_flags_struct,
	   g_list_length (enum_->values), entry_id);

  fprintf (ctx->mdata_init, enum_flags_header,
	   blob_type,
	   enum_->deprecated,
	   unregistered,
	   0,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   ctx->struct_name, gtype_name,
	   ctx->struct_name, gtype_init, g_list_length (enum_->values), 0);

  /*Insert value initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (c = enum_->values; c; c = c->next)
    {
      include_value (c->data, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf (ctx->mdata_init, " },\n\n");
}

/*FUNCTION*/ 
static void
write_function (GIdlNode * node,
				    guint entry_id,
				    GIdlCompilerContext * ctx)
{
  const char *function_struct =
  " FunctionBlob "ID_TO_ENTRY";\n";

  fprintf(ctx->mdata_struct, function_struct, entry_id);

  include_method(node, ctx);
}

/*SIGNATURE*/
static void
write_signature (GIdlNode * node,
				    guint entry_id,
				    GIdlCompilerContext * ctx)
{
  GList *c;
  GIdlNodeFunction *function = (GIdlNodeFunction *) node;
  GIdlNodeVFunc *vfunc = (GIdlNodeVFunc *) node;
  GIdlNodeSignal *signal = (GIdlNodeSignal *) node;
  guint n_args;
  GIdlNodeType *result_type;
  guint null_ok;
  guint transfer;
  guint shallow_transfer;
  GList *param_list;

  const char *signature_struct =
  " struct\n"
  " {\n"
  "  SignatureBlob fixed;\n"
  "  ArgBlob values[%d];\n"
  " } " ID_TO_ENTRY ";\n";

  const char *signature_prototype =
  "   %d, %d, %d, 0, %d,\n";

  switch (node->type)
    {
    case G_IDL_NODE_CALLBACK:
    case G_IDL_NODE_FUNCTION:
      null_ok = function->result->null_ok,
      transfer = function->result->transfer,
      shallow_transfer = function->result->shallow_transfer,
      param_list = function->parameters;
      result_type = function->result->type;
      break;
    case G_IDL_NODE_VFUNC:
      null_ok = vfunc->result->null_ok,
      transfer = vfunc->result->transfer,
      shallow_transfer = vfunc->result->shallow_transfer,
      param_list = vfunc->parameters;
      result_type = vfunc->result->type;
      break;
    case G_IDL_NODE_SIGNAL:
      null_ok = signal->result->null_ok,
      transfer = signal->result->transfer,
      shallow_transfer = signal->result->shallow_transfer,
      param_list = signal->parameters;
      result_type = signal->result->type;
      break;
    default:
      g_assert_not_reached();
      break;
    }

  n_args = g_list_length(param_list);

  fprintf(ctx->mdata_struct, signature_struct, n_args, entry_id);

  fprintf(ctx->mdata_init, " {\n");
  fprintf(ctx->mdata_init, "  {\n");

  g_idl_compiler_write_simple_type_blob ((GIdlNode *)result_type, ctx);

  fprintf(ctx->mdata_init, signature_prototype,
	  null_ok,
	  transfer,
	  shallow_transfer,
	  n_args);

  fprintf (ctx->mdata_init, "  },\n");

  /*Write out all the args*/
  fprintf (ctx->mdata_init, "  {\n");
  for (c = param_list; c; c = c->next)
    {
      include_param (c->data, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf(ctx->mdata_init, " },\n\n");
}

/*CALLBACK*/
static void
write_callback (GIdlNode * node,
				    guint entry_id,
				    GIdlCompilerContext * ctx)
{
  guint signature_id;
  GIdlNodeFunction *function = (GIdlNodeFunction *) node;

  const char *callback_struct =
  " CallbackBlob "ID_TO_ENTRY";\n";

  const char *callback_header =
  "  {\n"
  "   %d, %d, 0,\n"
  "   "STRING_POINTER",\n"
  "   "TYPE_POINTER",\n"
  "  },\n";

  fprintf(ctx->mdata_struct, callback_struct, entry_id);

  signature_id = g_idl_compiler_get_unique_id();

  g_idl_compiler_push_deferred_signature_node(ctx, node, signature_id);

  fprintf(ctx->mdata_init, callback_header,
          BLOB_TYPE_CALLBACK,
	  function->deprecated,
	  ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	  ctx->struct_name, signature_id);
}

/*BOXED*/
/*TODO merge the boxed and struct functions.*/
static void
write_boxed (GIdlNode * node,
				 guint entry_id,
				 GIdlCompilerContext * ctx)
{
  GIdlNodeBoxed *boxed = (GIdlNodeBoxed *) node;
  guint16 n_method = 0;
  guint16 n_field = 0;
  GList *l;

  const char *struct_struct =
  " struct\n"
  " {\n"
  "  StructBlob fixed;\n"
  "  FieldBlob fields[%d];\n"
  "  FunctionBlob methods[%d];\n" 
  " } " ID_TO_ENTRY ";\n";

  const gchar *struct_header = 
  " {\n"
  "  {\n"
  "   %d, %d, %d, %d,\n"        /*type/deprecated/unregistered/reserved */
  "   " STRING_POINTER ",\n"    /*name */
  "   " STRING_POINTER ",\n"    /*gtype-name */
  "   " STRING_POINTER ",\n"    /*gtype-init */
  "   %d, %d\n"                 /*n_fields/n_methods */
  "  },\n";                     /*n_values/reserved */

  for (l = boxed->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
	{
	  n_field++;
	}
      else
	{
	  n_method++;
	}
    }

  fprintf (ctx->mdata_struct, struct_struct, n_field, n_method, entry_id);

  fprintf (ctx->mdata_init, struct_header,
	   BLOB_TYPE_STRUCT,
	   boxed->deprecated,
	   FALSE,
	   0,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, boxed->gtype_name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, boxed->gtype_init),
	   n_field, n_method);

  /*Insert field initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (l = boxed->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
	include_field (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert method initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (l = boxed->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FUNCTION)
	include_method (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf (ctx->mdata_init, " },\n\n");
}

/*STRUCT*/ 
static void
write_struct (GIdlNode * node,
				  guint entry_id,
				  GIdlCompilerContext * ctx)
{
  GIdlNodeStruct *struct_ = (GIdlNodeStruct *) node;
  guint16 n_method = 0;
  guint16 n_field = 0;
  GList *l;

  const char *struct_struct =
  " struct\n"
  " {\n"
  "  StructBlob fixed;\n"
  "  FieldBlob fields[%d];\n"
  "  FunctionBlob methods[%d];\n" 
  " } " ID_TO_ENTRY ";\n";

  const gchar *struct_header = 
  " {\n"
  "  {\n"
  "   %d, %d, %d, %d,\n"        /*type/deprecated/unregistered/reserved */
  "   " STRING_POINTER ",\n"    /*name */
  "   " STRING_POINTER ",\n"    /*gtype-name */
  "   " STRING_POINTER ",\n"    /*gtype-init */
  "   %d, %d\n"                 /*n_fields/n_methods */
  "  },\n";                     /*n_values/reserved */

  for (l = struct_->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
	{
	  n_field++;
	}
      else
	{
	  n_method++;
	}
    }

  fprintf (ctx->mdata_struct, struct_struct, n_field, n_method, entry_id);

  fprintf (ctx->mdata_init, struct_header,
	   BLOB_TYPE_STRUCT,
	   struct_->deprecated,
	   TRUE,
	   0,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   ctx->struct_name, 0, ctx->struct_name, 0, n_field, n_method);

  /*Insert field initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (l = struct_->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
	include_field (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert method initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (l = struct_->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FUNCTION)
	include_method (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf (ctx->mdata_init, " },\n\n");
}

/*UNION*/ 
static void
write_union (GIdlNode * node,
				 guint entry_id,
				 GIdlCompilerContext * ctx)
{
  GIdlNodeUnion *union_ = (GIdlNodeUnion *)node;
  guint16 n_method = 0;
  guint16 n_field = 0;
  guint16 n_constant = 0;
  gboolean discriminated = FALSE;
  gboolean unregistered = TRUE;
  GList *l;

  const char *union_struct =
  " struct\n"
  " {\n"
  "  UnionBlob fixed;\n"
  "  FieldBlob fields[%d];\n"
  "  FunctionBlob methods[%d];\n"
  "  ConstantBlob discriminator_values[%d];\n"
  " } " ID_TO_ENTRY ";\n";

  const gchar *union_header = 
  " {\n"
  "  {\n"
  "   %d, %d, %d, %d, 0,\n"        /*type/deprecated/unregistered/descriminated */
  "   " STRING_POINTER ",\n"    /*name */
  "   " STRING_POINTER ",\n"    /*gtype-name */
  "   " STRING_POINTER ",\n"    /*gtype-init */
  "   %d, %d,\n"                /*n_fields/n_methods */
  "   %d,\n";                   /*discriminator_offset*/

  for (l = union_->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
	{
	  n_field++;
	}
      else
	{
	  n_method++;
	}
    }

  if (union_->discriminator_type)
    {
      discriminated = TRUE;
      n_constant = g_list_length(union_->discriminators);
    }

  if (union_->gtype_name)
    {
      unregistered = FALSE;
    }

  fprintf (ctx->mdata_struct, union_struct, n_field, n_method, n_constant, entry_id);

  fprintf (ctx->mdata_init, union_header,
	   BLOB_TYPE_UNION,
	   union_->deprecated,
	   unregistered,
	   discriminated,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, union_->gtype_name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, union_->gtype_init),
	   n_field, n_method,
	   union_->discriminator_offset);

  if (discriminated)
    {
      g_idl_compiler_write_simple_type_blob ((GIdlNode *)union_->discriminator_type, ctx);
    }
  else
    {
      fprintf (ctx->mdata_init, "   {},\n");
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert field initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (l = union_->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
	include_field (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert method initialisers here */
  fprintf (ctx->mdata_init, "  {\n");
  for (l = union_->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FUNCTION)
	include_method (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert discriminators here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = union_->discriminators; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      include_constant (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf (ctx->mdata_init, " },\n\n");
}

/*OBJECT*/
static void
write_object (GIdlNode * node,
				  guint entry_id,
				  GIdlCompilerContext * ctx)
{
  GIdlNodeInterface *object = (GIdlNodeInterface *) node;
  guint num_interfaces = 0;
  guint num_fields = 0;
  guint num_properties = 0;
  guint num_methods = 0;
  guint num_signals = 0;
  guint num_vfuncs = 0;
  guint num_constants = 0;

  GList *l;

  const char *object_struct =
  " struct\n"
  " {\n"
  "  ObjectBlob fixed;\n"
  "  guint16             interfaces[%d];\n"
  "  FieldBlob           fields[%d];\n"
  "  PropertyBlob        properties[%d];\n"
  "  FunctionBlob        methods[%d];\n"
  "  SignalBlob          signals[%d];\n"
  "  VFuncBlob           vfuncs[%d];\n"
  "  ConstantBlob        constants[%d];\n"
  " } " ID_TO_ENTRY ";\n";

  const gchar *object_header =
  " {\n"
  "  {\n"
  "   %d, %d, 0,\n"
  "   " STRING_POINTER ",\n"
  "   " STRING_POINTER ",\n"
  "   " STRING_POINTER ",\n";

  const gchar *object_footer =
  "   %d, %d, %d, %d, %d, %d, %d,\n"
  "  },\n";

  const gchar *type_entry =
  "   %d,\n";

  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      switch (tnode->type)
	{
	case G_IDL_NODE_FIELD:
	  num_fields++;
	  break;
	case G_IDL_NODE_PROPERTY:
	  num_properties++;
	  break;
	case G_IDL_NODE_FUNCTION:
	  num_methods++;
	  break;
	case G_IDL_NODE_SIGNAL:
	  num_signals++;
	  break;
	case G_IDL_NODE_VFUNC:
	  num_vfuncs++;
	  break;
	case G_IDL_NODE_CONSTANT:
	  num_constants++;
	  break;
	default:
	  ;
	}
    }

  num_interfaces = g_list_length(object->interfaces);

  fprintf(ctx->mdata_struct, object_struct,
	  num_interfaces,
	  num_fields,
	  num_properties,
	  num_methods,
	  num_signals,
	  num_vfuncs,
	  num_constants,
	  entry_id);

  fprintf (ctx->mdata_init, object_header,
	   BLOB_TYPE_INTERFACE,
	   object->deprecated,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, object->gtype_name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, object->gtype_init));

  if (object->parent)
    {
      fprintf(ctx->mdata_init, type_entry,
	      g_idl_compiler_get_entry_dirid(ctx, object->parent));
    }
  else
    {
      fprintf (ctx->mdata_init, "   0,\n");
    }

  fprintf (ctx->mdata_init, object_footer,
	   num_interfaces,
	   num_fields,
	   num_properties,
	   num_methods,
	   num_signals,
	   num_vfuncs,
	   num_constants);

  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->interfaces; l; l = l->next)
    {
      gchar *interface = l->data;
      fprintf(ctx->mdata_init, type_entry,
	      g_idl_compiler_get_entry_dirid(ctx, interface));
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert fields here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FIELD)
        include_field (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert properties here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_PROPERTY)
        include_property (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert functions here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FUNCTION)
        include_method (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert signals here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_SIGNAL)
        include_signal (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert vfuncs here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_VFUNC)
        include_vfunc (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert constants here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = object->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_CONSTANT)
        include_constant (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf (ctx->mdata_init, " },\n\n");
}

/*INTERFACE*/
static void
write_interface(GIdlNode * node,
		guint entry_id,
		GIdlCompilerContext * ctx)
{
  GIdlNodeInterface *iface = (GIdlNodeInterface *) node;
  guint num_prerequisites = 0;
  guint num_properties = 0;
  guint num_methods = 0;
  guint num_signals = 0;
  guint num_vfuncs = 0;
  guint num_constants = 0;

  GList *l;

  const char *interface_struct =
  " struct\n"
  " {\n"
  "  InterfaceBlob fixed;\n"
  "  guint16             prerequisites[%d];\n"
  "  PropertyBlob        properties[%d];\n"
  "  FunctionBlob        methods[%d];\n"
  "  SignalBlob          signals[%d];\n"
  "  VFuncBlob           vfuncs[%d];\n"
  "  ConstantBlob        constants[%d];\n"
  " } " ID_TO_ENTRY ";\n";

  const gchar *interface_header = 
  " {\n"
  "  {\n"
  "   %d, %d, 0,\n"
  "   " STRING_POINTER ",\n"
  "   " STRING_POINTER ",\n"
  "   " STRING_POINTER ",\n"
  "   %d, %d, %d, %d, %d, %d,\n"
  "  },\n";

  const gchar *prereq_entry =
  "   %d,\n";

  for (l = iface->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      switch (tnode->type)
	{
	case G_IDL_NODE_PROPERTY:
	  num_properties++;
	  break;
	case G_IDL_NODE_FUNCTION:
	  num_methods++;
	  break;
	case G_IDL_NODE_SIGNAL:
	  num_signals++;
	  break;
	case G_IDL_NODE_VFUNC:
	  num_vfuncs++;
	  break;
	case G_IDL_NODE_CONSTANT:
	  num_constants++;
	  break;
	default:
	  ;
	}
    }

  num_prerequisites = g_list_length(iface->prerequisites);

  fprintf(ctx->mdata_struct, interface_struct,
	  num_prerequisites,
	  num_properties,
	  num_methods,
	  num_signals,
	  num_vfuncs,
	  num_constants,
	  entry_id);

  fprintf (ctx->mdata_init, interface_header,
	   BLOB_TYPE_INTERFACE,
	   iface->deprecated,
	   ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, iface->gtype_name),
	   ctx->struct_name, g_idl_compiler_write_string (ctx, iface->gtype_init),
	   num_prerequisites,
	   num_properties,
	   num_methods,
	   num_signals,
	   num_vfuncs,
	   num_constants);

  fprintf (ctx->mdata_init, "  {\n");
  for (l = iface->prerequisites; l; l = l->next)
    {
      gchar *prereq = l->data;
      fprintf(ctx->mdata_init, prereq_entry,
	      g_idl_compiler_get_entry_dirid(ctx, prereq));
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert properties here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = iface->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_PROPERTY)
        include_property (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert functions here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = iface->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_FUNCTION)
        include_method (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert signals here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = iface->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_SIGNAL)
        include_signal (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert vfuncs here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = iface->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_VFUNC)
        include_vfunc (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  /*Insert constants here*/
  fprintf (ctx->mdata_init, "  {\n");
  for (l = iface->members; l; l = l->next)
    {
      GIdlNode *tnode = l->data;
      if (tnode->type == G_IDL_NODE_CONSTANT)
        include_constant (tnode, ctx);
    }
  fprintf (ctx->mdata_init, "  },\n");

  fprintf (ctx->mdata_init, " },\n\n");
}

/*ERROR DOMAIN*/
static void
write_error_domain (GIdlNode * node,
					guint entry_id,
					GIdlCompilerContext * ctx)
{
  GIdlNodeErrorDomain *domain = (GIdlNodeErrorDomain *) node;
  const char *error_domain_struct =
  " ErrorDomainBlob " ID_TO_ENTRY ";\n";

  const gchar *error_domain_header = 
  " {\n"
  "  %d, %d, 0,\n"
  "  " STRING_POINTER ",\n"    /*name */
  "  " STRING_POINTER ",\n"    /*get-quark */
  "  " TYPE_POINTER ",\n"    /*error-codes*/
  "  0,\n"
  " },\n\n";

  fprintf(ctx->mdata_struct, error_domain_struct, entry_id);

  fprintf(ctx->mdata_init, error_domain_header,
	  BLOB_TYPE_ERROR_DOMAIN,
	  domain->deprecated,
	  ctx->struct_name, g_idl_compiler_write_string (ctx, node->name),
	  ctx->struct_name, g_idl_compiler_write_string (ctx, domain->getquark),
	  ctx->struct_name, g_idl_compiler_get_entry_id (ctx, domain->codes));
}

/*CONSTANT*/
static void
write_constant (GIdlNode * node,
				    guint entry_id,
				    GIdlCompilerContext * ctx)
{
  const char *constant_struct =
  " ConstantBlob " ID_TO_ENTRY ";\n";

  fprintf(ctx->mdata_struct, constant_struct, entry_id);

  include_constant(node, ctx);
}

static void
write_deferred_constant_values(GIdlCompilerContext *ctx)
{
  /* TODO there are very few symbols that can be represented
   * as a constant, do we check if something is awry here
   * to prevent errors at compilation time?
   */
  GIdlNodeConstant *constant;
  guint entry_id;
  gchar *type_string;

  const char *cvalue_struct =
  " %s " ID_TO_ENTRY ";\n";

  const char *cvalue_str_struct =
  " gchar *" ID_TO_ENTRY ";\n";

  constant = (GIdlNodeConstant *) g_idl_compiler_pop_deferred_constant(ctx, &entry_id);
  while (constant != NULL)
    {
      fprintf(ctx->mdata_init, " /*Entry - %d*/\n",
              entry_id);
      if (constant->type->tag <= TYPE_TAG_DOUBLE)
	{
	  fprintf(ctx->mdata_struct, cvalue_struct,
	          g_idl_compiler_name_basic_type(constant->type->tag),
		  entry_id);
	  fprintf(ctx->mdata_init, " %s,\n",
	          constant->value);
	}
      else if (constant->type->tag <= TYPE_TAG_FILENAME)
	{
	  fprintf(ctx->mdata_struct, cvalue_str_struct,
		  entry_id);
	  fprintf(ctx->mdata_init, " \"%s\",\n",
	          constant->value);
	}
      else if (constant->type->tag <= TYPE_TAG_SYMBOL)
	{
	  GString *str;
	  gchar *s;

	  str = g_string_new (0);
	  g_idl_compiler_serialize_type (constant->type, str);
	  s = g_string_free (str, FALSE);

	  fprintf(ctx->mdata_struct, cvalue_struct,
		  s,
		  entry_id);
	  fprintf(ctx->mdata_init, " \"%s\",\n",
	          constant->value);
	  g_free(s);
	}
      else
	{
	  g_warning("Cannot write constant value");
	}
      constant = (GIdlNodeConstant *) g_idl_compiler_pop_deferred_constant(ctx, &entry_id);
    }
}

static void
write_deferred_signature_nodes(GIdlCompilerContext *ctx)
{
  GIdlNode *node;
  guint entry_id;

  node = g_idl_compiler_pop_deferred_signature_node(ctx, &entry_id);
  while (node != NULL)
    {
      fprintf(ctx->mdata_init, " /*Entry - %d*/\n",
              entry_id);
      write_signature(node, entry_id, ctx);
      node = g_idl_compiler_pop_deferred_signature_node(ctx, &entry_id);
    }
}

void
g_idl_compiler_write_node (GIdlNode * node,
			   guint entry_id, GIdlCompilerContext * ctx)
{
  GList *l;

  fprintf(ctx->mdata_init, " /*Entry - %d*/\n",
          entry_id);

  switch (node->type)
    {
    case G_IDL_NODE_FUNCTION:
      {
	write_function (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_CALLBACK:
      {
	write_callback (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_STRUCT:
      {
	write_struct (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_BOXED:
      {
	write_boxed (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_UNION:
      {
	write_union (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_ENUM:
    case G_IDL_NODE_FLAGS:
      {
	write_enum (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_OBJECT:
      {
	write_object (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_INTERFACE:
      {
	write_interface (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_ERROR_DOMAIN:
      {
	write_error_domain (node, entry_id, ctx);
      }
      break;

    case G_IDL_NODE_CONSTANT:
      {
	write_constant (node, entry_id, ctx);
      }
      break;
    default:
      g_assert_not_reached ();
    }

  write_deferred_constant_values(ctx);
  write_deferred_signature_nodes(ctx);
  g_idl_compiler_write_deferred_type_blobs(ctx);
}
