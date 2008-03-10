/* GObject introspection: Parsed IDL
 *
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

#ifndef __G_IDL_COMP_TYPE_N_H__
#define __G_IDL_COMP_TYPE_N_H__

#include <glib.h>

#include "gidlnode.h"
#include "gidlcompilercontext.h"

G_BEGIN_DECLS

const gchar *
g_idl_compiler_name_basic_type(guint type_tag);

void
g_idl_compiler_serialize_type (GIdlNodeType * node, GString * str);

void
g_idl_compiler_write_deferred_type_blobs (GIdlCompilerContext *ctx);

void
g_idl_compiler_write_simple_type_blob (GIdlNode * node, GIdlCompilerContext * ctx);

G_END_DECLS
#endif /* __G_IDL_COMP_TYPE_N_H__ */
