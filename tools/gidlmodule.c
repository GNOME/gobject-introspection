/* GObject introspection: Metadata creation 
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
#include <string.h>

#include "gidlmodule.h"
#include "gidlnode.h"

GIdlModule *
g_idl_module_new (const gchar *name, const gchar *shared_library)
{
  GIdlModule *module;

  module = g_new (GIdlModule, 1);

  module->name = g_strdup (name);
  if (shared_library)
      module->shared_library = g_strdup (shared_library);
  else
      module->shared_library = NULL;
  module->entries = NULL;

  return module;
}

void
g_idl_module_free (GIdlModule *module)
{
  GList *e;

  g_free (module->name);

  for (e = module->entries; e; e = e->next)
    g_idl_node_free ((GIdlNode *)e->data);

  g_list_free (module->entries);

  g_free (module);
}
