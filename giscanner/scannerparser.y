/* GObject introspection: C parser -*- indent-tabs-mode: t; tab-width: 8 -*-
 *
 * Copyright (c) 1997 Sandro Sigala  <ssigala@globalnet.it>
 * Copyright (c) 2007-2008 Jürg Billeter  <j@bitron.ch>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <glib/gstdio.h>
#include "sourcescanner.h"
#include "scannerparser.h"

extern FILE *yyin;
extern int lineno;
extern char linebuf[2000];
extern char *yytext;

extern int yylex (GISourceScanner *scanner);
static void yyerror (GISourceScanner *scanner, const char *str);

extern void ctype_free (GISourceType * type);

static int last_enum_value = -1;
static gboolean is_bitfield;
static GHashTable *const_table = NULL;

/**
 * parse_c_string_literal:
 * @str: A string containing a C string literal
 *
 * Based on g_strcompress(), but also handles
 * hexadecimal escapes.
 */
static char *
parse_c_string_literal (const char *str)
{
  const gchar *p = str, *num;
  gchar *dest = g_malloc (strlen (str) + 1);
  gchar *q = dest;

  while (*p)
    {
      if (*p == '\\')
        {
          p++;
          switch (*p)
            {
            case '\0':
              g_warning ("parse_c_string_literal: trailing \\");
              goto out;
            case '0':  case '1':  case '2':  case '3':  case '4':
            case '5':  case '6':  case '7':
              *q = 0;
              num = p;
              while ((p < num + 3) && (*p >= '0') && (*p <= '7'))
                {
                  *q = (*q * 8) + (*p - '0');
                  p++;
                }
              q++;
              p--;
              break;
	    case 'x':
	      *q = 0;
	      p++;
	      num = p;
	      while ((p < num + 2) && (g_ascii_isxdigit(*p)))
		{
		  *q = (*q * 16) + g_ascii_xdigit_value(*p);
		  p++;
		}
              q++;
              p--;
	      break;
            case 'b':
              *q++ = '\b';
              break;
            case 'f':
              *q++ = '\f';
              break;
            case 'n':
              *q++ = '\n';
              break;
            case 'r':
              *q++ = '\r';
              break;
            case 't':
              *q++ = '\t';
              break;
            default:            /* Also handles \" and \\ */
              *q++ = *p;
              break;
            }
        }
      else
        *q++ = *p;
      p++;
    }
out:
  *q = 0;

  return dest;
}

%}

%error-verbose
%union {
  char *str;
  GList *list;
  GISourceSymbol *symbol;
  GISourceType *ctype;
  StorageClassSpecifier storage_class_specifier;
  TypeQualifier type_qualifier;
  FunctionSpecifier function_specifier;
  UnaryOperator unary_operator;
}

%parse-param { GISourceScanner* scanner }
%lex-param { GISourceScanner* scanner }

%token <str> IDENTIFIER "identifier"
%token <str> TYPEDEF_NAME "typedef-name"

%token INTEGER FLOATING CHARACTER STRING

%token INTL_CONST INTUL_CONST
%token ELLIPSIS ADDEQ SUBEQ MULEQ DIVEQ MODEQ XOREQ ANDEQ OREQ SL SR
%token SLEQ SREQ EQ NOTEQ LTEQ GTEQ ANDAND OROR PLUSPLUS MINUSMINUS ARROW

%token AUTO BOOL BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM
%token EXTENSION EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT
%token RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED
%token VOID VOLATILE WHILE

%token FUNCTION_MACRO OBJECT_MACRO

%start translation_unit

