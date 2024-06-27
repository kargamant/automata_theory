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
#line 49 "bison/lang.y"

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
#line 39 "bison/lang.y"

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
    LESS_EQUAL = 272,
    MORE_EQUAL = 273,
    LEFT_ASSIGN = 276,
    RIGHT_ASSIGN = 277
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 71 "bison/lang.y"

	VarType var_type;
	std::string* str;
	int num;
	bool logic;
	Ast* st;
	//st->setRoot(main);

#line 184 "bison/bis.tab.c"

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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

#define YYUNDEFTOK  2
#define YYMAXUTOK   277


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
      32,    33,    19,    17,    28,    18,    27,    20,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,     2,    35,     2,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
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
      15,    16,    21,    22,    23,    24,    25,    26
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,   118,   127,   162,   184,   203,   215,   225,
     232,   239,   254,   258,   267,   272,   293,   297,   302,   307,
     314,   322,   334,   341,   369,   373,   391,   436,   481,   503,
     509,   513,   517,   521,   526,   531,   550,   595,   646,   672,
     677,   685,   691,   698,   712,   719,   726,   733,   739,   745,
     751,   757,   761,   767,   775,   782
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VAR_NAME", "VAR_TYPE", "LITERAL",
  "ARRAY", "UNTIL", "DO", "CHECK", "BEGIN_FUNC", "END_FUNC", "RETURN",
  "GO", "RL", "RR", "SONAR", "'+'", "'-'", "'*'", "'/'", "LESS_EQUAL",
  "MORE_EQUAL", "\"<\"", "\">\"", "LEFT_ASSIGN", "RIGHT_ASSIGN", "'.'",
  "','", "'@'", "'['", "']'", "'('", "')'", "'<'", "'>'", "$accept",
  "main", "complex_statement", "simple_statement", "args", "expr",
  "operand", "numeric_operand", "logic_expr", "expr_operand",
  "assign_expr", "args_to_call", "vars", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    43,    45,    42,
      47,   272,   273,   274,   275,   276,   277,    46,    44,    64,
      91,    93,    40,    41,    60,    62
};
# endif

