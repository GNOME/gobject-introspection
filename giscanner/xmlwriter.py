from cStringIO import StringIO
from xml.sax.saxutils import quoteattr


class XMLWriter(object):
    def __init__(self):
        self._data = StringIO()
        self._tag_stack = []
        self._indent = 0

    # Private

    def _collect_attributes(self, attributes):
        attrValue = ''
        if attributes:
            for attr, value in attributes:
                assert value is not None, attr
                attrValue += ' %s=%s' % (attr, quoteattr(value))
        return attrValue

    def _open_tag(self, tag_name, attributes=None):
        attrs = self._collect_attributes(attributes)
        self.write_line('<%s%s>' % (tag_name, attrs))

    def _close_tag(self, tag_name):
        self.write_line('</%s>' % (tag_name,))

    # Public API

    def get_xml(self):
        return self._data.getvalue()

    def write_line(self, line=''):
        self._data.write('%s%s\n' % (' ' * self._indent, line))

    def write_tag(self, tag_name, attributes):
        attrs = self._collect_attributes(attributes)
        self.write_line('<%s%s/>' % (tag_name, attrs))

    def write_tag_with_data(self, tag_name, data, attributes=None):
        if data is None:
            self.write_tag(tag_name, attributes)
        attrs = self._collect_attributes(attributes)
        self.write_line('<%s%s>%s</%s>' % (tag_name, attrs, data, tag_name))

    def push_tag(self, tag_name, attributes=None):
        self._open_tag(tag_name, attributes)
        self._tag_stack.append(tag_name)
        self._indent += 2

    def pop_tag(self):
        self._indent -= 2
        tag_name = self._tag_stack.pop()
        self._close_tag(tag_name)
        return tag_name
