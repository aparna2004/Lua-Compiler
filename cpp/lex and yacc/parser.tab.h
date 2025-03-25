/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     IDENT = 259,
     TRUE = 260,
     FALSE = 261,
     IF = 262,
     ELSE = 263,
     ELSEIF = 264,
     WHILE = 265,
     THEN = 266,
     END = 267,
     DO = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     FOR = 272,
     COMMA = 273,
     IN = 274,
     LPAREN = 275,
     RPAREN = 276,
     LBRACE = 277,
     RBRACE = 278,
     ASSIGN = 279,
     EQ = 280,
     LT = 281,
     GT = 282,
     PLUS = 283,
     MINUS = 284,
     MULT = 285,
     DIV = 286,
     PRINT = 287,
     STRING = 288,
     CONCAT = 289,
     GE = 290,
     LE = 291,
     NE = 292,
     UMINUS = 293
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define IDENT 259
#define TRUE 260
#define FALSE 261
#define IF 262
#define ELSE 263
#define ELSEIF 264
#define WHILE 265
#define THEN 266
#define END 267
#define DO 268
#define AND 269
#define OR 270
#define NOT 271
#define FOR 272
#define COMMA 273
#define IN 274
#define LPAREN 275
#define RPAREN 276
#define LBRACE 277
#define RBRACE 278
#define ASSIGN 279
#define EQ 280
#define LT 281
#define GT 282
#define PLUS 283
#define MINUS 284
#define MULT 285
#define DIV 286
#define PRINT 287
#define STRING 288
#define CONCAT 289
#define GE 290
#define LE 291
#define NE 292
#define UMINUS 293




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 22 "parser.y"
typedef union YYSTYPE {
    int intVal;
    char* strVal;
    bool boolVal;
    Node* node;
} YYSTYPE;
/* Line 1403 of yacc.c.  */
#line 121 "parser.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



