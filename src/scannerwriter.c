/* GObject introspection: gen-introspect
 *
 * Copyright (C) 2007  Jürg Billeter
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
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
 *
 * Author:
 * 	Jürg Billeter <j@bitron.ch>
 */

#include <stdio.h>
#include <glib.h>
#include "scanner.h"
#include "gidlnode.h"

static void node_generate (GIGenerator * igenerator, GIdlNode * node);

static void
g_igenerator_write_inline (GIGenerator * igenerator, const char *s)
{
  fprintf (stdout, "%s", s);
}

static void
g_igenerator_write (GIGenerator * igenerator, const char *s)
{
  int i;
  for (i = 0; i < igenerator->indent; i++)
    {
      fprintf (stdout, "\t");
    }

  g_igenerator_write_inline (igenerator, s);
}

static void
g_igenerator_write_indent (GIGenerator * igenerator, const char *s)
{
  g_igenerator_write (igenerator, s);
  igenerator->indent++;
}

static void
g_igenerator_write_unindent (GIGenerator * igenerator, const char *s)
{
  igenerator->indent--;
  g_igenerator_write (igenerator, s);
}

static void
field_generate (GIGenerator * igenerator, GIdlNodeField * node)
{
  char *markup =
    g_markup_printf_escaped ("<field name=\"%s\" type=\"%s\"/>\n",
			     node->node.name, node->type->unparsed);
  g_igenerator_write (igenerator, markup);
  g_free (markup);
}

static void
value_generate (GIGenerator * igenerator, GIdlNodeValue * node)
{
  char *markup =
    g_markup_printf_escaped ("<member name=\"%s\" value=\"%d\"/>\n",
			     node->node.name, node->value);
  g_igenerator_write (igenerator, markup);
  g_free (markup);
}

static void
constant_generate (GIGenerator * igenerator, GIdlNodeConstant * node)
{
  char *markup =
    g_markup_printf_escaped
    ("<constant name=\"%s\" type=\"%s\" value=\"%s\"/>\n", node->node.name,
     node->type->unparsed, node->value);
  g_igenerator_write (igenerator, markup);
  g_free (markup);
}

static void
property_generate (GIGenerator * igenerator, GIdlNodeProperty * node)
{
  char *markup =
    g_markup_printf_escaped ("<property name=\"%s\" "
			     "type=\"%s\" "
			     "readable=\"%s\" "
			     "writable=\"%s\" "
			     "construct=\"%s\" "
			     "construct-only=\"%s\"/>\n",
			     node->node.name,
			     node->type->unparsed,
			     node->readable ? "1" : "0",
			     node->writable ? "1" : "0",
			     node->construct ? "1" : "0",
			     node->construct_only ? "1" : "0");
  g_igenerator_write (igenerator, markup);
  g_free (markup);
}

static void
function_generate (GIGenerator * igenerator, GIdlNodeFunction * node)
{
  char *markup;
  const char *tag_name;
  if (node->node.type == G_IDL_NODE_CALLBACK)
    {
      tag_name = "callback";
      markup =
	g_markup_printf_escaped ("<callback name=\"%s\">\n", node->node.name);
    }
  else if (node->is_constructor)
    {
      tag_name = "constructor";
      markup =
	g_markup_printf_escaped ("<constructor name=\"%s\" symbol=\"%s\">\n",
				 node->node.name, node->symbol);
    }
  else if (node->is_method)
    {
      tag_name = "method";
      markup =
	g_markup_printf_escaped ("<method name=\"%s\" symbol=\"%s\">\n",
				 node->node.name, node->symbol);
    }
  else
    {
      tag_name = "function";
      markup =
	g_markup_printf_escaped ("<function name=\"%s\" symbol=\"%s\">\n",
				 node->node.name, node->symbol);
    }

  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  markup =
    g_markup_printf_escaped ("<return-type type=\"%s\"/>\n",
			     node->result->type->unparsed);
  g_igenerator_write (igenerator, markup);
  g_free (markup);
  if (node->parameters != NULL)
    {
      GList *l;
      g_igenerator_write_indent (igenerator, "<parameters>\n");
      for (l = node->parameters; l != NULL; l = l->next)
	{
	  GIdlNodeParam *param = l->data;
	  markup =
	    g_markup_printf_escaped ("<parameter name=\"%s\" type=\"%s\"/>\n",
				     param->node.name, param->type->unparsed);
	  g_igenerator_write (igenerator, markup);
	  g_free (markup);
	}
      g_igenerator_write_unindent (igenerator, "</parameters>\n");
    }
  markup = g_strdup_printf ("</%s>\n", tag_name);
  g_igenerator_write_unindent (igenerator, markup);
  g_free (markup);
}

