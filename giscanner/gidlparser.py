from xml.etree.ElementTree import parse

from .gobjecttreebuilder import GLibObject


class GIDLParser(object):
    def __init__(self, filename):
        self._nodes = []
        self._namespace_name = None

        tree = parse(filename)
        self._parse_api(tree.getroot())

    def _parse_api(self, root):
        assert root.tag == 'api'
        ns = root.find('namespace')
        self._namespace_name = ns.attrib['name']
        for child in ns.getchildren():
            if child.tag == 'object':
                self._parse_object(child)
            else:
                print 'PARSER: Unhandled %s' % (child.tag,)

    def _parse_object(self, node):
        gobj = GLibObject(node.attrib['name'],
                          node.attrib.get('parent'),
                          node.attrib['type-name'],
                          node.attrib['get-type'])
        self._nodes.append(gobj)

    def get_namespace_name(self):
        return self._namespace_name

    def get_nodes(self):
        return self._nodes
