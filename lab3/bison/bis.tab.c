/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 50 "bison/lang.y"

	#include "../VarMap/VarMap.h"
	#include "../Ast/Ast.h"
	#include <queue>
	#include <fstream>
	#include "../Robo/Map.h"
	#include <stack>
	#include "../compile_vars.h"

//	Map labirint{"labirint.txt"};
//	//labirint.changeCellType(3, 4, CellType::obstacle);
//	VarMap* vm=new VarMap();
//	std::stack<VarMap*> program_stack;
//	std::unordered_map<std::string, Ast*> declared_funcs;
//	std::ofstream bison_logger("report_bison.txt");

	int yylex(void);
	void yyerror(const char *s);


#line 91 "bison/bis.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_BISON_BIS_TAB_H_INCLUDED
# define YY_YY_BISON_BIS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 40 "bison/lang.y"

	#include <iostream>
	#include <string>
	#include "../VarMap/VarMap.h"
	#include "../Ast/Ast.h"
	#include <fstream>
	

#line 143 "bison/bis.tab.c"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VAR_NAME = 258,
    VAR_TYPE = 259,
    LITERAL = 260,
    ARRAY = 261,
    UNTIL = 262,
    DO = 263,
    CHECK = 264,
    BEGIN_FUNC = 265,
    END_FUNC = 266,
    RETURN = 267,
    GO = 268,
    RL = 269,
    RR = 270,
    SONAR = 271,
    COMPASS = 272,
    LESS_EQUAL = 273,
    MORE_EQUAL = 274,
    LEFT_ASSIGN = 277,
    RIGHT_ASSIGN = 278
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "bison/lang.y"

	VarType var_type;
	std::string* str;
	int num;
	bool logic;
	Ast* st;
	//st->setRoot(main);

#line 185 "bison/bis.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_BISON_BIS_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

#define YYUNDEFTOK  2
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,    20,    18,    29,    19,    28,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,     2,    36,     2,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    22,    23,    24,    25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,   120,   129,   164,   186,   207,   219,   229,
     236,   243,   258,   262,   271,   276,   297,   301,   306,   311,
     318,   326,   338,   345,   373,   377,   395,   490,   536,   568,
     572,   578,   582,   586,   590,   595,   600,   619,   664,   715,
     739,   743,   749,   754,   762,   774,   781,   795,   802,   809,
     823,   829,   835,   841,   847,   851,   857,   865,   872
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR_NAME", "VAR_TYPE", "LITERAL",
  "ARRAY", "UNTIL", "DO", "CHECK", "BEGIN_FUNC", "END_FUNC", "RETURN",
  "GO", "RL", "RR", "SONAR", "COMPASS", "'+'", "'-'", "'*'", "'/'",
  "LESS_EQUAL", "MORE_EQUAL", "\"<\"", "\">\"", "LEFT_ASSIGN",
  "RIGHT_ASSIGN", "'.'", "','", "'@'", "'['", "']'", "'('", "')'", "'<'",
  "'>'", "$accept", "main", "complex_statement", "simple_statement",
  "args", "expr", "operand", "numeric_operand", "logic_expr",
  "expr_operand", "assign_expr", "args_to_call", "vars", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,    43,    45,
      42,    47,   273,   274,   275,   276,   277,   278,    46,    44,
      64,    91,    93,    40,    41,    60,    62
};
# endif