static void
vfunc_generate (GIGenerator * igenerator, GIdlNodeVFunc * node)
{
  char *markup =
    g_markup_printf_escaped ("<vfunc name=\"%s\">\n", node->node.name);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  markup =
    g_markup_printf_escaped ("<return-type type=\"%s\"/>\n",
			     node->result->type->unparsed);
  g_igenerator_write (igenerator, markup);
  g_free (markup);
  if (node->parameters != NULL)
    {
      GList *l;
      g_igenerator_write_indent (igenerator, "<parameters>\n");
      for (l = node->parameters; l != NULL; l = l->next)
	{
	  GIdlNodeParam *param = l->data;
	  markup =
	    g_markup_printf_escaped ("<parameter name=\"%s\" type=\"%s\"/>\n",
				     param->node.name, param->type->unparsed);
	  g_igenerator_write (igenerator, markup);
	  g_free (markup);
	}
      g_igenerator_write_unindent (igenerator, "</parameters>\n");
    }
  g_igenerator_write_unindent (igenerator, "</vfunc>\n");
}

static void
signal_generate (GIGenerator * igenerator, GIdlNodeSignal * node)
{
  char *markup;
  const char *when = "LAST";
  if (node->run_first)
    {
      when = "FIRST";
    }
  else if (node->run_cleanup)
    {
      when = "CLEANUP";
    }
  markup =
    g_markup_printf_escaped ("<signal name=\"%s\" when=\"%s\">\n",
			     node->node.name, when);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  markup =
    g_markup_printf_escaped ("<return-type type=\"%s\"/>\n",
			     node->result->type->unparsed);
  g_igenerator_write (igenerator, markup);
  g_free (markup);
  if (node->parameters != NULL)
    {
      GList *l;
      g_igenerator_write_indent (igenerator, "<parameters>\n");
      for (l = node->parameters; l != NULL; l = l->next)
	{
	  GIdlNodeParam *param = l->data;
	  markup =
	    g_markup_printf_escaped ("<parameter name=\"%s\" type=\"%s\"/>\n",
				     param->node.name, param->type->unparsed);
	  g_igenerator_write (igenerator, markup);
	  g_free (markup);
	}
      g_igenerator_write_unindent (igenerator, "</parameters>\n");
    }
  g_igenerator_write_unindent (igenerator, "</signal>\n");
}

static void
interface_generate (GIGenerator * igenerator, GIdlNodeInterface * node)
{
  GList *l;
  char *markup;
  if (node->node.type == G_IDL_NODE_OBJECT)
    {
      markup =
	g_markup_printf_escaped ("<object name=\"%s\" "
				 "parent=\"%s\" "
				 "type-name=\"%s\" "
				 "get-type=\"%s\">\n",
				 node->node.name,
				 node->parent,
				 node->gtype_name,
				 node->gtype_init);
    }
  else if (node->node.type == G_IDL_NODE_INTERFACE)
    {
      markup =
	g_markup_printf_escaped
	("<interface name=\"%s\" type-name=\"%s\" get-type=\"%s\">\n",
	 node->node.name, node->gtype_name, node->gtype_init);
    }

  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  if (node->node.type == G_IDL_NODE_OBJECT && node->interfaces != NULL)
    {
      GList *l;
      g_igenerator_write_indent (igenerator, "<implements>\n");
      for (l = node->interfaces; l != NULL; l = l->next)
	{
	  markup =
	    g_markup_printf_escaped ("<interface name=\"%s\"/>\n",
				     (char *) l->data);
	  g_igenerator_write (igenerator, markup);
	  g_free (markup);
	}
      g_igenerator_write_unindent (igenerator, "</implements>\n");
    }
  else if (node->node.type == G_IDL_NODE_INTERFACE
	   && node->prerequisites != NULL)
    {
      GList *l;
      g_igenerator_write_indent (igenerator, "<requires>\n");
      for (l = node->prerequisites; l != NULL; l = l->next)
	{
	  markup =
	    g_markup_printf_escaped ("<interface name=\"%s\"/>\n",
				     (char *) l->data);
	  g_igenerator_write (igenerator, markup);
	  g_free (markup);
	}
      g_igenerator_write_unindent (igenerator, "</requires>\n");
    }

  for (l = node->members; l != NULL; l = l->next)
    {
      node_generate (igenerator, l->data);
    }

  if (node->node.type == G_IDL_NODE_OBJECT)
    {
      g_igenerator_write_unindent (igenerator, "</object>\n");
    }
  else if (node->node.type == G_IDL_NODE_INTERFACE)
    {
      g_igenerator_write_unindent (igenerator, "</interface>\n");
    }
}

