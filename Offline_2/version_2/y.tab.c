/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax_analyzer_student_version.y"

#include<bits/stdc++.h>
#include "symbol_info.h"

using namespace std;


int yyparse(void);
int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

ofstream outputlog;
int line_count = 1;

#line 87 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    INT = 262,                     /* INT  */
    FLOAT = 263,                   /* FLOAT  */
    VOID = 264,                    /* VOID  */
    RETURN = 265,                  /* RETURN  */
    PRINTLN = 266,                 /* PRINTLN  */
    ID = 267,                      /* ID  */
    CONST_INT = 268,               /* CONST_INT  */
    CONST_FLOAT = 269,             /* CONST_FLOAT  */
    ADDOP = 270,                   /* ADDOP  */
    MULOP = 271,                   /* MULOP  */
    INCOP = 272,                   /* INCOP  */
    RELOP = 273,                   /* RELOP  */
    ASSIGNOP = 274,                /* ASSIGNOP  */
    LOGICOP = 275,                 /* LOGICOP  */
    NOT = 276,                     /* NOT  */
    LPAREN = 277,                  /* LPAREN  */
    RPAREN = 278,                  /* RPAREN  */
    LCURL = 279,                   /* LCURL  */
    RCURL = 280,                   /* RCURL  */
    LTHIRD = 281,                  /* LTHIRD  */
    RTHIRD = 282,                  /* RTHIRD  */
    COMMA = 283,                   /* COMMA  */
    SEMICOLON = 284,               /* SEMICOLON  */
    LOWER_THAN_ELSE = 285          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "syntax_analyzer_student_version.y"

    SymbolInfo* sp;

