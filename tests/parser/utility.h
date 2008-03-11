#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <glib-object.h>

#define UTILITY_TYPE_OBJECT              (utility_object_get_type ())
#define UTILITY_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), UTILITY_TYPE_OBJECT, UtilityObject))
#define UTILITY_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), UTILITY_TYPE_OBJECT))

typedef struct _UtilityObject          UtilityObject;
typedef struct _UtilityObjectClass     UtilityObjectClass;

struct _UtilityObject
{
  GObject parent_instance;
};

struct _UtilityObjectClass
{
  GObjectClass parent_class;
};

GType                 utility_object_get_type          (void) G_GNUC_CONST;

#endif /* __UTILITY_H__ */