%type <ctype> declaration_specifiers
%type <ctype> enum_specifier
%type <ctype> pointer
%type <ctype> specifier_qualifier_list
%type <ctype> type_name
%type <ctype> struct_or_union
%type <ctype> struct_or_union_specifier
%type <ctype> type_specifier
%type <str> identifier
%type <str> typedef_name
%type <str> identifier_or_typedef_name
%type <symbol> abstract_declarator
%type <symbol> init_declarator
%type <symbol> declarator
%type <symbol> enumerator
%type <symbol> direct_abstract_declarator
%type <symbol> direct_declarator
%type <symbol> parameter_declaration
%type <symbol> struct_declarator
%type <list> enumerator_list
%type <list> identifier_list
%type <list> init_declarator_list
%type <list> parameter_list
%type <list> struct_declaration
%type <list> struct_declaration_list
%type <list> struct_declarator_list
%type <storage_class_specifier> storage_class_specifier
%type <type_qualifier> type_qualifier
%type <type_qualifier> type_qualifier_list
%type <function_specifier> function_specifier
%type <symbol> expression
%type <symbol> constant_expression
%type <symbol> conditional_expression
%type <symbol> logical_and_expression
%type <symbol> logical_or_expression
%type <symbol> inclusive_or_expression
%type <symbol> exclusive_or_expression
%type <symbol> multiplicative_expression
%type <symbol> additive_expression
%type <symbol> shift_expression
%type <symbol> relational_expression
%type <symbol> equality_expression
%type <symbol> and_expression
%type <symbol> cast_expression
%type <symbol> assignment_expression
%type <symbol> unary_expression
%type <symbol> postfix_expression
%type <symbol> primary_expression
%type <unary_operator> unary_operator
%type <str> function_macro
%type <str> object_macro
%type <symbol> strings

%%

/* A.2.1 Expressions. */

primary_expression
	: identifier
	  {
		$$ = g_hash_table_lookup (const_table, $1);
		if ($$ == NULL) {
			$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		} else {
			$$ = gi_source_symbol_ref ($$);
		}
	  }
	| INTEGER
	  {
		char *rest;
		guint64 value;
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		if (g_str_has_prefix (yytext, "0x") && strlen (yytext) > 2) {
			value = g_ascii_strtoull (yytext + 2, &rest, 16);
		} else if (g_str_has_prefix (yytext, "0") && strlen (yytext) > 1) {
			value = g_ascii_strtoull (yytext + 1, &rest, 8);
		} else {
			value = g_ascii_strtoull (yytext, &rest, 10);
		}
		$$->const_int = value;
		$$->const_int_is_unsigned = (rest && (rest[0] == 'U'));
	  }
	| CHARACTER
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = g_utf8_get_char(yytext + 1);
	  }
	| FLOATING
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_double_set = TRUE;
		$$->const_double = 0.0;
        sscanf (yytext, "%lf", &($$->const_double));
	  }
	| strings
	| '(' expression ')'
	  {
		$$ = $2;
	  }
	| EXTENSION '(' '{' block_item_list '}' ')'
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	;

/* concatenate adjacent string literal tokens */
strings
	: STRING
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		yytext[strlen (yytext) - 1] = '\0';
		$$->const_string = parse_c_string_literal (yytext + 1);
                if (!g_utf8_validate ($$->const_string, -1, NULL))
                  {
#if 0
                    g_warning ("Ignoring non-UTF-8 constant string \"%s\"", yytext + 1);
#endif
                    g_free($$->const_string);
                    $$->const_string = NULL;
                  }

	  }
	| strings STRING
	  {
		char *strings, *string2;
		$$ = $1;
		yytext[strlen (yytext) - 1] = '\0';
		string2 = parse_c_string_literal (yytext + 1);
		strings = g_strconcat ($$->const_string, string2, NULL);
		g_free ($$->const_string);
		g_free (string2);
		$$->const_string = strings;
	  }
	;

identifier
	: IDENTIFIER
	  {
		$$ = g_strdup (yytext);
	  }
	;