#define YYPACT_NINF (-55)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     130,    62,    -2,    17,     2,    12,    12,     9,   -15,    -5,
       0,   -55,    40,    45,     9,    12,    32,   -55,   100,   218,
      94,   -55,   158,   -55,     7,   123,     9,   127,    29,    38,
      23,   -55,    40,   207,    25,   161,   188,    50,   -55,   -55,
     -55,   -55,    17,   -55,    52,   105,    65,   -55,   -55,   -55,
     146,   146,   146,   146,     9,     9,    12,    12,    12,    12,
     -55,   149,   153,     9,    55,    88,    90,    91,   -55,   146,
      88,   169,     9,   130,   130,   -55,   -55,   -55,   -55,   146,
     141,   141,   -55,   -55,   -55,   -55,   168,   168,   158,   158,
      77,    79,   -55,   178,   117,   130,   222,   125,   172,   153,
     120,   -55,   -55,   105,   195,   199,   -55,   154,   -55,     9,
     126,   137,   -55,   145,   148,   -55,   -55,   -55,   -55
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    25,    55,    30,     0,     0,     0,     0,     0,     0,
       0,    29,     0,     0,     0,     0,     0,     2,     0,    52,
      23,    24,    33,    39,     0,     0,     0,    54,     0,     0,
      35,    34,     0,    52,     0,     0,    32,     0,    13,    15,
      14,    40,    31,    41,     0,    52,     0,     1,     4,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,    34,     0,    17,     0,    54,     0,     0,    53,     0,
      55,     0,     0,     0,     0,    12,     8,    46,    51,     0,
      44,    45,    42,    43,    20,    21,    47,    48,    49,    50,
       0,     0,    16,    28,    19,     0,     0,     0,    34,     0,
       0,     9,    10,     0,    27,    26,    18,     0,     5,     0,
       0,     0,    38,     0,     0,    37,    36,    11,     6
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -55,   -55,   -16,   -55,    97,    16,    -7,   -22,     5,    -8,
     177,   -54,     6
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    16,    17,    18,    67,    36,    20,    21,    22,    23,
      24,    64,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    27,    49,    62,    41,    43,    29,    44,    28,    92,
      34,    35,     1,    38,     3,    30,    19,    31,   100,    63,
      46,    33,    33,    39,    43,    11,    12,    13,    40,    12,
      32,    45,    47,    73,    19,    60,   -34,   -34,   -34,   -34,
      91,    15,    70,    30,    15,    31,    56,    57,    30,    99,
      42,   -34,   -34,    71,    69,    72,    63,   101,   102,    58,
      59,    86,    87,    88,    89,    63,    80,    81,    82,    83,
      19,    19,    33,    33,    33,    33,    97,   111,    75,   107,
      76,   -35,   -35,   -35,   -35,    96,    56,    57,    93,    19,
      19,    65,    25,    94,    26,   103,   -35,   -35,    78,    58,
      59,    95,   114,     1,     2,     3,     4,     5,   104,     6,
     105,    19,     7,     8,     9,    10,    11,    12,    13,    54,
      55,    66,    50,    51,    52,    53,    30,    48,    61,    14,
      65,    66,    15,     1,     2,     3,     4,     5,    77,     6,
      12,    13,     7,     8,     9,    10,    11,    12,    13,    30,
     109,    31,   -30,   112,    90,    15,    30,   115,     3,    14,
      52,    53,    15,    12,    32,   113,   -30,   -30,   116,    74,
      12,    13,    30,   117,    98,   -30,   118,   110,    79,    56,
      57,   -30,    56,    57,     0,    15,    12,    13,     0,   -30,
     -30,   106,    58,    59,     0,    58,    59,   -38,   -38,   -38,
     -38,    15,    58,    59,   -30,    50,    51,    52,    53,   -52,
     -52,     0,   -38,   -38,   -37,   -37,   -37,   -37,   -36,   -36,
     -36,   -36,   -52,   -52,    50,    51,    52,    53,     0,   -37,
     -37,    84,    85,   -36,   -36,    50,    51,    52,    53,    50,
      51,    52,    53,   -32,   -32,     0,   -22,     0,     0,     0,
     108
};

