# -*- coding: utf-8 -*-

import re
from urllib.parse import urlparse, urlunparse

from sphinx.application import Sphinx

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


_FRAGMENT_MATCH = re.compile(r'L(\d+)(-\d*)?$')


def rewrite_gitlab_source_anchors(app: Sphinx, uri: str):
    parsed = urlparse(uri)
    if (parsed.hostname in ["gitlab.gnome.org", "gitlab.com"]
            and parsed.fragment
            and _FRAGMENT_MATCH.match(parsed.fragment)):
        return urlunparse(parsed._replace(fragment=''))
    return None


def setup(app: Sphinx):
    app.connect('linkcheck-process-uri', rewrite_gitlab_source_anchors)
