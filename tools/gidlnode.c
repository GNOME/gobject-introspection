/* GObject introspection: Metadata creation
 *
 * Copyright (C) 2005 Matthias Clasen
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

#include "gidlmodule.h"
#include "gidlnode.h"
#include "gmetadata.h"

GIdlNode *
g_idl_node_new (GIdlNodeTypeId type)
{
  GIdlNode *node = NULL;

  switch (type)
    {
   case G_IDL_NODE_FUNCTION:
   case G_IDL_NODE_CALLBACK:
      node = g_malloc0 (sizeof (GIdlNodeFunction));
      break;

   case G_IDL_NODE_PARAM:
      node = g_malloc0 (sizeof (GIdlNodeParam));
      break;

   case G_IDL_NODE_TYPE:
      node = g_malloc0 (sizeof (GIdlNodeType));
      break;

    case G_IDL_NODE_OBJECT:
    case G_IDL_NODE_INTERFACE:
      node = g_malloc0 (sizeof (GIdlNodeInterface));
      break;

    case G_IDL_NODE_SIGNAL:
      node = g_malloc0 (sizeof (GIdlNodeSignal));
      break;

    case G_IDL_NODE_PROPERTY:
      node = g_malloc0 (sizeof (GIdlNodeProperty));
      break;

    case G_IDL_NODE_VFUNC:
      node = g_malloc0 (sizeof (GIdlNodeFunction));
      break;

    case G_IDL_NODE_FIELD:
      node = g_malloc0 (sizeof (GIdlNodeField));
      break;

    case G_IDL_NODE_ENUM:
    case G_IDL_NODE_FLAGS:
      node = g_malloc0 (sizeof (GIdlNodeEnum));
      break;

    case G_IDL_NODE_BOXED:
      node = g_malloc0 (sizeof (GIdlNodeBoxed));
      break;

    case G_IDL_NODE_STRUCT:
      node = g_malloc0 (sizeof (GIdlNodeStruct));
      break;

    case G_IDL_NODE_VALUE:
      node = g_malloc0 (sizeof (GIdlNodeValue));
      break;

    case G_IDL_NODE_CONSTANT:
      node = g_malloc0 (sizeof (GIdlNodeConstant));
      break;

    case G_IDL_NODE_ERROR_DOMAIN:
      node = g_malloc0 (sizeof (GIdlNodeErrorDomain));
      break;

    case G_IDL_NODE_XREF:
      node = g_malloc0 (sizeof (GIdlNodeXRef));
      break;

    case G_IDL_NODE_UNION:
      node = g_malloc0 (sizeof (GIdlNodeUnion));
      break;

    default:
      g_error ("Unhandled node type %d\n", type);
      break;
    }

  node->type = type;

  return node;
}

void
g_idl_node_free (GIdlNode *node)
{
  GList *l;

  if (node == NULL)
    return;

  switch (node->type)
    {
    case G_IDL_NODE_FUNCTION:
    case G_IDL_NODE_CALLBACK:
      {
	GIdlNodeFunction *function = (GIdlNodeFunction *)node;
	
	g_free (node->name);
	g_free (function->symbol);
	g_idl_node_free ((GIdlNode *)function->result);
	for (l = function->parameters; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (function->parameters);
      }
      break;

    case G_IDL_NODE_TYPE:
      {
	GIdlNodeType *type = (GIdlNodeType *)node;
	
	g_free (node->name);
	g_idl_node_free ((GIdlNode *)type->parameter_type1);
	g_idl_node_free ((GIdlNode *)type->parameter_type2);

	g_free (type->interface);
	g_strfreev (type->errors);

      }
      break;

    case G_IDL_NODE_PARAM:
      {
	GIdlNodeParam *param = (GIdlNodeParam *)node;
	
	g_free (node->name);
	g_idl_node_free ((GIdlNode *)param->type);
      }
      break;

    case G_IDL_NODE_PROPERTY:
      {
	GIdlNodeProperty *property = (GIdlNodeProperty *)node;
	
	g_free (node->name);
	g_idl_node_free ((GIdlNode *)property->type);
      }
      break;

    case G_IDL_NODE_SIGNAL:
      {
	GIdlNodeSignal *signal = (GIdlNodeSignal *)node;
	
	g_free (node->name);
	for (l = signal->parameters; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (signal->parameters);
	g_idl_node_free ((GIdlNode *)signal->result);
      }
      break;

    case G_IDL_NODE_VFUNC:
      {
	GIdlNodeVFunc *vfunc = (GIdlNodeVFunc *)node;
	
	g_free (node->name);
	for (l = vfunc->parameters; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (vfunc->parameters);
	g_idl_node_free ((GIdlNode *)vfunc->result);
      }
      break;

    case G_IDL_NODE_FIELD:
      {
	GIdlNodeField *field = (GIdlNodeField *)node;
	
	g_free (node->name);
	g_idl_node_free ((GIdlNode *)field->type);
      }
      break;

    case G_IDL_NODE_OBJECT:
    case G_IDL_NODE_INTERFACE:
      {
	GIdlNodeInterface *iface = (GIdlNodeInterface *)node;
	
	g_free (node->name);
	g_free (iface->gtype_name);
	g_free (iface->gtype_init);
	
	g_free (iface->parent);

	for (l = iface->interfaces; l; l = l->next)
	  g_free ((GIdlNode *)l->data);
	g_list_free (iface->interfaces);

	for (l = iface->members; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (iface->members);

      }
      break;
 
    case G_IDL_NODE_VALUE:
      {
	g_free (node->name);
      }
      break;

    case G_IDL_NODE_ENUM:
    case G_IDL_NODE_FLAGS:
      {
	GIdlNodeEnum *enum_ = (GIdlNodeEnum *)node;
	
	g_free (node->name);
	g_free (enum_->gtype_name);
	g_free (enum_->gtype_init);

	for (l = enum_->values; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (enum_->values);
      }
      break;

    case G_IDL_NODE_BOXED:
      {
	GIdlNodeBoxed *boxed = (GIdlNodeBoxed *)node;
	
	g_free (node->name);
	g_free (boxed->gtype_name);
	g_free (boxed->gtype_init);

	for (l = boxed->members; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (boxed->members);
      }
      break;

    case G_IDL_NODE_STRUCT:
      {
	GIdlNodeStruct *struct_ = (GIdlNodeStruct *)node;

	g_free (node->name);
	for (l = struct_->members; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	g_list_free (struct_->members);
      }
      break;

    case G_IDL_NODE_CONSTANT:
      {
	GIdlNodeConstant *constant = (GIdlNodeConstant *)node;
	
	g_free (node->name);
	g_free (constant->value);
	g_idl_node_free ((GIdlNode *)constant->type);
      }
      break;

    case G_IDL_NODE_ERROR_DOMAIN:
      {
	GIdlNodeErrorDomain *domain = (GIdlNodeErrorDomain *)node;
	
	g_free (node->name);
	g_free (domain->getquark);
	g_free (domain->codes);
      }
      break;

    case G_IDL_NODE_XREF:
      {
	GIdlNodeXRef *xref = (GIdlNodeXRef *)node;
	
	g_free (node->name);
	g_free (xref->namespace);
      }
      break;

    case G_IDL_NODE_UNION:
      {
	GIdlNodeUnion *union_ = (GIdlNodeUnion *)node;
	
	g_free (node->name);
	g_free (union_->gtype_name);
	g_free (union_->gtype_init);

	g_idl_node_free ((GIdlNode *)union_->discriminator_type);
	for (l = union_->members; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
	for (l = union_->discriminators; l; l = l->next)
	  g_idl_node_free ((GIdlNode *)l->data);
      }
      break;

    default:
      g_error ("Unhandled node type %d\n", node->type);
      break;
    } 

  g_free (node);
}

int
g_idl_node_cmp (GIdlNode *node,
		GIdlNode *other)
{
  if (node->type < other->type)
    return -1;
  else if (node->type > other->type)
    return 1;
  else
    return strcmp (node->name, other->name);
}

gboolean
g_idl_node_can_have_member (GIdlNode    *node)
{
  switch (node->type)
    {
    case G_IDL_NODE_OBJECT:
    case G_IDL_NODE_INTERFACE:
    case G_IDL_NODE_BOXED:
    case G_IDL_NODE_STRUCT:
    case G_IDL_NODE_UNION:
      return TRUE;
    };
  return FALSE;
}

void
g_idl_node_add_member (GIdlNode         *node,
		       GIdlNodeFunction *member)
{
  g_return_if_fail (node != NULL);
  g_return_if_fail (member != NULL);
		    
  switch (node->type)
    {
    case G_IDL_NODE_OBJECT:
    case G_IDL_NODE_INTERFACE:
      {
	GIdlNodeInterface *iface = (GIdlNodeInterface *)node;
	iface->members =
	  g_list_insert_sorted (iface->members, member,
				(GCompareFunc) g_idl_node_cmp);
	break;
      }
    case G_IDL_NODE_BOXED:
      {
	GIdlNodeBoxed *boxed = (GIdlNodeBoxed *)node;
	boxed->members =
	  g_list_insert_sorted (boxed->members, member,
				(GCompareFunc) g_idl_node_cmp);
	break;
      }
    case G_IDL_NODE_STRUCT:
      {
	GIdlNodeStruct *struct_ = (GIdlNodeStruct *)node;
	struct_->members =
	  g_list_insert_sorted (struct_->members, member,
				(GCompareFunc) g_idl_node_cmp);
	break;
      }
    case G_IDL_NODE_UNION:
      {
	GIdlNodeUnion *union_ = (GIdlNodeUnion *)node;
	union_->members =
	  g_list_insert_sorted (union_->members, member,
				(GCompareFunc) g_idl_node_cmp);
	break;
      }
    default:
      g_error ("Cannot add a member to unknown type tag type %d\n",
	       node->type);
      break;
    }
}

const gchar *
g_idl_node_param_direction_string (GIdlNodeParam * node)
{
  if (node->out)
    {
      if (node->in)
	return "in-out";
      else
	return "out";
    }
  return "in";
}

static gint64
parse_int_value (const gchar *str)
{
  return strtoll (str, NULL, 0);
}

static guint64
parse_uint_value (const gchar *str)
{
  return strtoull (str, NULL, 0);
}

static gdouble
parse_float_value (const gchar *str)
{
  return strtod (str, NULL);
}

static gboolean
parse_boolean_value (const gchar *str)
{
  if (strcmp (str, "TRUE") == 0)
    return TRUE;
  
  if (strcmp (str, "FALSE") == 0)
    return FALSE;

  return parse_int_value (str) ? TRUE : FALSE;
}

static GIdlNode *
find_entry_node (GIdlModule  *module,
		 GList       *modules,
		 const gchar *name,
		 guint16     *idx)

{
  GList *l;
  gint i;
  gchar **names;
  gint n_names;
  GIdlNode *result = NULL;

  names = g_strsplit (name, ".", 0);
  n_names = g_strv_length (names);
  if (n_names > 2)
    g_error ("Too many name parts");
  
  for (l = module->entries, i = 1; l; l = l->next, i++)
    {
      GIdlNode *node = (GIdlNode *)l->data;
      
      if (n_names > 1)
	{
	  if (node->type != G_IDL_NODE_XREF)
	    continue;
	  
	  if (((GIdlNodeXRef *)node)->namespace == NULL ||
	      strcmp (((GIdlNodeXRef *)node)->namespace, names[0]) != 0)
	    continue;
	}
	 
      if (strcmp (node->name, names[n_names - 1]) == 0)
	{
	  if (idx)
	    *idx = i;
	  
	  result = node;
	  goto out;
	}
    }

  if (n_names > 1)
    {
      GIdlNode *node = g_idl_node_new (G_IDL_NODE_XREF);

      ((GIdlNodeXRef *)node)->namespace = g_strdup (names[0]);
      node->name = g_strdup (names[1]);
  
      module->entries = g_list_append (module->entries, node);
  
      if (idx)
	*idx = g_list_length (module->entries);

      result = node;

      goto out;
    }

  g_warning ("Entry %s not found", name);

 out:

  g_strfreev (names);

  return result;
}

static guint16
find_entry (GIdlModule  *module,
	    GList       *modules,
	    const gchar *name)
{
  guint16 idx = 0;

  find_entry_node (module, modules, name, &idx);

  return idx;
}