static const yytype_int8 yycheck[] =
{
       7,     3,    18,    25,    12,    13,     4,    14,     2,    63,
       5,     6,     3,    28,     5,     3,     0,     5,    72,    26,
      15,     5,     6,    28,    32,    16,    17,    18,    28,    17,
      18,    15,     0,     8,    18,    28,    19,    20,    21,    22,
      62,    32,     4,     3,    32,     5,    21,    22,     3,    71,
       5,    34,    35,    30,    25,    32,    63,    73,    74,    34,
      35,    56,    57,    58,    59,    72,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    70,    99,    28,    95,
      28,    19,    20,    21,    22,    69,    21,    22,    33,    73,
      74,     3,    30,     3,    32,    79,    34,    35,    33,    34,
      35,    10,   109,     3,     4,     5,     6,     7,    31,     9,
      31,    95,    12,    13,    14,    15,    16,    17,    18,    25,
      26,     4,    17,    18,    19,    20,     3,    27,     5,    29,
       3,     4,    32,     3,     4,     5,     6,     7,    33,     9,
      17,    18,    12,    13,    14,    15,    16,    17,    18,     3,
      25,     5,     3,    33,     5,    32,     3,    31,     5,    29,
      19,    20,    32,    17,    18,    11,    17,    18,    31,     8,
      17,    18,     3,    28,     5,     3,    28,     5,    32,    21,
      22,    32,    21,    22,    -1,    32,    17,    18,    -1,    17,
      18,    94,    34,    35,    -1,    34,    35,    19,    20,    21,
      22,    32,    34,    35,    32,    17,    18,    19,    20,    21,
      22,    -1,    34,    35,    19,    20,    21,    22,    19,    20,
      21,    22,    34,    35,    17,    18,    19,    20,    -1,    34,
      35,    54,    55,    34,    35,    17,    18,    19,    20,    17,
      18,    19,    20,    25,    26,    -1,    28,    -1,    -1,    -1,
      28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    12,    13,    14,
      15,    16,    17,    18,    29,    32,    37,    38,    39,    41,
      42,    43,    44,    45,    46,    30,    32,     3,    48,     4,
       3,     5,    18,    41,    44,    44,    41,    42,    28,    28,
      28,    45,     5,    45,    42,    41,    44,     0,    27,    38,
      17,    18,    19,    20,    25,    26,    21,    22,    34,    35,
      28,     5,    43,    42,    47,     3,     4,    40,    48,    25,
       4,    30,    32,     8,     8,    28,    28,    33,    33,    32,
      41,    41,    41,    41,    46,    46,    44,    44,    44,    44,
       5,    43,    47,    33,     3,    10,    41,    48,     5,    43,
      47,    38,    38,    41,    31,    31,    40,    38,    28,    25,
       5,    43,    33,    11,    42,    31,    31,    28,    28
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    47,    47,    40,    40,
      46,    46,    46,    46,    42,    42,    42,    42,    42,    42,
      43,    43,    43,    43,    45,    45,    45,    45,    45,    41,
      41,    41,    41,    41,    41,    41,    41,    44,    44,    44,
      44,    44,    44,    48,    48,    48
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     5,     7,     2,     3,     4,
       4,     7,     3,     2,     2,     2,     2,     1,     3,     2,
       3,     3,     1,     1,     1,     1,     5,     5,     4,     1,
       1,     2,     1,     1,     1,     1,     5,     5,     4,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     2,     1,     0
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
#line 83 "bison/lang.y"
                        {
    				//ast.root=main_func;
				(yyval.st)->printAst();
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
#line 1601 "bison/bis.tab.c"
    break;

  case 3:
#line 118 "bison/lang.y"
                                           {
						Ast* nst=new Ast();
						nst->root=new ConnectingNode(",", (yyvsp[-1].st)->root, (yyvsp[0].st)->root);
						(yyval.st)=nst;
						//ast.root=main_func;
						//main_func->execute();
						//ast.printAst();
						//ast.execute();
						}
#line 1615 "bison/bis.tab.c"
    break;

  case 4:
#line 127 "bison/lang.y"
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
#line 1631 "bison/bis.tab.c"
    break;

  case 5:
#line 162 "bison/lang.y"
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
#line 1658 "bison/bis.tab.c"
    break;

  case 6:
#line 185 "bison/lang.y"
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
							//ost->execute();
							(yyval.st)=ost;	
						}
#line 1681 "bison/bis.tab.c"
    break;

  case 7:
#line 204 "bison/lang.y"
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
#line 1697 "bison/bis.tab.c"
    break;

  case 8:
#line 215 "bison/lang.y"
                                                {
							Ast* ost=new Ast(new PrintValueOperator((yyvsp[-1].st)->root), (yyvsp[-1].st));
							(yyval.st)=ost;
							//main_func->stmts.push_back(ost);
							//std::cout<<$2<<std::endl;
						}
#line 1708 "bison/bis.tab.c"
    break;

  case 9:
#line 225 "bison/lang.y"
                                                {
							//vm->clearBuffers();
							OperatorNode* op=new UntilOperator(vm, (yyvsp[-2].st)->root, (yyvsp[0].st)->root);
							Ast* ost=new Ast(op);
							(yyval.st)=ost;
							//ost->execute();
						}
#line 1720 "bison/bis.tab.c"
    break;

  case 10:
#line 232 "bison/lang.y"
                                                {
							OperatorNode* op=new CheckOperator(vm, (yyvsp[-2].st)->root, (yyvsp[0].st)->root);
							Ast* ost=new Ast(op);
							(yyval.st)=ost;

							
						}
#line 1732 "bison/bis.tab.c"
    break;

  case 11:
#line 239 "bison/lang.y"
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
#line 1752 "bison/bis.tab.c"
    break;

  case 12:
#line 254 "bison/lang.y"
                                                {
							OperatorNode* return_stmt=new ReturnOperator((yyvsp[-1].st)->root);
							(yyval.st)=new Ast(return_stmt);
						}
#line 1761 "bison/bis.tab.c"
    break;

  case 13:
#line 258 "bison/lang.y"
                                                {
						//	labirint.changeCellType(3, 4, CellType::obstacle);
						//	labirint.changeCellType(2, 4, CellType::obstacle);
						//	labirint.changeCellType(3, 3, CellType::obstacle);
							//labirint.changeCellType(1, 2, CellType::obstacle);
							OperatorNode* op=new GoOperator(labirint);
							op->execute();
							(yyval.st)=new Ast(op);
						}
#line 1775 "bison/bis.tab.c"
    break;

  case 14:
#line 267 "bison/lang.y"
                                                {
							OperatorNode* op=new RrOperator(labirint);
							op->execute();
							(yyval.st)=new Ast(op);
						}
#line 1785 "bison/bis.tab.c"
    break;

  case 15:
#line 272 "bison/lang.y"
                                                {
							OperatorNode* op=new RlOperator(labirint);
							op->execute();
							(yyval.st)=new Ast(op);
						}
#line 1795 "bison/bis.tab.c"
    break;

  case 16:
#line 293 "bison/lang.y"
                                 {
					(yyval.st)=new Ast((yyvsp[-1].st)->root, (yyvsp[0].st));
	    				
	    			}
#line 1804 "bison/bis.tab.c"
    break;

  case 17:
#line 297 "bison/lang.y"
                                {
	    				(yyval.st)=(yyvsp[0].st);
	    			}
#line 1812 "bison/bis.tab.c"
    break;

  case 18:
#line 302 "bison/lang.y"
                               {
					OperandNode* op=new OperandNode(new Operand(new Var((yyvsp[-2].var_type), *(yyvsp[-1].str))));

					(yyval.st)=new Ast(op, (yyvsp[0].st));
    				}
#line 1822 "bison/bis.tab.c"
    break;

  case 19:
#line 307 "bison/lang.y"
                                {
					OperandNode* op=new OperandNode(new Operand(new Var((yyvsp[-1].var_type), *(yyvsp[0].str))));
					Ast* ost=new Ast(op);
					(yyval.st)=ost;
				}
#line 1832 "bison/bis.tab.c"
    break;

  case 20:
#line 315 "bison/lang.y"
                                        {
						std::vector<int> params;
						params.push_back((yylsp[-2]).first_line);
						(yyval.st)=new Ast(new AssigningOperator((yyvsp[-2].st)->root, AssignType::Left, (yyvsp[0].st)->root, vm, params));
						vm->pushOperator({AssignType::Left});	
						bison_logger<<"left_assignment"<<std::endl;
					}
#line 1844 "bison/bis.tab.c"
    break;

  case 21:
#line 322 "bison/lang.y"
                                                {
						std::vector<int> params;
						params.push_back((yylsp[-2]).first_line);
						(yyval.st)=new Ast(new AssigningOperator((yyvsp[-2].st)->root, AssignType::Right, (yyvsp[0].st)->root, vm, params));
						
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						vm->pushOperator({AssignType::Right});	
						bison_logger<<"right_assignment"<<std::endl;
					}
#line 1860 "bison/bis.tab.c"
    break;

  case 22:
#line 334 "bison/lang.y"
                                        {
						(yyval.st)=(yyvsp[0].st);
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						//bison_logger<<"expr"<<std::endl;	
					}
#line 1872 "bison/bis.tab.c"
    break;

  case 23:
#line 341 "bison/lang.y"
                                        {
						(yyval.st)=(yyvsp[0].st);
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						//bison_logger<<"expr"<<std::endl;	
					}
#line 1884 "bison/bis.tab.c"
    break;

  case 24:
#line 369 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[0].st);
					bison_logger<<"operand_literal: "<<(yyvsp[0].st)<<std::endl;
				}