static void
struct_generate (GIGenerator * igenerator, GIdlNodeStruct * node)
{
  GList *l;
  char *markup =
    g_markup_printf_escaped ("<struct name=\"%s\">\n", node->node.name);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  for (l = node->members; l != NULL; l = l->next)
    {
      node_generate (igenerator, l->data);
    }
  g_igenerator_write_unindent (igenerator, "</struct>\n");
}

static void
union_generate (GIGenerator * igenerator, GIdlNodeUnion * node)
{
  GList *l;
  char *markup =
    g_markup_printf_escaped ("<union name=\"%s\">\n", node->node.name);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  for (l = node->members; l != NULL; l = l->next)
    {
      node_generate (igenerator, l->data);
    }
  g_igenerator_write_unindent (igenerator, "</union>\n");
}

static void
boxed_generate (GIGenerator * igenerator, GIdlNodeBoxed * node)
{
  GList *l;
  char *markup =
    g_markup_printf_escaped
    ("<boxed name=\"%s\" type-name=\"%s\" get-type=\"%s\">\n",
     node->node.name, node->gtype_name, node->gtype_init);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  for (l = node->members; l != NULL; l = l->next)
    {
      node_generate (igenerator, l->data);
    }
  g_igenerator_write_unindent (igenerator, "</boxed>\n");
}

static void
enum_generate (GIGenerator * igenerator, GIdlNodeEnum * node)
{
  GList *l;
  char *markup;
  const char *tag_name = NULL;

  if (node->node.type == G_IDL_NODE_ENUM)
    {
      tag_name = "enum";
    }
  else if (node->node.type == G_IDL_NODE_FLAGS)
    {
      tag_name = "flags";
    }
  markup =
    g_markup_printf_escaped ("<%s name=\"%s\">\n", tag_name, node->node.name);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);

  for (l = node->values; l != NULL; l = l->next)
    {
      node_generate (igenerator, l->data);
    }

  markup = g_strdup_printf ("</%s>\n", tag_name);
  g_igenerator_write_unindent (igenerator, markup);
  g_free (markup);
}

static void
node_generate (GIGenerator * igenerator, GIdlNode * node)
{
  switch (node->type)
    {
    case G_IDL_NODE_FUNCTION:
    case G_IDL_NODE_CALLBACK:
      function_generate (igenerator, (GIdlNodeFunction *) node);
      break;
    case G_IDL_NODE_VFUNC:
      vfunc_generate (igenerator, (GIdlNodeVFunc *) node);
      break;
    case G_IDL_NODE_OBJECT:
    case G_IDL_NODE_INTERFACE:
      interface_generate (igenerator, (GIdlNodeInterface *) node);
      break;
    case G_IDL_NODE_STRUCT:
      struct_generate (igenerator, (GIdlNodeStruct *) node);
      break;
    case G_IDL_NODE_UNION:
      union_generate (igenerator, (GIdlNodeUnion *) node);
      break;
    case G_IDL_NODE_BOXED:
      boxed_generate (igenerator, (GIdlNodeBoxed *) node);
      break;
    case G_IDL_NODE_ENUM:
    case G_IDL_NODE_FLAGS:
      enum_generate (igenerator, (GIdlNodeEnum *) node);
      break;
    case G_IDL_NODE_PROPERTY:
      property_generate (igenerator, (GIdlNodeProperty *) node);
      break;
    case G_IDL_NODE_FIELD:
      field_generate (igenerator, (GIdlNodeField *) node);
      break;
    case G_IDL_NODE_SIGNAL:
      signal_generate (igenerator, (GIdlNodeSignal *) node);
      break;
    case G_IDL_NODE_VALUE:
      value_generate (igenerator, (GIdlNodeValue *) node);
      break;
    case G_IDL_NODE_CONSTANT:
      constant_generate (igenerator, (GIdlNodeConstant *) node);
      break;
    default:
      g_assert_not_reached ();
    }
}

static void
module_generate (GIGenerator * igenerator, GIdlModule * module)
{
  GList *l;
  char *markup =
    g_markup_printf_escaped ("<namespace name=\"%s\">\n", module->name);
  g_igenerator_write_indent (igenerator, markup);
  g_free (markup);
  for (l = module->entries; l != NULL; l = l->next)
    {
      node_generate (igenerator, l->data);
    }
  g_igenerator_write_unindent (igenerator, "</namespace>\n");
}

void
g_scanner_write_file (GIGenerator *igenerator)
{
  g_igenerator_write (igenerator, "<?xml version=\"1.0\"?>\n");
  g_igenerator_write_indent (igenerator, "<api version=\"1.0\">\n");
  module_generate (igenerator, igenerator->module);
  g_igenerator_write_unindent (igenerator, "</api>\n");
}
