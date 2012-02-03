/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
#include "drawable.h"

G_DEFINE_ABSTRACT_TYPE (TestInheritDrawable, test_inherit_drawable, G_TYPE_OBJECT);

static void
test_inherit_drawable_class_init (TestInheritDrawableClass *klass)
{

}

static void
test_inherit_drawable_init (TestInheritDrawable *drawable)
{

}

void 
test_inherit_drawable_do_foo (TestInheritDrawable *drawable, int x)
{
  
}

/**
 * test_inherit_drawable_get_origin:
 * @drawable:
 * @x: (out):
 * @y: (out):
 */
void
test_inherit_drawable_get_origin (TestInheritDrawable *drawable, int *x, int *y)
{
  *x = 0;
  *y = 0;
}

/**
 * test_inherit_drawable_get_size:
 * @drawable:
 * @width: (out):
 * @height: (out):
 */
void
test_inherit_drawable_get_size (TestInheritDrawable *drawable, guint *width, guint *height)
{
  *width = 42;
  *height = 42;
}

void
test_inherit_drawable_do_foo_maybe_throw (TestInheritDrawable *drawable, int x, GError **error)
{
  if (x != 42)
    g_set_error(error, 0, 12, "The answer should be 42!");
}