#define YYPACT_NINF (-63)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-56)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     137,   215,     3,   198,    11,    13,    13,   142,   -10,    -8,
      -5,   219,   236,    86,   111,   142,    13,    45,   -63,   106,
     267,    12,   -63,    70,   -63,    25,   160,   142,    39,    33,
      59,   -20,   -63,   -63,   -63,    86,   112,   188,   190,   209,
      51,   -63,   -63,   -63,   -63,   198,   -63,    58,   263,    63,
     -63,   -63,   -63,   166,   166,   166,   166,   142,   142,    13,
      13,    13,    13,   -63,     4,     5,   184,   142,    34,    93,
      98,    94,   -63,   166,    93,   189,   142,   137,   137,   -63,
     -63,   -63,   -63,   166,    27,    27,   -63,   -63,   -63,   -63,
      47,    47,    70,    70,    76,    97,   103,   -63,   240,   122,
     137,   271,   131,    29,   114,   -63,   -63,   263,   -63,   244,
     -63,   -63,   151,   -63,   142,   132,   -63,   139,   143,   -63,
     -63,   -63
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    25,    58,    31,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     0,     0,     0,     0,     2,     0,
      55,    23,    24,    34,    42,     0,     0,     0,    57,     0,
       0,    36,    35,    40,    41,     0,    55,     0,     0,    33,
       0,    13,    15,    14,    43,    32,    44,     0,    55,     0,
       1,     4,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,    36,    31,     0,    17,     0,    57,
       0,     0,    56,     0,    58,     0,     0,     0,     0,    12,
       8,    49,    54,     0,    47,    48,    45,    46,    20,    21,
      50,    51,    52,    53,     0,     0,     0,    16,    28,    19,
       0,     0,     0,    31,     0,     9,    10,     0,    26,    27,
      37,    18,     0,     5,     0,     0,    39,     0,     0,    38,
      11,     6
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -16,   -63,    67,    17,    -7,   -22,    -4,    53,
      80,   -62,     7
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    17,    18,    19,    71,    39,    21,    22,    23,    24,
      25,    68,    72
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    37,    38,    52,    66,    97,    28,    94,    47,    29,
      95,    75,    49,    76,   104,    30,    31,    20,    32,    41,
      67,    42,    36,    36,    43,   -35,   -35,   -35,   -35,    33,
      34,    13,    35,    48,   115,    75,    20,    76,    57,    58,
     -35,   -35,    69,    70,    96,    50,    16,    55,    56,   -35,
     -35,   -35,   -35,    66,    63,    90,    91,    92,    93,    73,
      67,   105,   106,    74,   -35,   -35,    44,    46,    98,    67,
      84,    85,    86,    87,    20,    20,    36,    36,    36,    36,
      79,   102,    61,    62,   112,    59,    60,    80,    46,    31,
     101,    32,    59,    60,    20,    20,    69,    82,    61,    62,
     107,    99,    33,    34,   100,    61,    62,   118,   108,     1,
       2,     3,     4,     5,    31,     6,    45,    20,     7,     8,
       9,    10,    11,    12,    13,    14,    70,    33,    34,   109,
      53,    54,    55,    56,    51,   110,    15,    88,    89,    16,
       1,     2,     3,     4,     5,     1,     6,     3,   116,     7,
       8,     9,    10,    11,    12,    13,    14,   114,    11,    12,
      13,    14,   117,    64,   119,    65,   111,    15,   120,    31,
      16,    32,   121,     0,     0,    16,    33,    34,    13,    14,
       0,     0,    33,    34,    13,    35,     0,    31,     0,     3,
       0,     0,    31,    16,   103,     0,    77,     0,    78,    83,
      33,    34,    13,    14,     0,    33,    34,    13,    14,     0,
      59,    60,    59,    60,     0,     0,     0,    16,   -35,   -35,
     -35,   -35,    16,    61,    62,    61,    62,    53,    54,    55,
      56,   -55,   -55,   -35,   -35,   -36,   -36,   -36,   -36,   -40,
     -40,   -40,   -40,     0,   -55,   -55,    26,     0,    27,     0,
     -36,   -36,     0,     0,   -40,   -40,   -41,   -41,   -41,   -41,
     -39,   -39,   -39,   -39,   -38,   -38,   -38,   -38,     0,     0,
       0,   -41,   -41,     0,     0,   -39,   -39,     0,     0,   -38,
     -38,    53,    54,    55,    56,    53,    54,    55,    56,    53,
      54,    55,    56,   -33,   -33,     0,   -22,    81,     0,     0,
     113
};