#line 171 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_PRINTLN = 11,                   /* PRINTLN  */
  YYSYMBOL_ID = 12,                        /* ID  */
  YYSYMBOL_CONST_INT = 13,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 14,               /* CONST_FLOAT  */
  YYSYMBOL_ADDOP = 15,                     /* ADDOP  */
  YYSYMBOL_MULOP = 16,                     /* MULOP  */
  YYSYMBOL_INCOP = 17,                     /* INCOP  */
  YYSYMBOL_RELOP = 18,                     /* RELOP  */
  YYSYMBOL_ASSIGNOP = 19,                  /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 20,                   /* LOGICOP  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LCURL = 24,                     /* LCURL  */
  YYSYMBOL_RCURL = 25,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 26,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 27,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 29,                 /* SEMICOLON  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_start = 32,                     /* start  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_unit = 34,                      /* unit  */
  YYSYMBOL_func_definition = 35,           /* func_definition  */
  YYSYMBOL_param_list = 36,                /* param_list  */
  YYSYMBOL_compound_statement = 37,        /* compound_statement  */
  YYSYMBOL_variable_decl = 38,             /* variable_decl  */
  YYSYMBOL_type_specifier = 39,            /* type_specifier  */
  YYSYMBOL_declaration_list = 40,          /* declaration_list  */
  YYSYMBOL_statements = 41,                /* statements  */
  YYSYMBOL_statement = 42,                 /* statement  */
  YYSYMBOL_expression_statement = 43,      /* expression_statement  */
  YYSYMBOL_variable = 44,                  /* variable  */
  YYSYMBOL_expression = 45,                /* expression  */
  YYSYMBOL_logic_expression = 46,          /* logic_expression  */
  YYSYMBOL_rel_expression = 47,            /* rel_expression  */
  YYSYMBOL_simple_expression = 48,         /* simple_expression  */
  YYSYMBOL_term = 49,                      /* term  */
  YYSYMBOL_unary_expression = 50,          /* unary_expression  */
  YYSYMBOL_factor = 51,                    /* factor  */
  YYSYMBOL_argument_list = 52,             /* argument_list  */
  YYSYMBOL_arguments = 53                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    33,    33,    41,    49,    58,    65,    74,    86,    99,
     109,   118,   126,   135,   144,   154,   165,   172,   179,   188,
     197,   209,   216,   228,   235,   245,   252,   259,   266,   279,
     290,   303,   314,   325,   336,   343,   353,   360,   372,   379,
     390,   397,   408,   415,   426,   433,   444,   451,   462,   470,
     478,   489,   496,   506,   515,   522,   529,   546,   554,   561,
     570
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "INT", "FLOAT", "VOID", "RETURN", "PRINTLN", "ID", "CONST_INT",
  "CONST_FLOAT", "ADDOP", "MULOP", "INCOP", "RELOP", "ASSIGNOP", "LOGICOP",
  "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA",
  "SEMICOLON", "LOWER_THAN_ELSE", "$accept", "start", "program", "unit",
  "func_definition", "param_list", "compound_statement", "variable_decl",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-65)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,   -65,   -65,   -65,     6,    11,   -65,   -65,   -65,    20,
     -65,   -65,     9,    59,     5,    24,    29,   -65,    40,    -6,
      46,    45,    41,    68,   -65,    40,    11,   -65,   -65,    72,
      69,    73,    87,    39,    88,    12,   -65,   -65,    39,    39,
      39,   -65,   -65,   -65,   -65,    82,    93,   -65,   -65,    67,
      83,   -65,    91,    47,    97,   -65,   -65,   -65,   104,    92,
      39,    34,    39,   105,   108,    39,    39,   119,   -65,   -65,
     112,   111,   -65,   -65,   -65,    39,   -65,    39,    39,    39,
      39,   -65,   -65,   115,    34,   120,   -65,   121,   -65,   122,
     113,   123,   -65,   -65,   -65,    97,   131,   -65,   118,    39,
     118,   124,   -65,    39,   -65,   144,   126,   -65,   -65,   -65,
     118,   118,   -65,   -65
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    17,    18,     0,     2,     4,     6,     5,     0,
       1,     3,    21,     0,     0,     0,     0,    15,     0,     0,
      12,     0,    19,     0,     8,     0,     0,    11,    22,     0,
       0,     0,     0,     0,     0,    36,    54,    55,     0,     0,
       0,    14,    34,    27,    25,     0,     0,    23,    26,    51,
       0,    38,    40,    42,    44,    46,    50,     7,    10,     0,
       0,     0,     0,     0,     0,    58,     0,    51,    48,    49,
       0,    21,    13,    24,    56,     0,    35,     0,     0,     0,
       0,     9,    20,     0,     0,     0,    33,     0,    60,     0,
      57,     0,    53,    39,    41,    45,    43,    47,     0,     0,
       0,     0,    52,     0,    37,    29,     0,    31,    32,    59,
       0,     0,    30,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,   146,   -65,   -65,    -2,    21,    10,   -65,
     -65,   -41,   -59,   -35,   -33,   -64,    75,    76,    78,   -30,
     -65,   -65,   -65
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    19,    43,    44,    45,    13,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    89,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      63,    88,    84,    67,    67,    73,    10,    70,    68,    69,
       9,    93,     1,     2,     3,     9,    24,    25,     1,     2,
       3,     8,    26,    57,    20,    99,     8,    83,    18,    85,
      67,    14,    12,    91,    65,    15,    58,    21,    66,   109,
      67,    22,    67,    67,    67,    67,    35,    36,    37,    38,
      97,    35,    36,    37,    38,    39,    40,   105,    27,   107,
      39,    40,    78,    42,    23,    79,   106,    29,    67,   112,
     113,    30,    28,    31,    32,     1,     2,     3,    33,    34,
      35,    36,    37,    38,    74,    59,    75,    16,    17,    39,
      40,    60,    23,    41,    71,    61,    30,    42,    31,    32,
       1,     2,     3,    33,    34,    35,    36,    37,    38,    62,
      64,    77,    76,    80,    39,    40,    81,    23,    72,    82,
      87,    30,    42,    31,    32,     1,     2,     3,    33,    34,
      35,    36,    37,    38,    86,    92,    74,    15,    98,    39,
      40,   103,    23,   100,   101,   102,    78,    42,   110,   111,
     104,    11,    94,   108,     0,    96,    95
};