identifier_or_typedef_name
	: identifier
	| typedef_name
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| postfix_expression '(' argument_expression_list ')'
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| postfix_expression '(' ')'
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| postfix_expression '.' identifier_or_typedef_name
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| postfix_expression ARROW identifier_or_typedef_name
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| postfix_expression PLUSPLUS
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| postfix_expression MINUSMINUS
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| PLUSPLUS unary_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| MINUSMINUS unary_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| unary_operator cast_expression
	  {
		switch ($1) {
		case UNARY_PLUS:
			$$ = $2;
			break;
		case UNARY_MINUS:
			$$ = $2;
			$$->const_int = -$2->const_int;
			break;
		case UNARY_BITWISE_COMPLEMENT:
			$$ = $2;
			$$->const_int = ~$2->const_int;
			break;
		case UNARY_LOGICAL_NEGATION:
			$$ = $2;
			$$->const_int = !gi_source_symbol_get_const_boolean ($2);
			break;
		default:
			$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
			break;
		}
	  }
	| INTL_CONST '(' unary_expression ')'
	  {
		$$ = $3;
		if ($$->const_int_set) {
			$$->base_type = gi_source_basic_type_new ($$->const_int_is_unsigned ? "guint64" : "gint64");
		}
	  }
	| INTUL_CONST '(' unary_expression ')'
	  {
		$$ = $3;
		if ($$->const_int_set) {
			$$->base_type = gi_source_basic_type_new ("guint64");
		}
	  }
	| SIZEOF unary_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| SIZEOF '(' type_name ')'
	  {
		ctype_free ($3);
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	;

unary_operator
	: '&'
	  {
		$$ = UNARY_ADDRESS_OF;
	  }
	| '*'
	  {
		$$ = UNARY_POINTER_INDIRECTION;
	  }
	| '+'
	  {
		$$ = UNARY_PLUS;
	  }
	| '-'
	  {
		$$ = UNARY_MINUS;
	  }
	| '~'
	  {
		$$ = UNARY_BITWISE_COMPLEMENT;
	  }
	| '!'
	  {
		$$ = UNARY_LOGICAL_NEGATION;
	  }
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	  {
		$$ = $4;
		if ($$->const_int_set || $$->const_double_set || $$->const_string != NULL) {
			$$->base_type = $2;
		} else {
			ctype_free ($2);
		}
	  }
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int * $3->const_int;
	  }
	| multiplicative_expression '/' cast_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		if ($3->const_int != 0) {
			$$->const_int = $1->const_int / $3->const_int;
		}
	  }
	| multiplicative_expression '%' cast_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		if ($3->const_int != 0) {
			$$->const_int = $1->const_int % $3->const_int;
		}
	  }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int + $3->const_int;
	  }
	| additive_expression '-' multiplicative_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int - $3->const_int;
	  }
	;

shift_expression
	: additive_expression
	| shift_expression SL additive_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int << $3->const_int;

		/* assume this is a bitfield/flags declaration
		 * if a left shift operator is sued in an enum value
                 * This mimics the glib-mkenum behavior.
		 */
		is_bitfield = TRUE;
	  }
	| shift_expression SR additive_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int >> $3->const_int;
	  }
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int < $3->const_int;
	  }
	| relational_expression '>' shift_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int > $3->const_int;
	  }
	| relational_expression LTEQ shift_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int <= $3->const_int;
	  }
	| relational_expression GTEQ shift_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int >= $3->const_int;
	  }
	;

equality_expression
	: relational_expression
	| equality_expression EQ relational_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int == $3->const_int;
	  }
	| equality_expression NOTEQ relational_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int != $3->const_int;
	  }
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int & $3->const_int;
	  }
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int ^ $3->const_int;
	  }
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int = $1->const_int | $3->const_int;
	  }
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression ANDAND inclusive_or_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int =
		  gi_source_symbol_get_const_boolean ($1) &&
		  gi_source_symbol_get_const_boolean ($3);
	  }
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OROR logical_and_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_filename, lineno);
		$$->const_int_set = TRUE;
		$$->const_int =
		  gi_source_symbol_get_const_boolean ($1) ||
		  gi_source_symbol_get_const_boolean ($3);
	  }
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' expression
	  {
		$$ = gi_source_symbol_get_const_boolean ($1) ? $3 : $5;
	  }
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	;

assignment_operator
	: '='
	| MULEQ
	| DIVEQ
	| MODEQ
	| ADDEQ
	| SUBEQ
	| SLEQ
	| SREQ
	| ANDEQ
	| XOREQ
	| OREQ
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	| EXTENSION expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	;

constant_expression
	: conditional_expression
	;

/* A.2.2 Declarations. */

