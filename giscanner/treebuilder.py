import giscanner

class Node(object):
    pass


class Function(Node):
    def __init__(self, name, retval, parameters):
        self.name = name
        self.retval = retval
        self.parameters = parameters

    def __repr__(self):
        return 'Function(%r, %r, %r)' % (self.name, self.retval, self.parameters)


class Parameter(Node):
    def __init__(self, name, type):
        self.name = name
        self.type = type

    def __repr__(self):
        return 'Parameter(%r, %r)' % (self.name, self.type)


class Enum(Node):
    def __init__(self, name, members):
        self.name = name
        self.members = members

    def __repr__(self):
        return 'Enum(%r, %r)' % (self.name, self.members)


class Member(Node):
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def __repr__(self):
        return 'Member(%r, %r)' % (self.name, self.value)


class Struct(Node):
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return 'Struct(%r)' % (self.name,)


class Return(Node):
    def __init__(self, type):
        self.type = type

    def __repr__(self):
        return 'Return(%r)' % (self.type,)


class Class(Node):
    def __init__(self, name, parent, methods):
        self.name = name
        self.parent = parent
        self.methods = methods

    def __repr__(self):
        return 'Class(%r, %r)' % (self.name, self.methods)


class TreeBuilder(object):
    def __init__(self, generator):
        self.generator = generator
        self.nodes = []

        self._traverse()

    def get_nodes(self):
        for node in self.nodes:
            yield node

    def _traverse(self):
        for symbol in self.generator.get_symbols():
            node = self._traverse_one(symbol)
            if node is not None:
                self.nodes.append(node)

    def _traverse_one(self, symbol, stype=None):
        if stype is None:
            stype = symbol.type
        if stype == giscanner.CSYMBOL_TYPE_FUNCTION:
            return self._create_function(symbol)
        elif stype == giscanner.CSYMBOL_TYPE_TYPEDEF:
            return self._traverse_one(symbol, symbol.base_type.type)
        elif stype == giscanner.CSYMBOL_TYPE_STRUCT:
            return self._create_struct(symbol)
        elif stype == giscanner.CSYMBOL_TYPE_ENUM:
            return self._create_enum(symbol)
        else:
            print 'unhandled symbol', symbol.type

    def _create_enum(self, symbol):
        members = []
        for child in symbol.base_type.child_list:
            members.append(Member(child.ident,
                                  child.const_int))

        return Enum(symbol.ident, members)

    def _create_function(self, symbol):
        parameters = []
        for child in symbol.base_type.child_list:
            parameters.append(self._create_parameter(child))

        retval = Return(self._create_source_type(symbol.base_type.base_type))
        return Function(symbol.ident, retval, parameters)

    def _create_source_type(self, source_type):
        if source_type.type == giscanner.CTYPE_VOID:
            value = 'void'
        elif source_type.type == giscanner.CTYPE_BASIC_TYPE:
            value = source_type.name
        elif source_type.type == giscanner.CTYPE_TYPEDEF:
            value = source_type.name
        elif source_type.type == giscanner.CTYPE_POINTER:
            value = self._create_source_type(source_type.base_type) + '*'
        else:
            print 'Unhandled source type: %d' % (source_type.type,)
            value = '???'
        return value

    def _create_parameter(self, symbol):
        return Parameter(symbol.ident,
                         self._create_source_type(symbol.base_type))

    def _create_struct(self, symbol):
        return Struct(symbol.ident)