static const yytype_int8 yycheck[] =
{
       7,     5,     6,    19,    26,    67,     3,     3,    15,     2,
       5,    31,    16,    33,    76,     4,     3,     0,     5,    29,
      27,    29,     5,     6,    29,    20,    21,    22,    23,    16,
      17,    18,    19,    16,     5,    31,    19,    33,    26,    27,
      35,    36,     3,     4,    66,     0,    33,    20,    21,    20,
      21,    22,    23,    75,    29,    59,    60,    61,    62,    26,
      67,    77,    78,     4,    35,    36,    13,    14,    34,    76,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      29,    74,    35,    36,   100,    22,    23,    29,    35,     3,
      73,     5,    22,    23,    77,    78,     3,    34,    35,    36,
      83,     3,    16,    17,    10,    35,    36,   114,    32,     3,
       4,     5,     6,     7,     3,     9,     5,   100,    12,    13,
      14,    15,    16,    17,    18,    19,     4,    16,    17,    32,
      18,    19,    20,    21,    28,    32,    30,    57,    58,    33,
       3,     4,     5,     6,     7,     3,     9,     5,    34,    12,
      13,    14,    15,    16,    17,    18,    19,    26,    16,    17,
      18,    19,    11,     3,    32,     5,    99,    30,    29,     3,
      33,     5,    29,    -1,    -1,    33,    16,    17,    18,    19,
      -1,    -1,    16,    17,    18,    19,    -1,     3,    -1,     5,
      -1,    -1,     3,    33,     5,    -1,     8,    -1,     8,    33,
      16,    17,    18,    19,    -1,    16,    17,    18,    19,    -1,
      22,    23,    22,    23,    -1,    -1,    -1,    33,    20,    21,
      22,    23,    33,    35,    36,    35,    36,    18,    19,    20,
      21,    22,    23,    35,    36,    20,    21,    22,    23,    20,
      21,    22,    23,    -1,    35,    36,    31,    -1,    33,    -1,
      35,    36,    -1,    -1,    35,    36,    20,    21,    22,    23,
      20,    21,    22,    23,    20,    21,    22,    23,    -1,    -1,
      -1,    35,    36,    -1,    -1,    35,    36,    -1,    -1,    35,
      36,    18,    19,    20,    21,    18,    19,    20,    21,    18,
      19,    20,    21,    26,    27,    -1,    29,    34,    -1,    -1,
      29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    12,    13,    14,
      15,    16,    17,    18,    19,    30,    33,    38,    39,    40,
      42,    43,    44,    45,    46,    47,    31,    33,     3,    49,
       4,     3,     5,    16,    17,    19,    42,    45,    45,    42,
      43,    29,    29,    29,    46,     5,    46,    43,    42,    45,
       0,    28,    39,    18,    19,    20,    21,    26,    27,    22,
      23,    35,    36,    29,     3,     5,    44,    43,    48,     3,
       4,    41,    49,    26,     4,    31,    33,     8,     8,    29,
      29,    34,    34,    33,    42,    42,    42,    42,    47,    47,
      45,    45,    45,    45,     3,     5,    44,    48,    34,     3,
      10,    42,    49,     5,    48,    39,    39,    42,    32,    32,
      32,    41,    39,    29,    26,     5,    34,    11,    43,    32,
      29,    29
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    48,    48,    41,    41,
      47,    47,    47,    47,    43,    43,    43,    43,    43,    43,
      43,    44,    44,    44,    44,    46,    46,    46,    46,    46,
      46,    46,    42,    42,    42,    42,    42,    42,    42,    42,
      45,    45,    45,    45,    45,    45,    49,    49,    49
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     5,     7,     2,     3,     4,
       4,     7,     3,     2,     2,     2,     2,     1,     3,     2,
       3,     3,     1,     1,     1,     1,     5,     5,     4,     1,
       1,     1,     2,     1,     1,     1,     1,     5,     5,     4,
       1,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 84 "bison/lang.y"
                        {
    				//labirint.transportRobo(0, 5);
    				//ast.root=main_func;
				//$$->printAst();
			//	std::cout<<"funcs:"<<std::endl;
			//	for(auto& func: declared_funcs)
			//	{
			//		func.second->printAst();
			//	}
				//$$->root->applyFinalExec(true);
				program_stack.push(vm);
				(yyval.st)->root->applyProgramStack(&program_stack);
				(yyval.st)->root->applyScope(vm);
				(yyval.st)->root->applyErrors(&err_vec);
				(yyval.st)->execute();
				std::cout<<"Errors: "<<err_vec.size()<<std::endl;
				for(auto& err: err_vec)
				{
					std::cerr<<err;
					std::cerr<<std::endl;
				}
			//	std::cout<<"Stack:"<<std::endl;
				
				//cleaning
			//	while(!program_stack.empty())
			//	{
			//		program_stack.top()->clear();
			//		std::cout<<*program_stack.top();
			//		std::cout<<std::endl;
			//		program_stack.pop();
			//	}
				//$$->printAst();
				//ast.printAst();
    			}
#line 1616 "bison/bis.tab.c"
    break;

  case 3:
#line 120 "bison/lang.y"
                                           {
						Ast* nst=new Ast();
						nst->root=new ConnectingNode(",", (yyvsp[-1].st)->root, (yyvsp[0].st)->root);
						(yyval.st)=nst;
						//ast.root=main_func;
						//main_func->execute();
						//ast.printAst();
						//ast.execute();
						}
#line 1630 "bison/bis.tab.c"
    break;

  case 4:
#line 129 "bison/lang.y"
                               {
					Ast* nst=new Ast();
					nst->root=new ConnectingNode(".", (yyvsp[-1].st)->root, nullptr);
					(yyval.st)=nst;
					//$$=$1;
					//$$->printAst();
					//ast.root=main_func;
					//main_func->execute();
					//ast.printAst();
					//ast.execute();
				}
#line 1646 "bison/bis.tab.c"
    break;

  case 5:
#line 164 "bison/lang.y"
                                           {
						vm->clearBuffers();
						//vm->pushVarToInit(*$2);
						
						//std::vector<Node*> args;
						//args.push_back($5->root);
						std::vector<int> params;
						params.push_back(intByType((yyvsp[-4].var_type)));
						params.push_back((yylsp[0]).first_line);
						params.push_back((yylsp[-3]).first_line);
						
						OperatorNode* on=new DefiningOperator(vm, (yyvsp[-3].st), (yyvsp[-1].st)->root, params);
						
						Ast* ost=new Ast(on);

						//main_func->stmts.push_back(ost);
						//stmt_group->stmts.push_back(ost);
						//to uncomment
						//ost->execute();
						(yyval.st)=ost;	
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
						}
#line 1673 "bison/bis.tab.c"
    break;

  case 6:
#line 187 "bison/lang.y"
                                                {
							vm->clearBuffers();
							//vm->pushVarToInit(*$4);
							
							//std::vector<Node*> args;
							//args.push_back($7->root);
							std::vector<int> params;
							params.push_back(intByType((yyvsp[-5].var_type)));
							params.push_back(intByType((yyvsp[-4].var_type)));
							params.push_back((yylsp[-6]).first_line);
							OperatorNode* on=new DefiningOperator(vm, (yyvsp[-3].st), (yyvsp[-1].st)->root, params, true);
							
							Ast* ost=new Ast(on);

							//main_func->stmts.push_back(ost);
							program_stack.push(vm);
							ost->root->applyProgramStack(&program_stack);
							ost->execute();
							(yyval.st)=ost;	
						}
#line 1698 "bison/bis.tab.c"
    break;

  case 7:
#line 208 "bison/lang.y"
                                                {
							//std::vector<int> params;
							//params.push_back(@1.first_line);
							//OperatorNode* on=new AssigningOperator(vm, params);
							//Ast* ost=new Ast(on);
							//main_func->stmts.push_back(ost);
							//ost->execute();
							//$$->execute();
							(yyval.st)=(yyvsp[-1].st);
							//$$->execute();
	  					}
#line 1714 "bison/bis.tab.c"
    break;

  case 8:
#line 219 "bison/lang.y"
                                                {
							Ast* ost=new Ast(new PrintValueOperator((yyvsp[-1].st)->root), (yyvsp[-1].st));
							(yyval.st)=ost;
							//main_func->stmts.push_back(ost);
							//std::cout<<$2<<std::endl;
						}
#line 1725 "bison/bis.tab.c"
    break;

  case 9:
#line 229 "bison/lang.y"
                                                {
							//vm->clearBuffers();
							OperatorNode* op=new UntilOperator(vm, (yyvsp[-2].st)->root, (yyvsp[0].st)->root);
							Ast* ost=new Ast(op);
							(yyval.st)=ost;
							//ost->execute();
						}
#line 1737 "bison/bis.tab.c"
    break;

  case 10:
#line 236 "bison/lang.y"
                                                {
							OperatorNode* op=new CheckOperator(vm, (yyvsp[-2].st)->root, (yyvsp[0].st)->root);
							Ast* ost=new Ast(op);
							(yyval.st)=ost;

							
						}
#line 1749 "bison/bis.tab.c"
    break;

  case 11:
#line 243 "bison/lang.y"
                                                                           {
								OperatorNode* func=new FunctionOperator((yyvsp[-6].var_type), *(yyvsp[-5].str), (yyvsp[-4].st), (yyvsp[-2].st)->root, vm);		
								dynamic_cast<FunctionOperator*>(func)->declared_funcs=&declared_funcs;
								if(!declared_funcs.contains(*(yyvsp[-5].str))) declared_funcs.insert({*(yyvsp[-5].str), new Ast(func)});
								else
								{
									std::cout<<"redeclariiiiing "<<*(yyvsp[-5].str)<<std::endl;
									declared_funcs[*(yyvsp[-5].str)]->root=func;
									
									//declared_funcs[*$2]->root->updateFunctionCalls(declared_funcs);
									//declared_funcs[*$2]->root->printNode(std::cout);
								}
								Ast* ost=new Ast();
								(yyval.st)=ost;
								}
#line 1769 "bison/bis.tab.c"
    break;

  case 12:
#line 258 "bison/lang.y"
                                                {
							OperatorNode* return_stmt=new ReturnOperator((yyvsp[-1].st)->root);
							(yyval.st)=new Ast(return_stmt);
						}
#line 1778 "bison/bis.tab.c"
    break;

  case 13:
#line 262 "bison/lang.y"
                                                {
						//	labirint.changeCellType(3, 4, CellType::obstacle);
						//	labirint.changeCellType(2, 4, CellType::obstacle);
						//	labirint.changeCellType(3, 3, CellType::obstacle);
							//labirint.changeCellType(1, 2, CellType::obstacle);
							OperatorNode* op=new GoOperator(labirint);
							//op->execute();
							(yyval.st)=new Ast(op);
						}
#line 1792 "bison/bis.tab.c"
    break;

  case 14:
#line 271 "bison/lang.y"
                                                {
							OperatorNode* op=new RrOperator(labirint);
							//op->execute();
							(yyval.st)=new Ast(op);
						}
#line 1802 "bison/bis.tab.c"
    break;

  case 15:
#line 276 "bison/lang.y"
                                                {
							OperatorNode* op=new RlOperator(labirint);
							//op->execute();
							(yyval.st)=new Ast(op);
						}
#line 1812 "bison/bis.tab.c"
    break;

  case 16:
#line 297 "bison/lang.y"
                                 {
					(yyval.st)=new Ast((yyvsp[-1].st)->root, (yyvsp[0].st));
	    				
	    			}
#line 1821 "bison/bis.tab.c"
    break;

  case 17:
#line 301 "bison/lang.y"
                                {
	    				(yyval.st)=(yyvsp[0].st);
	    			}
#line 1829 "bison/bis.tab.c"
    break;

  case 18:
#line 306 "bison/lang.y"
                               {
					OperandNode* op=new OperandNode(new Operand(new Var((yyvsp[-2].var_type), *(yyvsp[-1].str))));

					(yyval.st)=new Ast(op, (yyvsp[0].st));
    				}
#line 1839 "bison/bis.tab.c"
    break;

  case 19:
#line 311 "bison/lang.y"
                                {
					OperandNode* op=new OperandNode(new Operand(new Var((yyvsp[-1].var_type), *(yyvsp[0].str))));
					Ast* ost=new Ast(op);
					(yyval.st)=ost;
				}
#line 1849 "bison/bis.tab.c"
    break;

  case 20:
#line 319 "bison/lang.y"
                                        {
						std::vector<int> params;
						params.push_back((yylsp[-2]).first_line);
						(yyval.st)=new Ast(new AssigningOperator((yyvsp[-2].st)->root, AssignType::Left, (yyvsp[0].st)->root, vm, params));
						vm->pushOperator({AssignType::Left});	
						bison_logger<<"left_assignment"<<std::endl;
					}
#line 1861 "bison/bis.tab.c"
    break;

  case 21:
#line 326 "bison/lang.y"
                                                {
						std::vector<int> params;
						params.push_back((yylsp[-2]).first_line);
						(yyval.st)=new Ast(new AssigningOperator((yyvsp[-2].st)->root, AssignType::Right, (yyvsp[0].st)->root, vm, params));
						
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						vm->pushOperator({AssignType::Right});	
						bison_logger<<"right_assignment"<<std::endl;
					}
#line 1877 "bison/bis.tab.c"
    break;

  case 22:
#line 338 "bison/lang.y"
                                        {
						(yyval.st)=(yyvsp[0].st);
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						//bison_logger<<"expr"<<std::endl;	
					}
#line 1889 "bison/bis.tab.c"
    break;

  case 23:
#line 345 "bison/lang.y"
                                        {
						(yyval.st)=(yyvsp[0].st);
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						//bison_logger<<"expr"<<std::endl;	
					}
#line 1901 "bison/bis.tab.c"
    break;

  case 24:
#line 373 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[0].st);
					bison_logger<<"operand_literal: "<<(yyvsp[0].st)<<std::endl;
				}
