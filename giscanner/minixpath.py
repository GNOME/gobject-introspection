# -*- Mode: Python -*-
# GObject-Introspection - a framework for introspecting GObject libraries
# Copyright (C) 2008 Colin Walters
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

from .girparser import C_NS, GLIB_NS
from .girparser import _corens

_nsmap = {'c': C_NS,
          'glib': GLIB_NS}


def myxpath(node, expr):
    """I Can't Believe It's Not XPath!"""
    elts = expr.split('/')
    curnode = node
    for elt in elts:
        if elt == '':
            continue
        try:
            (elt, qual) = elt.split('[', 1)
            qual = qual[1:-1]
            pairs = [x.split('=', 1) for x in qual.split(',')]
            exp_attrs = [(x[0], x[1][1:-1]) for x in pairs]
        except ValueError, e:
            (elt, exp_attrs) = (elt, [])
        try:
            (ns, elt) = elt.split(':', 1)
            ns = _nsmap[ns]
            elt = '{%s}%s' % (ns, elt)
        except ValueError, e:
            elt = _corens(elt)
        curnodes = curnode.findall(elt)
        if not curnodes:
            return None
        found = True
        #print "LOOKING %d nodes" % (len(curnodes), )
        for node in curnodes:
            #print "LOOKING: %r expecting: %r attrib: %r" \
            #    % (node, exp_attrs, node.attrib)
            passes = True
            for name, val in exp_attrs:
                a = node.attrib.get(name)
                if not a or a != val:
                    #print "ATTR FAIL: %r=%r" % (val, a)
                    passes = False
                    break
            if passes:
                found = True
                #print 'ATTR PASS: %r' % (node, )
                curnode = node
                break
            found = False
        if not found:
            return None
    return curnode


def xpath_assert(node, path, attribs=[]):
    elt = myxpath(node, path)
    if elt is None:
        raise AssertionError("Failed to find %r" % (path, ))
    for (name, expvalue) in attribs:
        value = elt.attrib.get(name)
        if not value:
            raise AssertionError("Failed to find attibute %r" +
                                 "in node %r" % (name, elt, ))
        if value != expvalue:
            raise AssertionError("Attibute %r in node %r has " +
                                 "unexpected value %r" % (name, elt, expvalue))
