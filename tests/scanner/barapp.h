
#include <glib-object.h>

#define BAR_TYPE_BAZ              (bar_baz_get_type ())
#define BAR_BAZ(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), BAR_TYPE_BAZ, BarBaz))
#define BAR_IS_BAZ(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), BAR_TYPE_BAZ))

typedef struct BarBaz          BarBaz;
typedef struct BarBazClass     BarBazClass;

struct BarBaz
{
  GObject parent_instance;
};

struct BarBazClass
{
  GObjectClass parent_class;
};

GType bar_baz_get_type          (void) G_GNUC_CONST;

void barapp_func (void);
void barapp_func2 (int x, double y);
