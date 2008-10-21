#ifndef __TEST_DRAWABLE_H__
#define __TEST_DRAWABLE_H__

#include <glib-object.h>

typedef struct _TestDrawable TestDrawable;
typedef struct _TestDrawableClass TestDrawableClass;

struct _TestDrawable
{
  GObject parent_instance;
};

struct _TestDrawableClass
{
  GObjectClass parent_class;
};

GType test_drawable_get_type (void) G_GNUC_CONST;

void test_drawable_do_foo (TestDrawable *drawable, int x);
void test_drawable_get_origin (TestDrawable *drawable, int *x, int *y);
void test_drawable_get_size (TestDrawable *drawable, guint *width, guint *height);
void test_drawable_do_foo_maybe_throw (TestDrawable *drawable, int x, GError **error);

struct _TestPixmapObjectClass
{
  TestDrawableClass parent_class;
};

#endif /* __TEST_DRAWABLE_H__ */
