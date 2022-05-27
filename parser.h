
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     FOR = 261,
     FUNCTION = 262,
     RETURN = 263,
     BREAK = 264,
     CONTINUE = 265,
     LOCAL = 266,
     TRUE = 267,
     FALSE = 268,
     NIL = 269,
     NOT = 270,
     AND = 271,
     OR = 272,
     ASSIGNMENT = 273,
     ADDITION = 274,
     SUBTRACTION = 275,
     MULTIPLICATION = 276,
     DIVISION = 277,
     MODULO = 278,
     EQUALITY = 279,
     INEQUALITY = 280,
     INCREMENT = 281,
     DECREMENT = 282,
     GREATER_THAN = 283,
     LESS_THAN = 284,
     GREATER_THAN_OR_EQ_TO = 285,
     LESS_THAN_OR_EQ_TO = 286,
     INTCONST = 287,
     REALCONST = 288,
     ID = 289,
     STRING = 290,
     LEFT_BRACE = 291,
     RIGHT_BRACE = 292,
     LEFT_SQ_BRACKET = 293,
     RIGHT_SQ_BRACKET = 294,
     LEFT_PARENTHESES = 295,
     RIGHT_PARENTHESES = 296,
     SEMICOLON = 297,
     COMMA = 298,
     COLON = 299,
     DOUBLE_COLON = 300,
     PERIOD = 301,
     DOUBLE_PERIOD = 302,
     OTHER = 303,
     UMINUS = 304
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define LOCAL 266
#define TRUE 267
#define FALSE 268
#define NIL 269
#define NOT 270
#define AND 271
#define OR 272
#define ASSIGNMENT 273
#define ADDITION 274
#define SUBTRACTION 275
#define MULTIPLICATION 276
#define DIVISION 277
#define MODULO 278
#define EQUALITY 279
#define INEQUALITY 280
#define INCREMENT 281
#define DECREMENT 282
#define GREATER_THAN 283
#define LESS_THAN 284
#define GREATER_THAN_OR_EQ_TO 285
#define LESS_THAN_OR_EQ_TO 286
#define INTCONST 287
#define REALCONST 288
#define ID 289
#define STRING 290
#define LEFT_BRACE 291
#define RIGHT_BRACE 292
#define LEFT_SQ_BRACKET 293
#define RIGHT_SQ_BRACKET 294
#define LEFT_PARENTHESES 295
#define RIGHT_PARENTHESES 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define DOUBLE_COLON 300
#define PERIOD 301
#define DOUBLE_PERIOD 302
#define OTHER 303
#define UMINUS 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 98 "parser.y"

	char* sValue;
	int iValue;
	double dValue;
	unsigned int prefix;
	struct expr* exprs;
	struct stoixeio *node;
	struct indexed *indexed_t;
	struct forprefix* forpref;



/* Line 1676 of yacc.c  */
#line 163 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