static const yytype_int8 yycheck[] =
{
      33,    65,    61,    38,    39,    46,     0,    40,    38,    39,
       0,    75,     7,     8,     9,     5,    18,    23,     7,     8,
       9,     0,    28,    25,    14,    84,     5,    60,    23,    62,
      65,    22,    12,    66,    22,    26,    26,    13,    26,   103,
      75,    12,    77,    78,    79,    80,    12,    13,    14,    15,
      80,    12,    13,    14,    15,    21,    22,    98,    12,   100,
      21,    22,    15,    29,    24,    18,    99,    26,   103,   110,
     111,     3,    27,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    17,    13,    19,    28,    29,    21,
      22,    22,    24,    25,    12,    22,     3,    29,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    22,
      22,    20,    29,    16,    21,    22,    12,    24,    25,    27,
      12,     3,    29,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    29,    23,    17,    26,    23,    21,
      22,    28,    24,    23,    23,    23,    15,    29,     4,    23,
      27,     5,    77,    29,    -1,    79,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    32,    33,    34,    35,    38,    39,
       0,    34,    12,    40,    22,    26,    28,    29,    23,    36,
      39,    13,    12,    24,    37,    23,    28,    12,    27,    26,
       3,     5,     6,    10,    11,    12,    13,    14,    15,    21,
      22,    25,    29,    37,    38,    39,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    37,    39,    13,
      22,    22,    22,    45,    22,    22,    26,    44,    50,    50,
      45,    12,    25,    42,    17,    19,    29,    20,    15,    18,
      16,    12,    27,    45,    43,    45,    29,    12,    46,    52,
      53,    45,    23,    46,    47,    49,    48,    50,    23,    43,
      23,    23,    23,    28,    27,    42,    45,    42,    29,    46,
       4,    23,    42,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    36,    36,    37,    37,    38,    39,    39,    39,    40,
      40,    40,    40,    41,    41,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    43,    43,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      50,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     6,     5,     4,
       3,     2,     1,     3,     2,     3,     1,     1,     1,     3,
       6,     1,     4,     1,     2,     1,     1,     1,     7,     5,
       7,     5,     5,     3,     1,     2,     1,     4,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     2,     2,
       1,     1,     4,     3,     1,     1,     2,     1,     0,     3,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_IF: /* IF  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1025 "y.tab.c"
        break;

    case YYSYMBOL_ELSE: /* ELSE  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1031 "y.tab.c"
        break;

    case YYSYMBOL_FOR: /* FOR  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1037 "y.tab.c"
        break;

    case YYSYMBOL_WHILE: /* WHILE  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1043 "y.tab.c"
        break;

    case YYSYMBOL_INT: /* INT  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1049 "y.tab.c"
        break;

    case YYSYMBOL_FLOAT: /* FLOAT  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1055 "y.tab.c"
        break;

    case YYSYMBOL_VOID: /* VOID  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1061 "y.tab.c"
        break;

    case YYSYMBOL_RETURN: /* RETURN  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1067 "y.tab.c"
        break;

    case YYSYMBOL_PRINTLN: /* PRINTLN  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1073 "y.tab.c"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1079 "y.tab.c"
        break;

    case YYSYMBOL_CONST_INT: /* CONST_INT  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1085 "y.tab.c"
        break;

    case YYSYMBOL_CONST_FLOAT: /* CONST_FLOAT  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1091 "y.tab.c"
        break;

    case YYSYMBOL_ADDOP: /* ADDOP  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1097 "y.tab.c"
        break;

    case YYSYMBOL_MULOP: /* MULOP  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1103 "y.tab.c"
        break;

    case YYSYMBOL_INCOP: /* INCOP  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1109 "y.tab.c"
        break;

    case YYSYMBOL_RELOP: /* RELOP  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1115 "y.tab.c"
        break;

    case YYSYMBOL_ASSIGNOP: /* ASSIGNOP  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1121 "y.tab.c"
        break;

    case YYSYMBOL_LOGICOP: /* LOGICOP  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1127 "y.tab.c"
        break;

    case YYSYMBOL_NOT: /* NOT  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1133 "y.tab.c"
        break;

    case YYSYMBOL_LPAREN: /* LPAREN  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1139 "y.tab.c"
        break;

    case YYSYMBOL_RPAREN: /* RPAREN  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1145 "y.tab.c"
        break;

    case YYSYMBOL_LCURL: /* LCURL  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1151 "y.tab.c"
        break;

    case YYSYMBOL_RCURL: /* RCURL  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1157 "y.tab.c"
        break;

    case YYSYMBOL_LTHIRD: /* LTHIRD  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1163 "y.tab.c"
        break;

    case YYSYMBOL_RTHIRD: /* RTHIRD  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1169 "y.tab.c"
        break;

    case YYSYMBOL_COMMA: /* COMMA  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1175 "y.tab.c"
        break;

    case YYSYMBOL_SEMICOLON: /* SEMICOLON  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1181 "y.tab.c"
        break;

    case YYSYMBOL_start: /* start  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1187 "y.tab.c"
        break;

    case YYSYMBOL_program: /* program  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1193 "y.tab.c"
        break;

    case YYSYMBOL_unit: /* unit  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1199 "y.tab.c"
        break;

    case YYSYMBOL_func_definition: /* func_definition  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1205 "y.tab.c"
        break;

    case YYSYMBOL_param_list: /* param_list  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1211 "y.tab.c"
        break;

    case YYSYMBOL_compound_statement: /* compound_statement  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1217 "y.tab.c"
        break;

    case YYSYMBOL_variable_decl: /* variable_decl  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1223 "y.tab.c"
        break;

    case YYSYMBOL_type_specifier: /* type_specifier  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1229 "y.tab.c"
        break;

    case YYSYMBOL_declaration_list: /* declaration_list  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1235 "y.tab.c"
        break;

    case YYSYMBOL_statements: /* statements  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1241 "y.tab.c"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1247 "y.tab.c"
        break;

    case YYSYMBOL_expression_statement: /* expression_statement  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1253 "y.tab.c"
        break;

    case YYSYMBOL_variable: /* variable  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1259 "y.tab.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1265 "y.tab.c"
        break;

    case YYSYMBOL_logic_expression: /* logic_expression  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1271 "y.tab.c"
        break;

    case YYSYMBOL_rel_expression: /* rel_expression  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1277 "y.tab.c"
        break;

    case YYSYMBOL_simple_expression: /* simple_expression  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1283 "y.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1289 "y.tab.c"
        break;

    case YYSYMBOL_unary_expression: /* unary_expression  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1295 "y.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1301 "y.tab.c"
        break;

    case YYSYMBOL_argument_list: /* argument_list  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1307 "y.tab.c"
        break;

    case YYSYMBOL_arguments: /* arguments  */
#line 28 "syntax_analyzer_student_version.y"
            { delete ((*yyvaluep).sp); }
#line 1313 "y.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 34 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" start : program "<<endl<<endl;
        delete (yyvsp[0].sp);
        (yyval.sp) = NULL;
    }