declaration
	: declaration_specifiers init_declarator_list ';'
	  {
		GList *l;
		for (l = $2; l != NULL; l = l->next) {
			GISourceSymbol *sym = l->data;
			gi_source_symbol_merge_type (sym, gi_source_type_copy ($1));
			if ($1->storage_class_specifier & STORAGE_CLASS_TYPEDEF) {
				sym->type = CSYMBOL_TYPE_TYPEDEF;
			} else if (sym->base_type->type == CTYPE_FUNCTION) {
				sym->type = CSYMBOL_TYPE_FUNCTION;
			} else {
				sym->type = CSYMBOL_TYPE_OBJECT;
			}
			gi_source_scanner_add_symbol (scanner, sym);
			gi_source_symbol_unref (sym);
		}
		ctype_free ($1);
	  }
	| declaration_specifiers ';'
	  {
		ctype_free ($1);
	  }
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers
	  {
		$$ = $2;
		$$->storage_class_specifier |= $1;
	  }
	| storage_class_specifier
	  {
		$$ = gi_source_type_new (CTYPE_INVALID);
		$$->storage_class_specifier |= $1;
	  }
	| type_specifier declaration_specifiers
	  {
		$$ = $1;
		/* combine basic types like unsigned int and long long */
		if ($$->type == CTYPE_BASIC_TYPE && $2->type == CTYPE_BASIC_TYPE) {
			char *name = g_strdup_printf ("%s %s", $$->name, $2->name);
			g_free ($$->name);
			$$->name = name;
			ctype_free ($2);
		} else {
			$$->base_type = $2;
		}
	  }
	| type_specifier
	| type_qualifier declaration_specifiers
	  {
		$$ = $2;
		$$->type_qualifier |= $1;
	  }
	| type_qualifier
	  {
		$$ = gi_source_type_new (CTYPE_INVALID);
		$$->type_qualifier |= $1;
	  }
	| function_specifier declaration_specifiers
	  {
		$$ = $2;
		$$->function_specifier |= $1;
	  }
	| function_specifier
	  {
		$$ = gi_source_type_new (CTYPE_INVALID);
		$$->function_specifier |= $1;
	  }
	;

init_declarator_list
	: init_declarator
	  {
		$$ = g_list_append (NULL, $1);
	  }
	| init_declarator_list ',' init_declarator
	  {
		$$ = g_list_append ($1, $3);
	  }
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	  {
		$$ = STORAGE_CLASS_TYPEDEF;
	  }
	| EXTERN
	  {
		$$ = STORAGE_CLASS_EXTERN;
	  }
	| STATIC
	  {
		$$ = STORAGE_CLASS_STATIC;
	  }
	| AUTO
	  {
		$$ = STORAGE_CLASS_AUTO;
	  }
	| REGISTER
	  {
		$$ = STORAGE_CLASS_REGISTER;
	  }
	;

type_specifier
	: VOID
	  {
		$$ = gi_source_type_new (CTYPE_VOID);
	  }
	| CHAR
	  {
		$$ = gi_source_basic_type_new ("char");
	  }
	| SHORT
	  {
		$$ = gi_source_basic_type_new ("short");
	  }
	| INT
	  {
		$$ = gi_source_basic_type_new ("int");
	  }
	| LONG
	  {
		$$ = gi_source_basic_type_new ("long");
	  }
	| FLOAT
	  {
		$$ = gi_source_basic_type_new ("float");
	  }
	| DOUBLE
	  {
		$$ = gi_source_basic_type_new ("double");
	  }
	| SIGNED
	  {
		$$ = gi_source_basic_type_new ("signed");
	  }
	| UNSIGNED
	  {
		$$ = gi_source_basic_type_new ("unsigned");
	  }
	| BOOL
	  {
		$$ = gi_source_basic_type_new ("bool");
	  }
	| struct_or_union_specifier
	| enum_specifier
	| typedef_name
	  {
		$$ = gi_source_typedef_new ($1);
		g_free ($1);
	  }
	;

