import ctypes

from giscanner.treebuilder import Enum, Function, Member, Struct
from giscanner import cgobject


class GLibEnum(Enum):
    def __init__(self, name, members, get_type):
        Enum.__init__(self, name, members)
        self.get_type = get_type


class GLibFlags(GLibEnum):
    pass


class GLibEnumMember(Member):
    def __init__(self, name, value, nick):
        Member.__init__(self, name, value)
        self.nick = nick


class GObjectTreeBuilder(object):
    def __init__(self):
        self.inputnodes = []
        self.outputnodes = []
        self._library = None

    # Public API

    def get_nodes(self):
        return self.outputnodes

    def load_library(self, libname):
        self._library = ctypes.cdll.LoadLibrary(libname)

    def parse(self, nodes):
        nodes = list(nodes)
        for node in nodes:
            self._parse_node(node)

    # Private

    def _call_get_type_function(self, symbol_name):
        func = getattr(self._library, symbol_name)
        func.restype = cgobject.GType
        func.argtypes = []
        return func()

    def _parse_node(self, node):
        if isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Struct):
            self._parse_struct(node)
        else:
            print 'Unhandled node:', node

    def _parse_enum(self, enum):
        self.outputnodes.append(enum)

    def _parse_function(self, func):
        if (func.name.endswith('_get_type') and
            func.retval.type == 'GType' and
            not func.parameters):
            symbol = func.name
            type_id = self._call_get_type_function(symbol)
            self._parse_gtype(type_id, symbol)
            return
        print 'todo', func

    def _parse_struct(self, struct):
        if (struct.name.startswith('_') or
            struct.name.endswith('Iface') or
            struct.name.endswith('Class')):
            return
        print 'todo', struct

    def _parse_gtype(self, type_id, symbol):
        fundamental_type_id = cgobject.type_fundamental(type_id)
        if (fundamental_type_id == cgobject.TYPE_ENUM or
            fundamental_type_id == cgobject.TYPE_FLAGS):
            self._introspect_enum(fundamental_type_id, type_id, symbol)
        #elif fundamental_type == cgobject.TYPE_OBJECT:
        #    pass
        else:
            print 'unhandled GType: %s' % (cgobject.type_name(type_id),)

    def _introspect_enum(self, ftype_id, type_id, symbol):
        type_class = cgobject.type_class_ref(type_id)
        if type_class is None:
            return

        members = []
        for enum_value in type_class.get_values():
            members.append(GLibEnumMember(enum_value.value_name,
                                          enum_value.value,
                                          enum_value.value_nick))

        klass = (GLibFlags if ftype_id == cgobject.TYPE_FLAGS else GLibEnum)
        cenum = klass(cgobject.type_name(type_id), members, symbol)
        self.outputnodes.append(cenum)