#line 1587 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 42 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" program : program unit "<<endl<<endl;
        outputlog<<(yyvsp[-1].sp)->get_name()+"\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-1].sp)->get_name()+"\n"+(yyvsp[0].sp)->get_name(),"program");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1599 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 50 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" program : unit "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"program");
        delete (yyvsp[0].sp);
    }
#line 1610 "y.tab.c"
    break;

  case 5: /* unit: variable_decl  */
#line 59 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" unit : variable_decl "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"unit");
        delete (yyvsp[0].sp);
    }
#line 1621 "y.tab.c"
    break;

  case 6: /* unit: func_definition  */
#line 66 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" unit : func_definition "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"unit");
        delete (yyvsp[0].sp);
    }
#line 1632 "y.tab.c"
    break;

  case 7: /* func_definition: type_specifier ID LPAREN param_list RPAREN compound_statement  */
#line 75 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement "<<endl<<endl;
        outputlog<<(yyvsp[-5].sp)->get_name()+" "+(yyvsp[-4].sp)->get_name()+"("+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-5].sp)->get_name()+" "+(yyvsp[-4].sp)->get_name()+"("+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name(),"func_def");
        delete (yyvsp[-5].sp);
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1648 "y.tab.c"
    break;

  case 8: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 87 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
        outputlog<<(yyvsp[-4].sp)->get_name()+" "+(yyvsp[-3].sp)->get_name()+"()\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-4].sp)->get_name()+" "+(yyvsp[-3].sp)->get_name()+"()\n"+(yyvsp[0].sp)->get_name(),"func_def");
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1663 "y.tab.c"
    break;

  case 9: /* param_list: param_list COMMA type_specifier ID  */