#line 1910 "bison/bis.tab.c"
    break;

  case 25:
#line 377 "bison/lang.y"
                        {
			
				if(vm->checkIfDefined(*(yyvsp[0].str)))
				{
					Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[0].str)))));
					(yyval.st)=ost;
					bison_logger<<"operand_variable: "<<std::endl;
					bison_logger<<*vm->getVar(*(yyvsp[0].str));
					bison_logger<<std::endl;
				}
				else
				{
					Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::big, *(yyvsp[0].str), 0))));
					(yyval.st)=ost;
					std::cerr<<"Syntax error at line "<<(yylsp[0]).first_line<<std::endl;
					std::cerr<<"Error text: "<<"Error. Variable "+*(yyvsp[0].str)+" was not defined."<<std::endl;
				}
			}
#line 1933 "bison/bis.tab.c"
    break;

  case 26:
#line 395 "bison/lang.y"
                                             {
					bool exists=vm->checkIfDefined(*(yyvsp[-4].str));

					if(exists && !vm->getVar(*(yyvsp[-4].str))->isField)
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						err_vec.push_back(Error(Err::typeMisMatch, "Error. Variable "+*(yyvsp[-4].str)+" is not an array.", (yyval.st)->root));
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error. Variable "+*(yyvsp[-4].str)+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							if(!vm->checkIfDefined(*(yyvsp[-2].str)) || !vm->checkIfDefined(*(yyvsp[-1].str)))
							{
								vm->setErrCode(Err::undefined);
								throw std::invalid_argument("Error. Indecies are undefined.");
							}
							bison_logger<<dynamic_cast<Field*>(vm->getVar(*(yyvsp[-4].str)))->getVar(vm->getVar(*(yyvsp[-2].str))->value, vm->getVar(*(yyvsp[-1].str))->value);
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[-4].str)), *(yyvsp[-2].str), *(yyvsp[-1].str))));
							(yyval.st)=ost;
							err_vec.push_back(Error(vm->getErrCode(), error.what(), (yyval.st)->root));
							isError=true;
							std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[-4].str)), *(yyvsp[-2].str), *(yyvsp[-1].str))));
							(yyval.st)=ost;
						}
					}
					else
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						err_vec.push_back(Error(Err::undefined, "Error. Variable "+*(yyvsp[-4].str)+" was not defined.", (yyval.st)->root));
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*(yyvsp[-4].str)+" was not defined."<<std::endl;
					}
					
					}