#line 1893 "bison/bis.tab.c"
    break;

  case 25:
#line 373 "bison/lang.y"
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
#line 1916 "bison/bis.tab.c"
    break;

  case 26:
#line 391 "bison/lang.y"
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
#line 1966 "bison/bis.tab.c"
    break;

  case 27:
#line 436 "bison/lang.y"
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
#line 2016 "bison/bis.tab.c"
    break;

  case 28:
#line 481 "bison/lang.y"
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
								std::cout<<"predeclaring "<<*(yyvsp[-3].str)<<std::endl;
								Ast* ost=new Ast(new FunctionOperator(VarType::tiny, *(yyvsp[-3].str), (yyvsp[-1].st), nullptr, vm));
								declared_funcs.insert({*(yyvsp[-3].str), ost});
								dynamic_cast<FunctionOperator*>(declared_funcs[*(yyvsp[-3].str)]->root)->declared_funcs=&declared_funcs;
								(yyval.st)=declared_funcs[*(yyvsp[-3].str)];
								std::cerr<<"Syntax error at line "<<(yylsp[-3]).first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Function "+*(yyvsp[-3].str)+" was not declared."<<std::endl;
							}
						}
#line 2043 "bison/bis.tab.c"
    break;

  case 29:
#line 503 "bison/lang.y"
                                                {
							OperatorNode* op=new SonarOperator(labirint);
							(yyval.st)=new Ast(op);
						}