#line 100 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" param_list : param_list COMMA type_specifier ID "<<endl<<endl;
        outputlog<<(yyvsp[-3].sp)->get_name()+","+(yyvsp[-1].sp)->get_name()+" "+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-3].sp)->get_name()+","+(yyvsp[-1].sp)->get_name()+" "+(yyvsp[0].sp)->get_name(),"param_list");
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1677 "y.tab.c"
    break;

  case 10: /* param_list: param_list COMMA type_specifier  */
#line 110 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" param_list : param_list COMMA type_specifier "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+","+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+","+(yyvsp[0].sp)->get_name(),"param_list");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1690 "y.tab.c"
    break;

  case 11: /* param_list: type_specifier ID  */
#line 119 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" param_list : type_specifier ID "<<endl<<endl;
        outputlog<<(yyvsp[-1].sp)->get_name()+" "+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-1].sp)->get_name()+" "+(yyvsp[0].sp)->get_name(),"param_list");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1702 "y.tab.c"
    break;

  case 12: /* param_list: type_specifier  */
#line 127 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" param_list : type_specifier "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"param_list");
        delete (yyvsp[0].sp);
    }
#line 1713 "y.tab.c"
    break;

  case 13: /* compound_statement: LCURL statements RCURL  */
#line 136 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" compound_statement : LCURL statements RCURL "<<endl<<endl;
        outputlog<<"{\n"+(yyvsp[-1].sp)->get_name()+"\n}"<<endl<<endl;
        (yyval.sp) = new SymbolInfo("{\n"+(yyvsp[-1].sp)->get_name()+"\n}","compound_statement");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1726 "y.tab.c"
    break;

  case 14: /* compound_statement: LCURL RCURL  */
#line 145 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" compound_statement : LCURL RCURL "<<endl<<endl;
        outputlog<<"{\n}"<<endl<<endl;
        (yyval.sp) = new SymbolInfo("{\n}","compound_statement");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1738 "y.tab.c"
    break;

  case 15: /* variable_decl: type_specifier declaration_list SEMICOLON  */
#line 155 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" variable_decl : type_specifier declaration_list SEMICOLON "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+" "+(yyvsp[-1].sp)->get_name()+";"<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+" "+(yyvsp[-1].sp)->get_name()+";","variable_decl");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1751 "y.tab.c"
    break;

  case 16: /* type_specifier: INT  */
#line 166 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : INT "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"type_specifier");
        delete (yyvsp[0].sp);
    }
#line 1762 "y.tab.c"
    break;

  case 17: /* type_specifier: FLOAT  */
#line 173 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : FLOAT "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"type_specifier");
        delete (yyvsp[0].sp);
    }
#line 1773 "y.tab.c"
    break;

  case 18: /* type_specifier: VOID  */
#line 180 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : VOID "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"type_specifier");
        delete (yyvsp[0].sp);
    }
#line 1784 "y.tab.c"
    break;

  case 19: /* declaration_list: declaration_list COMMA ID  */
