/* GObject - GLib Type, Object, Parameter and Signal Library
 * testmarshallergeneric.c: Generic CClosure marshaller
 * Copyright (C) 2007 Johan Dahlin
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

#include <string.h>
#include <glib-object.h>
#include "girepository.h"

typedef struct {
  GObject parent;
} TestObject;

typedef struct {
  GObjectClass parent_class;
  void (* test1)                (TestObject *object);
  void (* test2)                (TestObject *object, char *str);
  int  (* test3)                (TestObject *object, int i);
  void (* test4)                (TestObject *object,
                                 gboolean b, long l, float f, double d,
                                 guint uint, gulong ulong);
} TestObjectClass;

#define TEST_TYPE_OBJECT            (test_object_get_type())
#define TEST_OBJECT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TEST_TYPE_OBJECT, TestObject))
#define TEST_OBJECT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), TEST_TYPE_OBJECT, TestObjectClass))
#define TEST_IS_OBJECT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TEST_TYPE_OBJECT))
#define TEST_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((obj), TEST_TYPE_OBJECT))
#define TEST_OBJECT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), TEST_TYPE_OBJECT, TestObjectClass))

GType test_object_get_type (void);

enum {
  TEST1,
  TEST2,
  TEST3,
  TEST4,
  LAST_SIGNAL
};

static guint object_signals[LAST_SIGNAL] = { 0 };

G_DEFINE_TYPE (TestObject, test_object, G_TYPE_OBJECT);

static void test_object_init (TestObject *self) 
{
}

static void test_object_class_init (TestObjectClass *klass)
{
  GObjectClass *gobject_class = (GObjectClass*) klass;

  object_signals[TEST1] =
    g_signal_new ("test1",
                  G_TYPE_FROM_CLASS (gobject_class),
                  G_SIGNAL_RUN_FIRST,
                  G_STRUCT_OFFSET (TestObjectClass, test1),
                  NULL, NULL,
                  gi_cclosure_marshal_generic,
                  G_TYPE_NONE, 0);
  object_signals[TEST2] =
    g_signal_new ("test2",
                  G_TYPE_FROM_CLASS (gobject_class),
                  G_SIGNAL_RUN_FIRST,
                  G_STRUCT_OFFSET (TestObjectClass, test2),
                  NULL, NULL,
                  gi_cclosure_marshal_generic,
                  G_TYPE_NONE, 1,
                  G_TYPE_STRING);
  object_signals[TEST3] =
    g_signal_new ("test3",
                  G_TYPE_FROM_CLASS (gobject_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (TestObjectClass, test3),
                  NULL, NULL,
                  gi_cclosure_marshal_generic,
                  G_TYPE_INT, 1,
                  G_TYPE_DOUBLE);
  object_signals[TEST4] =
    g_signal_new ("test4",
                  G_TYPE_FROM_CLASS (gobject_class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (TestObjectClass, test3),
                  NULL, NULL,
                  gi_cclosure_marshal_generic,
                  G_TYPE_NONE, 6,
                  G_TYPE_BOOLEAN,
                  G_TYPE_LONG,
                  G_TYPE_FLOAT,
                  G_TYPE_DOUBLE,
                  G_TYPE_UINT,
                  G_TYPE_ULONG);
}

static void
test1_callback (TestObject *object, char *data)
{
  g_return_if_fail (TEST_IS_OBJECT (object));
  g_return_if_fail (!strcmp (data, "user-data"));
}

static void
test1_callback_swapped (char *data, TestObject *object)
{
  g_return_if_fail (TEST_IS_OBJECT (object));
  g_return_if_fail (!strcmp (data, "user-data"));
}

static void
test2_callback (TestObject *object, char *string)
{
  g_return_if_fail (TEST_IS_OBJECT (object));
  g_return_if_fail (!strcmp (string, "string"));
}

static int
test3_callback (TestObject *object, double f)
{
  g_return_val_if_fail (TEST_IS_OBJECT (object), -1);
  g_return_val_if_fail (f == 42.0, -1);

  return 20;
}

static void
test4_callback (TestObject *object,
                gboolean b, long l, float f, double d, guint uint, gulong ulong,
                gpointer user_data)
{
  g_return_if_fail (b == TRUE);
  g_return_if_fail (l == 10L);
  g_return_if_fail (f <= 3.14001 && f >= 3.13999);
  g_return_if_fail (d == 1.78);
  g_return_if_fail (uint == 20);
  g_return_if_fail (ulong == 30L);
}

/* this callback has no "this" */
static void
test5_callback (gpointer user_data)
{
  g_return_if_fail (!strcmp (user_data, "user-data"));
}

static void
test_cclosure_marshal (void)
{
  TestObject *object;
  gchar *data = "user-data";
  int i;
  GClosure *closure;
  
  g_type_init ();
  
  object = g_object_new (TEST_TYPE_OBJECT, NULL);
  g_signal_connect (G_OBJECT (object),
                    "test1",
                    G_CALLBACK (test1_callback), 
                    data);
  g_signal_connect_swapped (G_OBJECT (object),
                    "test1",
                    G_CALLBACK (test1_callback_swapped), 
                    data);
  g_signal_connect (G_OBJECT (object),
                    "test2",
                    G_CALLBACK (test2_callback), 
                    NULL);
  g_signal_connect (G_OBJECT (object),
                    "test3",
                    G_CALLBACK (test3_callback), 
                    NULL);
  g_signal_connect (G_OBJECT (object),
                    "test4",
                    G_CALLBACK (test4_callback), 
                    NULL);

  g_signal_emit (G_OBJECT (object), object_signals[TEST1], 0);
  g_signal_emit (G_OBJECT (object), object_signals[TEST2], 0, "string");
  g_signal_emit (G_OBJECT (object), object_signals[TEST3], 0, 42.0, &i);
  g_signal_emit (G_OBJECT (object), object_signals[TEST4], 0,
                 TRUE, 10L, 3.14, 1.78, 20, 30L);
  g_assert (i == 20);

  g_object_unref (object);

  closure = g_cclosure_new (G_CALLBACK (test5_callback),
                            data,
                            NULL);
  g_closure_ref (closure);
  g_closure_sink (closure);
  g_closure_set_marshal (closure, gi_cclosure_marshal_generic);
  g_closure_invoke (closure, NULL, 0, NULL, NULL);
  g_closure_unref (closure);
}

  
int main(void)
{
  test_cclosure_marshal ();

  return 0;
}

