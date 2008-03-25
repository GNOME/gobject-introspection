/* GObject introspection: scanner
 *
 * Copyright (C) 2008
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include "sourcescanner.h"
#include <Python.h>

#define NEW_CLASS(ctype, name, cname)	      \
static PyMethodDef _Py##cname##_methods[];    \
PyTypeObject Py##cname##_Type = {             \
    PyObject_HEAD_INIT(NULL)                  \
    0,			                      \
    "scanner." name,                          \
    sizeof(ctype),     	              \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	      \
    0, 0, 0, 0,	0, 0,			      \
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, \
    NULL, 0, 0, 0,	                      \
    0,	      \
    0, 0,                                     \
    0,                                        \
    0, 0, NULL, NULL, 0, 0,	              \
    0             \
}

#define REGISTER_TYPE(d, name, type)	      \
    type.ob_type = &PyType_Type;              \
    type.tp_alloc = PyType_GenericAlloc;      \
    type.tp_new = PyType_GenericNew;          \
    if (PyType_Ready (&type))                 \
	return;                               \
    PyDict_SetItemString (d, name, (PyObject *)&type); \
    Py_INCREF (&type);

typedef struct {
  PyObject_HEAD
  GISourceType *type;
} PyGISourceType;

typedef struct {
  PyObject_HEAD
  GISourceSymbol *symbol;
} PyGISourceSymbol;

typedef struct {
  PyObject_HEAD
  GISourceScanner *scanner;
} PyGISourceScanner;

NEW_CLASS(PyGISourceSymbol, "SourceSymbol", GISourceSymbol);
NEW_CLASS(PyGISourceType, "SourceType", GISourceType);
NEW_CLASS(PyGISourceScanner, "SourceScanner", GISourceScanner);


/* Symbol */

static PyObject *
symbol_get_type(PyGISourceSymbol *self,
		void             *context)
{
  return PyInt_FromLong(self->symbol->type);
}

static PyObject *
symbol_get_ident(PyGISourceSymbol *self,
		  void            *context)
{
  return PyString_FromString(self->symbol->ident);
}

static PyObject *
symbol_get_base_type(PyGISourceSymbol *self,
		     void             *context)
{
  PyGISourceType *item;
  item = (PyGISourceType *)PyObject_GC_New(PyGISourceType,
					   &PyGISourceType_Type);
  item->type = self->symbol->base_type;
  return (PyObject*)item;
}

static PyGetSetDef _PyGISourceSymbol_getsets[] = {
  { "type", (getter)symbol_get_type, NULL, NULL},
  { "ident", (getter)symbol_get_ident, NULL, NULL},
  { "base_type", (getter)symbol_get_base_type, NULL, NULL},
  { 0 }
};



/* Type */

static PyObject *
type_get_type(PyGISourceType *self,
	      void           *context)
{
  return PyInt_FromLong(self->type->type);
}

static PyObject *
type_get_name(PyGISourceType *self,
	      void           *context)
{
  if (!self->type->name)
    {
      Py_INCREF(Py_None);
      return Py_None;
    }
    
  return PyString_FromString(self->type->name);
}

static PyGetSetDef _PyGISourceType_getsets[] = {
  { "type", (getter)type_get_type, NULL, NULL},
  { "name", (getter)type_get_name, NULL, NULL},
  { 0 }
};



/* Scanner */

static int
pygi_source_scanner_init (PyGISourceScanner *self,
			  PyObject  	    *args,
			  PyObject 	    *kwargs)
{
  if (!PyArg_ParseTuple (args, ":SourceScanner.__init__"))
    return -1;

  self->scanner = gi_source_scanner_new ();

  return 0;
}

static PyObject *
pygi_source_scanner_parse_file (PyGISourceScanner *self,
				PyObject          *args)
{
  char *filename;
  FILE *fp;
  
  if (!PyArg_ParseTuple (args, "s:SourceScanner.__init__", &filename))
    return NULL;

  fp = fopen (filename, "r");
  if (!fp)
    {
      PyErr_SetFromErrnoWithFilename (PyExc_OSError, filename);
      return NULL;
    }

  self->scanner->filenames =
    g_list_append (self->scanner->filenames, g_strdup (filename));
  self->scanner->current_filename = self->scanner->filenames->data;
  
  if (!gi_source_scanner_parse_file (self->scanner, fp))
    {
      g_print ("Something went wrong..\n");
      return NULL;
    }

  fclose (fp);

  Py_INCREF (Py_None);
  return Py_None;
}

static PyObject *
pygi_source_scanner_set_macro_scan (PyGISourceScanner *self,
				    PyObject          *args)
{
  int macro_scan;
  
  if (!PyArg_ParseTuple (args, "b:SourceScanner.set_macro_scan", &macro_scan))
    return NULL;

  gi_source_scanner_set_macro_scan (self->scanner, macro_scan);

  Py_INCREF (Py_None);
  return Py_None;
}

static PyObject *
pygi_source_scanner_get_symbols (PyGISourceScanner *self)
{
  GSList *l, *symbols;
  PyObject *list;
  int i = 0;
  
  symbols = gi_source_scanner_get_symbols (self->scanner);
  list = PyList_New (g_slist_length (symbols));
  
  for (l = symbols; l; l = l->next)
    {
      PyGISourceSymbol *item;
      item = (PyGISourceSymbol *)PyObject_GC_New(PyGISourceSymbol,
						 &PyGISourceSymbol_Type);
      item->symbol = l->data;
      PyList_SetItem(list, i++, (PyObject*)item);
    }
  
  return list;
}

static PyMethodDef _PyGISourceScanner_methods[] = {
  { "get_symbols", (PyCFunction) pygi_source_scanner_get_symbols, METH_NOARGS },
  { "parse_file", (PyCFunction) pygi_source_scanner_parse_file, METH_VARARGS },
  { "set_macro_scan", (PyCFunction) pygi_source_scanner_set_macro_scan, METH_VARARGS },
  { NULL, NULL, 0 }
};


/* Module */

PyMethodDef pyscanner_functions[] = {
  { NULL, NULL, 0, NULL }
};

DL_EXPORT(void)
init_giscanner(void)
{
    PyObject *m, *d;

    m = Py_InitModule ("giscanner._giscanner", pyscanner_functions);
    d = PyModule_GetDict (m);

    PyGISourceScanner_Type.tp_init = (initproc)pygi_source_scanner_init;
    PyGISourceScanner_Type.tp_methods = _PyGISourceScanner_methods;
    REGISTER_TYPE (d, "SourceScanner", PyGISourceScanner_Type);

    PyGISourceSymbol_Type.tp_getset = _PyGISourceSymbol_getsets;
    REGISTER_TYPE (d, "SourceSymbol", PyGISourceSymbol_Type);

    PyGISourceType_Type.tp_getset = _PyGISourceType_getsets;
    REGISTER_TYPE (d, "SourceType", PyGISourceType_Type);
}
