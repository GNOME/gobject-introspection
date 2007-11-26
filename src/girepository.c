/* GObject introspection: Repository implementation
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
#include <string.h>

#include <glib.h>
#include <glib/gprintf.h>
#include "girepository.h"
#include "gmetadata.h"

static GIRepository *default_repository = NULL;
static GHashTable *default_metadata = NULL;

struct _GIRepositoryPrivate 
{
  GHashTable *metadata;
};

G_DEFINE_TYPE (GIRepository, g_irepository, G_TYPE_OBJECT);

static void 
g_irepository_init (GIRepository *repository)
{
  repository->priv = G_TYPE_INSTANCE_GET_PRIVATE (repository, G_TYPE_IREPOSITORY,
						  GIRepositoryPrivate);
}

static void
g_irepository_finalize (GObject *object)
{
  GIRepository *repository = G_IREPOSITORY (object);

  g_hash_table_destroy (repository->priv->metadata);
  
  (* G_OBJECT_CLASS (g_irepository_parent_class)->finalize) (G_OBJECT (repository));
}

static void
g_irepository_class_init (GIRepositoryClass *class)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (class);

  gobject_class->finalize = g_irepository_finalize;

  g_type_class_add_private (class, sizeof (GIRepositoryPrivate)); 
}

void
g_irepository_register (GIRepository *repository, 
			const guchar *metadata)
{
  Header *header = (Header *)metadata;
  const gchar *name;
  GHashTable *table;

  if (repository != NULL)
    {
      if (repository->priv->metadata == NULL)
	repository->priv->metadata = g_hash_table_new (g_str_hash, g_str_equal);
      table = repository->priv->metadata;
    }
  else 
    {
      if (default_metadata == NULL)
	default_metadata = g_hash_table_new (g_str_hash, g_str_equal);
      table = default_metadata;
    }

  name = g_metadata_get_string (metadata, header->namespace);

  if (g_hash_table_lookup (table, name))
    {
      g_fprintf (stderr, "metadata (%p) for '%s' already registered\n",
		 metadata, name);

      return;
    }

  g_hash_table_insert (table, (void *)name, (void *)metadata);
}

void
g_irepository_unregister (GIRepository *repository, 
			  const guchar *metadata)
{
  Header *header = (Header *)metadata;
  const gchar *name;
  GHashTable *table;

  if (repository != NULL)
    table = repository->priv->metadata;
  else
    table = default_metadata;
  
  name = g_metadata_get_string (metadata, header->namespace);

  if (!g_hash_table_remove (table, name))
    {
      g_fprintf (stderr, "metadata (%p) for '%s' not registered\n",
		 metadata, name);
    }
}

gboolean
g_irepository_is_registered (GIRepository *repository, 
			     const gchar *namespace)
{
  GHashTable *table;

  if (repository != NULL)
    table = repository->priv->metadata;
  else
    table = default_metadata;

  return g_hash_table_lookup (table, namespace) != NULL;
}

GIRepository * 
g_irepository_get_default (void)
{
  if (default_repository == NULL) 
    { 
      default_repository = g_object_new (G_TYPE_IREPOSITORY, NULL);
      if (default_metadata == NULL)
	default_metadata = g_hash_table_new (g_str_hash, g_str_equal);
      default_repository->priv->metadata = default_metadata;
    }

  return default_repository; 
}

static void 
count_interfaces (gpointer key,
		  gpointer value,
		  gpointer data)
{
  guchar *metadata = (guchar *)value;
  gint *n_interfaces = (gint *)data;
  
  *n_interfaces += ((Header *)metadata)->n_local_entries;
}

gint                   
g_irepository_get_n_infos (GIRepository *repository,
			   const gchar  *namespace)
{
  gint n_interfaces = 0;
  if (namespace)
    {
      guchar *metadata;

      metadata = g_hash_table_lookup (repository->priv->metadata, namespace);

      if (metadata)
	n_interfaces = ((Header *)metadata)->n_local_entries;
    }
  else
    {
      g_hash_table_foreach (repository->priv->metadata, 
			    count_interfaces, &n_interfaces);
    }

  return n_interfaces;
}

typedef struct
{
  gint index;
  const gchar *name;
  const gchar *type;
  GIBaseInfo *iface;
} IfaceData;

static void
find_interface (gpointer key,
		gpointer value,
		gpointer data)
{
  gint i;
  guchar *metadata = (guchar *)value;
  IfaceData *iface_data = (IfaceData *)data;
  gint index;
  gint n_entries;
  guint32 offset;
  const gchar *name;
  const gchar *type;
  DirEntry *entry;    

  index = 0;
  n_entries = ((Header *)metadata)->n_local_entries;

  if (iface_data->name)
    {
      for (i = 1; i <= n_entries; i++)
	{
	  entry = g_metadata_get_dir_entry (metadata, i);
	  name = g_metadata_get_string (metadata, entry->name);
	  if (strcmp (name, iface_data->name) == 0)
	    {
	      index = i;
	      break;
	    }
	}
    }
  else if (iface_data->type)
    {
      for (i = 1; i <= n_entries; i++)
	{
	  entry = g_metadata_get_dir_entry (metadata, i);
	  if (entry->blob_type < 4)
	    continue;
	  
	  offset = *(guint32*)&metadata[entry->offset + 8];
	  type = g_metadata_get_string (metadata, offset);
	  if (strcmp (type, iface_data->type) == 0)
	    {
	      index = i;
	      break;
	    }
	}
    }
  else if (iface_data->index > n_entries)
    iface_data->index -= n_entries;
  else if (iface_data->index > 0)
    {
      index = iface_data->index;
      iface_data->index = 0;
    }

  if (index != 0)
    {
      entry = g_metadata_get_dir_entry (metadata, index);
      iface_data->iface = g_info_new (entry->blob_type, NULL,
				      metadata, entry->offset);
    }
}

GIBaseInfo * 
g_irepository_get_info (GIRepository *repository,
			const gchar  *namespace,
			gint          index)
{
  IfaceData data;

  data.name = NULL;
  data.type = NULL;
  data.index = index + 1;
  data.iface = NULL;

  if (namespace)
    {
      guchar *metadata;
      
      metadata = g_hash_table_lookup (repository->priv->metadata, namespace);
      
      if (metadata)
	find_interface ((void *)namespace, metadata, &data);
    }
  else
    g_hash_table_foreach (repository->priv->metadata, find_interface, &data);

  return data.iface;  
}

GIBaseInfo * 
g_irepository_find_by_gtype (GIRepository *repository,
			     GType         type)
{
  IfaceData data;

  data.name = NULL;
  data.type = g_type_name (type);
  data.index = -1;
  data.iface = NULL;

  g_hash_table_foreach (repository->priv->metadata, find_interface, &data);

  return data.iface;
}

GIBaseInfo * 
g_irepository_find_by_name (GIRepository *repository,
			    const gchar  *namespace,
			    const gchar  *name)
{
  IfaceData data;

  data.name = name;
  data.type = NULL;
  data.index = -1;
  data.iface = NULL;

  if (namespace)
    {
      guchar *metadata;
      
      metadata = g_hash_table_lookup (repository->priv->metadata, namespace);
      
      if (metadata)
	find_interface ((void *)namespace, metadata, &data);
    }
  else
    g_hash_table_foreach (repository->priv->metadata, find_interface, &data);

  return data.iface;
}

static void
collect_namespaces (gpointer key,
		    gpointer value,
		    gpointer data)
{
  GList **list = data;

  *list = g_list_append (*list, key);
}

gchar ** 
g_irepository_get_namespaces (GIRepository *repository)
{
  GList *l, *list = NULL;
  gchar **names;
  gint i;

  g_hash_table_foreach (repository->priv->metadata, collect_namespaces, &list);

  names = g_malloc0 (sizeof (gchar *) * (g_list_length (list) + 1));
  i = 0;
  for (l = list; l; l = l->next)
    names[i++] = g_strdup (l->data); 
  g_list_free (list);

  return names;
}
