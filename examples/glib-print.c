#include <girepository.h>

int main(void)
{
    GIRepository *repository;
    GError *error = NULL;
    GIBaseInfo *base_info;
    GIArgument in_args[5];
    GIArgument retval;

    repository = g_irepository_get_default();
    g_irepository_require(repository, "GLib", "2.0", 0, &error);
    if (error) {
      g_error("ERROR: %s\n", error->message);
      return 1;
    }

    base_info = g_irepository_find_by_name(repository, "GLib", "assertion_message");
    if (!base_info) {
      g_error("ERROR: %s\n", "Could not find GLib.warn_message");
      return 1;
    }

    in_args[0].v_pointer = "domain";
    in_args[1].v_pointer = "glib-print.c";
    in_args[2].v_pointer = "30";
    in_args[3].v_pointer = "main";
    in_args[4].v_pointer = "hello world";

    if (!g_function_info_invoke ((GIFunctionInfo *)base_info,
                                 (const GIArgument*)&in_args,
                                 5,
                                 NULL,
                                 0,
                                 &retval,
                                 &error)) {
      g_error("ERROR: %s\n", error->message);
      return 1;
    }

    g_base_info_unref (base_info);

    return 0;
}
