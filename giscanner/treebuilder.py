import giscanner


class Node(object):
    def __init__(self, name=None):
        self.name = name


class Function(Node):
    def __init__(self, name, retval, parameters, symbol):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters
        self.symbol = symbol

    def __repr__(self):
        return '%s(%r, %r, %r)' % (self.__class__.__name__,
                                   self.name, self.retval,
                                   self.parameters)


class VFunction(Function):
    pass


class Parameter(Node):
    def __init__(self, name, type):
        Node.__init__(self, name)
        self.type = type
        self.direction = 'in'
        self.transfer = 'none'

    def __repr__(self):
        return 'Parameter(%r, %r)' % (self.name, self.type)


class Enum(Node):
    def __init__(self, name, members):
        Node.__init__(self, name)
        self.members = members

    def __repr__(self):
        return 'Enum(%r, %r)' % (self.name, self.members)


class Member(Node):
    def __init__(self, name, value):
        Node.__init__(self, name)
        self.value = value

    def __repr__(self):
        return 'Member(%r, %r)' % (self.name, self.value)


class Struct(Node):
    def __init__(self, name):
        Node.__init__(self, name)
        self.fields = []

    def __repr__(self):
        return 'Struct(%r)' % (self.name,)


class Return(Node):
    def __init__(self, type):
        Node.__init__(self)
        self.type = type
        self.transfer = 'none'

    def __repr__(self):
        return 'Return(%r)' % (self.type,)


class Class(Node):
    def __init__(self, name, parent):
        Node.__init__(self, name)
        self.parent = parent
        self.methods = []
        self.constructors = []
        self.properties = []
        self.fields = []

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.parent, self.methods)


class Interface(Node):
    def __init__(self, name):
        Node.__init__(self, name)
        self.methods = []
        self.properties = []
        self.fields = []

    def __repr__(self):
        return '%s(%r, %r)' % (
            self.__class__.__name__,
            self.name, self.methods)


class Constant(Node):
    def __init__(self, name, type, value):
        Node.__init__(self, name)
        self.type = type
        self.value = value

    def __repr__(self):
        return 'Constant(%r, %r, %r)' % (
            self.name, self.type, self.value)


class Property(Node):
    def __init__(self, name, type):
        Node.__init__(self, name)
        self.type = type

    def __repr__(self):
        return '%s(%r, %r, %r)' % (
            self.__class__.__name__,
            self.name, self.type, self.value)


class Callback(Node):
    def __init__(self, name, retval, parameters):
        Node.__init__(self, name)
        self.retval = retval
        self.parameters = parameters

    def __repr__(self):
        return 'Callback(%r, %r, %r)' % (
            self.name, self.retval, self.parameters)


class TreeBuilder(object):
    def __init__(self, generator):
        self.generator = generator
        self.nodes = []
        self._output_ns = {}
        self._typedefs_ns = {}
        self._traverse()

    def get_nodes(self):
        for node in self.nodes:
            yield node

    def _traverse(self):
        for symbol in self.generator.get_symbols():
            node = self._traverse_one(symbol)
            if node is None:
                continue
            if node.name.startswith('_'):
                continue
            self.nodes.append(node)
            self._output_ns[node.name] = node

    def _traverse_one(self, symbol, stype=None):
        if stype is None:
            stype = symbol.type
        if stype == giscanner.CSYMBOL_TYPE_FUNCTION:
            return self._create_function(symbol)
        elif stype == giscanner.CSYMBOL_TYPE_TYPEDEF:
            if (symbol.base_type.type == giscanner.CTYPE_POINTER and
                symbol.base_type.base_type.type == giscanner.CTYPE_FUNCTION):
                node = self._create_callback(symbol)
            elif symbol.base_type.type == giscanner.CTYPE_STRUCT:
                node = self._create_typedef_struct(symbol)
            else:
                node = self._traverse_one(symbol, symbol.base_type.type)
            return node
        elif stype == giscanner.CSYMBOL_TYPE_STRUCT:
            return self._create_struct(symbol)
        elif stype == giscanner.CSYMBOL_TYPE_ENUM:
            return self._create_enum(symbol)
        else:
            print 'BUILDER: unhandled symbol', symbol.type

    def _create_enum(self, symbol):
        members = []
        for child in symbol.base_type.child_list:
            members.append(Member(child.ident,
                                  child.const_int))

        return Enum(symbol.ident, members)

    def _create_function(self, symbol):
        directives = symbol.directives()
        parameters = list(self._create_parameters(symbol.base_type, directives))
        return_ = self._create_return(symbol.base_type.base_type,
                                      directives.get('return', []))
        return Function(symbol.ident, return_, parameters, symbol.ident)

    def _create_source_type(self, source_type):
        if source_type is None:
            return 'None'
        if source_type.type == giscanner.CTYPE_VOID:
            value = 'void'
        elif source_type.type == giscanner.CTYPE_BASIC_TYPE:
            value = source_type.name
        elif source_type.type == giscanner.CTYPE_TYPEDEF:
            value = source_type.name
        elif source_type.type == giscanner.CTYPE_POINTER:
            value = self._create_source_type(source_type.base_type) + '*'
        else:
            print 'BUILDER: Unhandled source type: %d' % (source_type.type,)
            value = '???'
        return value

    def _create_parameters(self, base_type, options=None):
        if not options:
            options = {}
        for child in base_type.child_list:
            yield self._create_parameter(
                child, options.get(child.ident, []))

    def _create_parameter(self, symbol, options):
        param = Parameter(symbol.ident,
                          self._create_source_type(symbol.base_type))
        for option in options:
            if option in ['in-out', 'inout']:
                param.direction = 'inout'
            elif option == 'in':
                param.direction = 'in'
            elif option == 'out':
                param.direction = 'out'
            elif option == 'callee-owns':
                param.transfer = 'full'
            else:
                print 'Unhandled parameter annotation option: %s' % (
                    option,)
        return param

    def _create_return(self, symbol, options):
        return_ = Return(self._create_source_type(symbol))
        for option in options:
            if option == 'caller-owns':
                return_.transfer = 'full'
            else:
                print 'Unhandled parameter annotation option: %s' % (
                    option,)
        return return_

    def _create_typedef_struct(self, symbol):
        self._typedefs_ns[symbol.base_type.name] = symbol.ident

    def _create_struct(self, symbol):
        name = self._typedefs_ns.get(symbol.ident, symbol.ident)
        struct = Struct(name)
        for child in symbol.base_type.child_list:
            struct.fields.append(self._traverse_one(child,
                                                    child.base_type.type))
        return struct

    def _create_callback(self, symbol):
        parameters = self._create_parameters(symbol.base_type.base_type)
        retval = Return(self._create_source_type(symbol.base_type.base_type.base_type))
        return Callback(symbol.ident, retval, list(parameters))
