#include "drawable.h"

G_DEFINE_ABSTRACT_TYPE (TestDrawable, test_drawable, G_TYPE_OBJECT);

static void
test_drawable_class_init (TestDrawableClass *klass)
{

}

static void
test_drawable_init (TestDrawable *drawable)
{

}

void 
test_drawable_do_foo (TestDrawable *drawable, int x)
{
  
}