struct_or_union_specifier
	: struct_or_union identifier_or_typedef_name '{' struct_declaration_list '}'
	  {
		$$ = $1;
		$$->name = $2;
		$$->child_list = $4;

		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		if ($$->type == CTYPE_STRUCT) {
			sym->type = CSYMBOL_TYPE_STRUCT;
		} else if ($$->type == CTYPE_UNION) {
			sym->type = CSYMBOL_TYPE_UNION;
		} else {
			g_assert_not_reached ();
		}
		sym->ident = g_strdup ($$->name);
		sym->base_type = gi_source_type_copy ($$);
		gi_source_scanner_add_symbol (scanner, sym);
		gi_source_symbol_unref (sym);
	  }
	| struct_or_union '{' struct_declaration_list '}'
	  {
		$$ = $1;
		$$->child_list = $3;
	  }
	| struct_or_union identifier_or_typedef_name
	  {
		$$ = $1;
		$$->name = $2;
	  }
	;

struct_or_union
	: STRUCT
	  {
                scanner->private = FALSE;
		$$ = gi_source_struct_new (NULL);
	  }
	| UNION
	  {
                scanner->private = FALSE;
		$$ = gi_source_union_new (NULL);
	  }
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	  {
		$$ = g_list_concat ($1, $2);
	  }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	  {
	    GList *l;
	    $$ = NULL;
	    for (l = $2; l != NULL; l = l->next)
	      {
		GISourceSymbol *sym = l->data;
		if ($1->storage_class_specifier & STORAGE_CLASS_TYPEDEF)
		    sym->type = CSYMBOL_TYPE_TYPEDEF;
		else
		    sym->type = CSYMBOL_TYPE_MEMBER;
		gi_source_symbol_merge_type (sym, gi_source_type_copy ($1));
                sym->private = scanner->private;
                $$ = g_list_append ($$, sym);
	      }
	    ctype_free ($1);
	  }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	  {
		$$ = $1;
		$$->base_type = $2;
	  }
	| type_specifier
	| type_qualifier specifier_qualifier_list
	  {
		$$ = $2;
		$$->type_qualifier |= $1;
	  }
	| type_qualifier
	  {
		$$ = gi_source_type_new (CTYPE_INVALID);
		$$->type_qualifier |= $1;
	  }
	;

struct_declarator_list
	: struct_declarator
	  {
		$$ = g_list_append (NULL, $1);
	  }
	| struct_declarator_list ',' struct_declarator
	  {
		$$ = g_list_append ($1, $3);
	  }
	;

struct_declarator
	: /* empty, support for anonymous structs and unions */
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| declarator
	| ':' constant_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
	  }
	| declarator ':' constant_expression
	  {
		$$ = $1;
		if ($3->const_int_set) {
		  $$->const_int_set = TRUE;
		  $$->const_int = $3->const_int;
		}
	  }
	;

enum_specifier
	: enum_keyword identifier_or_typedef_name '{' enumerator_list '}'
	  {
		$$ = gi_source_enum_new ($2);
		$$->child_list = $4;
		$$->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
	| enum_keyword '{' enumerator_list '}'
	  {
		$$ = gi_source_enum_new (NULL);
		$$->child_list = $3;
		$$->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
	| enum_keyword identifier_or_typedef_name '{' enumerator_list ',' '}'
	  {
		$$ = gi_source_enum_new ($2);
		$$->child_list = $4;
		$$->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
	| enum_keyword '{' enumerator_list ',' '}'
	  {
		$$ = gi_source_enum_new (NULL);
		$$->child_list = $3;
		$$->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
	| enum_keyword identifier_or_typedef_name
	  {
		$$ = gi_source_enum_new ($2);
	  }
	;

enum_keyword
        : ENUM
          {
                scanner->flags = FALSE;
                scanner->private = FALSE;
          }
        ;

enumerator_list
	:
	  {
		/* reset flag before the first enum value */
		is_bitfield = FALSE;
	  }
	  enumerator
	  {
            $2->private = scanner->private;
            $$ = g_list_append (NULL, $2);
	  }
	| enumerator_list ',' enumerator
	  {
            $3->private = scanner->private;
            $$ = g_list_append ($1, $3);
	  }
	;

enumerator
	: identifier
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_OBJECT, scanner->current_filename, lineno);
		$$->ident = $1;
		$$->const_int_set = TRUE;
		$$->const_int = ++last_enum_value;
		g_hash_table_insert (const_table, g_strdup ($$->ident), gi_source_symbol_ref ($$));
	  }
	| identifier '=' constant_expression
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_OBJECT, scanner->current_filename, lineno);
		$$->ident = $1;
		$$->const_int_set = TRUE;
		$$->const_int = $3->const_int;
		last_enum_value = $$->const_int;
		g_hash_table_insert (const_table, g_strdup ($$->ident), gi_source_symbol_ref ($$));
	  }
	;

