#ifndef __OFFSETS_H__
#define __OFFSETS_H__

#include <glib.h>
#include <glib-object.h>
#include <time.h>

/* Test we get the alignment right for various basic types; we put
 * a char in front of of each field to make it more likely that we'll
 * stress out the alignment code.
 */
typedef struct _OffsetsBasic OffsetsBasic;

struct _OffsetsBasic {
  char dummy1;
  gint8 field_int8;
  char dummy2;
  gint16 field_int16;
  char dummy3;
  gint32 field_int32;
  char dummy4;
  gint64 field_int64;
  char dummy5;
  gchar *field_pointer;
  char dummy6;
  gfloat field_float;
  char dummy7;
  gdouble field_double;
  char dummy8;
  gsize field_size;
  char dummy9;
  time_t field_time;
};

typedef enum {
  ENUM_1 = 1 /* compiler could use int8, uint8, int16, uint16, int32, uint32 */
} Enum1;

typedef enum {
  ENUM_2 = 128 /* compiler could use uint8, int16, uint16, int32, uint32 */
} Enum2;

typedef enum {
  ENUM_3 = 257 /* compiler could use int16, uint16, int32, uint32 */
} Enum3;

typedef enum {
  ENUM_4 = G_MAXSHORT + 1 /* compiler could use uint16, int32, uint32 */
} Enum4;

typedef enum {
  ENUM_5 = G_MAXUSHORT + 1 /* compiler could use int32, uint32 */
} Enum5;

typedef enum {
  ENUM_6 = ((guint)G_MAXINT) + 1 /* compiler could use uint32 */
} Enum6;

/* Test that we get the width of enum fields right. The char after
 * each field will have aligment 1 (almost certainly) so should
 * be placed right the field.
 */
typedef struct _OffsetsEnum OffsetsEnum;

struct _OffsetsEnum {
  Enum1 enum1;
  char dummy1;
  Enum2 enum2;
  char dummy2;
  Enum3 enum3;
  char dummy3;
  Enum4 enum4;
  char dummy4;
  Enum5 enum5;
  char dummy5;
  Enum6 enum6;
  char dummy6;
};

/* Test nested structures
 */

typedef struct _OffsetsNestee OffsetsNestee;

struct _OffsetsNestee {
  char field1;
  double field2; /* alignment of structure is greater than its first element */
  char field3; /* structure has tail padding */
};

typedef union _OffsetsNesteeUnion OffsetsNesteeUnion;

union _OffsetsNesteeUnion {
  char field1;
  double field2;
};

typedef struct _OffsetsNested OffsetsNested;

struct _OffsetsNested {
  char dummy1;
  OffsetsNestee nestee;
  char dummy2;
  OffsetsNesteeUnion nestee_union;
  char dummy3;
};

/* Test array offsets
 */

typedef struct _OffsetsArray OffsetsArray;

struct _OffsetsArray
{ 
  gint some_ints[2];
  gint8 some_int8s[3];
  gdouble some_doubles[4];
  Enum1 some_enum[2];
  gpointer some_ptrs[5];
};

/** Test object offsets
 */

typedef struct _OffsetsObj OffsetsObj;
typedef struct _OffsetsObjClass OffsetsObjClass;

struct _OffsetsObj
{
  GObject parent_instance;

  GObject *other;
};

struct _OffsetsObjClass
{
  GObjectClass parent_class;
};

#endif /* __OFFSETS_H__ */
