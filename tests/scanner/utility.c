#include "utility.h"

G_DEFINE_TYPE (UtilityObject, utility_object, G_TYPE_OBJECT);

/**
 * UtilityFlagType: (type bitfield)
 **/

/**
 * UtilityBuffer:
 *
 * @data: (type pointer): the data
 **/

static void
utility_object_class_init (UtilityObjectClass *klass)
{

}

static void
utility_object_init (UtilityObject *object)
{

}

void
utility_object_watch_dir (UtilityObject *object,
                          const char *path,
                          UtilityFileFunc func,
                          gpointer user_data,
                          GDestroyNotify destroy)
{

}

void
utility_dir_foreach (const char *path, UtilityFileFunc func, gpointer user_data)
{

}