#line 189 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+","+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+","+(yyvsp[0].sp)->get_name(),"declaration_list");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1797 "y.tab.c"
    break;

  case 20: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 198 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
        outputlog<<(yyvsp[-5].sp)->get_name()+","+(yyvsp[-3].sp)->get_name()+"["+(yyvsp[-1].sp)->get_name()+"]"<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-5].sp)->get_name()+","+(yyvsp[-3].sp)->get_name()+"["+(yyvsp[-1].sp)->get_name()+"]","declaration_list");
        delete (yyvsp[-5].sp);
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1813 "y.tab.c"
    break;

  case 21: /* declaration_list: ID  */
#line 210 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : ID "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"declaration_list");
        delete (yyvsp[0].sp);
    }
#line 1824 "y.tab.c"
    break;

  case 22: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 217 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
        outputlog<<(yyvsp[-3].sp)->get_name()+"["+(yyvsp[-1].sp)->get_name()+"]"<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-3].sp)->get_name()+"["+(yyvsp[-1].sp)->get_name()+"]","declaration_list");
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1838 "y.tab.c"
    break;

  case 23: /* statements: statement  */
#line 229 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statements : statement "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"statements");
        delete (yyvsp[0].sp);
    }
#line 1849 "y.tab.c"
    break;

  case 24: /* statements: statements statement  */
#line 236 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statements : statements statement "<<endl<<endl;
        outputlog<<(yyvsp[-1].sp)->get_name()+"\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-1].sp)->get_name()+"\n"+(yyvsp[0].sp)->get_name(),"statements");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1861 "y.tab.c"
    break;

  case 25: /* statement: variable_decl  */
#line 246 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : variable_decl "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[0].sp);
    }
#line 1872 "y.tab.c"
    break;

  case 26: /* statement: expression_statement  */
#line 253 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : expression_statement "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[0].sp);
    }
#line 1883 "y.tab.c"
    break;

  case 27: /* statement: compound_statement  */
#line 260 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : compound_statement "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[0].sp);
    }
#line 1894 "y.tab.c"
    break;

  case 28: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 267 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
        outputlog<<"for("+(yyvsp[-4].sp)->get_name()+(yyvsp[-3].sp)->get_name()+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo("for("+(yyvsp[-4].sp)->get_name()+(yyvsp[-3].sp)->get_name()+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[-6].sp);
        delete (yyvsp[-5].sp);
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1911 "y.tab.c"
    break;

  case 29: /* statement: IF LPAREN expression RPAREN statement  */
#line 280 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : IF LPAREN expression RPAREN statement "<<endl<<endl;
        outputlog<<"if("+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo("if("+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1926 "y.tab.c"
    break;

  case 30: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 291 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : IF LPAREN expression RPAREN statement ELSE statement "<<endl<<endl;
        outputlog<<"if("+(yyvsp[-4].sp)->get_name()+")\n"+(yyvsp[-2].sp)->get_name()+"\nelse\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo("if("+(yyvsp[-4].sp)->get_name()+")\n"+(yyvsp[-2].sp)->get_name()+"\nelse\n"+(yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[-6].sp);
        delete (yyvsp[-5].sp);
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1943 "y.tab.c"
    break;

  case 31: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 304 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : WHILE LPAREN expression RPAREN statement "<<endl<<endl;
        outputlog<<"while("+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo("while("+(yyvsp[-2].sp)->get_name()+")\n"+(yyvsp[0].sp)->get_name(),"stmnt");
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1958 "y.tab.c"
    break;

  case 32: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 315 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON "<<endl<<endl;
        outputlog<<"printf("+(yyvsp[-2].sp)->get_name()+");"<<endl<<endl;
        (yyval.sp) = new SymbolInfo("printf("+(yyvsp[-2].sp)->get_name()+");","stmnt");
        delete (yyvsp[-4].sp);
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1973 "y.tab.c"
    break;

  case 33: /* statement: RETURN expression SEMICOLON  */
#line 326 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" statement : RETURN expression SEMICOLON "<<endl<<endl;
        outputlog<<"return "+(yyvsp[-1].sp)->get_name()+";"<<endl<<endl;
        (yyval.sp) = new SymbolInfo("return "+(yyvsp[-1].sp)->get_name()+";","stmnt");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 1986 "y.tab.c"
    break;

  case 34: /* expression_statement: SEMICOLON  */
#line 337 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" expression_statement : SEMICOLON "<<endl<<endl;
        outputlog<<";"<<endl<<endl;
        (yyval.sp) = new SymbolInfo(";","expression_statement");
        delete (yyvsp[0].sp);
    }
