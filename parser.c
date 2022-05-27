
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "symtable.h"
	#include "functions.h"
	#include "quads.h"
	#include "targetCode.h"
	#include "avm.h"

	int scope=0;
	SymTable *symTable;
	
	node* lastFunc;
	int arrayFlag=0;
	extern unsigned int currQuad;
		unsigned int programVarOffset=0;
	unsigned int functionLocalOffset=0;
	unsigned int formalArgOffset=0;
	unsigned int scopeSpaceCounter=1;
	   struct list* continueList;
	    struct list* breakList;
	    struct loopList* loopCounterStack;
	    unsigned int loopCounter=0;
	    struct functionLocals* localsHead;
	struct expr *res=NULL;
	int memberFlag;



		void printLocals(){
			printf("current Locals %d\n",functionLocalOffset);
		struct functionLocals* temp=localsHead;
		while(temp!=NULL){
			printf("previous %d\n",temp->locals );	
			temp=temp->next;
		}
		
	}


/* Line 189 of yacc.c  */
#line 115 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 98 "parser.y"

	char* sValue;
	int iValue;
	double dValue;
	unsigned int prefix;
	struct expr* exprs;
	struct stoixeio *node;
	struct indexed *indexed_t;
	struct forprefix* forpref;



/* Line 214 of yacc.c  */
#line 262 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 274 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   541

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    14,    16,    18,
      20,    23,    26,    28,    30,    32,    34,    38,    42,    46,
      50,    54,    58,    62,    66,    70,    74,    78,    82,    86,
      88,    92,    95,    98,   101,   102,   106,   109,   110,   114,
     116,   117,   122,   124,   126,   128,   132,   134,   136,   139,
     142,   144,   148,   153,   157,   162,   167,   170,   177,   179,
     181,   185,   191,   194,   195,   199,   200,   204,   208,   211,
     215,   216,   222,   223,   227,   228,   234,   236,   237,   240,
     241,   246,   248,   254,   255,   256,   258,   260,   262,   264,
     266,   268,   269,   273,   274,   275,   280,   281,   286,   288,
     291,   296,   297,   298,   302,   304,   308,   312,   313,   314,
     322,   330,   333
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    -1,    53,    52,    -1,    -1,    54,
      42,    -1,    91,    -1,    97,    -1,   101,    -1,   102,    -1,
       9,    42,    -1,    10,    42,    -1,    73,    -1,    81,    -1,
      42,    -1,    58,    -1,    54,    19,    54,    -1,    54,    20,
      54,    -1,    54,    21,    54,    -1,    54,    22,    54,    -1,
      54,    23,    54,    -1,    54,    28,    54,    -1,    54,    30,
      54,    -1,    54,    31,    54,    -1,    54,    29,    54,    -1,
      54,    24,    54,    -1,    54,    25,    54,    -1,    54,    16,
      54,    -1,    54,    17,    54,    -1,    55,    -1,    40,    54,
      41,    -1,    20,    54,    -1,    15,    54,    -1,    26,    61,
      -1,    -1,    61,    56,    26,    -1,    27,    61,    -1,    -1,
      61,    57,    27,    -1,    60,    -1,    -1,    61,    59,    18,
      54,    -1,    61,    -1,    63,    -1,    69,    -1,    40,    81,
      41,    -1,    84,    -1,    34,    -1,    11,    34,    -1,    45,
      34,    -1,    62,    -1,    61,    46,    34,    -1,    61,    38,
      54,    39,    -1,    63,    46,    34,    -1,    63,    38,    54,
      39,    -1,    63,    40,    67,    41,    -1,    61,    64,    -1,
      40,    81,    41,    40,    67,    41,    -1,    65,    -1,    66,
      -1,    40,    67,    41,    -1,    47,    34,    40,    67,    41,
      -1,    54,    68,    -1,    -1,    43,    54,    68,    -1,    -1,
      38,    67,    39,    -1,    38,    70,    39,    -1,    72,    71,
      -1,    43,    72,    71,    -1,    -1,    36,    54,    44,    54,
      37,    -1,    -1,    36,    74,    37,    -1,    -1,    36,    75,
      53,    52,    37,    -1,    34,    -1,    -1,     7,    76,    -1,
      -1,    40,    79,    85,    41,    -1,    73,    -1,    77,    78,
      82,    80,    83,    -1,    -1,    -1,    32,    -1,    33,    -1,
      35,    -1,    14,    -1,    12,    -1,    13,    -1,    -1,    34,
      86,    87,    -1,    -1,    -1,    43,    34,    88,    87,    -1,
      -1,     3,    40,    54,    41,    -1,     4,    -1,    89,    53,
      -1,    89,    53,    90,    53,    -1,    -1,    -1,    92,    53,
      93,    -1,     5,    -1,    40,    54,    41,    -1,    95,    96,
      94,    -1,    -1,    -1,     6,    40,    67,    42,    98,    54,
      42,    -1,   100,    99,    67,    41,    99,    94,    99,    -1,
       8,    42,    -1,     8,    54,    42,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   112,   112,   115,   116,   119,   123,   125,   127,   129,
     131,   140,   147,   149,   151,   155,   157,   161,   165,   169,
     173,   177,   184,   191,   198,   205,   212,   219,   228,   237,
     244,   246,   252,   257,   271,   271,   285,   298,   298,   312,
     317,   317,   340,   343,   345,   347,   349,   353,   357,   361,
     363,   368,   372,   380,   383,   393,   395,   404,   411,   413,
     417,   422,   426,   429,   432,   435,   439,   441,   445,   450,
     453,   457,   471,   471,   475,   475,   480,   484,   490,   510,
     510,   518,   521,   530,   537,   543,   545,   547,   550,   552,
     554,   558,   558,   566,   569,   569,   576,   578,   583,   586,
     588,   592,   594,   596,   598,   601,   608,   621,   624,   628,
     636,   650,   653
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "LOCAL", "TRUE", "FALSE", "NIL", "NOT",
  "AND", "OR", "ASSIGNMENT", "ADDITION", "SUBTRACTION", "MULTIPLICATION",
  "DIVISION", "MODULO", "EQUALITY", "INEQUALITY", "INCREMENT", "DECREMENT",
  "GREATER_THAN", "LESS_THAN", "GREATER_THAN_OR_EQ_TO",
  "LESS_THAN_OR_EQ_TO", "INTCONST", "REALCONST", "ID", "STRING",
  "LEFT_BRACE", "RIGHT_BRACE", "LEFT_SQ_BRACKET", "RIGHT_SQ_BRACKET",
  "LEFT_PARENTHESES", "RIGHT_PARENTHESES", "SEMICOLON", "COMMA", "COLON",
  "DOUBLE_COLON", "PERIOD", "DOUBLE_PERIOD", "OTHER", "UMINUS", "$accept",
  "program", "stmnts", "stm", "expr", "term", "$@1", "$@2", "assignexpr",
  "$@3", "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "elist2", "objectdef", "indexed", "indexed2",
  "indexedelem", "block", "$@4", "$@5", "funcname", "funcprefix",
  "funcargs", "$@6", "funcbody", "funcdef", "funcblockstart",
  "funcblockend", "const", "idlist", "$@7", "idlist2", "$@8", "ifprefix",
  "elseprefix", "ifstm", "loopstart", "loopend", "loopstm", "whilestart",
  "whilecond", "whilestm", "M", "N", "forprefix", "forstm", "returnstm", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    56,    55,    55,    57,    55,    55,
      59,    58,    60,    60,    60,    60,    60,    61,    61,    61,
      61,    62,    62,    62,    62,    63,    63,    63,    64,    64,
      65,    66,    67,    67,    68,    68,    69,    69,    70,    71,
      71,    72,    74,    73,    75,    73,    76,    76,    77,    79,
      78,    80,    81,    82,    83,    84,    84,    84,    84,    84,
      84,    86,    85,    85,    88,    87,    87,    89,    90,    91,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   102
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     0,     3,     2,     0,     3,     1,
       0,     4,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     2,     0,     3,     0,     3,     3,     2,     3,
       0,     5,     0,     3,     0,     5,     1,     0,     2,     0,
       4,     1,     5,     0,     0,     1,     1,     1,     1,     1,
       1,     0,     3,     0,     0,     4,     0,     4,     1,     2,
       4,     0,     0,     3,     1,     3,     3,     0,     0,     7,
       7,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,   104,     0,    77,     0,     0,     0,     0,    89,
      90,    88,     0,     0,     0,     0,    85,    86,    47,    87,
      74,    63,     0,    14,     0,     0,     2,     4,     0,    29,
      15,    39,    42,    50,    43,    44,    12,     0,    13,    46,
       0,     6,     0,     7,   108,     8,     9,     0,    63,    76,
      78,   111,     0,    10,    11,    48,    32,    31,     0,    33,
       0,    36,     0,     0,     0,    65,     0,     0,    70,     0,
       0,    49,     1,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     0,    63,
       0,     0,     0,     0,     0,    56,    58,    59,     0,    63,
       0,    79,    83,    99,     0,   101,    63,     0,     0,   112,
       0,    73,     4,     0,     0,    62,    66,    67,     0,    68,
      30,    45,    27,    28,    16,    17,    18,    19,    20,    25,
      26,    21,    24,    22,    23,     0,     0,    51,     0,    35,
      38,     0,     0,     0,    53,    93,     0,    98,     0,     0,
       0,   106,     0,    97,   107,     0,     0,     0,    65,    70,
      63,    52,    60,    63,    41,    54,    55,    91,     0,    81,
      84,   100,   105,   102,   108,     0,    75,     0,    64,    69,
       0,     0,    96,    80,    82,   103,   101,     0,    71,    57,
      61,     0,    92,   108,   109,    94,   110,    96,    95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    92,    93,    30,    94,
      31,    32,    33,    34,    95,    96,    97,    66,   115,    35,
      67,   119,    68,    36,    62,    63,    50,    37,   102,   145,
     170,    38,   146,   184,    39,   168,   182,   192,   197,    40,
     148,    41,   150,   185,   151,    42,   105,    43,   175,   106,
      44,    45,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -165
