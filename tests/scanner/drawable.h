#ifndef __TEST_INHERIT_DRAWABLE_H__
#define __TEST_INHERIT_DRAWABLE_H__

#include <glib-object.h>

typedef struct _TestInheritDrawable TestInheritDrawable;
typedef struct _TestInheritDrawableClass TestInheritDrawableClass;

struct _TestInheritDrawable
{
  GObject parent_instance;
};

struct _TestInheritDrawableClass
{
  GObjectClass parent_class;
};

GType test_inherit_drawable_get_type (void) G_GNUC_CONST;

void test_inherit_drawable_do_foo (TestInheritDrawable *drawable, int x);
void test_inherit_drawable_get_origin (TestInheritDrawable *drawable, int *x, int *y);
void test_inherit_drawable_get_size (TestInheritDrawable *drawable, guint *width, guint *height);
void test_inherit_drawable_do_foo_maybe_throw (TestInheritDrawable *drawable, int x, GError **error);

typedef struct _TestInheritPixmapObjectClass TestInheritPixmapObjectClass;

struct _TestInheritPixmapObjectClass
{
  TestInheritDrawableClass parent_class;
};

#endif /* __TEST_INHERIT_DRAWABLE_H__ */
