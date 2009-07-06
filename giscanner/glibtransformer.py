# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008  Johan Dahlin
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

import os
import sys
import re
import tempfile
import shutil
import subprocess

from .ast import (Alias, Bitfield, Callback, Constant, Enum, Function, Member,
                  Namespace, Parameter, Property, Record, Return, Type, Union,
                  Field, VFunction, type_name_from_ctype,
                  default_array_types, TYPE_UINT8, PARAM_TRANSFER_FULL)
from .transformer import Names
from .glibast import (GLibBoxed, GLibEnum, GLibEnumMember, GLibFlags,
                      GLibInterface, GLibObject, GLibSignal, GLibBoxedStruct,
                      GLibBoxedUnion, GLibBoxedOther, GLibRecord,
                      type_names)
from .utils import to_underscores, to_underscores_noprefix

default_array_types['guchar*'] = TYPE_UINT8

# GParamFlags
G_PARAM_READABLE = 1 << 0
G_PARAM_WRITABLE = 1 << 1
G_PARAM_CONSTRUCT = 1 << 2
G_PARAM_CONSTRUCT_ONLY = 1 << 3
G_PARAM_LAX_VALIDATION = 1 << 4
G_PARAM_STATIC_NAME = 1 << 5
G_PARAM_STATIC_NICK = 1 << 6
G_PARAM_STATIC_BLURB = 1 << 7

SYMBOL_BLACKLIST = [
    # These ones break GError conventions
    'g_simple_async_result_new_from_error',
    'g_simple_async_result_set_from_error',
    'g_simple_async_result_propagate_error',
    'g_simple_async_result_report_error_in_idle',
    'gtk_print_operation_get_error',
]

SYMBOL_BLACKLIST_RE = [re.compile(x) for x in \
                           [r'\w+_marshal_[A-Z]+__', ]]

GET_TYPE_OVERRIDES = {
    # this is a special case, from glibtransforer.py:create_gobject
    'intern': 'g_object_get_type',
    # this is presumably a typo, should be fixed upstream
    'g_gstring_get_type': 'g_string_get_type',
    # this is historical cruft: there's a deprecated
    #   #define gdk_window_get_type gdk_window_get_window_type
    # upstream; this method can be renamed properly upstream once
    # that deprecated alias is removed (in some future release)
    'gdk_window_object_get_type': 'gdk_window_get_type',
}


class IntrospectionBinary(object):

    def __init__(self, args, tmpdir=None):
        self.args = args
        if tmpdir is None:
            self.tmpdir = tempfile.mkdtemp('', 'tmp-introspect')
        else:
            self.tmpdir = tmpdir


class Unresolved(object):

    def __init__(self, target):
        self.target = target


class UnknownTypeError(Exception):
    pass


