/* GObject introspection: auxiliary functions related to the binary
 * metadata format
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

#include <glib.h>

#include "gmetadata.h"

DirEntry *
g_metadata_get_dir_entry (const guchar *metadata,
			  guint16       index)
{
  Header *header = (Header *)metadata;

  return (DirEntry *)&metadata[header->directory + index * header->entry_blob_size];
}

void    
g_metadata_check_sanity (void)
{
  /* Check that struct layout is as we expect */
  g_assert (sizeof (Header) == 80);
  g_assert (sizeof (DirEntry) == 12);
  g_assert (sizeof (SimpleTypeBlob) == 4);
  g_assert (sizeof (ArgBlob) == 12);
  g_assert (sizeof (SignatureBlob) == 8);
  g_assert (sizeof (CommonBlob) == 8);
  g_assert (sizeof (FunctionBlob) == 16);
  g_assert (sizeof (InterfaceTypeBlob) == 4);
  g_assert (sizeof (ArrayTypeBlob) == 8);
  g_assert (sizeof (ParamTypeBlob) == 4);
  g_assert (sizeof (ErrorTypeBlob) == 4);
  g_assert (sizeof (ErrorDomainBlob) == 16);
  g_assert (sizeof (ValueBlob) == 16);
  g_assert (sizeof (FieldBlob) == 12);
  g_assert (sizeof (RegisteredTypeBlob) == 16);
  g_assert (sizeof (StructBlob) == 20);
  g_assert (sizeof (EnumBlob) == 20);
  g_assert (sizeof (PropertyBlob) == 12);
  g_assert (sizeof (SignalBlob) == 12);
  g_assert (sizeof (VFuncBlob) == 16);
  g_assert (sizeof (ObjectBlob) == 32);
  g_assert (sizeof (InterfaceBlob) == 28);
  g_assert (sizeof (ConstantBlob) == 20);
  g_assert (sizeof (AnnotationBlob) == 12);
}


