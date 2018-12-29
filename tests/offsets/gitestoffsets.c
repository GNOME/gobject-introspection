/*
 * Copyright (C) 2008 Red Hat, Inc.
 * Copyright (C) 2018 Tomasz Miąsko
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * The idea here is that we want to compare offset information two ways:
 *
 *  1) As generated by the compiler
 *  2) As found in the typelib
 *
 * So we write the field offsets using G_STRUCT_OFFSET() to one file and the
 * field offsets using the typelib to the another file. We can then diff the
 * two files to see if they are the same.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <girepository.h>
#include "offsets.h"

#define ALIGNOF(T) G_STRUCT_OFFSET(struct {char a; T b;}, b)

static GIRepository *repository;
static const char *namespace = "Offsets";
static const char *version = "1.0";

static void
introspected_struct (FILE *outfile, const gchar *name)
{
  gint i, n_fields;
  GIStructInfo *struct_info;

  struct_info = g_irepository_find_by_name(repository, namespace, name);
  if (!struct_info)
     g_error ("Can't find GIStructInfo for '%s'", name);

  fprintf (outfile, "%s%s: size=%" G_GSIZE_FORMAT ", alignment=%" G_GSIZE_FORMAT "\n",
           namespace, name,
           g_struct_info_get_size (struct_info),
           g_struct_info_get_alignment (struct_info));

   n_fields = g_struct_info_get_n_fields (struct_info);
   for (i = 0; i != n_fields; ++i)
     {
       GIFieldInfo *field_info;

       field_info = g_struct_info_get_field (struct_info, i);

       fprintf (outfile, "%s %d\n",
                g_base_info_get_name ((GIBaseInfo *) field_info),
                g_field_info_get_offset (field_info));

       g_base_info_unref ((GIBaseInfo *)field_info);
     }

  fprintf (outfile, "\n");

  g_base_info_unref ((GIBaseInfo *)struct_info);
}

static void
compiled (FILE *outfile)
{
  fprintf (outfile, "OffsetsArray: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsArray), ALIGNOF(OffsetsArray));
  fprintf (outfile, "%s %ld\n", "some_ints", G_STRUCT_OFFSET(OffsetsArray, some_ints));
  fprintf (outfile, "%s %ld\n", "some_int8s", G_STRUCT_OFFSET(OffsetsArray, some_int8s));
  fprintf (outfile, "%s %ld\n", "some_doubles", G_STRUCT_OFFSET(OffsetsArray, some_doubles));
  fprintf (outfile, "%s %ld\n", "some_enum", G_STRUCT_OFFSET(OffsetsArray, some_enum));
  fprintf (outfile, "%s %ld\n", "some_ptrs", G_STRUCT_OFFSET(OffsetsArray, some_ptrs));
  fprintf (outfile, "\n");

  fprintf (outfile, "OffsetsBasic: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsBasic), ALIGNOF(OffsetsBasic));
  fprintf (outfile, "%s %ld\n", "dummy1", G_STRUCT_OFFSET(OffsetsBasic, dummy1));
  fprintf (outfile, "%s %ld\n", "field_int8", G_STRUCT_OFFSET(OffsetsBasic, field_int8));
  fprintf (outfile, "%s %ld\n", "dummy2", G_STRUCT_OFFSET(OffsetsBasic, dummy2));
  fprintf (outfile, "%s %ld\n", "field_int16", G_STRUCT_OFFSET(OffsetsBasic, field_int16));
  fprintf (outfile, "%s %ld\n", "dummy3", G_STRUCT_OFFSET(OffsetsBasic, dummy3));
  fprintf (outfile, "%s %ld\n", "field_int32", G_STRUCT_OFFSET(OffsetsBasic, field_int32));
  fprintf (outfile, "%s %ld\n", "dummy4", G_STRUCT_OFFSET(OffsetsBasic, dummy4));
  fprintf (outfile, "%s %ld\n", "field_int64", G_STRUCT_OFFSET(OffsetsBasic, field_int64));
  fprintf (outfile, "%s %ld\n", "dummy5", G_STRUCT_OFFSET(OffsetsBasic, dummy5));
  fprintf (outfile, "%s %ld\n", "field_pointer", G_STRUCT_OFFSET(OffsetsBasic, field_pointer));
  fprintf (outfile, "%s %ld\n", "dummy6", G_STRUCT_OFFSET(OffsetsBasic, dummy6));
  fprintf (outfile, "%s %ld\n", "field_float", G_STRUCT_OFFSET(OffsetsBasic, field_float));
  fprintf (outfile, "%s %ld\n", "dummy7", G_STRUCT_OFFSET(OffsetsBasic, dummy7));
  fprintf (outfile, "%s %ld\n", "field_double", G_STRUCT_OFFSET(OffsetsBasic, field_double));
  fprintf (outfile, "%s %ld\n", "dummy8", G_STRUCT_OFFSET(OffsetsBasic, dummy8));
  fprintf (outfile, "%s %ld\n", "field_size", G_STRUCT_OFFSET(OffsetsBasic, field_size));
  fprintf (outfile, "\n");

  fprintf (outfile, "OffsetsEnum: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsEnum), ALIGNOF(OffsetsEnum));
  fprintf (outfile, "%s %ld\n", "enum1", G_STRUCT_OFFSET(OffsetsEnum, enum1));
  fprintf (outfile, "%s %ld\n", "dummy1", G_STRUCT_OFFSET(OffsetsEnum, dummy1));
  fprintf (outfile, "%s %ld\n", "enum2", G_STRUCT_OFFSET(OffsetsEnum, enum2));
  fprintf (outfile, "%s %ld\n", "dummy2", G_STRUCT_OFFSET(OffsetsEnum, dummy2));
  fprintf (outfile, "%s %ld\n", "enum3", G_STRUCT_OFFSET(OffsetsEnum, enum3));
  fprintf (outfile, "%s %ld\n", "dummy3", G_STRUCT_OFFSET(OffsetsEnum, dummy3));
  fprintf (outfile, "%s %ld\n", "enum4", G_STRUCT_OFFSET(OffsetsEnum, enum4));
  fprintf (outfile, "%s %ld\n", "dummy4", G_STRUCT_OFFSET(OffsetsEnum, dummy4));
  fprintf (outfile, "%s %ld\n", "enum5", G_STRUCT_OFFSET(OffsetsEnum, enum5));
  fprintf (outfile, "%s %ld\n", "dummy5", G_STRUCT_OFFSET(OffsetsEnum, dummy5));
  fprintf (outfile, "%s %ld\n", "enum6", G_STRUCT_OFFSET(OffsetsEnum, enum6));
  fprintf (outfile, "%s %ld\n", "dummy6", G_STRUCT_OFFSET(OffsetsEnum, dummy6));
  fprintf (outfile, "\n");

  fprintf (outfile, "OffsetsNested: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsNested), ALIGNOF(OffsetsNested));
  fprintf (outfile, "%s %ld\n", "dummy1", G_STRUCT_OFFSET(OffsetsNested, dummy1));
  fprintf (outfile, "%s %ld\n", "nestee", G_STRUCT_OFFSET(OffsetsNested, nestee));
  fprintf (outfile, "%s %ld\n", "dummy2", G_STRUCT_OFFSET(OffsetsNested, dummy2));
  fprintf (outfile, "%s %ld\n", "nestee_union", G_STRUCT_OFFSET(OffsetsNested, nestee_union));
  fprintf (outfile, "%s %ld\n", "dummy3", G_STRUCT_OFFSET(OffsetsNested, dummy3));
  fprintf (outfile, "\n");

  fprintf (outfile, "OffsetsNestee: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsNestee), ALIGNOF(OffsetsNestee));
  fprintf (outfile, "%s %ld\n", "field1", G_STRUCT_OFFSET(OffsetsNestee, field1));
  fprintf (outfile, "%s %ld\n", "field2", G_STRUCT_OFFSET(OffsetsNestee, field2));
  fprintf (outfile, "%s %ld\n", "field3", G_STRUCT_OFFSET(OffsetsNestee, field3));
  fprintf (outfile, "\n");

  fprintf (outfile, "OffsetsObj: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsObj), ALIGNOF(OffsetsObj));
  fprintf (outfile, "%s %ld\n", "parent_instance", G_STRUCT_OFFSET(OffsetsObj, parent_instance));
  fprintf (outfile, "%s %ld\n", "other", G_STRUCT_OFFSET(OffsetsObj, other));
  fprintf (outfile, "\n");

  fprintf (outfile, "OffsetsObjClass: size=%" G_GSIZE_FORMAT ", alignment=%ld\n",
           sizeof(OffsetsObjClass), ALIGNOF(OffsetsObjClass));
  fprintf (outfile, "%s %ld\n", "parent_class", G_STRUCT_OFFSET(OffsetsObjClass, parent_class));
  fprintf (outfile, "\n");
}

int main(int argc, char **argv)
{
  GError *error = NULL;
  FILE *outfile;

  if (argc != 3)
    g_error ("Usage: gitestoffsets COMPILED_OFFSETS_FILE INTROSPECTED_OFFSETS_FILE");

  repository = g_irepository_get_default ();
  if (!g_irepository_require (repository, namespace, version, 0, &error))
     g_error ("Failed to load %s-%s.typelib: %s", namespace, version, error->message);

  outfile = fopen (argv[1], "w");
  if (!outfile)
    g_error ("Cannot open '%s': %s'", argv[1], g_strerror(errno));

  compiled (outfile);
  fclose (outfile);

  outfile = fopen (argv[2], "w");
  if (!outfile)
    g_error ("Cannot open '%s': %s'", argv[1], g_strerror(errno));

  introspected_struct (outfile, "Array");
  introspected_struct (outfile, "Basic");
  introspected_struct (outfile, "Enum");
  introspected_struct (outfile, "Nested");
  introspected_struct (outfile, "Nestee");
  introspected_struct (outfile, "Obj");
  introspected_struct (outfile, "ObjClass");

  fclose (outfile);

  return 0;
}