#line 1997 "y.tab.c"
    break;

  case 35: /* expression_statement: expression SEMICOLON  */
#line 344 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" expression_statement : expression SEMICOLON "<<endl<<endl;
        outputlog<<(yyvsp[-1].sp)->get_name()+";"<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-1].sp)->get_name()+";","expression_statement");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2009 "y.tab.c"
    break;

  case 36: /* variable: ID  */
#line 354 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" variable : ID "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"variable");
        delete (yyvsp[0].sp);
    }
#line 2020 "y.tab.c"
    break;

  case 37: /* variable: ID LTHIRD expression RTHIRD  */
#line 361 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
        outputlog<<(yyvsp[-3].sp)->get_name()+"["+(yyvsp[-1].sp)->get_name()+"]"<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-3].sp)->get_name()+"["+(yyvsp[-1].sp)->get_name()+"]","variable");
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2034 "y.tab.c"
    break;

  case 38: /* expression: logic_expression  */
#line 373 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" expression : logic_expression "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"expression");
        delete (yyvsp[0].sp);
    }
#line 2045 "y.tab.c"
    break;

  case 39: /* expression: variable ASSIGNOP logic_expression  */
#line 380 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+"="+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+"="+(yyvsp[0].sp)->get_name(),"expression");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2058 "y.tab.c"
    break;

  case 40: /* logic_expression: rel_expression  */
#line 391 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" logic_expression : rel_expression "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"logic_expression");
        delete (yyvsp[0].sp);
    }
#line 2069 "y.tab.c"
    break;

  case 41: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 398 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name(),"logic_expression");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2082 "y.tab.c"
    break;

  case 42: /* rel_expression: simple_expression  */
#line 409 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" rel_expression : simple_expression "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"rel_expression");
        delete (yyvsp[0].sp);
    }
#line 2093 "y.tab.c"
    break;

  case 43: /* rel_expression: simple_expression RELOP simple_expression  */
#line 416 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name(),"rel_expression");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2106 "y.tab.c"
    break;

  case 44: /* simple_expression: term  */
#line 427 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" simple_expression : term "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"simple_expression");
        delete (yyvsp[0].sp);
    }
#line 2117 "y.tab.c"
    break;

  case 45: /* simple_expression: simple_expression ADDOP term  */
#line 434 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name(),"simple_expression");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2130 "y.tab.c"
    break;

  case 46: /* term: unary_expression  */
#line 445 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" term : unary_expression "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"term");
        delete (yyvsp[0].sp);
    }
#line 2141 "y.tab.c"
    break;

  case 47: /* term: term MULOP unary_expression  */
#line 452 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" term : term MULOP unary_expression "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name(),"term");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2154 "y.tab.c"
    break;

  case 48: /* unary_expression: ADDOP unary_expression  */
#line 463 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
        outputlog<<(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name(),"unary_expression");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2166 "y.tab.c"
    break;

  case 49: /* unary_expression: NOT unary_expression  */
#line 471 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" unary_expression : NOT unary_expression "<<endl<<endl;
        outputlog<<"!"+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo("!"+(yyvsp[0].sp)->get_name(),"unary_expression");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2178 "y.tab.c"
    break;

  case 50: /* unary_expression: factor  */
#line 479 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" factor_info : factor "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        outputlog<<"At line no: "<<line_count<<" unary_expression : factor "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"unary_expression");
        delete (yyvsp[0].sp);
    }
#line 2191 "y.tab.c"
    break;

  case 51: /* factor: variable  */
#line 490 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" factor : variable "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"factor");
        delete (yyvsp[0].sp);
    }
#line 2202 "y.tab.c"
    break;

  case 52: /* factor: ID LPAREN argument_list RPAREN  */