#line 1988 "bison/bis.tab.c"
    break;

  case 27:
#line 490 "bison/lang.y"
                                           {
					bool exists=vm->checkIfDefined(*(yyvsp[-4].str));

					if(exists && !vm->getVar(*(yyvsp[-4].str))->isField)
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						err_vec.push_back(Error(Err::typeMisMatch, "Error. Variable "+*(yyvsp[-4].str)+" is not an array.", (yyval.st)->root));
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error. Variable "+*(yyvsp[-4].str)+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm->getVar(*(yyvsp[-4].str)))->getVar((yyvsp[-2].num), (yyvsp[-1].num));
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
							(yyval.st)=ost;
							err_vec.push_back(Error(vm->getErrCode(), error.what(), (yyval.st)->root));
							isError=true;
							std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							//std::cout<<"HAHAHAHAHAH"<<std::endl;
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[-4].str)), (yyvsp[-2].num), (yyvsp[-1].num))));
							(yyval.st)=ost;
						}
					}
					else
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						err_vec.push_back(Error(Err::undefined, "Error. Variable "+*(yyvsp[-4].str)+" was not defined.", (yyval.st)->root));
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*(yyvsp[-4].str)+" was not defined."<<std::endl;
					}
					
					}
#line 2039 "bison/bis.tab.c"
    break;

  case 28:
#line 536 "bison/lang.y"
                                        {
							if(declared_funcs.contains(*(yyvsp[-3].str)))
							{
								FunctionOperator* fp=dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root);
								OperatorNode* op=new FunctionOperator(fp->return_type, fp->name, fp->arguments, fp->stmts, vm);
								dynamic_cast<FunctionOperator*>(op)->declared_funcs=&declared_funcs;
								dynamic_cast<FunctionOperator*>(op)->loadArgs((yyvsp[-1].st));
							//	std::cout<<"func operand:"<<std::endl;
							//	fp->printNode(std::cout, 1);
								(yyval.st)=new Ast(op);
							}
							else
							{
								err_vec.push_back(Error(Err::undefined, "Error. Function "+*(yyvsp[-3].str)+" was not declared.", (yyval.st)->root));
								std::cout<<"predeclaring "<<*(yyvsp[-3].str)<<std::endl;
								try
								{	
									Ast* ost=new Ast(new FunctionOperator(VarType::tiny, *(yyvsp[-3].str), (yyvsp[-1].st), nullptr, vm));
									declared_funcs.insert({*(yyvsp[-3].str), ost});
									dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root)->declared_funcs=&declared_funcs;
									(yyval.st)=declared_funcs[*(yyvsp[-3].str)];
								}
								catch(std::invalid_argument error)
								{
									Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::big, *(yyvsp[-3].str), 0))));
									(yyval.st)=ost;
									err_vec.push_back(Error(Err::undefined, error.what(), ost->root));
								}
								std::cerr<<"Syntax error at line "<<(yylsp[-3]).first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Function "+*(yyvsp[-3].str)+" was not declared."<<std::endl;
							}
						}
#line 2076 "bison/bis.tab.c"
    break;

  case 29:
#line 568 "bison/lang.y"
                                                {
							OperatorNode* op=new SonarOperator(labirint);
							(yyval.st)=new Ast(op);
						}
#line 2085 "bison/bis.tab.c"
    break;

  case 30:
#line 572 "bison/lang.y"
                                                {
							OperatorNode* op=new CompassOperator(labirint);
							(yyval.st)=new Ast(op);
						}
#line 2094 "bison/bis.tab.c"
    break;

  case 31:
#line 578 "bison/lang.y"
                        {
				Ast* ost=new Ast(new OperandNode(new Operand({(yyvsp[0].num)})));
				(yyval.st)=ost;
			}
#line 2103 "bison/bis.tab.c"
    break;

  case 32:
#line 582 "bison/lang.y"
                                {
				Ast* ost=new Ast(new OperandNode(new Operand({-(yyvsp[0].num)})));
				(yyval.st)=ost;
			}
#line 2112 "bison/bis.tab.c"
    break;

  case 33:
#line 586 "bison/lang.y"
                        {

				(yyval.st)=(yyvsp[0].st);
			}
#line 2121 "bison/bis.tab.c"
    break;

  case 34:
#line 590 "bison/lang.y"
                        {
				(yyval.st)=(yyvsp[0].st);
			}
#line 2129 "bison/bis.tab.c"
    break;

  case 35:
#line 595 "bison/lang.y"
                        {
				Ast* ost=new Ast(new OperandNode(new Operand({(yyvsp[0].num)})));
				(yyval.st)=ost;
				bison_logger<<"operand_literal: "<<(yyvsp[0].num)<<std::endl;
			}
#line 2139 "bison/bis.tab.c"
    break;

  case 36:
