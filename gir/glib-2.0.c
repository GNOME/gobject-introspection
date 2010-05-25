/**
 * g_file_get_contents:
 * @contents: (out):
 * @length: (out) (allow-none):
 */

/**
 * g_file_set_contents:
 * @contents: (array length=length) (element-type uint8):
 */

/**
 * g_file_open_tmp:
 * @name_used: (out):
 */

/**
 * g_filename_to_uri:
 * @hostname: (allow-none):
 */

/**
 * g_markup_escape_text:
 * Return value: (transfer full):
 */

/**
 * g_thread_init:
 * @vtable: (allow-none):
 */

/**
 * g_main_loop_new:
 * @context: (allow-none):
 */

/**
 * g_idle_add_full:
 *
 * Rename to: g_idle_add
 */

/**
 * g_child_watch_add_full:
 *
 * Rename to: g_child_watch_add
 */

/**
 * g_io_add_watch_full:
 *
 * Rename to: g_io_add_watch
 */

/**
 * g_timeout_add_full:
 *
 * Rename to: g_timeout_add
 */

/**
 * g_timeout_add_seconds_full:
 *
 * Rename to: g_timeout_add_seconds
 */

/**
 * g_option_context_parse:
 * @argc: (inout):
 * @argv: (array length=argc) (inout) (allow-none):
 */

/**
 * GIOCondition: (type bitfield)
 **/

/**
 * GSourceFunc:
 * @data: (closure):
 */

/**
 * GIOFunc:
 * @data: (closure):
 */

/**
 * g_spawn_async:
 * @working_directory: (allow-none):
 * @envp: (allow-none):
 * @child_setup: (scope async): (allow-none):
 * @user_data: (allow-none):
 * @child_pid: (out):
 */

/**
 * g_spawn_async_with_pipes:
 * @working_directory: (allow-none):
 * @envp: (allow-none):
 * @child_setup: (scope async): (allow-none):
 * @user_data: (allow-none):
 * @child_pid: (out):
 * @standard_input: (out):
 * @standard_output: (out):
 * @standard_error: (out):
 */

/**
 * g_spawn_sync:
 * @working_directory: (allow-none):
 * @envp: (allow-none):
 * @child_setup: (scope call): (allow-none):
 * @user_data: (allow-none):
 * @standard_output: (out):
 * @standard_error: (out):
 * @exit_status: (out):
 */

/**
 * g_spawn_command_line_sync:
 * @standard_output: (out):
 * @standard_error: (out):
 * @exit_status: (out):
 */

/**
 * g_get_system_config_dirs:
 * Return value: (array zero-terminated=1) (transfer none)
 */

/**
 * g_get_system_data_dirs:
 * Return value: (array zero-terminated=1) (transfer none)
 */

/**
 * g_shell_parse_argv:
 * @command_line:
 * @argcp: (out):
 * @argvp: (out): (array zero-terminated=1):
 * @error:
 */

/**
 * g_completion_complete_utf8:
 * Return value: (element-type utf8) (transfer none):
 */

/**
 * g_convert:
 * @bytes_read: (out):
 * @bytes_written: (out):
 */

/**
 * g_key_file_get_string:
 * Return value: (transfer full):
 */

/**
  * g_key_file_get_string_list:
  * @length: (out):
  * Return value: (array zero-terminated=1 length=length) (element-type utf8) (transfer full):
  */

/**
  * g_key_file_set_string_list:
  * @list: (array zero-terminated=1 length=length) (element-type utf8):
  * @length: (out):
  */

/**
 * g_key_file_get_locale_string:
 * @locale: (null-ok):
 * Return value: (transfer full):
 */

/**
  * g_key_file_get_locale_string_list:
  * @length: (out):
  * @locale: (null-ok):
  * Return value: (array zero-terminated=1 length=length) (element-type utf8) (transfer full):
  */

/**
  * g_key_file_set_locale_string_list:
  * @list: (array zero-terminated=1 length=length) (element-type utf8):
  * @length: (out):
  */

// Skip this as "tm" is not available at present.

/**
 * g_date_to_struct_tm: (skip)
 */
