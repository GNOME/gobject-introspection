#!/usr/bin/env python3

import sys
from pycparser import c_parser, c_ast, parse_file

class TypedefVisitor(c_ast.NodeVisitor):
    def visit_Typedef(self, node):
        if node.name.startswith("Vk"):
            print("<record name=\"" + str(node.name)[2:] + "\" c:type=\"" + str(node.name) + "\"/>")

def show_func_defs(filename):
    # Note that cpp is used. Provide a path to your own cpp or
    # make sure one exists in PATH.
    ast = parse_file(filename, use_cpp=True,
                     cpp_args=r'-I/home/matt/Projects/pycparser/utils/fake_libc_include')

    print("""<?xml version="1.0"?>
<repository version="1.2"
            xmlns="http://www.gtk.org/introspection/core/1.0"
            xmlns:c="http://www.gtk.org/introspection/c/1.0">
  <namespace name="Vulkan" version="1.0"
	     c:identifier-prefixes="VK"
	     c:symbol-prefixes="vk">
""")
    v = TypedefVisitor()
    v.visit(ast)
    print("""
  </namespace>
</repository>""")

if __name__ == "__main__":
    show_func_defs(sys.argv[1])
