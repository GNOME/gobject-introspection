/**
 * g_app_info_create_from_commandline:
 * @application_name: (allow-none):
 */

/**
 * g_volume_monitor_get_connected_drives:
 *
 * Returns: (element-type GDrive) (transfer full):
 */

/**
 * g_volume_monitor_get_volumes:
 *
 * Returns: (element-type GVolume) (transfer full):
 */

/**
 * g_volume_monitor_get_mounts:
 *
 * Returns: (element-type GMount) (transfer full):
 */

/**
 * g_drive_get_volumes:
 *
 * Returns: (element-type GVolume) (transfer full):
 */

/**
 * g_app_info_get_all:
 *
 * Returns: (element-type GAppInfo) (transfer full):
 */

/**
 * g_app_info_get_all_for_type:
 *
 * Returns: (element-type GAppInfo) (transfer full):
 */

/**
 * g_app_info_get_icon:
 *
 * Returns: (transfer none):
 */

/**
 * g_file_info_get_attribute_object:
 *
 * Returns: (transfer none):
 */

/**
 * g_file_info_get_attribute_data:
 *
 * @value_pp: (out)
 * Returns: (transfer none):
 */

/**
 * g_file_info_get_icon:
 *
 * Returns: (transfer none):
 */

/**
 * g_app_info_launch:
 * @appinfo:
 * @files: (element-type GFile):
 * @launch_context: (allow-none):
 * @error:
 */

/**
 * g_app_info_launch_uris:
 * @appinfo:
 * @uris: (element-type char*):
 * @launch_context: (allow-none):
 * @error:
 */

/**
 * g_file_enumerator_next_files_finish:
 *
 * Return value: (transfer full) (element-type FileInfo):
 */

/**
 * g_file_load_contents:
 * @contents: (out) (transfer full):
 * @length: (allow-none) (out):
 * @etag_out: (allow-none) (out):
 */


/**
 * g_file_load_contents_finish:
 * @contents: (out) (transfer full):
 * @length: (allow-none) (out):
 * @etag_out: (allow-none) (out):
 */

/**
 * g_file_load_partial_contents_finish:
 * @contents: (out) (transfer full):
 * @length: (allow-none) (out):
 * @etag_out: (allow-none) (out):
 */

/**
 * g_file_replace:
 * @etag: (allow-none):
 */

/**
 * g_file_replace_contents:
 * @etag: (allow-none):
 * @new_etag: (allow-none) (out):
 */

/**
 * g_file_replace_contents_async:
 * @etag: (allow-none):
 */

/**
 * g_file_replace_contents_finish:
 * @new_etag: (allow-none) (out):
 */

/**
 * g_file_set_attributes_finish:
 * @info: (out):
 */

/**
 * g_filename_completer_get_completions:
 *
 * Return value: (array zero-terminated=1) (transfer full):
 */

/**
 * g_volume_mount:
 * @mount_operation: (allow-none):
 */

/**
 * g_file_info_list_attributes:
 *
 * Return value: (array zero-terminated=1) (transfer full):
 */

/**
 * g_filter_input_stream_get_base_stream:
 *
 * Return value: (transfer none):
 */

/**
 * g_filter_output_stream_get_base_stream:
 *
 * Return value: (transfer none):
 */

/**
 * g_app_launch_context_get_display:
 * @context: a #GAppLaunchContext
 * @info: a #GAppInfo
 * @files: (element-type GFile): a #GList of #GFile objects
 */

/**
 * g_app_launch_context_get_startup_notify_id:
 * @context: a #GAppLaunchContext
 * @info: a #GAppInfo
 * @files: (element-type GFile): a #GList of of #GFile objects
 */

/**
 * g_dbus_proxy_new_sync:
 * @info: (allow-none):
 * @name: (allow-none):
 * @cancellable: (allow-none):
 * @error: (allow-none):
 */

/**
 * g_io_extension_point_get_extensions:
 *
 * Returns: (element-type GIOExtensionPoint) (transfer none):
 */

/**
 * g_resolver_lookup_by_name:
 *
 * Returns: (element-type GInetAddress) (transfer full):
 */

/**
 * g_resolver_lookup_by_name_finish:
 *
 * Returns: (element-type GInetAddress) (transfer full):
 */

/**
 * g_resolver_lookup_service:
 *
 * Returns: (element-type GSrvTarget) (transfer full):
 */

/**
 * g_resolver_lookup_service_finish:
 *
 * Returns: (element-type GSrvTarget) (transfer full):
 */

/**
 * g_resolver_free_addresses: (skip)
 * @addresses: (element-type GInetAddress) (transfer full):
 */

/**
 * g_resolver_free_targets: (skip)
 * @targets: (element-type GSrvTarget) (transfer full):
 */

/**
 * g_content_types_get_registered:
 *
 * Returns: (element-type utf8) (transfer full):
 */

/**
 * g_emblemed_icon_get_emblems:
 *
 * Returns: (element-type utf8) (transfer none):
 */

/**
 * g_io_modules_load_all_in_directory:
 *
 * Returns: (element-type GIOModule) (transfer full):
 */

/**
 * g_srv_target_list_sort: (skip)
 * @targets: (element-type GSrvTarget) (transfer full):
 *
 * Returns: (element-type GSrvTarget) (transfer full):
 */

/**
 * g_unix_mount_points_get:
 *
 * Returns: (element-type utf8) (transfer full):
 */

/**
 * g_unix_mounts_get:
 *
 * Returns: (element-type utf8) (transfer full):
 */