#line 2052 "bison/bis.tab.c"
    break;

  case 30:
#line 509 "bison/lang.y"
                        {
				Ast* ost=new Ast(new OperandNode(new Operand({(yyvsp[0].num)})));
				(yyval.st)=ost;
			}
#line 2061 "bison/bis.tab.c"
    break;

  case 31:
#line 513 "bison/lang.y"
                                {
				Ast* ost=new Ast(new OperandNode(new Operand({-(yyvsp[0].num)})));
				(yyval.st)=ost;
			}
#line 2070 "bison/bis.tab.c"
    break;

  case 32:
#line 517 "bison/lang.y"
                        {

				(yyval.st)=(yyvsp[0].st);
			}
#line 2079 "bison/bis.tab.c"
    break;

  case 33:
#line 521 "bison/lang.y"
                        {
				(yyval.st)=(yyvsp[0].st);
			}
#line 2087 "bison/bis.tab.c"
    break;

  case 34:
#line 526 "bison/lang.y"
                        {
				Ast* ost=new Ast(new OperandNode(new Operand({(yyvsp[0].num)})));
				(yyval.st)=ost;
				bison_logger<<"operand_literal: "<<(yyvsp[0].num)<<std::endl;
			}
#line 2097 "bison/bis.tab.c"
    break;

  case 35:
#line 531 "bison/lang.y"
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
#line 2121 "bison/bis.tab.c"
    break;

  case 36:
#line 550 "bison/lang.y"
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
#line 2171 "bison/bis.tab.c"
    break;

  case 37:
#line 595 "bison/lang.y"
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
#line 2227 "bison/bis.tab.c"
    break;

  case 38:
#line 646 "bison/lang.y"
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
#line 2256 "bison/bis.tab.c"
    break;

  case 39:
#line 672 "bison/lang.y"
                                        {
					(yyval.st)=(yyvsp[0].st);
					//vm->popOperand();
					bison_logger<<"operand with value "<<(yyvsp[0].st)<<std::endl;
					}
#line 2266 "bison/bis.tab.c"
    break;

  case 40:
#line 677 "bison/lang.y"
                                        {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::uplus, {(yyvsp[0].st)->root}), (yyvsp[0].st));
					(yyval.st)=ost;

					//$$=$2;
					//vm->popOperand();
					bison_logger<<"plused operand with value "<<(yyvsp[0].st)<<std::endl;
					}
#line 2279 "bison/bis.tab.c"
    break;

  case 41:
#line 685 "bison/lang.y"
                                        {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::uminus, {(yyvsp[0].st)->root}), (yyvsp[0].st));
					(yyval.st)=ost;
					//vm->popOperand();
					//bison_logger<<"minused operand with value "<<-$2<<std::endl;
					}
#line 2290 "bison/bis.tab.c"
    break;

  case 42:
#line 691 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::mult, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1*$3;
					//vm->pushOperand($$);
					bison_logger<<"product of two expressions with value "<<(yyval.st)<<std::endl;
				}
#line 2302 "bison/bis.tab.c"
    break;

  case 43:
#line 698 "bison/lang.y"
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
#line 2321 "bison/bis.tab.c"
    break;

  case 44:
#line 712 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::plus, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1+$3;
					//vm->pushOperand($$);
					bison_logger<<"sum of two expressions with value "<<(yyval.st)<<std::endl;
				}
#line 2333 "bison/bis.tab.c"
    break;

  case 45:
#line 719 "bison/lang.y"
                                {
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::minus, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1-$3;
					//vm->pushOperand($$);
					bison_logger<<"difference between two expressions with value "<<(yyval.st)<<std::endl;
				}
#line 2345 "bison/bis.tab.c"
    break;

  case 46:
#line 726 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[-1].st);
					bison_logger<<"expression in brackets with value "<<(yyval.st)<<std::endl;
					//vm->pushOperand($$);
				}
#line 2355 "bison/bis.tab.c"
    break;

  case 47:
#line 733 "bison/lang.y"
                                                {
					Ast* ost=new Ast(new LogicOperator(LogicType::le, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1<=$3;
					bison_logger<<(yyvsp[-2].st)<<"<="<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2366 "bison/bis.tab.c"
    break;

  case 48:
#line 739 "bison/lang.y"
                                            {
					Ast* ost=new Ast(new LogicOperator(LogicType::me, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1>=$3;
					bison_logger<<(yyvsp[-2].st)<<">="<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2377 "bison/bis.tab.c"
    break;

  case 49:
#line 745 "bison/lang.y"
                                                {
					Ast* ost=new Ast(new LogicOperator(LogicType::l, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1<$3;
					bison_logger<<(yyvsp[-2].st)<<"<"<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2388 "bison/bis.tab.c"
    break;

  case 50:
#line 751 "bison/lang.y"
                                                {
					Ast* ost=new Ast(new LogicOperator(LogicType::m, {(yyvsp[-2].st)->root, (yyvsp[0].st)->root}), (yyvsp[-2].st), (yyvsp[0].st));
					(yyval.st)=ost;
					//$$=$1>$3;
					bison_logger<<(yyvsp[-2].st)<<">"<<(yyvsp[0].st)<<": "<<(yyval.st)<<std::endl;
				}
#line 2399 "bison/bis.tab.c"
    break;

  case 51:
#line 757 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[-1].st);
					bison_logger<<"("<<(yyvsp[-1].st)<<")"<<std::endl;
				}
#line 2408 "bison/bis.tab.c"
    break;

  case 52:
#line 761 "bison/lang.y"
                                {
					(yyval.st)=(yyvsp[0].st);
					bison_logger<<"expr from logic expr"<<std::endl;
				}
#line 2417 "bison/bis.tab.c"
    break;

  case 53:
#line 767 "bison/lang.y"
                      {
				
				OperandNode* op=new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[-1].str), 0)));
				(yyval.st)=new Ast(op, (yyvsp[0].st));
				//targetVec.push_back(*$1);
				//vm->pushVarToInit(*$1);
				bison_logger<<"var "<<*(yyvsp[-1].str)<<"pushed to init queue."<<std::endl;
			}
#line 2430 "bison/bis.tab.c"
    break;

  case 54:
#line 775 "bison/lang.y"
                   {
				OperandNode* op=new OperandNode(new Operand(new Var(VarType::tiny, *(yyvsp[0].str), 0)));		
				(yyval.st)=new Ast(op);
				//targetVec.push_back(*$1);
				//vm->pushVarToInit(*$1);
				bison_logger<<"var "<<*(yyvsp[0].str)<<"pushed to init queue."<<std::endl;
			}
#line 2442 "bison/bis.tab.c"
    break;

  case 55:
#line 782 "bison/lang.y"
                        {}
#line 2448 "bison/bis.tab.c"
    break;


#line 2452 "bison/bis.tab.c"

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
#line 785 "bison/lang.y"



void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}



