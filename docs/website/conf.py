# -*- coding: utf-8 -*-

extensions = [
    'sphinx.ext.extlinks',
]
source_suffix = '.rst'
master_doc = 'index'
exclude_patterns = ['_build']

html_theme = 'sphinx_rtd_theme'
html_show_copyright = False
project = "GObject Introspection"
html_title = project

html_theme_options = {
    "display_version": False,
}

html_static_path = [
    "extra.css",
]

html_context = {
    'extra_css_files': [
        '_static/extra.css',
    ],
}

extlinks = {
    'bzbug': ('https://bugzilla.gnome.org/show_bug.cgi?id=%s', 'bz#%s'),
    'commit': ('https://gitlab.gnome.org/GNOME/gobject-introspection/-/commit/%s', None),
    'issue': ('https://gitlab.gnome.org/GNOME/gobject-introspection/-/issues/%s', '#%s'),
    'mr': (
        'https://gitlab.gnome.org/GNOME/gobject-introspection/-/merge_requests/%s', '!%s'),
    'user': ('https://gitlab.gnome.org/%s', None),
}