type_qualifier
	: CONST
	  {
		$$ = TYPE_QUALIFIER_CONST;
	  }
	| RESTRICT
	  {
		$$ = TYPE_QUALIFIER_RESTRICT;
	  }
	| EXTENSION
	  {
		$$ = TYPE_QUALIFIER_EXTENSION;
	  }
	| VOLATILE
	  {
		$$ = TYPE_QUALIFIER_VOLATILE;
	  }
	;

function_specifier
	: INLINE
	  {
		$$ = FUNCTION_INLINE;
	  }
	;

declarator
	: pointer direct_declarator
	  {
		$$ = $2;
		gi_source_symbol_merge_type ($$, $1);
	  }
	| direct_declarator
	;

direct_declarator
	: identifier
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		$$->ident = $1;
	  }
	| '(' declarator ')'
	  {
		$$ = $2;
	  }
	| direct_declarator '[' assignment_expression ']'
	  {
		$$ = $1;
		gi_source_symbol_merge_type ($$, gi_source_array_new ($3));
	  }
	| direct_declarator '[' ']'
	  {
		$$ = $1;
		gi_source_symbol_merge_type ($$, gi_source_array_new (NULL));
	  }
	| direct_declarator '(' parameter_list ')'
	  {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ($3 != NULL && ($3->next != NULL || ((GISourceSymbol *) $3->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = $3;
		}
		$$ = $1;
		gi_source_symbol_merge_type ($$, func);
	  }
	| direct_declarator '(' identifier_list ')'
	  {
		GISourceType *func = gi_source_function_new ();
		func->child_list = $3;
		$$ = $1;
		gi_source_symbol_merge_type ($$, func);
	  }
	| direct_declarator '(' ')'
	  {
		GISourceType *func = gi_source_function_new ();
		$$ = $1;
		gi_source_symbol_merge_type ($$, func);
	  }
	;

pointer
	: '*' type_qualifier_list
	  {
		$$ = gi_source_pointer_new (NULL);
		$$->type_qualifier = $2;
	  }
	| '*'
	  {
		$$ = gi_source_pointer_new (NULL);
	  }
	| '*' type_qualifier_list pointer
	  {
		GISourceType **base = &($3->base_type);

		while (*base != NULL) {
			base = &((*base)->base_type);
		}
		*base = gi_source_pointer_new (NULL);
		(*base)->type_qualifier = $2;
		$$ = $3;
	  }
	| '*' pointer
	  {
		GISourceType **base = &($2->base_type);

		while (*base != NULL) {
			base = &((*base)->base_type);
		}
		*base = gi_source_pointer_new (NULL);
		$$ = $2;
	  }
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	  {
		$$ = $1 | $2;
	  }
	;

parameter_list
	: parameter_declaration
	  {
		$$ = g_list_append (NULL, $1);
	  }
	| parameter_list ',' parameter_declaration
	  {
		$$ = g_list_append ($1, $3);
	  }
	;

parameter_declaration
	: declaration_specifiers declarator
	  {
		$$ = $2;
		gi_source_symbol_merge_type ($$, $1);
	  }
	| declaration_specifiers abstract_declarator
	  {
		$$ = $2;
		gi_source_symbol_merge_type ($$, $1);
	  }
	| declaration_specifiers
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		$$->base_type = $1;
	  }
	| ELLIPSIS
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_ELLIPSIS, scanner->current_filename, lineno);
	  }
	;