#line 600 "bison/lang.y"
                        {
				if(vm->checkIfDefined(*(yyvsp[0].str)))
				{
					Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[0].str)))));
					(yyval.st)=ost;
					//$$=vm->getVar(*$1)->value;
					//vm->pushOperand({vm->getVar(*$1)});
					bison_logger<<"operand_variable: "<<std::endl;
					bison_logger<<*vm->getVar(*(yyvsp[0].str));
					bison_logger<<std::endl;
				}
				else
				{
					Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::big, *(yyvsp[0].str), 0))));
					(yyval.st)=ost;
					std::cerr<<"Syntax error at line "<<(yylsp[0]).first_line<<std::endl;
					std::cerr<<"Error text: "<<"Error. Variable "+*(yyvsp[0].str)+" was not defined."<<std::endl;
				}
			}
#line 2163 "bison/bis.tab.c"
    break;

  case 37:
#line 619 "bison/lang.y"
                                                           {
					bool exists=vm->checkIfDefined(*(yyvsp[-4].str));

					if(exists && !vm->getVar(*(yyvsp[-4].str))->isField)
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						err_vec.push_back(Error(Err::typeMisMatch, "Error. Variable "+*(yyvsp[-4].str)+" is not an array.", (yyval.st)->root));
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error. Variable "+*(yyvsp[-4].str)+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm->getVar(*(yyvsp[-4].str)))->getVar((yyvsp[-2].st)->execute(), (yyvsp[-1].st)->execute());
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
							(yyval.st)=ost;
							err_vec.push_back(Error(vm->getErrCode(), error.what(), (yyval.st)->root));
							isError=true;
							std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[-4].str)), (yyvsp[-2].st)->execute(), (yyvsp[-1].st)->execute())));
							(yyval.st)=ost;
						}
					}
					else
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						err_vec.push_back(Error(Err::undefined, "Error. Variable "+*(yyvsp[-4].str)+" was not defined.", (yyval.st)->root));
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*(yyvsp[-4].str)+" was not defined."<<std::endl;
					}
					
					}
#line 2213 "bison/bis.tab.c"
    break;

  case 38:
#line 664 "bison/lang.y"
                                           {
					bool exists=vm->checkIfDefined(*(yyvsp[-4].str));

					if(exists && !vm->getVar(*(yyvsp[-4].str))->isField)
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error. Variable "+*(yyvsp[-4].str)+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							//vm->pushOperand({vm->getVar(*$1), $3, $4});
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm->getVar(*(yyvsp[-4].str)))->getVar((yyvsp[-2].num), (yyvsp[-1].num));
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
							(yyval.st)=ost;
							isError=true;
							if(vm->getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
							}
							else if(vm->getErrCode()==Err::outOfRange)
							{
								std::cerr<<"Syntax error at line "<<(yylsp[-1]).first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							//$$=dynamic_cast<Field*>(vm->getVar(*$1))->getVar($3, $4).value;
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*(yyvsp[-4].str)), (yyvsp[-2].num), (yyvsp[-1].num))));
							(yyval.st)=ost;
						}
					}
					else
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-4].str), 0))));
						(yyval.st)=ost;
						std::cerr<<"Syntax error at line "<<(yylsp[-4]).first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*(yyvsp[-4].str)+" was not defined."<<std::endl;
					}
					
					}
#line 2269 "bison/bis.tab.c"
    break;

  case 39:
#line 715 "bison/lang.y"
                                        {
							if(declared_funcs.contains(*(yyvsp[-3].str)))
							{
								FunctionOperator* fp=dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root);
								dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root)->declared_funcs=&declared_funcs;
								OperatorNode* op=new FunctionOperator(fp->return_type, fp->name, fp->arguments, fp->stmts, vm);
								dynamic_cast<FunctionOperator*>(op)->declared_funcs=&declared_funcs;
								dynamic_cast<FunctionOperator*>(op)->loadArgs((yyvsp[-1].st));
							//	std::cout<<"func operand:"<<std::endl;
							//	fp->printNode(std::cout, 1);
								(yyval.st)=new Ast(op);
							}
							else
							{
								std::cout<<"predeclaring "<<*(yyvsp[-3].str)<<std::endl;
								Ast* ost=new Ast(new FunctionOperator(VarType::tiny, *(yyvsp[-3].str), (yyvsp[-1].st), nullptr, vm));
								declared_funcs.insert({*(yyvsp[-3].str), ost});
								dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root)->declared_funcs=&declared_funcs;
								std::cout<<"here declared_funcs adress: "<<dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root)->declared_funcs<<std::endl;
								(yyval.st)=declared_funcs[*(yyvsp[-3].str)];
								std::cerr<<"Syntax error at line "<<(yylsp[-3]).first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Function "+*(yyvsp[-3].str)+" was not declared."<<std::endl;
							}
						}
#line 2298 "bison/bis.tab.c"
    break;

  case 40:
#line 739 "bison/lang.y"
                                                {
							OperatorNode* op=new SonarOperator(labirint);
							(yyval.st)=new Ast(op);
						}
#line 2307 "bison/bis.tab.c"
    break;

  case 41:
#line 743 "bison/lang.y"
                                                {
							OperatorNode* op=new CompassOperator(labirint);
							(yyval.st)=new Ast(op);
						}
