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

#ifndef __GEN_INTROSPECT_H__
#define __GEN_INTROSPECT_H__

#include <glib.h>
#include "gidlmodule.h"
#include "sourcescanner.h"

G_BEGIN_DECLS
typedef struct _GIGenerator GIGenerator;

struct _GIGenerator
{
  /* parameters */
  char *namespace;
  char *shared_library;
  char *lower_case_namespace;
  gboolean verbose;

  GIdlModule *module;
  GList *get_type_symbols;
  GHashTable *type_map;
  GHashTable *type_by_lower_case_prefix;

  GHashTable *symbols; /* typename -> module.name */

  GISourceScanner *scanner;
};

void     g_igenerator_set_verbose   (GIGenerator *igenerator,
				     gboolean     verbose);

G_END_DECLS

#endif /* __SCANNER_H__ */
