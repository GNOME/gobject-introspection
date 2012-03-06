#ifndef __GETTYPE_OBJECT_H__
#define __GETTYPE_OBJECT_H__

#include <glib-object.h>

#define GETTYPE_TYPE_OBJECT            (gettype_object_get_type ())
#define GETTYPE_OBJECT(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), GETTYPE_TYPE_OBJECT, GetTypeObject))
#define GETTYPE_IS_OBJECT(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), GETTYPE_TYPE_OBJECT))

typedef struct _GetTypeObject           GetTypeObject;
typedef struct _GetTypeObjectClass      GetTypeObjectClass;
struct _GetTypeObject
{
  GObject parent_instance;
};

struct _GetTypeObjectClass
{
  GObjectClass parent_class;
};

GType           gettype_object_get_type          (void) G_GNUC_CONST;
GetTypeObject*  gettype_object_new               (void);

GType           gettype_object_nonmeta1_get_type (GetTypeObject *obj);
gboolean        gettype_object_nonmeta2_get_type (void);
gboolean        gettype_object_nonmeta_get_gtype (void);

#endif /* __GETTYPE_OBJECT_H__ */
