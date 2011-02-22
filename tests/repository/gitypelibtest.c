/* -*- Mode: C; c-basic-offset: 4 -*-
 * vim: tabstop=4 shiftwidth=4 expandtab
 */

#include "girepository.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void
test_enum_and_flags_cidentifier(GIRepository *repo)
{
    GITypelib *ret;
    GError *error = NULL;
    gint n_infos, i;

    ret = g_irepository_require (repo, "GIMarshallingTests", NULL, 0, &error);
    if (!ret)
        g_error ("%s", error->message);

    n_infos = g_irepository_get_n_infos (repo, "GIMarshallingTests");

    for (i = 0; i < n_infos; i++) {
        GIBaseInfo *info;
        GIInfoType type;

        info = g_irepository_get_info (repo, "GIMarshallingTests", i);
        type = g_base_info_get_type (info);

        /* both GI_INFO_TYPE_ENUM and GI_INFO_TYPE_FLAGS use GIEnumInfo */
        if (GI_IS_ENUM_INFO (info)) {
            gint n_values, j;

            n_values = g_enum_info_get_n_values ((GIEnumInfo *) info);
            for (j = 0; j < n_values; j++) {
                GIValueInfo *value_info;
                const gchar *c_identifier = NULL;

                value_info = g_enum_info_get_value ((GIEnumInfo *) info, j);
                c_identifier = g_base_info_get_attribute ((GIBaseInfo *) value_info, "c:identifier");

                if (c_identifier == NULL) {
                    g_error ("Error: no 'c:identifier' attribute on GIMarshallingTests.%s.%s\n",
                             g_base_info_get_name (info),
                             g_base_info_get_name ((GIBaseInfo *) value_info));
                }

                g_base_info_unref ((GIBaseInfo *) value_info);
            }
        }

        g_base_info_unref (info);
    }
}

int
main(int argc, char **argv)
{
    GIRepository *repo;

    g_type_init ();

    repo = g_irepository_get_default ();

    /* do tests */
    test_enum_and_flags_cidentifier (repo);

    exit(0);
}