#line 2316 "bison/bis.tab.c"
    break;

  case 42:
#line 749 "bison/lang.y"
                                        {
					(yyval.st)=(yyvsp[0].st);
					//vm->popOperand();
					bison_logger<<"operand with value "<<(yyvsp[0].st)<<std::endl;
					}
#line 2326 "bison/bis.tab.c"
    break;

  case 43:
#line 754 "bison/lang.y"
                                        {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::uplus, {(yyvsp[0].st)->root}), (yyvsp[0].st));
					(yyval.st)=ost;

					//$$=$2;
					//vm->popOperand();
					bison_logger<<"plused operand with value "<<(yyvsp[0].st)<<std::endl;
					}
#line 2339 "bison/bis.tab.c"
    break;

  case 44:
#line 762 "bison/lang.y"
                                        {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::uminus, {(yyvsp[0].st)->root}), (yyvsp[0].st));
					(yyval.st)=ost;
					//vm->popOperand();
					//bison_logger<<"minused operand with value "<<-$2<<std::endl;
					}
#line 2350 "bison/bis.tab.c"
    break;

  case 45:
#line 774 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::mult, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1*$3;
					//vm->pushOperand($$);
					bison_logger<<"product of two expressions with value "<<(yyval.st)<<std::endl;
				}
#line 2362 "bison/bis.tab.c"
    break;

  case 46:
#line 781 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::div, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					/*if($3==0)
					{
						$$=32768;
					}
					else
					{
						$$=$1/$3;
					}*/
					bison_logger<<"division of two expressions with value "<<(yyval.st)<<std::endl;
					//vm->pushOperand($$);
				}
#line 2381 "bison/bis.tab.c"
    break;

  case 47:
#line 795 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::plus, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1+$3;
					//vm->pushOperand($$);
					bison_logger<<"sum of two expressions with value "<<(yyval.st)<<std::endl;
				}
#line 2393 "bison/bis.tab.c"
    break;

  case 48:
#line 802 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::minus, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1-$3;
					//vm->pushOperand($$);
					bison_logger<<"difference between two expressions with value "<<(yyval.st)<<std::endl;
				}
#line 2405 "bison/bis.tab.c"
    break;

  case 49:
#line 809 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[-1].st);
					bison_logger<<"expression in brackets with value "<<(yyval.st)<<std::endl;
					//vm->pushOperand($$);
				}
#line 2415 "bison/bis.tab.c"
    break;

  case 50:
#line 823 "bison/lang.y"
                                                {
					Ast* ost=new Ast(new LogicOperator(LogicType::le, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1<=$3;
					bison_logger<<(yyvsp[-2].st)<<"<="<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2426 "bison/bis.tab.c"
    break;

  case 51:
#line 829 "bison/lang.y"
                                            {
					Ast* ost=new Ast(new LogicOperator(LogicType::me, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1>=$3;
					bison_logger<<(yyvsp[-2].st)<<">="<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2437 "bison/bis.tab.c"
    break;

  case 52:
#line 835 "bison/lang.y"
                                                {
					Ast* ost=new Ast(new LogicOperator(LogicType::l, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1<$3;
					bison_logger<<(yyvsp[-2].st)<<"<"<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2448 "bison/bis.tab.c"
    break;

  case 53:
#line 841 "bison/lang.y"
                                                {
					Ast* ost=new Ast(new LogicOperator(LogicType::m, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1>$3;
					bison_logger<<(yyvsp[-2].st)<<">"<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2459 "bison/bis.tab.c"
    break;

  case 54:
#line 847 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[-1].st);
					bison_logger<<"("<<(yyvsp[-1].st)<<")"<<std::endl;
				}
#line 2468 "bison/bis.tab.c"
    break;

  case 55:
#line 851 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[0].st);
					bison_logger<<"expr from logic expr"<<std::endl;
				}
#line 2477 "bison/bis.tab.c"
    break;

  case 56:
#line 857 "bison/lang.y"
                      {
				
				OperandNode* op=new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-1].str), 0)));
				(yyval.st)=new Ast(op, (yyvsp[0].st));
				//targetVec.push_back(*$1);
				//vm->pushVarToInit(*$1);
				bison_logger<<"var "<<*(yyvsp[-1].str)<<"pushed to init queue."<<std::endl;
			}
#line 2490 "bison/bis.tab.c"
    break;

  case 57:
#line 865 "bison/lang.y"
                   {
				OperandNode* op=new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[0].str), 0)));		
				(yyval.st)=new Ast(op);
				//targetVec.push_back(*$1);
				//vm->pushVarToInit(*$1);
				bison_logger<<"var "<<*(yyvsp[0].str)<<"pushed to init queue."<<std::endl;
			}
#line 2502 "bison/bis.tab.c"
    break;

  case 58:
#line 872 "bison/lang.y"
                        {}
#line 2508 "bison/bis.tab.c"
    break;


#line 2512 "bison/bis.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 875 "bison/lang.y"



void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}