identifier_list
	: identifier
	  {
		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		sym->ident = $1;
		$$ = g_list_append (NULL, sym);
	  }
	| identifier_list ',' identifier
	  {
		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		sym->ident = $3;
		$$ = g_list_append ($1, sym);
	  }
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		gi_source_symbol_merge_type ($$, $1);
	  }
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	  {
		$$ = $2;
		gi_source_symbol_merge_type ($$, $1);
	  }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	  {
		$$ = $2;
	  }
	| '[' ']'
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		gi_source_symbol_merge_type ($$, gi_source_array_new (NULL));
	  }
	| '[' assignment_expression ']'
	  {
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		gi_source_symbol_merge_type ($$, gi_source_array_new ($2));
	  }
	| direct_abstract_declarator '[' ']'
	  {
		$$ = $1;
		gi_source_symbol_merge_type ($$, gi_source_array_new (NULL));
	  }
	| direct_abstract_declarator '[' assignment_expression ']'
	  {
		$$ = $1;
		gi_source_symbol_merge_type ($$, gi_source_array_new ($3));
	  }
	| '(' ')'
	  {
		GISourceType *func = gi_source_function_new ();
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		gi_source_symbol_merge_type ($$, func);
	  }
	| '(' parameter_list ')'
	  {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ($2 != NULL && ($2->next != NULL || ((GISourceSymbol *) $2->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = $2;
		}
		$$ = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_filename, lineno);
		gi_source_symbol_merge_type ($$, func);
	  }
	| direct_abstract_declarator '(' ')'
	  {
		GISourceType *func = gi_source_function_new ();
		$$ = $1;
		gi_source_symbol_merge_type ($$, func);
	  }
	| direct_abstract_declarator '(' parameter_list ')'
	  {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ($3 != NULL && ($3->next != NULL || ((GISourceSymbol *) $3->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = $3;
		}
		$$ = $1;
		gi_source_symbol_merge_type ($$, func);
	  }
	;

typedef_name
	: TYPEDEF_NAME
	  {
		$$ = g_strdup (yytext);
	  }
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

/* A.2.3 Statements. */

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: identifier_or_typedef_name ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' block_item_list '}'
	;

block_item_list
	: block_item
	| block_item_list block_item
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' ';' ';' ')' statement
	| FOR '(' expression ';' ';' ')' statement
	| FOR '(' ';' expression ';' ')' statement
	| FOR '(' expression ';' expression ';' ')' statement
	| FOR '(' ';' ';' expression ')' statement
	| FOR '(' expression ';' ';' expression ')' statement
	| FOR '(' ';' expression ';' expression ')' statement
	| FOR '(' expression ';' expression ';' expression ')' statement
	;

jump_statement
	: GOTO identifier_or_typedef_name ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

/* A.2.4 External definitions. */

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	| macro
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

/* Macros */

function_macro
	: FUNCTION_MACRO
	  {
		$$ = g_strdup (yytext + strlen ("#define "));
	  }
	;

object_macro
	: OBJECT_MACRO
	  {
		$$ = g_strdup (yytext + strlen ("#define "));
	  }
	;

function_macro_define
	: function_macro '(' identifier_list ')'
	;

object_macro_define
	: object_macro constant_expression
	  {
		if ($2->const_int_set || $2->const_double_set || $2->const_string != NULL) {
			$2->ident = $1;
			gi_source_scanner_add_symbol (scanner, $2);
			gi_source_symbol_unref ($2);
		}
	  }
	;

macro
	: function_macro_define
	| object_macro_define
	| error
	;

%%
static void
yyerror (GISourceScanner *scanner, const char *s)
{
  /* ignore errors while doing a macro scan as not all object macros
   * have valid expressions */
  if (!scanner->macro_scan)
    {
      fprintf(stderr, "%s:%d: %s in '%s' at '%s'\n",
	      scanner->current_filename, lineno, s, linebuf, yytext);
    }
}

static int
eat_hspace (FILE * f)
{
  int c;
  do
    {
      c = fgetc (f);
    }
  while (c == ' ' || c == '\t');
  return c;
}

static int
eat_line (FILE * f, int c)
{
  while (c != EOF && c != '\n')
    {
      c = fgetc (f);
    }
  if (c == '\n')
    {
      c = fgetc (f);
      if (c == ' ' || c == '\t')
        {
          c = eat_hspace (f);
        }
    }
  return c;
}

static int
read_identifier (FILE * f, int c, char **identifier)
{
  GString *id = g_string_new ("");
  while (g_ascii_isalnum (c) || c == '_')
    {
      g_string_append_c (id, c);
      c = fgetc (f);
    }
  *identifier = g_string_free (id, FALSE);
  return c;
}

void
gi_source_scanner_parse_macros (GISourceScanner *scanner, GList *filenames)
{
  GError *error = NULL;
  char *tmp_name = NULL;
  FILE *fmacros =
    fdopen (g_file_open_tmp ("gen-introspect-XXXXXX.h", &tmp_name, &error),
            "w+");
  g_unlink (tmp_name);

  GList *l;
  for (l = filenames; l != NULL; l = l->next)
    {
      FILE *f = fopen (l->data, "r");
      int line = 1;

      GString *define_line;
      char *str;
      gboolean error_line = FALSE;
      int c = eat_hspace (f);
      while (c != EOF)
        {
          if (c != '#')
            {
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }

          /* print current location */
          str = g_strescape (l->data, "");
          fprintf (fmacros, "# %d \"%s\"\n", line, str);
          g_free (str);

          c = eat_hspace (f);
          c = read_identifier (f, c, &str);
          if (strcmp (str, "define") != 0 || (c != ' ' && c != '\t'))
            {
              g_free (str);
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          g_free (str);
          c = eat_hspace (f);
          c = read_identifier (f, c, &str);
          if (strlen (str) == 0 || (c != ' ' && c != '\t' && c != '('))
            {
              g_free (str);
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          define_line = g_string_new ("#define ");
          g_string_append (define_line, str);
          g_free (str);
          if (c == '(')
            {
              while (c != ')')
                {
                  g_string_append_c (define_line, c);
                  c = fgetc (f);
                  if (c == EOF || c == '\n')
                    {
                      error_line = TRUE;
                      break;
                    }
                }
              if (error_line)
                {
                  g_string_free (define_line, TRUE);
                  /* ignore line */
                  c = eat_line (f, c);
                  line++;
                  continue;
                }

              g_assert (c == ')');
              g_string_append_c (define_line, c);
              c = fgetc (f);

              /* found function-like macro */
              fprintf (fmacros, "%s\n", define_line->str);

              g_string_free (define_line, TRUE);
              /* ignore rest of line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          if (c != ' ' && c != '\t')
            {
              g_string_free (define_line, TRUE);
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          while (c != EOF && c != '\n')
            {
              g_string_append_c (define_line, c);
              c = fgetc (f);
              if (c == '\\')
                {
                  c = fgetc (f);
                  if (c == '\n')
                    {
                      /* fold lines when seeing backslash new-line sequence */
                      c = fgetc (f);
                    }
                  else
                    {
                      g_string_append_c (define_line, '\\');
                    }
                }
            }

          /* found object-like macro */
          fprintf (fmacros, "%s\n", define_line->str);

          c = eat_line (f, c);
          line++;
        }

      fclose (f);
    }

  rewind (fmacros);
  gi_source_scanner_parse_file (scanner, fmacros);
}

gboolean
gi_source_scanner_parse_file (GISourceScanner *scanner, FILE *file)
{
  g_return_val_if_fail (file != NULL, FALSE);

  const_table = g_hash_table_new_full (g_str_hash, g_str_equal,
				       g_free, (GDestroyNotify)gi_source_symbol_unref);

  lineno = 1;
  yyin = file;
  yyparse (scanner);

  g_hash_table_destroy (const_table);
  const_table = NULL;

  yyin = NULL;

  return TRUE;
}

gboolean
gi_source_scanner_lex_filename (GISourceScanner *scanner, const gchar *filename)
{
  lineno = 1;
  yyin = fopen (filename, "r");

  while (yylex (scanner) != YYEOF)
    ;

  fclose (yyin);

  return TRUE;
}