static const yytype_int16 yypact[] =
{
     154,   -34,  -165,   -31,     3,   189,    -4,    -1,    11,  -165,
    -165,  -165,   259,   259,    -6,    -6,  -165,  -165,  -165,  -165,
      14,   224,    93,  -165,    19,    46,  -165,   154,   319,  -165,
    -165,  -165,     9,  -165,    12,  -165,  -165,     8,  -165,  -165,
     154,  -165,    17,  -165,  -165,  -165,  -165,   259,   259,  -165,
    -165,  -165,   335,  -165,  -165,  -165,  -165,  -165,    53,   -14,
      12,   -14,    28,   154,   259,   303,    27,    29,    24,   367,
      44,  -165,  -165,  -165,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,  -165,   259,   259,
      48,    54,    61,    62,    72,  -165,  -165,  -165,   259,   259,
      57,  -165,  -165,    88,   259,  -165,   259,   390,    55,  -165,
      70,  -165,   154,   286,   259,  -165,  -165,  -165,    59,  -165,
    -165,    56,   120,   120,    41,    41,  -165,  -165,  -165,   510,
     510,    -8,    -8,    -8,    -8,   436,    73,  -165,    58,  -165,
    -165,   259,   457,    75,  -165,    68,    67,  -165,   154,   413,
     154,  -165,    76,  -165,  -165,    56,    84,   259,   303,    24,
     259,  -165,  -165,   259,   497,  -165,  -165,  -165,    81,  -165,
    -165,  -165,  -165,  -165,  -165,   259,  -165,   478,  -165,  -165,
      82,    83,    86,  -165,  -165,  -165,  -165,   351,  -165,  -165,
    -165,    96,  -165,  -165,  -165,  -165,  -165,    86,  -165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,   -26,   -38,    -5,  -165,  -165,  -165,  -165,  -165,
    -165,     4,  -165,    16,  -165,  -165,  -165,   -45,   -24,  -165,
    -165,   -27,    35,   -11,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,   -18,  -165,  -165,  -165,  -165,  -165,   -60,  -165,  -165,
    -165,  -165,  -165,  -165,   -40,  -165,  -165,  -165,  -165,  -164,
    -165,  -165,  -165
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -73
static const yytype_int16 yytable[] =
{
      52,    73,   103,   108,    70,     8,    47,    56,    57,    48,
     186,    76,    77,    78,    79,    80,    65,    69,    59,    61,
     -73,   -73,   -73,   -73,    88,   112,    89,   -40,    18,   196,
      60,    60,    90,    91,    58,   -34,   -37,    49,    53,    24,
     110,    54,   107,    65,   136,    55,    72,    88,   101,    89,
      98,   -72,    99,    71,   143,    90,    91,   104,   100,   113,
       4,   152,    78,    79,    80,   111,   116,   118,   117,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   137,   135,    65,   121,   156,   139,   138,   140,
     141,   144,   147,   142,    65,    64,   160,   154,   163,   149,
       4,    65,   167,    20,     8,     9,    10,    11,    12,   158,
     171,   155,   173,    13,   162,   180,   166,   174,   181,    14,
      15,   176,   183,   189,   190,    16,    17,    18,    19,   191,
     195,    21,   179,    22,   178,   169,   164,   198,    24,    76,
      77,    78,    79,    80,    81,    82,   193,     0,    83,    84,
      85,    86,   177,   159,     0,    65,     0,     1,    65,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     187,     0,     0,     0,    13,     0,     0,     0,     0,     0,
      14,    15,     0,     0,     0,     0,    16,    17,    18,    19,
      20,     0,    21,     0,    22,     0,    23,     0,     0,    24,
       8,     9,    10,    11,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,    15,     0,     0,     0,
       0,    16,    17,    18,    19,     0,     0,    21,     0,    22,
       0,    51,     0,     0,    24,     8,     9,    10,    11,    12,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
      14,    15,     0,     0,     0,     0,    16,    17,    18,    19,
      64,     0,    21,     0,    22,     0,     0,     0,     0,    24,
       8,     9,    10,    11,    12,     0,     0,     0,     0,    13,
       0,     0,     0,     0,     0,    14,    15,     0,     0,     0,
       0,    16,    17,    18,    19,     0,     0,    21,     0,    22,
       0,     0,    74,    75,    24,    76,    77,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,     0,    74,
      75,     0,    76,    77,    78,    79,    80,    81,    82,     0,
     157,    83,    84,    85,    86,    74,    75,     0,    76,    77,
      78,    79,    80,    81,    82,     0,   114,    83,    84,    85,
      86,    74,    75,     0,    76,    77,    78,    79,    80,    81,
      82,    87,     0,    83,    84,    85,    86,    74,    75,     0,
      76,    77,    78,    79,    80,    81,    82,   109,     0,    83,
      84,    85,    86,    74,    75,     0,    76,    77,    78,    79,
      80,    81,    82,   194,     0,    83,    84,    85,    86,     0,
       0,     0,     0,     0,     0,     0,    74,    75,   120,    76,
      77,    78,    79,    80,    81,    82,     0,     0,    83,    84,
      85,    86,     0,     0,     0,     0,     0,     0,     0,    74,
      75,   153,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,     0,     0,     0,     0,     0,
       0,     0,    74,    75,   172,    76,    77,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,     0,     0,
       0,     0,     0,    74,    75,   161,    76,    77,    78,    79,
      80,    81,    82,     0,     0,    83,    84,    85,    86,     0,
       0,     0,     0,     0,    74,    75,   165,    76,    77,    78,
      79,    80,    81,    82,     0,     0,    83,    84,    85,    86,
       0,     0,     0,    74,    75,   188,    76,    77,    78,    79,
      80,    81,    82,     0,     0,    83,    84,    85,    86,    76,
      77,    78,    79,    80,   -73,   -73,     0,     0,    83,    84,
      85,    86
};

static const yytype_int16 yycheck[] =
{
       5,    27,    40,    48,    22,    11,    40,    12,    13,    40,
     174,    19,    20,    21,    22,    23,    21,    22,    14,    15,
      28,    29,    30,    31,    38,    63,    40,    18,    34,   193,
      14,    15,    46,    47,    40,    26,    27,    34,    42,    45,
      58,    42,    47,    48,    89,    34,     0,    38,    40,    40,
      38,    37,    40,    34,    99,    46,    47,    40,    46,    64,
       7,   106,    21,    22,    23,    37,    39,    43,    39,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    34,    88,    89,    41,   112,    26,    34,    27,
      18,    34,     4,    98,    99,    36,    40,    42,    40,   104,
       7,   106,    34,    36,    11,    12,    13,    14,    15,   114,
     148,    41,   150,    20,    41,   160,    41,    41,   163,    26,
      27,    37,    41,    41,    41,    32,    33,    34,    35,    43,
      34,    38,   159,    40,   158,   146,   141,   197,    45,    19,
      20,    21,    22,    23,    24,    25,   186,    -1,    28,    29,
      30,    31,   157,   118,    -1,   160,    -1,     3,   163,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     175,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    -1,    38,    -1,    40,    -1,    42,    -1,    -1,    45,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    38,    -1,    40,
      -1,    42,    -1,    -1,    45,    11,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    -1,    38,    -1,    40,    -1,    -1,    -1,    -1,    45,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    38,    -1,    40,
      -1,    -1,    16,    17,    45,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    -1,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      44,    28,    29,    30,    31,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    43,    28,    29,    30,
      31,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    42,    -1,    28,    29,    30,    31,    16,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    42,    -1,    28,
      29,    30,    31,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    42,    -1,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    41,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      17,    41,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    17,    41,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    16,    17,    39,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    16,    17,    39,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    -1,    -1,    16,    17,    37,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    20,    26,    27,    32,    33,    34,    35,
      36,    38,    40,    42,    45,    51,    52,    53,    54,    55,
      58,    60,    61,    62,    63,    69,    73,    77,    81,    84,
      89,    91,    95,    97,   100,   101,   102,    40,    40,    34,
      76,    42,    54,    42,    42,    34,    54,    54,    40,    61,
      63,    61,    74,    75,    36,    54,    67,    70,    72,    54,
      81,    34,     0,    52,    16,    17,    19,    20,    21,    22,
      23,    24,    25,    28,    29,    30,    31,    42,    38,    40,
      46,    47,    56,    57,    59,    64,    65,    66,    38,    40,
      46,    40,    78,    53,    40,    96,    99,    54,    67,    42,
      81,    37,    53,    54,    43,    68,    39,    39,    43,    71,
      41,    41,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    67,    34,    34,    26,
      27,    18,    54,    67,    34,    79,    82,     4,    90,    54,
      92,    94,    67,    41,    42,    41,    52,    44,    54,    72,
      40,    39,    41,    40,    54,    39,    41,    34,    85,    73,
      80,    53,    41,    53,    41,    98,    37,    54,    68,    71,
      67,    67,    86,    41,    83,    93,    99,    54,    37,    41,
      41,    43,    87,    94,    42,    34,    99,    88,    87
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    {printf("#%d program -> statements\n",yylineno);}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {printf("#%d statements -> stm statements \n",yylineno);}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    {printf("#%d statements -> empty \n", yylineno);}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    {resetCounter();
								
								
							printf("#%d statement -> expr; \n", yylineno);}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
						printf("#%d statement -> if statement \n", yylineno);}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    {(yyval.exprs)=NULL;
						 printf("#%d statement -> while statement \n", yylineno);}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    {(yyval.exprs)=NULL;
						printf("#%d statement -> for statement \n", yylineno);}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    {(yyval.exprs)=NULL;
						printf("#%d statement -> return; \n", yylineno);}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    {if(loopCounter!=0){
									breakList=createList(currQuad,breakList);
									emit(jump,NULL,NULL,NULL,-1,currQuad);
									
								}else{
									fprintf(stderr, "\t\t\tBREAK found, but not in a loop!, line: %d\n",yylineno );
								}
								
								printf("#%d statement -> break \n", yylineno);}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    {if(loopCounter!=0){
									continueList=createList(currQuad,continueList);
									emit(jump,NULL,NULL,NULL,-1,currQuad);
								}else{
									fprintf(stderr, "\t\t\tCONTINUE found, but not in a loop!, line: %d\n",yylineno );
								}
								printf("#%d statement -> continue; \n", yylineno);}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
						printf("#%d statement -> block \n", yylineno);}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    {(yyval.exprs)=lvalue_expr((yyvsp[(1) - (1)].node));
						printf("#%d statement -> funcdef \n", yylineno);}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    {(yyval.exprs)=NULL;
						printf("#%d statement -> ; \n", yylineno);}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
							printf("#%d expr -> assignexpr \n", yylineno);}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
									(yyval.exprs)=res;
									emit(add,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
									printf("#%d expr -> expr + expr \n", yylineno);}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
									(yyval.exprs)=res;
									emit(sub,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
										printf("#%d expr -> expr - expr \n", yylineno);}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
										(yyval.exprs)=res;
										emit(mul,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
										printf("#%d expr -> expr * expr \n", yylineno);}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
									(yyval.exprs)=res;
									emit(divv,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
									printf("#%d expr -> expr / expr \n", yylineno);}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 173 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
								  (yyval.exprs)=res;
								  emit(mod,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
								  printf("#%d expr -> expr mod expr \n", yylineno);}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    {emit(if_greater,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),NULL,currQuad+3,currQuad);
										res=lvalue_expr(newTemp(symTable));
										(yyval.exprs)=res;
										emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
										emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
										emit(assign,NewBoolExp(1),NULL,(yyval.exprs),-1,currQuad);
					 				printf("#%d expr -> expr > expr \n", yylineno);}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    {emit(if_greatereq,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),NULL,currQuad+3,currQuad);
											res=lvalue_expr(newTemp(symTable));
											(yyval.exprs)=res;
											emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
											emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
											emit(assign,NewBoolExp(1),NULL,(yyval.exprs),-1,currQuad);
										printf("#%d expr -> expr >= expr \n", yylineno);}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    {emit(if_lesseq,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),NULL,currQuad+3,currQuad);
											res=lvalue_expr(newTemp(symTable));
											(yyval.exprs)=res;
											emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
											emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
											emit(assign,NewBoolExp(1),NULL,(yyval.exprs),-1,currQuad);
											printf("#%d expr -> expr <= expr \n", yylineno);}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 198 "parser.y"
    {emit(if_less,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),NULL,currQuad+3,currQuad);
											res=lvalue_expr(newTemp(symTable));
											(yyval.exprs)=res;
											emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
											emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
											emit(assign,NewBoolExp(1),NULL,(yyval.exprs),-1,currQuad);	
									printf("#%d expr -> expr < expr \n", yylineno);}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    {emit(if_eq,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),NULL,currQuad+3,currQuad);
									res=lvalue_expr(newTemp(symTable));
									(yyval.exprs)=res;
									emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
									emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
									emit(assign,NewBoolExp(1),NULL,(yyval.exprs),-1,currQuad);
									printf("#%d expr -> expr == expr \n", yylineno);}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    {emit(if_noteq,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),NULL,currQuad+3,currQuad);
									res=lvalue_expr(newTemp(symTable));
									(yyval.exprs)=res;
									emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
									emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
									emit(assign,NewBoolExp(1),NULL,(yyval.exprs),-1,currQuad);
									printf("#%d expr -> expr != expr \n", yylineno);}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 219 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
								(yyval.exprs)=res;
								emit(and,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
								//emit(if_eq,$$,NewBoolExp(1),NULL,currQuad+3,currQuad);
								
								//emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
								//emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
								//emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
								printf("#%d expr -> expr and expr \n", yylineno);}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
								(yyval.exprs)=res;
								emit(or,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].exprs),res,-1,currQuad);
								//emit(if_eq,$$,NewBoolExp(1),NULL,currQuad+3,currQuad);
								
								//emit(assign,NewBoolExp(0),NULL,res,-1,currQuad);
								//emit(jump,NULL,NULL,NULL,currQuad+2,currQuad);
								//emit(assign,NewBoolExp(1),NULL,$$,-1,currQuad);
								printf("#%d expr -> expr or expr \n", yylineno);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 237 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
				
						printf("#%d expr -> term \n", yylineno);
						
					}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 244 "parser.y"
    {(yyval.exprs)=(yyvsp[(2) - (3)].exprs);
														printf("#%d term -> (expr) \n", yylineno);}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    {checkuminus((yyvsp[(2) - (2)].exprs));
												res=lvalue_expr(newTemp(symTable));
												(yyval.exprs)=res;
												(yyval.exprs)->type=arithexpr_e;
												emit(uminus,NULL,(yyvsp[(2) - (2)].exprs),res,-1,currQuad);
												printf("#%d term -> -expr \n", yylineno);}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 252 "parser.y"
    {res=lvalue_expr(newTemp(symTable));
						(yyval.exprs)=res;
						(yyval.exprs)->type=boolexpr_e;
						emit(not,(yyvsp[(2) - (2)].exprs),NULL,res,-1,currQuad);
							printf("#%d term -> not expr \n", yylineno);}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 257 "parser.y"
    {
									if((yyvsp[(2) - (2)].exprs)->type==tableitem_e){
										(yyval.exprs)=emit_ifTableItem(symTable,(yyvsp[(2) - (2)].exprs));
										emit(add,(yyval.exprs),NewExprInt(1),(yyval.exprs),-1,currQuad);
										emit(tablesetelem,(yyvsp[(2) - (2)].exprs),(yyvsp[(2) - (2)].exprs)->index,(yyval.exprs),-1,currQuad);
									}else{
										emit(add,(yyvsp[(2) - (2)].exprs),NewExprInt(1),(yyvsp[(2) - (2)].exprs),-1,currQuad);
										(yyval.exprs)=newExpr(arithexpr_e);
										(yyval.exprs)->symbol=newTemp(symTable);
										(yyval.exprs)->sValue=strdup((yyval.exprs)->symbol->name);
										emit(assign,(yyvsp[(2) - (2)].exprs),NULL,(yyval.exprs),-1,currQuad);
									}
									handleLvalue(symTable, (yyvsp[(2) - (2)].exprs)->sValue, yylineno);
									printf("#%d term -> ++lvalue \n", yylineno);}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {handleLvalue(symTable, (yyvsp[(1) - (1)].exprs)->sValue, yylineno);}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {(yyval.exprs)=newExpr(var_e);
																				  (yyval.exprs)->symbol=newTemp(symTable);
																				  (yyval.exprs)->sValue=strdup((yyval.exprs)->symbol->name);
																				  if((yyvsp[(1) - (3)].exprs)->type==tableitem_e){
																				  
																				  		struct expr *value=emit_ifTableItem(symTable,(yyvsp[(1) - (3)].exprs));
																				  		emit(assign,value,NULL,(yyval.exprs),-1,currQuad);
																				  		emit(add,value,NewExprInt(1),value,-1,currQuad);
																				  		emit(tablesetelem,(yyvsp[(1) - (3)].exprs),(yyvsp[(1) - (3)].exprs)->index,value,-1,currQuad);
																				  }else{
																				  		emit(assign,(yyvsp[(1) - (3)].exprs),NULL,(yyval.exprs),-1,currQuad);
																				  		emit(add,(yyvsp[(1) - (3)].exprs),NewExprInt(1),(yyvsp[(1) - (3)].exprs),-1,currQuad);
																				  }
																				printf("#%d term -> lvalue++ \n", yylineno);}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 285 "parser.y"
    {if((yyvsp[(2) - (2)].exprs)->type==tableitem_e){
										(yyval.exprs)=emit_ifTableItem(symTable,(yyvsp[(2) - (2)].exprs));
										emit(sub,(yyval.exprs),NewExprInt(1),(yyval.exprs),-1,currQuad);
										emit(tablesetelem,(yyvsp[(2) - (2)].exprs),(yyvsp[(2) - (2)].exprs)->index,(yyval.exprs),-1,currQuad);
									}else{
										emit(sub,(yyvsp[(2) - (2)].exprs),NewExprInt(1),(yyvsp[(2) - (2)].exprs),-1,currQuad);
										(yyval.exprs)=newExpr(arithexpr_e);
										(yyval.exprs)->symbol=newTemp(symTable);
										(yyval.exprs)->sValue=strdup((yyval.exprs)->symbol->name);
										emit(assign,(yyvsp[(2) - (2)].exprs),NULL,(yyval.exprs),-1,currQuad);
									}
									handleLvalue(symTable,(yyvsp[(2) - (2)].exprs)->sValue, yylineno);
									printf("#%d term -> --lvalue \n", yylineno);}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {handleLvalue(symTable, (yyvsp[(1) - (1)].exprs)->sValue, yylineno);}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {(yyval.exprs)=newExpr(var_e);
																				  (yyval.exprs)->symbol=newTemp(symTable);
																				  (yyval.exprs)->sValue=strdup((yyval.exprs)->symbol->name);
																				  if((yyvsp[(1) - (3)].exprs)->type==tableitem_e){
																				  
																				  		struct expr *value=emit_ifTableItem(symTable,(yyvsp[(1) - (3)].exprs));
																				  		emit(assign,value,NULL,(yyval.exprs),-1,currQuad);
																				  		emit(sub,value,NewExprInt(1),value,-1,currQuad);
																				  		emit(tablesetelem,(yyvsp[(1) - (3)].exprs),(yyvsp[(1) - (3)].exprs)->index,value,-1,currQuad);
																				  }else{
																				  		emit(assign,(yyvsp[(1) - (3)].exprs),NULL,(yyval.exprs),-1,currQuad);
																				  		emit(sub,(yyvsp[(1) - (3)].exprs),NewExprInt(1),(yyvsp[(1) - (3)].exprs),-1,currQuad);
																				  }
																					printf("#%d term -> lvalue-- \n", yylineno);}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
						printf("#%d term -> primary \n", yylineno);
						}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {if(arrayFlag==0 && memberFlag==0){
		handleLvalue(symTable, (yyvsp[(1) - (1)].exprs)->sValue, yylineno);
							}
							arrayFlag=0;
							
	 }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    {
							if((yyvsp[(1) - (4)].exprs)->type==tableitem_e){
								emit(tablesetelem,(yyvsp[(1) - (4)].exprs),(yyvsp[(1) - (4)].exprs)->index,(yyvsp[(4) - (4)].exprs),-1,currQuad);
								(yyval.exprs)=emit_ifTableItem(symTable,(yyvsp[(1) - (4)].exprs));
								(yyval.exprs)->type=assgnexpr_e;
							}else{
								emit(assign,(yyvsp[(4) - (4)].exprs),NULL,(yyvsp[(1) - (4)].exprs),-1,currQuad);
								(yyval.exprs)=newExpr(assgnexpr_e);
								(yyval.exprs)->symbol=newTemp(symTable);
								
								(yyval.exprs)->sValue=strdup((yyval.exprs)->symbol->name);
								emit(assign,(yyvsp[(1) - (4)].exprs),NULL,(yyval.exprs),-1,currQuad);
								
							}
					printf("#%d assignexpr -> lvalue = expr \n", yylineno);}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {
						(yyval.exprs)=emit_ifTableItem(symTable,(yyvsp[(1) - (1)].exprs));
						printf("#%d primary -> lvalue \n", yylineno);}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
						printf("#%d primary -> call \n", yylineno);}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 345 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
						printf("#%d primary -> objectdef \n", yylineno);}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 347 "parser.y"
    {(yyval.exprs)=lvalue_expr((yyvsp[(2) - (3)].node));
															printf("#%d primary -> (funcdef) \n", yylineno);}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 349 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
						printf("#%d primary -> const \n", yylineno);}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    {(yyval.exprs)=lvalue_expr(handleId(symTable,(yyvsp[(1) - (1)].sValue),scope,yylineno));
					inCurrScopeOffset();
					
					printf("#%d lvalue -> id \n", yylineno);}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 357 "parser.y"
    {(yyval.exprs)=lvalue_expr(handleLocalId(symTable,(yyvsp[(2) - (2)].sValue),scope,yylineno));
								inCurrScopeOffset();
								
							printf("#%d lvalue -> local id \n", yylineno);}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    {(yyval.exprs)=lvalue_expr(handleScopeId(symTable,(yyvsp[(2) - (2)].sValue),yylineno));
							printf("#%d lvalue -> ::id \n", yylineno);}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 363 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
					
						printf("#%d lvalue -> member \n", yylineno);}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    {(yyval.exprs)=member_item(symTable,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].sValue));
									
									//$$->sValue=strdup($1->sValue);
		printf("#%d member -> lvalue.id \n", yylineno);}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 372 "parser.y"
    {(yyvsp[(1) - (4)].exprs)=emit_ifTableItem(symTable,(yyvsp[(1) - (4)].exprs));
															  (yyval.exprs)=newExpr(tableitem_e);
															  (yyval.exprs)->symbol=(yyvsp[(1) - (4)].exprs)->symbol;
															  (yyval.exprs)->index=(yyvsp[(3) - (4)].exprs);
															  (yyval.exprs)->sValue=strdup((yyvsp[(1) - (4)].exprs)->sValue);
															  arrayFlag=1;
															  
															  printf("#%d member -> lvalue[expr] \n", yylineno);}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    {(yyval.exprs)=member_item(symTable,(yyvsp[(1) - (3)].exprs),(yyvsp[(3) - (3)].sValue));
				
							printf("#%d member -> call.id \n", yylineno);}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {arrayFlag=1;
															if((yyvsp[(3) - (4)].exprs)->sValue==NULL){
																(yyval.exprs)=member_item1(symTable,(yyvsp[(1) - (4)].exprs),(yyvsp[(3) - (4)].exprs)->iValue);
															}else{
																(yyval.exprs)=member_item(symTable,(yyvsp[(1) - (4)].exprs),(yyvsp[(3) - (4)].exprs)->sValue);	
															}
															
															printf("#%d member -> call[expr] \n", yylineno);}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 393 "parser.y"
    {(yyval.exprs)=make_call(symTable,(yyvsp[(1) - (4)].exprs),(yyvsp[(3) - (4)].exprs));
																printf("#%d call -> call(elist) \n", yylineno);}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    {if((yyvsp[(2) - (2)].exprs)->callList->method==1){
									//struct expr* self=$1;
									struct expr* tmp=emit_ifTableItem(symTable,member_item(symTable,(yyvsp[(1) - (2)].exprs),(yyvsp[(2) - (2)].exprs)->callList->name));
									(yyvsp[(1) - (2)].exprs)->next=(yyvsp[(2) - (2)].exprs)->callList->elist;
									(yyvsp[(2) - (2)].exprs)->callList->elist=(yyvsp[(1) - (2)].exprs);
									
			}
				(yyval.exprs)=make_call(symTable,(yyvsp[(1) - (2)].exprs),(yyvsp[(2) - (2)].exprs)->callList->elist);
									printf("#%d call -> lvalue callsuffix \n", yylineno);}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 404 "parser.y"
    {struct expr* func=newExpr(programfunc_e);
																									func->symbol=(yyvsp[(2) - (6)].node);
																									func->sValue=strdup((yyvsp[(2) - (6)].node)->name);
																									(yyval.exprs)=make_call(symTable,func,(yyvsp[(5) - (6)].exprs));
																									printf("#%d call -> (funcdec)(elist) \n", yylineno);}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 411 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
								printf("#%d callsuffix -> normcall \n", yylineno);}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (1)].exprs);
								printf("#%d callsuffix -> methodcall \n", yylineno);}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {
															(yyval.exprs)=make_normcall((yyvsp[(2) - (3)].exprs));
																printf("#%d normcall -> (elist) \n", yylineno);}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 422 "parser.y"
    {(yyval.exprs)=make_methodcall((yyvsp[(2) - (5)].sValue),(yyvsp[(4) - (5)].exprs));
																				printf("#%d methodcall -> ..id(elist) \n", yylineno);}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    {(yyval.exprs)=(yyvsp[(1) - (2)].exprs);
							(yyval.exprs)->next=(yyvsp[(2) - (2)].exprs);
							printf("#%d elist -> expr elist2 \n", yylineno);}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 429 "parser.y"
    {(yyval.exprs)=NULL;
				printf("#%d elist -> empty \n", yylineno);}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 432 "parser.y"
    {(yyval.exprs)=(yyvsp[(2) - (3)].exprs);
									(yyval.exprs)->next=(yyvsp[(3) - (3)].exprs);
									printf("#%d elist2 -> , expr elist2 \n", yylineno);}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 435 "parser.y"
    {(yyval.exprs)=NULL;
				printf("#%d elist2 -> empty \n", yylineno);}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 439 "parser.y"
    {(yyval.exprs)=tableMake(symTable,(yyvsp[(2) - (3)].exprs));
															printf("#%d objectdef -> [elist] \n", yylineno);}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 441 "parser.y"
    {(yyval.exprs)=tableMakeIndex(symTable,(yyvsp[(2) - (3)].indexed_t));
															printf("#%d objectdef -> [indexed] \n", yylineno);}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    {(yyval.indexed_t)=(yyvsp[(1) - (2)].indexed_t);
										(yyval.indexed_t)->next=(yyvsp[(2) - (2)].indexed_t);
										printf("#%d indexed -> indexelem indexed2 \n", yylineno);}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 450 "parser.y"
    {(yyval.indexed_t)=(yyvsp[(2) - (3)].indexed_t);
												(yyval.indexed_t)->next=(yyvsp[(3) - (3)].indexed_t);
												printf("#%d indexed2 -> , indexelem indexed2 \n", yylineno);}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 453 "parser.y"
    {(yyval.indexed_t)=NULL;
					printf("#%d indexed2 -> empty \n", yylineno);}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 457 "parser.y"
    {struct indexed *new=malloc(sizeof(struct indexed));
																new->name=(yyvsp[(2) - (5)].exprs);
																if((yyvsp[(2) - (5)].exprs)->sValue!=NULL){
																	new->name->sValue=strdup((yyvsp[(2) - (5)].exprs)->sValue);	
																}else{
																	new->name->iValue=(yyvsp[(2) - (5)].exprs)->iValue;
																}
																
																
																new->value=(yyvsp[(4) - (5)].exprs);
																(yyval.indexed_t)=new;
																printf("#%d indexedelem -> {expr:expr} \n", yylineno);}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 471 "parser.y"
    {scope++; }
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 471 "parser.y"
    {hideVar(symTable,scope);
												  scope--;

												  printf("#%d block -> {} \n", yylineno);}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {scope++;   }
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {hideVar(symTable,scope);
													printf("#%d block -> [stmt*] \n",yylineno);
															scope--;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 480 "parser.y"
    {(yyval.sValue)=(yyvsp[(1) - (1)].sValue);
				lastFunc=handleFuncId(symTable,(yyvsp[(1) - (1)].sValue),scope,yylineno);
						//inCurrScopeOffset();
						}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
    {lastFunc=handleFuncNoId(symTable,"def_func_",scope,yylineno);
				(yyval.sValue)=lastFunc->name;
			//inCurrScopeOffset();
						}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 490 "parser.y"
    {
    			(yyval.node)=lastFunc;
    			(yyval.node)->iAddress=nextQuadLabel();
    			emit(funcstart,lvalue_expr((yyval.node)),NULL,NULL,-1,currQuad);
    			
    			localsHead=createLocalsList(functionLocalOffset,localsHead);
    				//push(functioLocalStaxk,functionLocalOffset)
    			
    		    	enterScopeSpace();
    		    	
    		    	resetFormalArgsOffset();
    		    	
    		    	resetFunctionLocalsOffset();
    		    	
    	
    			
    			
    			}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 510 "parser.y"
    {scope++; }
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 510 "parser.y"
    {scope--;
    	
    		enterScopeSpace();
    		

    }
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 518 "parser.y"
    {(yyval.iValue)=functionLocalOffset;		restoreCurrScopeOffset(popLocalsList(&localsHead)); exitScopeSpace();exitScopeSpace();}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    {
   			
   				
   				(yyvsp[(1) - (5)].node)->totalLocals=(yyvsp[(4) - (5)].iValue);
   				
   				(yyval.node)=(yyvsp[(1) - (5)].node);
   				emit(funcend,lvalue_expr((yyvsp[(1) - (5)].node)),NULL,NULL,-1,currQuad);
   			}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 530 "parser.y"
    {loopCounterStack=createLoopList(loopCounter,loopCounterStack);
   						loopCounter=0;
   					
    			
    			
    			}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 537 "parser.y"
    {if(loopCounterStack!=NULL){
   					loopCounter=popLoopList(&loopCounterStack);
   					}
   					
   					}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 543 "parser.y"
    {(yyval.exprs)=NewExprInt((yyvsp[(1) - (1)].iValue));
						printf("#%d const -> integer number \n", yylineno);}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 545 "parser.y"
    {(yyval.exprs)=NewExpDouble((yyvsp[(1) - (1)].dValue));
							printf("#%d const -> real number \n", yylineno);}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 547 "parser.y"
    {(yyval.exprs)=NewStringExp((yyvsp[(1) - (1)].sValue));

						printf("#%d const -> string \n", yylineno);}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 550 "parser.y"
    {(yyval.exprs)=NewNilExp();
						printf("#%d const -> nil \n", yylineno);}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 552 "parser.y"
    { (yyval.exprs)=NewBoolExp(1);
						printf("#%d const -> true \n", yylineno);}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 554 "parser.y"
    { (yyval.exprs)=NewBoolExp(0);
						printf("#%d const -> false \n", yylineno);}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 558 "parser.y"
    {if(lastFunc!=NULL){
					handleArgs(symTable,(yyvsp[(1) - (1)].sValue),lastFunc->name,scope,yylineno);

					inCurrScopeOffset();
					
									}
					printf("#%d idlist -> ID idlist2 \n", yylineno);}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 566 "parser.y"
    {printf("#%d idlist2 -> empty \n", yylineno);}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
    {if(lastFunc!=NULL){
						handleArgs(symTable,(yyvsp[(2) - (2)].sValue),lastFunc->name,scope,yylineno);}
						printf("#%d idlist2 -> , ID idlist2 \n", yylineno);
						inCurrScopeOffset();
						
					}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 576 "parser.y"
    {printf("#%d idlist2 -> empty \n", yylineno);}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 578 "parser.y"
    {emit(if_eq,(yyvsp[(3) - (4)].exprs),NewBoolExp(1),NULL,nextQuadLabel()+2,currQuad);
																(yyval.prefix)=nextQuadLabel();
																emit(jump,NULL,NULL,NULL,0,currQuad);
																}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 583 "parser.y"
    {(yyval.prefix)=nextQuadLabel();
						emit(jump,NULL,NULL,NULL,0,currQuad);}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 586 "parser.y"
    {patchLabel((yyvsp[(1) - (2)].prefix),nextQuadLabel());
							printf("#%d ifstm -> if(expr) stm \n", yylineno);}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 588 "parser.y"
    {patchLabel((yyvsp[(1) - (4)].prefix),(yyvsp[(3) - (4)].prefix)+1);
										patchLabel((yyvsp[(3) - (4)].prefix),nextQuadLabel());
										printf("#%d ifstm -> if(expr) stm else stmt \n", yylineno);}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 592 "parser.y"
    {++loopCounter;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 594 "parser.y"
    {--loopCounter;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 596 "parser.y"
    {(yyval.exprs)=(yyvsp[(2) - (3)].exprs);}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 598 "parser.y"
    {
					(yyval.prefix)=nextQuadLabel();}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 601 "parser.y"
    {
				emit(if_eq,(yyvsp[(2) - (3)].exprs),NewBoolExp(1),NULL,nextQuadLabel()+2,currQuad);
				(yyval.prefix)=nextQuadLabel();
				emit(jump,NULL,NULL,NULL,0,currQuad);
				}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 608 "parser.y"
    {emit(jump,NULL,NULL,NULL,(yyvsp[(1) - (3)].prefix),currQuad);
												patchLabel((yyvsp[(2) - (3)].prefix),nextQuadLabel());
												if(breakList!=NULL){
													patchLabel(breakList->tempQuad,nextQuadLabel());
													breakList=NULL;
												}
												if(continueList!=NULL){
													patchLabel(continueList->tempQuad,(yyvsp[(1) - (3)].prefix));
													continueList=NULL;
												}
																								
											printf("#%d whilestm -> while(expr) stm \n", yylineno);}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 621 "parser.y"
    {(yyval.prefix)=nextQuadLabel();}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 624 "parser.y"
    {(yyval.prefix)=nextQuadLabel();
		emit(jump,NULL,NULL,NULL,-1,currQuad);}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 628 "parser.y"
    {
				(yyval.forpref)=malloc(sizeof(struct forprefix));
				(yyval.forpref)->test=(yyvsp[(5) - (7)].prefix);
				(yyval.forpref)->enter=nextQuadLabel();
				emit(if_eq,(yyvsp[(6) - (7)].exprs),NewBoolExp(1),NULL,-1,currQuad);
				}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 636 "parser.y"
    {
					patchLabel((yyvsp[(1) - (7)].forpref)->enter,(yyvsp[(5) - (7)].prefix)+1);
					patchLabel((yyvsp[(2) - (7)].prefix),nextQuadLabel());
					patchLabel((yyvsp[(5) - (7)].prefix),(yyvsp[(1) - (7)].forpref)->test);
					patchLabel((yyvsp[(7) - (7)].prefix),(yyvsp[(2) - (7)].prefix)+1);
					if(breakList!=NULL){
						patchLabel(breakList->tempQuad,nextQuadLabel());
					}
					if(continueList!=NULL){
						patchLabel(continueList->tempQuad,(yyvsp[(2) - (7)].prefix)+1);
					}
					printf("#%d forstmt -> for(elist; expr; elist) stmt \n", yylineno);}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 650 "parser.y"
    {
					emit(ret,NULL,NULL,NULL,-1,currQuad);
		printf("#%d returnstm -> return; \n", yylineno);}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 653 "parser.y"
    {
					emit(ret,NULL,NULL,(yyvsp[(2) - (3)].exprs),-1,currQuad);
					printf("#%d returnstm -> return expr; \n", yylineno);}
    break;



/* Line 1455 of yacc.c  */
#line 2855 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 660 "parser.y"



int main(int argc, char** argv){

	FILE *in_file;
	FILE *out_file;

	char* in_name;
	char* out_name;

	in_name = argv[1];
	out_name = argv[2];

  	if(argc == 1){
  		yyin = stdin;
  	}

  	if(argc == 2){
  		in_file = fopen(in_name,"r");
  		yyin = in_file;

  	}

  	if(argc==3){
  		in_file = fopen(in_name,"r");
  		yyin = in_file; 
  		out_file = fopen(out_name,"w+");
  		yyout=out_file;
  	}
  	/*
  	//gia testing while under construction
  	node* test=createEntry(0,GLOBAL,"test",0,5);
  	printf("here\n");
	expr *expt=lvalue_expr(test);
	printf("name %s\n",expt->sValue);
	char *ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	ex=newTempName();
	printf("%s\n",ex );
	printf("%d\n",istempname(ex) );
	
	*/

	symTable=createSymbolTable();
	initSumbolTable(symTable,"print");
	initSumbolTable(symTable,"input");
	initSumbolTable(symTable,"objectmemberkeys");
	initSumbolTable(symTable,"objecttotalmembers");
	initSumbolTable(symTable,"objectcopy");
	initSumbolTable(symTable,"totalarguments");
	initSumbolTable(symTable,"argument");
	initSumbolTable(symTable,"typeof");
	initSumbolTable(symTable,"strtonum");
	initSumbolTable(symTable,"sqrt");
	initSumbolTable(symTable,"cos");
	initSumbolTable(symTable,"sin");
	

	yyparse();
	printTable(symTable);
	PrintQuads();
		initiator();
		readBinary();
	
	return 0;
}

 	