#line 497 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
        outputlog<<(yyvsp[-3].sp)->get_name()+"("+(yyvsp[-1].sp)->get_name()+")"<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-3].sp)->get_name()+"("+(yyvsp[-1].sp)->get_name()+")","factor");
        delete (yyvsp[-3].sp);
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2216 "y.tab.c"
    break;

  case 53: /* factor: LPAREN expression RPAREN  */
#line 507 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" factor : LPAREN expression RPAREN "<<endl<<endl;
        outputlog<<"("+(yyvsp[-1].sp)->get_name()+")"<<endl<<endl;
        (yyval.sp) = new SymbolInfo("("+(yyvsp[-1].sp)->get_name()+")","factor");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2229 "y.tab.c"
    break;

  case 54: /* factor: CONST_INT  */
#line 516 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" factor : CONST_INT "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"factor");
        delete (yyvsp[0].sp);
    }
#line 2240 "y.tab.c"
    break;

  case 55: /* factor: CONST_FLOAT  */
#line 523 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" factor : CONST_FLOAT "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"factor");
        delete (yyvsp[0].sp);
    }
#line 2251 "y.tab.c"
    break;

  case 56: /* factor: variable INCOP  */
#line 530 "syntax_analyzer_student_version.y"
    {
        if((yyvsp[0].sp)->get_name() == "--")
        {
            outputlog<<"At line no: "<<line_count<<" factor : variable DECOP "<<endl<<endl;
        }
        else
        {
            outputlog<<"At line no: "<<line_count<<" factor : variable INCOP "<<endl<<endl;
        }
        outputlog<<(yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-1].sp)->get_name()+(yyvsp[0].sp)->get_name(),"factor");
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2270 "y.tab.c"
    break;

  case 57: /* argument_list: arguments  */
#line 547 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" argument_list : arguments "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"argument_list");
        delete (yyvsp[0].sp);
    }
#line 2281 "y.tab.c"
    break;

  case 58: /* argument_list: %empty  */
#line 554 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" argument_list :  "<<endl<<endl;
        outputlog<<""<<endl<<endl;
        (yyval.sp) = new SymbolInfo("","argument_list");
    }
#line 2291 "y.tab.c"
    break;

  case 59: /* arguments: arguments COMMA logic_expression  */
#line 562 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
        outputlog<<(yyvsp[-2].sp)->get_name()+","+(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[-2].sp)->get_name()+","+(yyvsp[0].sp)->get_name(),"arguments");
        delete (yyvsp[-2].sp);
        delete (yyvsp[-1].sp);
        delete (yyvsp[0].sp);
    }
#line 2304 "y.tab.c"
    break;

  case 60: /* arguments: logic_expression  */
#line 571 "syntax_analyzer_student_version.y"
    {
        outputlog<<"At line no: "<<line_count<<" arguments : logic_expression "<<endl<<endl;
        outputlog<<(yyvsp[0].sp)->get_name()<<endl<<endl;
        (yyval.sp) = new SymbolInfo((yyvsp[0].sp)->get_name(),"arguments");
        delete (yyvsp[0].sp);
    }
#line 2315 "y.tab.c"
    break;


#line 2319 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 579 "syntax_analyzer_student_version.y"


void yyerror(const char *s)
{
    outputlog<<"Error at line no: "<<line_count<<": "<<s<<endl<<endl;
}

int main(int c, char *v[])
{
    if(c != 2)
    {
        cout<<"Please provide input file name"<<endl;
        return 1;
    }
    yyin = fopen(v[1], "r");
    if(yyin == NULL)
    {
        cout<<"Couldn't open file"<<endl;
        return 1;
    }
    outputlog.open("my_log.txt", ios::trunc);
    if(!outputlog)
    {
        cout<<"Couldn't open log file"<<endl;
        fclose(yyin);
        return 1;
    }
    int result = yyparse();
    outputlog<<endl<<"Total lines: "<<line_count<<endl;
    outputlog.close();
    fclose(yyin);
    return result;
}