class GLibTransformer(object):

    def __init__(self, transformer, noclosure=False):
        self._transformer = transformer
        self._noclosure = noclosure
        self._namespace_name = None
        self._names = Names()
        self._uscore_type_names = {}
        self._binary = None
        self._get_type_functions = []
        self._error_quark_functions = []
        self._gtype_data = {}
        self._failed_types = {}
        self._boxed_types = {}
        self._private_internal_types = {}
        self._validating = False

    # Public API

    def _print_statistics(self):
        nodes = list(self._names.names.itervalues())

        def count_type(otype):
            return len([x for x in nodes
                        if isinstance(x[1], otype)])
        objectcount = count_type(GLibObject)
        ifacecount = count_type(GLibInterface)
        enumcount = count_type(GLibEnum)
        print " %d nodes; %d objects, %d interfaces, %d enums" \
            % (len(nodes), objectcount, ifacecount, enumcount)

    def init_parse(self):
        """Do parsing steps that don't involve the introspection binary

        This does enough work that get_type_functions() can be called.

        """

        namespace = self._transformer.parse()
        self._namespace_name = namespace.name
        self._namespace_version = namespace.version

        # First pass: parsing
        for node in namespace.nodes:
            self._parse_node(node)

        # We don't want an alias for this - it's handled specially in
        # the typelib compiler.
        if namespace.name == 'GObject':
            del self._names.aliases['Type']

    def get_get_type_functions(self):
        return self._get_type_functions

    def set_introspection_binary(self, binary):
        self._binary = binary

    def parse(self):
        """Do remaining parsing steps requiring introspection binary"""

        # Get all the GObject data by passing our list of get_type
        # functions to the compiled binary

        self._execute_binary()

        # Introspection is done from within parsing

        # Second pass: pair boxed structures
        for boxed in self._boxed_types.itervalues():
            self._pair_boxed_type(boxed)
        # Third pass: delete class structures, resolve
        # all types we now know about
        nodes = list(self._names.names.itervalues())
        for (ns, node) in nodes:
            try:
                self._resolve_node(node)
            except KeyError, e:
                #print "WARNING: DELETING node %s: %s" % (node.name, e)
                self._remove_attribute(node.name)
        # Another pass, since we need to have the methods parsed
        # in order to correctly modify them after class/record
        # pairing
        for (ns, node) in nodes:
            # associate GtkButtonClass with GtkButton
            if isinstance(node, Record):
                self._pair_class_record(node)
        for (ns, alias) in self._names.aliases.itervalues():
            self._resolve_alias(alias)
        self._resolve_quarks()
        # Fourth pass: ensure all types are known
        if not self._noclosure:
            self._resolve_types(nodes)

        #self._validate(nodes)

        # Create a new namespace with what we found
        namespace = Namespace(self._namespace_name, self._namespace_version)
        namespace.nodes = map(lambda x: x[1], self._names.aliases.itervalues())
        for (ns, x) in self._names.names.itervalues():
            namespace.nodes.append(x)
        return namespace

    # Private

    def _add_attribute(self, node, replace=False):
        node_name = node.name
        if (not replace) and node_name in self._names.names:
            return
        self._names.names[node_name] = (None, node)

    def _remove_attribute(self, name):
        del self._names.names[name]

    def _get_attribute(self, name):
        node = self._names.names.get(name)
        if node:
            return node[1]
        return None

    def _lookup_node(self, name):
        if name in type_names:
            return None
        node = self._get_attribute(name)
        if node is None:
            node = self._transformer.get_names().names.get(name)
            if node:
                return node[1]
        return node

    def _register_internal_type(self, type_name, node):
        self._names.type_names[type_name] = (None, node)
        uscored = to_underscores(type_name).lower()
        # prefer the prefix of the get_type method, if there is one
        if hasattr(node, 'get_type'):
            uscored = GET_TYPE_OVERRIDES.get(node.get_type, node.get_type)
            uscored = uscored[:-len('_get_type')]
        self._uscore_type_names[uscored] = node
        # Besides the straight underscore conversion, we also try
        # removing the underscores from the namespace as a possible C
        # mapping; e.g. it's webkit_web_view, not web_kit_web_view
        suffix = self._transformer.remove_prefix(type_name)
        prefix = type_name[:-len(suffix)]
        no_uscore_prefixed = (prefix + '_' + to_underscores(suffix)).lower()
        # since this is a guess, don't overwrite any 'real' prefix
        if no_uscore_prefixed not in self._uscore_type_names:
            self._uscore_type_names[no_uscore_prefixed] = node

    def _resolve_quarks(self):
        for node in self._error_quark_functions:
            short = node.symbol[:-len('_quark')]
            enum = self._uscore_type_names.get(short)
            if enum is not None:
                enum.error_quark = node.symbol

    # Helper functions

    def _resolve_gtypename(self, gtype_name):
        try:
            return self._transformer.gtypename_to_giname(gtype_name,
                                                         self._names)
        except KeyError, e:
            return Unresolved(gtype_name)

    def _execute_binary(self):
        in_path = os.path.join(self._binary.tmpdir, 'types.txt')
        f = open(in_path, 'w')
        # TODO: Introspect GQuark functions
        for func in self._get_type_functions:
            f.write(func)
            f.write('\n')
        f.close()
        out_path = os.path.join(self._binary.tmpdir, 'dump.xml')

        args = []
        args.extend(self._binary.args)
        args.append('--introspect-dump=%s,%s' % (in_path, out_path))

        # Invoke the binary, having written our get_type functions to types.txt
        try:
            subprocess.check_call(args, stdout=sys.stdout, stderr=sys.stderr)
        except subprocess.CalledProcessError, e:
            raise SystemExit(e)
        self._read_introspect_dump(out_path)

        # Clean up temporaries
        shutil.rmtree(self._binary.tmpdir)

    def _read_introspect_dump(self, xmlpath):
        from xml.etree.cElementTree import parse
        tree = parse(xmlpath)
        root = tree.getroot()
        for child in root:
            self._gtype_data[child.attrib['name']] = child
        for child in root:
            self._introspect_type(child)

    def _create_gobject(self, node):
        type_name = 'G' + node.name
        if type_name == 'GObject':
            parent_gitype = None
            symbol = 'intern'
        elif type_name == 'GInitiallyUnowned':
            parent_type_name = 'GObject'
            parent_gitype = self._resolve_gtypename(parent_type_name)
            symbol = 'g_initially_unowned_get_type'
        else:
            assert False
        gnode = GLibObject(node.name, parent_gitype, type_name, symbol, True)
        if type_name == 'GObject':
            gnode.fields.extend(node.fields)
        else:
            # http://bugzilla.gnome.org/show_bug.cgi?id=569408
            # GInitiallyUnowned is actually a typedef for GObject, but
            # that's not reflected in the GIR, where it appears as a
            # subclass (as it appears in the GType hierarchy).  So
            # what we do here is copy all of the GObject fields into
            # GInitiallyUnowned so that struct offset computation
            # works correctly.
            gnode.fields = self._names.names['Object'][1].fields
        self._add_attribute(gnode)
        self._register_internal_type(type_name, gnode)

    # Parser

    def _parse_node(self, node):
        if isinstance(node, Enum):
            self._parse_enum(node)
        elif isinstance(node, Bitfield):
            self._parse_bitfield(node)
        elif isinstance(node, Function):
            self._parse_function(node)
        elif isinstance(node, Record):
            self._parse_record(node)
        elif isinstance(node, Callback):
            self._parse_callback(node)
        elif isinstance(node, Alias):
            self._parse_alias(node)
        elif isinstance(node, Member):
            # FIXME: atk_misc_instance singletons
            pass
        elif isinstance(node, Union):
            self._parse_union(node)
        elif isinstance(node, Constant):
            self._parse_constant(node)
        else:
            print 'GLIB Transformer: Unhandled node:', node

    def _parse_alias(self, alias):
        self._names.aliases[alias.name] = (None, alias)

    def _parse_enum(self, enum):
        self._add_attribute(enum)

    def _parse_bitfield(self, enum):
        self._add_attribute(enum)

    def _parse_constant(self, constant):
        self._add_attribute(constant)

    def _parse_function(self, func):
        if func.symbol in SYMBOL_BLACKLIST:
            return
        if func.symbol.startswith('_'):
            return
        for regexp in SYMBOL_BLACKLIST_RE:
            if regexp.match(func.symbol):
                return
        if self._parse_get_type_function(func):
            return
        if self._parse_error_quark_function(func):
            return

        self._add_attribute(func)

    def _parse_get_type_function(self, func):
        symbol = func.symbol
        if not symbol.endswith('_get_type'):
            return False
        if self._namespace_name == 'GLib':
            # No GObjects in GLib
            return False
        if (self._namespace_name == 'GObject' and
            symbol in ('g_object_get_type', 'g_initially_unowned_get_type')):
            # We handle these internally, see _create_gobject
            return True
        if func.parameters:
            return False
        # GType *_get_type(void)
        if func.retval.type.name not in ['Type',
                                         'GType',
                                         'GObject.Type',
                                         'Gtk.Type']:
            print ("Warning: *_get_type function returns '%r'"
                   ", not GObject.Type") % (func.retval.type.name, )
            return False

        self._get_type_functions.append(symbol)
        return True

    def _parse_error_quark_function(self, func):
        if not func.symbol.endswith('_error_quark'):
            return False
        if func.parameters:
            return False
        if func.retval.type.name not in ['GLib.Quark',
                                         'GQuark']:
            return False

        self._error_quark_functions.append(func)
        return True

    def _name_is_internal_gtype(self, giname):
        try:
            node = self._get_attribute(giname)
            return isinstance(node, (GLibObject, GLibInterface,
                                     GLibBoxed, GLibEnum, GLibFlags))
        except KeyError, e:
            return False

    def _parse_static_method(self, func):
        components = func.symbol.split('_')
        if len(components) < 2:
            return None
        target_klass = None
        prefix_components = None
        methname = None
        for i in xrange(1, len(components)):
            prefix_components = '_'.join(components[0:-i])
            methname = '_'.join(components[-i:])
            target_klass = self._uscore_type_names.get(prefix_components)
            if target_klass and isinstance(target_klass, GLibObject):
                break
            target_klass = None
        if not target_klass:
            return None
        self._remove_attribute(func.name)
        func.name = methname
        target_klass.static_methods.append(func)
        func.is_method = True
        return func

    def _parse_method(self, func):
        if not func.parameters:
            return False
        return self._parse_method_common(func, True)

    def _parse_constructor(self, func):
        return self._parse_method_common(func, False)

    def _parse_method_common(self, func, is_method):
        # Skip _get_type functions, we processed them
        # already
        if func.symbol.endswith('_get_type'):
            return None
        if self._namespace_name == 'GLib':
            # No GObjects in GLib
            return None

        if not is_method:
            target_arg = func.retval
        else:
            target_arg = func.parameters[0]

        if is_method:
            # Methods require their first arg to be a known class
            # Look at the original C type (before namespace stripping), without
            # pointers: GtkButton -> gtk_button_, so we can figure out the
            # method name
            argtype = target_arg.type.ctype.replace('*', '')
            name = self._transformer.remove_prefix(argtype)
            name_uscore = to_underscores_noprefix(name).lower()
            # prefer the prefix of the _get_type method, if there is one
            if argtype in self._names.type_names:
                node = self._names.type_names[argtype][1]
                if hasattr(node, 'get_type'):
                    name_uscore = GET_TYPE_OVERRIDES.get(node.get_type,
                                                         node.get_type)
                    name_uscore = name_uscore[:-len('_get_type')]
            name_offset = func.symbol.find(name_uscore)
            if name_offset < 0:
                return None
            prefix = func.symbol[:name_offset+len(name_uscore)]
        else:
            # Constructors must have _new
            # Take everything before that as class name
            new_idx = func.symbol.find('_new')
            if new_idx < 0:
                return None
            # Constructors don't return basic types
            derefed = self._transformer.follow_aliases(target_arg.type.name,
                                                       self._names)
            if derefed in type_names:
                #print "NOTE: Rejecting constructor returning basic: %r" \
                #    % (func.symbol, )
                return None
            prefix = func.symbol[:new_idx]

        klass = self._uscore_type_names.get(prefix)
        if klass is None:
            #print "NOTE: No valid matching class for likely "+\
            #    "method or constructor: %r" % (func.symbol, )
            return None
        # Enums can't have ctors or methods
        if isinstance(klass, (GLibEnum, GLibFlags)):
            return None

        # The _uscore_type_names member holds the plain GLibBoxed
        # object; we want to actually use the struct/record associated
        if isinstance(klass, (Record, Union)):
            remove_prefix = klass.symbol
        else:
            remove_prefix = klass.type_name

        name = self._transformer.remove_prefix(remove_prefix)
        klass = self._get_attribute(name)
        if klass is None:
            return

        if not is_method:
            # Interfaces can't have constructors, punt to global scope
            if isinstance(klass, GLibInterface):
                #print "NOTE: Rejecting constructor for"+\
                #    " interface type: %r" % (func.symbol, )
                return None
            # TODO - check that the return type is a subclass of the
            # class from the prefix
            # But for now, ensure that constructor returns are always
            # the most concrete class
            name = self._transformer.remove_prefix(remove_prefix)
            func.retval.type = Type(name, func.retval.type.ctype)

        self._remove_attribute(func.name)
        # Strip namespace and object prefix: gtk_window_new -> new
        func.name = func.symbol[len(prefix)+1:]
        if is_method:
            # We don't need the "this" parameter
            del func.parameters[0]
            klass.methods.append(func)
            func.is_method = True
        else:
            klass.constructors.append(func)
        return func

    def _parse_record(self, record):
        # This is a hack, but GObject is a rather fundamental piece so.
        internal_names = ["Object", 'InitiallyUnowned']
        g_internal_names = ["G" + x for x in internal_names]
        if (self._namespace_name == 'GObject' and
            record.name in internal_names):
            self._create_gobject(record)
            return
        elif record.name in g_internal_names:
            # Avoid duplicates
            return
        node = self._names.names.get(record.name)
        if node is None:
            self._add_attribute(record, replace=True)
            self._register_internal_type(record.symbol, record)
            return
        (ns, node) = node
        node.fields = record.fields[:]

    def _parse_union(self, union):
        node = self._names.names.get(union.name)
        if node is None:
            self._add_attribute(union, replace=True)
            self._register_internal_type(union.symbol, union)
            return
        (ns, node) = node
        node.fields = union.fields[:]

    def _parse_callback(self, callback):
        self._add_attribute(callback)

    def _strip_class_suffix(self, name):
        if (name.endswith('Class') or
            name.endswith('Iface')):
            return name[:-5]
        elif name.endswith('Interface'):
            return name[:-9]
        else:
            return name

    def _arg_is_failed(self, param):
        ctype = self._transformer.ctype_of(param).replace('*', '')
        uscored = to_underscores(self._strip_class_suffix(ctype)).lower()
        if uscored in self._failed_types:
            print "Warning: failed type: %r" % (param, )
            return True
        return False

    def _pair_class_record(self, maybe_class):
        name = self._strip_class_suffix(maybe_class.name)
        if name == maybe_class.name:
            return

        class_struct = maybe_class
        if self._arg_is_failed(class_struct):
            print "WARNING: deleting no-type %r" % (class_struct.name, )
            del self._names.names[class_struct.name]
            return

        pair_class = self._get_attribute(name)
        if (not pair_class or
            not isinstance(pair_class, (GLibObject, GLibInterface))):
            return

        # Object class fields are assumed to be read-only
        # (see also _introspect_object and transformer.py)
        for field in maybe_class.fields:
            if isinstance(field, Field):
                field.writable = False

        # Loop through fields to determine which are virtual
        # functions and which are signal slots by
        # assuming everything that doesn't share a name
        # with a known signal is a virtual slot.
        for field in maybe_class.fields:
            if not isinstance(field, Callback):
                continue
            # Check the first parameter is the object
            if len(field.parameters) == 0:
                continue
            firstparam_type = field.parameters[0].type
            if firstparam_type != pair_class:
                continue
            # Also double check we don't have a signal with this
            # name.
            matched_signal = False
            for signal in pair_class.signals:
                if signal.name.replace('-', '_') == field.name:
                    matched_signal = True
                    break
            if matched_signal:
                continue
            vfunc = VFunction.from_callback(field)
            pair_class.virtual_methods.append(vfunc)

        # Take the set of virtual methods we found, and try
        # to pair up with any matching methods using the
        # name+signature.
        for vfunc in pair_class.virtual_methods:
            for method in pair_class.methods:
                if (method.name != vfunc.name or
                    method.retval != vfunc.retval or
                    method.parameters != vfunc.parameters):
                    continue
                vfunc.invoker = method.name

        gclass_struct = GLibRecord.from_record(class_struct)
        self._remove_attribute(class_struct.name)
        self._add_attribute(gclass_struct, True)
        pair_class.glib_type_struct = gclass_struct
        gclass_struct.is_gtype_struct_for = name

    # Introspection

    def _introspect_type(self, xmlnode):
        if xmlnode.tag in ('enum', 'flags'):
            self._introspect_enum(xmlnode)
        elif xmlnode.tag == 'class':
            self._introspect_object(xmlnode)
        elif xmlnode.tag == 'interface':
            self._introspect_interface(xmlnode)
        elif xmlnode.tag == 'boxed':
            self._introspect_boxed(xmlnode)
        else:
            raise ValueError("Unhandled introspection XML tag %s", xmlnode.tag)

    def _introspect_enum(self, node):
        members = []
        for member in node.findall('member'):
            # Keep the name closer to what we'd take from C by default;
            # see http://bugzilla.gnome.org/show_bug.cgi?id=575613
            name = member.attrib['nick'].replace('-', '_')
            members.append(GLibEnumMember(name,
                                          member.attrib['value'],
                                          member.attrib['name'],
                                          member.attrib['nick']))

        klass = (GLibFlags if node.tag == 'flags' else GLibEnum)
        type_name = node.attrib['name']
        enum_name = self._transformer.remove_prefix(type_name)
        node = klass(enum_name, type_name, members, node.attrib['get-type'])
        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_object(self, xmlnode):
        type_name = xmlnode.attrib['name']
        # We handle this specially above; in 2.16 and below there
        # was no g_object_get_type, for later versions we need
        # to skip it
        if type_name == 'GObject':
            return
        parent_type_name = xmlnode.attrib['parent']
        parent_gitype = self._resolve_gtypename(parent_type_name)
        is_abstract = not not xmlnode.attrib.get('abstract', False)
        node = GLibObject(
            self._transformer.remove_prefix(type_name),
            parent_gitype,
            type_name,
            xmlnode.attrib['get-type'], is_abstract)
        self._introspect_properties(node, xmlnode)
        self._introspect_signals(node, xmlnode)
        self._introspect_implemented_interfaces(node, xmlnode)

        # add record fields
        record = self._get_attribute(node.name)
        if record is not None:
            node.fields = record.fields
            for field in node.fields:
                if isinstance(field, Field):
                    # Object instance fields are assumed to be read-only
                    # (see also _pair_class_record and transformer.py)
                    field.writable = False

        self._add_attribute(node, replace=True)
        self._register_internal_type(type_name, node)

    def _introspect_interface(self, xmlnode):
        type_name = xmlnode.attrib['name']
        node = GLibInterface(
            self._transformer.remove_prefix(type_name),
            None,
            type_name, xmlnode.attrib['get-type'])
        self._introspect_properties(node, xmlnode)
        self._introspect_signals(node, xmlnode)
        for child in xmlnode.findall('prerequisite'):
            name = child.attrib['name']
            prereq = self._resolve_gtypename(name)
            node.prerequisites.append(prereq)
        # GtkFileChooserEmbed is an example of a private interface, we
        # just filter them out
        if xmlnode.attrib['get-type'].startswith('_'):
            print "NOTICE: Marking %s as internal type" % (type_name, )
            self._private_internal_types[type_name] = node
        else:
            self._add_attribute(node, replace=True)
            self._register_internal_type(type_name, node)

    def _introspect_boxed(self, xmlnode):
        type_name = xmlnode.attrib['name']
        # This one doesn't go in the main namespace; we associate it with
        # the struct or union
        node = GLibBoxed(type_name, xmlnode.attrib['get-type'])
        self._boxed_types[node.type_name] = node
        self._register_internal_type(type_name, node)

    def _introspect_implemented_interfaces(self, node, xmlnode):
        gt_interfaces = []
        for interface in xmlnode.findall('implements'):
            gitype = self._resolve_gtypename(interface.attrib['name'])
            gt_interfaces.append(gitype)
        node.interfaces = gt_interfaces

    def _introspect_properties(self, node, xmlnode):
        for pspec in xmlnode.findall('property'):
            ctype = pspec.attrib['type']
            flags = int(pspec.attrib['flags'])
            readable = (flags & G_PARAM_READABLE) != 0
            writable = (flags & G_PARAM_WRITABLE) != 0
            construct = (flags & G_PARAM_CONSTRUCT) != 0
            construct_only = (flags & G_PARAM_CONSTRUCT_ONLY) != 0
            node.properties.append(Property(
                pspec.attrib['name'],
                type_name_from_ctype(ctype),
                readable, writable, construct, construct_only,
                ctype,
                ))

    def _introspect_signals(self, node, xmlnode):
        for signal_info in xmlnode.findall('signal'):
            rctype = signal_info.attrib['return']
            rtype = Type(self._transformer.parse_ctype(rctype), rctype)
            return_ = Return(rtype, signal_info.attrib['return'])
            return_.transfer = PARAM_TRANSFER_FULL
            signal = GLibSignal(signal_info.attrib['name'], return_)
            for i, parameter in enumerate(signal_info.findall('param')):
                if i == 0:
                    name = 'object'
                else:
                    name = 'p%s' % (i-1, )
                pctype = parameter.attrib['type']
                ptype = Type(self._transformer.parse_ctype(pctype), pctype)
                param = Parameter(name, ptype)
                param.transfer = 'none'
                signal.parameters.append(param)
            node.signals.append(signal)

    # Resolver

    def _resolve_type_name(self, type_name, ctype=None):
        # Workaround glib bug #548689, to be included in 2.18.0
        if type_name == "GParam":
            type_name = "GObject.ParamSpec"
        res = self._transformer.resolve_type_name_full
        try:
            return res(type_name, ctype, self._names)
        except KeyError, e:
            return self._transformer.resolve_type_name(type_name, ctype)

    def _resolve_param_type(self, ptype, **kwargs):
        # Workaround glib bug #548689, to be included in 2.18.0
        if ptype.name == "GParam":
            ptype.name = "GObject.ParamSpec"
        return self._transformer.resolve_param_type_full(ptype,
                                                         self._names,
                                                         **kwargs)

    def _resolve_node(self, node):
        if isinstance(node, Function):
            self._resolve_function_toplevel(node)

        elif isinstance(node, Callback):
            self._resolve_function(node)
        elif isinstance(node, GLibObject):
            self._resolve_glib_object(node)
        elif isinstance(node, GLibInterface):
            self._resolve_glib_interface(node)
        elif isinstance(node, Record):
            self._resolve_record(node)
        elif isinstance(node, Union):
            self._resolve_union(node)
        elif isinstance(node, Alias):
            self._resolve_alias(node)

    def _resolve_function_toplevel(self, func):
        for parser in [self._parse_constructor,
                       self._parse_method,
                       self._parse_static_method]:
            newfunc = parser(func)
            if newfunc:
                self._resolve_function(newfunc)
                return
        self._resolve_function(func)

    def _pair_boxed_type(self, boxed):
        name = self._transformer.remove_prefix(boxed.type_name)
        pair_node = self._get_attribute(name)
        if not pair_node:
            boxed_item = GLibBoxedOther(name, boxed.type_name,
                                        boxed.get_type)
        elif isinstance(pair_node, Record):
            boxed_item = GLibBoxedStruct(pair_node.name, boxed.type_name,
                                         boxed.get_type)
            boxed_item.fields = pair_node.fields
        elif isinstance(pair_node, Union):
            boxed_item = GLibBoxedUnion(pair_node.name, boxed.type_name,
                                         boxed.get_type)
            boxed_item.fields = pair_node.fields
        else:
            return False
        self._add_attribute(boxed_item, replace=True)

    def _resolve_record(self, node):
        for field in node.fields:
            self._resolve_field(field)

    def _resolve_union(self, node):
        for field in node.fields:
            self._resolve_field(field)

    def _force_resolve(self, item, allow_unknown=False):
        if isinstance(item, Unresolved):
            if item.target in self._private_internal_types:
                return None
            try:
                return self._transformer.gtypename_to_giname(item.target,
                                                             self._names)
            except KeyError, e:
                if allow_unknown:
                    print "WARNING: Skipping unknown interface %s" % \
                        (item.target, )
                    return None
                else:
                    raise
        if item in self._private_internal_types:
            return None
        return item

    def _resolve_glib_interface(self, node):
        node.parent = self._force_resolve(node.parent)
        self._resolve_methods(node.methods)
        self._resolve_properties(node.properties, node)
        self._resolve_signals(node.signals)
        node.prerequisites = filter(None,
            [self._force_resolve(x, allow_unknown=True)
             for x in node.prerequisites])

    def _resolve_glib_object(self, node):
        # If we can't find the parent class, just drop back to GObject.
        # This supports hidden parent classes.
        # http://bugzilla.gnome.org/show_bug.cgi?id=561360
        try:
            node.parent = self._force_resolve(node.parent)
        except KeyError, e:
            #print ("WARNING: Parent %r of class %r" +\
            #       " not found; using GObject") % (node.parent.target,
            #                                       node.name)
            node.parent = self._transformer.gtypename_to_giname("GObject",
                                                                self._names)
        node.interfaces = filter(None,
            [self._force_resolve(x, allow_unknown=True)
                                    for x in node.interfaces])
        self._resolve_constructors(node.constructors)
        self._resolve_methods(node.methods)
        self._resolve_methods(node.static_methods)
        self._resolve_properties(node.properties, node)
        self._resolve_signals(node.signals)
        for field in node.fields:
            self._resolve_field(field)

    def _resolve_glib_boxed(self, node):
        self._resolve_constructors(node.constructors)
        self._resolve_methods(node.methods)

    def _resolve_constructors(self, constructors):
        for ctor in constructors:
            self._resolve_function(ctor)

    def _resolve_methods(self, methods):
        for method in methods:
            self._resolve_function(method)

    def _resolve_signals(self, signals):
        for signal in signals:
            self._resolve_function(signal)

    def _resolve_properties(self, properties, context):
        failed = []
        for prop in properties:
            try:
                self._resolve_property(prop)
            except KeyError, e:
                failed.append(prop)
        for fail in failed:
            #print ("WARNING: Deleting object property %r (of %r) "
            #       "with unknown type") % (fail, context)
            properties.remove(fail)

    def _resolve_property(self, prop):
        prop.type = self._resolve_param_type(prop.type, allow_invalid=False)

    def _adjust_throws(self, func):
        if func.parameters == []:
            return

        last_param = func.parameters.pop()

        if (last_param.type.name == 'GLib.Error' or
            (self._namespace_name == 'GLib' and
             last_param.type.name == 'Error')):
            func.throws = True
        else:
            func.parameters.append(last_param)

    def _resolve_function(self, func):
        self._resolve_parameters(func.parameters)
        func.retval.type = self._resolve_param_type(func.retval.type)
        self._adjust_throws(func)

    def _resolve_parameters(self, parameters):
        for parameter in parameters:
            parameter.type = self._resolve_param_type(parameter.type)

    def _resolve_field(self, field):
        if isinstance(field, Callback):
            self._resolve_function(field)
        elif isinstance(field, Record): # non-typedef'd struct
            self._resolve_record(field)
        elif isinstance(field, Union): # non-typedef'd union
            self._resolve_union(field)
        else:
            field.type = self._resolve_param_type(field.type)

    def _resolve_alias(self, alias):
        alias.target = self._resolve_type_name(alias.target, alias.target)

    def _resolve_types(self, nodes):
        nodes = list(self._names.names.itervalues())
        i = 0
        self._validating = True
        while True:
            initlen = len(nodes)

            #print "Type resolution; pass=%d" % (i, )
            nodes = list(self._names.names.itervalues())
            for node in nodes:
                try:
                    self._resolve_node(node)
                except UnknownTypeError, e:
                    print "WARNING: %s: Deleting %r" % (e, node)
                    self._remove_attribute(node.name)
            if len(nodes) == initlen:
                break
            i += 1
            self._print_statistics()
        self._validating = False

    # Validation

    def _validate_interface(self, iface):
        for vfunc in iface.virtual_methods:
            if not vfunc.invoker:
                print ("warning: Interface %r virtual function %r " + \
                       "has no known invoker") % (iface.name, vfunc.name)

    # This function is called at the very end, before we hand back the
    # completed namespace to the writer.  Add static analysis checks here.
    def _validate(self, nodes):
        for (name, node) in nodes:
            if isinstance(node, GLibInterface):
                self._validate_interface(node)
