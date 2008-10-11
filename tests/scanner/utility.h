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

typedef enum
{
  UTILITY_ENUM_A,
  UTILITY_ENUM_B,
  UTILITY_ENUM_C
} UtilityEnumType;

typedef enum
{
  UTILITY_FLAG_A,
  UTILITY_FLAG_B,
  UTILITY_FLAG_C
} UtilityFlagType;

typedef struct
{
  int field;
  guint bitfield1 : 3;
  guint bitfield2 : 2;
} UtilityStruct;

typedef union
{
  char *pointer;
  glong integer;
  double real;
} UtilityUnion;
  
#endif /* __UTILITY_H__ */
