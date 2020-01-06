/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "opl.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

extern int yylex();
extern int yyerror(char * syntaxError);

VariableTable listOfVariables;
FunctionTable listOfFunctions;
ClassTable listOfClasses;
ArrayEval listOfEval;

struct Variable v;
struct Function fun;
struct Class cl;
struct EvalExpr expr;

int noSyntacticErrors = 0;
int noSemanticErrors = 1;
int isFunction = 0;
int arithmeticExprType = -2;
int returnType;

void update_scope();

//3.1
void variable_previously_defined(char* id);
void class_variable_previously_defined(char* className, char* id);

//3.2
void variable_was_declared(char* id);
void class_variable_was_declared(VariableTable arr, char* id);

//3.3
int variable_is_init(VariableTable arr, char* id);
int class_variable_is_init(ClassTable arr, char* className, char* id);
void set_init_variable(VariableTable* arr, char* id);
void set_init_class_variable(ClassTable* arr, char* className, char* id);
void check_variable_is_init(VariableTable arr, char* id);
void check_class_variable_is_init(ClassTable arr, char* className, char* id);

//3.4
int compare_params(struct Variable v1, struct Variable v2);
void function_was_declared(FunctionTable arr, struct Function fun);
void method_was_declared(FunctionTable arr, struct Function fun);

//3.5
void function_previously_defined(char* id);
void method_previously_defined(char* className, char* id);

//3.6
int leftType, rightType, valueType;
int type_of_variable(VariableTable arr, char* id);
int type_of_class_variable(ClassTable arr, char* className, char* id);
int type_of_return_function(FunctionTable arr, char* id);
int type_of_return_method(ClassTable arr, char* className, char* id);
void different_types();

//3.7
int variable_is_array(VariableTable arr, char* id);
int class_variable_is_array(ClassTable arr, char* className, char* id);
void check_function_signature(FunctionTable arr, struct Function fun);
void check_method_signature(ClassTable arr, char* className, struct Function fun);

//3.8
expr_info* create_int_expr(int value);
expr_info* create_str_expr(char* value1, char* value2);
void free_expr(expr_info* expr);
void print_expr(expr_info* expr);

//extra
void check_scope(VariableTable arr, char* id, char* currentScope);
void check_array_length(int len);
int variable_is_const(VariableTable arr, char* id);
int class_variable_is_const(ClassTable arr, char* className, char* id);
void check_variable_is_const(VariableTable arr, char* id);
void check_class_variable_is_const(ClassTable arr, char* className, char* id);


#line 149 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    STRING = 261,
    BOOL = 262,
    CONST = 263,
    BEGIN_DECL = 264,
    END_DECL = 265,
    BEGIN_MAIN = 266,
    END_MAIN = 267,
    ID = 268,
    INTEGER_NUMBER = 269,
    FLOAT_NUMBER = 270,
    STRING_VALUE = 271,
    BOOL_VALUE = 272,
    CHAR_VALUE = 273,
    FNC = 274,
    CALL = 275,
    CLASS = 276,
    MTH = 277,
    IF = 278,
    THEN = 279,
    ELSE = 280,
    WHILE = 281,
    DO = 282,
    FOR = 283,
    LE = 284,
    GE = 285,
    EQ = 286,
    NE = 287,
    OR = 288,
    AND = 289,
    RET = 290,
    EVAL = 291,
    CONCAT = 292,
    LENGTH = 293,
    COMPARE = 294,
    LOWER = 295,
    UPPER = 296
  };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define CHAR 260
#define STRING 261
#define BOOL 262
#define CONST 263
#define BEGIN_DECL 264
#define END_DECL 265
#define BEGIN_MAIN 266
#define END_MAIN 267
#define ID 268
#define INTEGER_NUMBER 269
#define FLOAT_NUMBER 270
#define STRING_VALUE 271
#define BOOL_VALUE 272
#define CHAR_VALUE 273
#define FNC 274
#define CALL 275
#define CLASS 276
#define MTH 277
#define IF 278
#define THEN 279
#define ELSE 280
#define WHILE 281
#define DO 282
#define FOR 283
#define LE 284
#define GE 285
#define EQ 286
#define NE 287
#define OR 288
#define AND 289
#define RET 290
#define EVAL 291
#define CONCAT 292
#define LENGTH 293
#define COMPARE 294
#define LOWER 295
#define UPPER 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 85 "opl.y" /* yacc.c:355  */

    int intval;
    char* strval;
    struct expr_info* expr_ptr;

#line 277 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 294 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   501

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  367

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,     2,     2,     2,
      57,    58,    47,    45,    51,    46,    59,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    50,
      43,    42,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   123,   124,   125,   128,   128,   131,   132,
     135,   136,   137,   140,   143,   143,   144,   147,   160,   173,
     189,   204,   214,   226,   229,   230,   233,   234,   235,   236,
     237,   240,   241,   242,   243,   244,   247,   248,   251,   259,
     272,   273,   272,   284,   285,   288,   288,   289,   292,   297,
     307,   314,   321,   331,   330,   348,   349,   352,   353,   356,
     359,   359,   360,   363,   376,   389,   404,   414,   426,   426,
     426,   436,   437,   440,   441,   441,   444,   445,   453,   466,
     466,   469,   470,   473,   474,   478,   479,   480,   481,   482,
     485,   500,   514,   528,   541,   553,   564,   577,   589,   602,
     614,   630,   645,   660,   674,   691,   707,   723,   740,   740,
     756,   756,   771,   771,   787,   787,   804,   805,   808,   809,
     809,   812,   817,   825,   834,   835,   838,   853,   872,   890,
     907,   908,   909,   910,   913,   913,   913,   916,   916,   917,
     920,   921,   922,   923,   924,   925,   926,   927,   928,   929,
     930,   931,   932,   935,   936,   937,   940,   940,   943,   943,
     946,   947,   950,   953,   962,   968,   974,   980,   986,   988,
    1000,  1012,  1024,  1035,  1046,  1059,  1060,  1061,  1064,  1067,
    1078,  1088
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "CHAR", "STRING", "BOOL",
  "CONST", "BEGIN_DECL", "END_DECL", "BEGIN_MAIN", "END_MAIN", "ID",
  "INTEGER_NUMBER", "FLOAT_NUMBER", "STRING_VALUE", "BOOL_VALUE",
  "CHAR_VALUE", "FNC", "CALL", "CLASS", "MTH", "IF", "THEN", "ELSE",
  "WHILE", "DO", "FOR", "LE", "GE", "EQ", "NE", "OR", "AND", "RET", "EVAL",
  "CONCAT", "LENGTH", "COMPARE", "LOWER", "UPPER", "'='", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'!'", "';'", "','", "'['", "']'", "'{'",
  "'}'", "':'", "'('", "')'", "'.'", "$accept", "s", "progr",
  "declarations", "$@1", "declarations_content", "decl", "variable_decl",
  "variable_list", "$@2", "var", "type", "subtype", "maintype", "value",
  "array", "array_element", "function_decl", "$@3", "$@4",
  "function_param", "list_of_param", "$@5", "variable", "class_decl",
  "$@6", "class_content", "decl_in_class", "variable_decl_in_class",
  "class_variable_list", "$@7", "class_variable", "method_decl_in_class",
  "$@8", "$@9", "method_param", "list_of_method_param", "$@10",
  "return_value", "main", "$@11", "main_content", "statement", "assign",
  "call", "$@12", "$@13", "$@14", "$@15", "call_param", "list_call_param",
  "$@16", "param", "arithmetic_expression", "operand", "operator",
  "if_statement", "$@17", "$@18", "else_statement", "$@19", "condition",
  "code_block", "while_statement", "$@20", "for_statement", "$@21",
  "for_initialization", "eval_statement", "eval_expression", "eval_result",
  "string_statement", "string_function", "strings_content",
  "string_content", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    61,    60,    62,    43,    45,    42,    47,    33,
      59,    44,    91,    93,   123,   125,    58,    40,    41,    46
};
# endif

#define YYPACT_NINF -286

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-286)))

#define YYTABLE_NINF -159

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     133,  -286,  -286,    35,  -286,    30,  -286,    40,    11,  -286,
    -286,  -286,  -286,    81,    96,   141,    82,   145,   359,  -286,
    -286,    55,    38,    38,    12,   149,   105,   114,   115,  -286,
    -286,  -286,   143,   130,   135,   178,  -286,  -286,  -286,  -286,
     -23,  -286,   151,  -286,  -286,  -286,  -286,  -286,  -286,   159,
     169,   189,   174,  -286,  -286,  -286,  -286,  -286,   205,    44,
    -286,   327,   281,   299,   230,  -286,  -286,  -286,  -286,   190,
    -286,  -286,   199,   202,   277,   232,   214,    65,   240,   212,
     216,   219,   220,   221,   205,    87,  -286,  -286,   218,   -22,
     275,    -2,   241,  -286,  -286,  -286,  -286,    59,  -286,    38,
      38,    38,    38,    38,    38,    38,    38,  -286,  -286,   242,
     332,    19,   285,     9,  -286,  -286,   249,   145,   291,   247,
      54,    54,    54,    54,    54,   251,   265,   197,   308,   336,
     307,   328,   340,   317,  -286,  -286,   327,   286,  -286,  -286,
    -286,  -286,   138,   138,  -286,  -286,   335,  -286,   230,   230,
     230,   230,    75,  -286,  -286,   341,  -286,  -286,   377,   338,
       9,   342,  -286,   352,  -286,   191,   382,   339,   344,  -286,
     346,   347,   348,   349,   350,   351,  -286,   303,   181,   384,
     345,   354,   192,  -286,  -286,   357,   358,   386,    85,    85,
      91,    91,  -286,  -286,    86,   388,    38,   355,   178,    16,
    -286,   363,  -286,  -286,  -286,   360,  -286,   321,   392,  -286,
      54,  -286,  -286,  -286,  -286,   -31,  -286,   402,   361,    54,
      54,   374,   397,  -286,   368,    10,   364,   366,    78,   253,
       4,   409,   353,   410,   372,   139,   369,   370,  -286,   367,
    -286,   376,  -286,  -286,   414,   417,   193,   418,   375,   378,
     379,   331,    10,  -286,  -286,  -286,   175,   420,   421,   380,
    -286,   381,  -286,  -286,   387,   377,  -286,  -286,  -286,   389,
     390,   321,   422,  -286,   391,   393,   395,  -286,   321,  -286,
    -286,    60,  -286,  -286,   423,   385,    84,   396,   394,   398,
     407,  -286,  -286,   337,   399,  -286,   321,  -286,   437,   401,
     403,   438,   440,  -286,  -286,   400,   353,   442,   244,   178,
       5,   405,  -286,  -286,  -286,   411,   321,  -286,   412,   408,
     413,    85,  -286,   415,   427,  -286,   377,   416,  -286,   211,
    -286,   419,  -286,   449,    85,   424,   428,   343,   425,   429,
     430,  -286,   426,  -286,   432,   431,  -286,   433,  -286,  -286,
     434,   439,   244,  -286,  -286,  -286,   246,  -286,   178,   427,
    -286,   436,  -286,   443,  -286,   441,  -286
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     6,    79,     0,     2,     0,     4,    24,   158,     1,
       3,    25,    40,     0,     0,    24,     0,     0,     0,    11,
      12,     0,     0,     0,     0,     0,    81,     0,     0,    85,
      86,    87,     0,     0,     0,    24,    53,     7,     9,    10,
      17,    13,    14,    26,    27,    28,    29,    30,    23,     0,
       0,     0,   150,    31,    32,    34,    35,    33,     0,   149,
     152,     0,     0,     0,     0,    80,    82,    83,    84,     0,
      88,    89,     0,     0,     0,     0,     0,   127,     0,     0,
       0,     0,     0,     0,     0,   126,    96,   169,     0,     0,
       0,     0,     0,   130,   131,   132,   133,     0,   134,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   168,     0,
     163,    24,     0,    24,    19,    18,     0,     0,     0,   108,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   151,
       0,     0,   148,   127,   126,   125,   124,     0,   142,   143,
     144,   145,   146,   147,   140,   141,     0,   162,     0,     0,
       0,     0,     0,   161,   160,     0,    41,    68,     0,     0,
      24,     0,    58,    20,    15,   128,     0,     0,   179,   181,
       0,     0,     0,     0,     0,     0,   129,     0,   127,     0,
       0,     0,   126,    97,   172,     0,     0,     0,    24,    24,
     164,   165,   166,   167,     0,     0,     0,     0,    24,    63,
      59,    60,    54,    55,    57,     0,   112,   116,     0,   175,
       0,   170,   171,   176,   177,   100,    98,     0,   110,     0,
       0,     0,     0,   128,     0,    24,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,     0,   122,   121,     0,
     117,   118,   180,   178,     0,     0,   128,     0,     0,     0,
       0,     0,    24,   154,   135,   157,     0,     0,     0,     0,
      44,    45,    69,    64,     0,     0,    39,    21,    38,     0,
      36,   116,     0,   109,     0,     0,   102,   114,   116,   173,
     174,   101,    99,   155,   139,     0,    48,     0,     0,     0,
      65,    61,    22,     0,     0,   123,     0,   104,     0,     0,
       0,     0,     0,   137,   136,     0,     0,     0,    24,    24,
      24,     0,    37,   113,   120,     0,   116,   111,     0,   103,
       0,    24,    49,     0,     0,    46,     0,     0,    72,     0,
     105,     0,   106,     0,    24,     0,    50,    76,     0,    73,
       0,    66,     0,   115,     0,     0,   159,     0,    78,    77,
       0,     0,    24,    67,   107,   138,     0,    42,    24,     0,
      51,     0,    75,     0,    52,     0,    70
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -286,  -286,  -286,  -286,  -286,   451,  -286,    -1,   356,  -286,
    -286,   -35,  -286,  -286,   -48,  -285,  -286,  -286,  -286,  -286,
    -286,   160,  -286,  -286,  -286,  -286,   311,  -286,  -286,   207,
    -286,   150,  -286,  -286,  -286,  -286,   120,  -286,   123,   478,
    -286,   462,    17,  -107,   -42,  -286,  -286,  -286,  -286,  -256,
     196,  -286,  -286,   -47,   404,  -286,  -286,  -286,  -286,  -286,
    -286,   -18,  -186,  -286,  -286,  -286,  -286,  -286,  -286,  -286,
      56,  -286,   371,  -111,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     7,    14,    15,   224,    41,    76,
      42,    17,    18,    48,    59,   269,   270,    19,    35,   197,
     259,   260,   288,   261,    20,    73,   159,   160,   161,   200,
     234,   201,   162,   198,   289,   327,   328,   351,   338,     6,
       8,    25,   225,    27,    28,   167,   248,   236,   299,   239,
     240,   274,   241,    60,    61,    97,    29,   137,   284,   304,
     320,    62,   226,    30,   146,    31,    32,   155,    33,   109,
     110,    34,    87,   170,   171
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    85,    86,   227,   154,    63,    16,   172,   312,   174,
     175,   173,    11,    11,    16,   294,    92,    11,    11,    74,
     127,   244,   300,    21,    21,    26,   115,    11,   245,    75,
     128,   157,   152,    22,    22,     9,    23,    23,  -158,   253,
     130,     2,   125,    26,   342,  -153,    24,    24,    11,   134,
     135,    52,    53,    54,    55,    56,    57,   131,   232,    12,
     331,    13,   -43,   -71,   -56,  -153,   283,   168,   233,    64,
     169,   361,   133,    53,    54,    55,    56,    57,   158,   182,
     183,   138,   139,   140,   141,   142,   143,   144,   145,  -126,
    -126,  -126,  -126,    11,    36,    58,   243,    49,    21,    77,
      53,    54,    55,    56,    57,   249,    37,    50,    22,   250,
     153,    23,   301,  -158,    51,   -90,    84,   194,    21,   302,
     256,    24,   324,   -90,   118,   158,   306,    50,    22,   216,
     128,    23,    39,  -158,   195,   335,   307,   -94,   150,   151,
    -153,    24,     1,    84,     2,   -94,    85,    86,   345,    11,
     285,    -8,   266,    53,    54,    55,    56,    57,    40,   238,
      12,    65,    13,   231,    67,    68,   359,    99,   100,   101,
     102,    69,    77,    53,    54,    55,    56,    57,   229,    78,
      70,   105,   106,    88,   263,    71,    11,   268,   178,    53,
      54,    55,    56,    57,   267,   258,    79,    80,    81,    82,
      83,   -16,    89,   282,   190,   191,   192,   193,   182,   183,
     178,    53,    54,    55,    56,    57,    84,   179,    91,  -127,
    -127,  -127,  -127,   238,   266,    53,    54,    55,    56,    57,
     238,   -91,    84,    90,    79,   180,   181,    82,    83,   -91,
     217,   -92,   -95,   -93,   108,   268,   116,   111,   238,   -92,
     -95,   -93,    11,   119,    84,   112,   113,    21,   322,   266,
      53,    54,    55,    56,    57,   117,   341,    22,   238,   120,
      23,   126,  -158,   121,   258,   326,   122,   123,   124,  -153,
      24,   268,    99,   100,   101,   102,   103,   104,   129,   349,
     114,    53,    54,    55,    56,    57,   105,   106,   156,   132,
     147,   360,   163,   257,   165,    98,   166,   177,   268,   176,
      99,   100,   101,   102,   103,   104,   215,    53,    54,    55,
      56,    57,   185,   326,   105,   106,   107,    78,    99,   100,
     101,   102,   103,   104,   237,    53,    54,    55,    56,    57,
     188,   186,   105,   106,   281,    53,    54,    55,    56,    57,
     266,    53,    54,    55,    56,    57,   348,    53,    54,    55,
      56,    57,    43,    44,    45,    46,    47,    53,    54,    55,
      56,    57,    93,    94,    95,    96,   187,   148,   149,   150,
     151,  -128,  -128,  -128,  -128,  -129,  -129,  -129,  -129,   189,
     199,   196,   204,   202,   205,   206,   207,   218,   210,   223,
     222,   228,   219,   208,   209,   242,   211,   212,   213,   214,
     221,   220,   230,   -62,   235,   246,   251,   179,   252,   254,
     247,   255,   262,   265,   264,   273,   271,  -119,   275,   272,
     276,   277,   278,   152,   286,   295,   279,   280,   287,   -47,
     290,   293,   296,   305,   292,   309,   297,   298,   303,   311,
     308,   315,   318,   319,   321,   310,   323,   313,   316,   329,
     333,   317,   337,   344,   330,   332,    38,   334,   336,   325,
     347,   203,   291,   164,   340,   350,   339,   343,   362,   346,
     -74,   353,   363,    10,   352,   354,   355,   356,    66,   357,
     358,   364,   314,   365,     0,     0,   366,     0,   184,     0,
       0,   136
};

static const yytype_int16 yycheck[] =
{
      35,    49,    49,   189,   111,    23,     7,   121,   293,   123,
     124,   122,     8,     8,    15,   271,    58,     8,     8,    42,
      42,    52,   278,    13,    13,     8,    74,     8,    59,    52,
      52,    22,    13,    23,    23,     0,    26,    26,    28,   225,
      42,    11,    84,    26,   329,    35,    36,    36,     8,    97,
      97,    13,    14,    15,    16,    17,    18,    59,    42,    19,
     316,    21,    58,    58,    55,    55,   252,    13,    52,    57,
      16,   356,    13,    14,    15,    16,    17,    18,   113,   127,
     127,    99,   100,   101,   102,   103,   104,   105,   106,    45,
      46,    47,    48,     8,    13,    57,   210,    42,    13,    13,
      14,    15,    16,    17,    18,   219,    10,    52,    23,   220,
     111,    26,    52,    28,    59,    50,    57,    42,    13,    59,
      42,    36,   308,    58,    59,   160,    42,    52,    23,   177,
      52,    26,    50,    28,    59,   321,    52,    50,    47,    48,
      55,    36,     9,    57,    11,    58,   194,   194,   334,     8,
     257,    10,    13,    14,    15,    16,    17,    18,    13,   207,
      19,    12,    21,   198,    50,    50,   352,    29,    30,    31,
      32,    28,    13,    14,    15,    16,    17,    18,   196,    20,
      50,    43,    44,    14,   232,    50,     8,   235,    13,    14,
      15,    16,    17,    18,    55,   230,    37,    38,    39,    40,
      41,    50,    13,   251,   148,   149,   150,   151,   256,   256,
      13,    14,    15,    16,    17,    18,    57,    20,    13,    45,
      46,    47,    48,   271,    13,    14,    15,    16,    17,    18,
     278,    50,    57,    59,    37,    38,    39,    40,    41,    58,
      59,    50,    50,    50,    14,   293,    14,    57,   296,    58,
      58,    58,     8,    13,    57,    56,    54,    13,   306,    13,
      14,    15,    16,    17,    18,    51,    55,    23,   316,    57,
      26,    53,    28,    57,   309,   310,    57,    57,    57,    35,
      36,   329,    29,    30,    31,    32,    33,    34,    13,   337,
      13,    14,    15,    16,    17,    18,    43,    44,    13,    58,
      58,    55,    53,    50,    13,    24,    59,    42,   356,    58,
      29,    30,    31,    32,    33,    34,    13,    14,    15,    16,
      17,    18,    14,   358,    43,    44,    27,    20,    29,    30,
      31,    32,    33,    34,    13,    14,    15,    16,    17,    18,
      54,    13,    43,    44,    13,    14,    15,    16,    17,    18,
      13,    14,    15,    16,    17,    18,    13,    14,    15,    16,
      17,    18,     3,     4,     5,     6,     7,    14,    15,    16,
      17,    18,    45,    46,    47,    48,    59,    45,    46,    47,
      48,    45,    46,    47,    48,    45,    46,    47,    48,    54,
      13,    50,    50,    55,    42,    13,    57,    13,    51,    13,
      42,    13,    57,    59,    58,    13,    58,    58,    58,    58,
      53,    57,    57,    50,    54,    13,    42,    20,    50,    55,
      59,    55,    13,    51,    14,    58,    57,    51,    14,    59,
      13,    13,    57,    13,    13,    13,    58,    58,    58,    58,
      53,    51,    51,    58,    55,    51,    53,    52,    25,    42,
      54,    14,    14,    13,    54,    57,    14,    58,    57,    54,
      52,    58,    35,    14,    53,    53,    15,    54,    53,   309,
      42,   160,   265,   117,    58,    50,   326,    58,   358,    55,
      51,    55,   359,     5,    54,    53,    55,    54,    26,    55,
      51,    55,   296,    50,    -1,    -1,    55,    -1,   127,    -1,
      -1,    97
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    61,    62,    63,    99,    64,   100,     0,
      99,     8,    19,    21,    65,    66,    67,    71,    72,    77,
      84,    13,    23,    26,    36,   101,   102,   103,   104,   116,
     123,   125,   126,   128,   131,    78,    13,    10,    65,    50,
      13,    68,    70,     3,     4,     5,     6,     7,    73,    42,
      52,    59,    13,    14,    15,    16,    17,    18,    57,    74,
     113,   114,   121,   121,    57,    12,   101,    50,    50,    28,
      50,    50,    71,    85,    42,    52,    69,    13,    20,    37,
      38,    39,    40,    41,    57,    74,   113,   132,    14,    13,
      59,    13,   104,    45,    46,    47,    48,   115,    24,    29,
      30,    31,    32,    33,    34,    43,    44,    27,    14,   129,
     130,    57,    56,    54,    13,    74,    14,    51,    59,    13,
      57,    57,    57,    57,    57,   104,    53,    42,    52,    13,
      42,    59,    58,    13,    74,   113,   114,   117,   121,   121,
     121,   121,   121,   121,   121,   121,   124,    58,    45,    46,
      47,    48,    13,    67,   103,   127,    13,    22,    71,    86,
      87,    88,    92,    53,    68,    13,    59,   105,    13,    16,
     133,   134,   134,   133,   134,   134,    58,    42,    13,    20,
      38,    39,    74,   113,   132,    14,    13,    59,    54,    54,
     130,   130,   130,   130,    42,    59,    50,    79,    93,    13,
      89,    91,    55,    86,    50,    42,    13,    57,    59,    58,
      51,    58,    58,    58,    58,    13,    74,    59,    13,    57,
      57,    53,    42,    13,    67,   102,   122,   122,    13,   121,
      57,    71,    42,    52,    90,    54,   107,    13,    74,   109,
     110,   112,    13,   134,    52,    59,    13,    59,   106,   134,
     133,    42,    50,   122,    55,    55,    42,    50,    71,    80,
      81,    83,    13,    74,    14,    51,    13,    55,    74,    75,
      76,    57,    59,    58,   111,    14,    13,    13,    57,    58,
      58,    13,    74,   122,   118,   103,    13,    58,    82,    94,
      53,    89,    55,    51,   109,    13,    51,    53,    52,   108,
     109,    52,    59,    25,   119,    58,    42,    52,    54,    51,
      57,    42,    75,    58,   110,    14,    57,    58,    14,    13,
     120,    54,    74,    14,   122,    81,    71,    95,    96,    54,
      53,   109,    53,    52,    54,   122,    53,    35,    98,    91,
      58,    55,    75,    58,    14,   122,    55,    42,    13,    74,
      50,    97,    54,    55,    53,    55,    54,    55,    51,   122,
      55,    75,    96,    98,    55,    50,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    62,    62,    62,    64,    63,    65,    65,
      66,    66,    66,    67,    69,    68,    68,    70,    70,    70,
      70,    70,    70,    71,    72,    72,    73,    73,    73,    73,
      73,    74,    74,    74,    74,    74,    75,    75,    76,    76,
      78,    79,    77,    80,    80,    82,    81,    81,    83,    83,
      83,    83,    83,    85,    84,    86,    86,    87,    87,    88,
      90,    89,    89,    91,    91,    91,    91,    91,    93,    94,
      92,    95,    95,    96,    97,    96,    98,    98,    98,   100,
      99,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   105,   104,
     106,   104,   107,   104,   108,   104,   109,   109,   110,   111,
     110,   112,   112,   112,   113,   113,   114,   114,   114,   114,
     115,   115,   115,   115,   117,   118,   116,   120,   119,   119,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   122,   122,   124,   123,   126,   125,
     127,   127,   128,   129,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   133,   134,
     134,   134
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     0,     4,     1,     2,
       2,     1,     1,     2,     0,     4,     1,     1,     3,     3,
       4,     7,     8,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       0,     0,    14,     0,     1,     0,     4,     1,     2,     4,
       5,     8,     9,     0,     6,     2,     0,     2,     1,     2,
       0,     4,     1,     1,     3,     4,     7,     8,     0,     0,
      13,     0,     1,     2,     0,     5,     1,     2,     2,     0,
       4,     1,     2,     2,     2,     1,     1,     1,     2,     2,
       3,     5,     5,     7,     3,     5,     3,     5,     6,     8,
       6,     8,     8,    10,     9,    11,    11,    13,     0,     8,
       0,    10,     0,    10,     0,    12,     0,     1,     1,     0,
       4,     1,     1,     3,     3,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     0,     0,     9,     0,     5,     0,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     0,     2,     3,     0,     7,     0,    12,
       1,     1,     4,     1,     3,     3,     3,     3,     1,     3,
       6,     6,     5,     8,     8,     4,     4,     4,     3,     1,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 120 "opl.y" /* yacc.c:1646  */
    {printf("No syntactic errors\n"); noSyntacticErrors = 1;}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 128 "opl.y" /* yacc.c:1646  */
    {strcpy(v.scope, "#\0");}
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 143 "opl.y" /* yacc.c:1646  */
    {insert_variable(&listOfVariables, v);}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 144 "opl.y" /* yacc.c:1646  */
    {insert_variable(&listOfVariables, v);}
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 148 "opl.y" /* yacc.c:1646  */
    {
        variable_was_declared((yyvsp[0].strval));
        if (v.t.isConst == 1)
        {
            printf("Const variable %s (line: %d) must be initialized\n", (yyvsp[0].strval), yylineno);
            noSemanticErrors = 0;
        }
        v.t.isInit = 0;
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, (yyvsp[0].strval));
    }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 161 "opl.y" /* yacc.c:1646  */
    {
        variable_was_declared((yyvsp[-2].strval));
        leftType = v.t.mainType;
        if (leftType != valueType)
        {
            different_types();
        }
        v.t.isInit = 1;
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, (yyvsp[-2].strval));
    }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 174 "opl.y" /* yacc.c:1646  */
    {
        variable_was_declared((yyvsp[-2].strval));
        variable_previously_defined((yyvsp[0].strval));
        check_variable_is_init(listOfVariables, (yyvsp[0].strval));
        leftType = v.t.mainType;
        if (leftType != type_of_variable(listOfVariables, (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
        v.t.isInit = 1;
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, (yyvsp[-2].strval));
    }
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 190 "opl.y" /* yacc.c:1646  */
    {
        variable_was_declared((yyvsp[-3].strval));
        check_array_length((yyvsp[-1].intval));
        v.line = yylineno;
        if (v.t.isConst == 1)
        {
            printf("Const variable %s (line: %d) must be initialized\n", (yyvsp[-3].strval), v.line);
            noSemanticErrors = 0;
        }
        v.t.isInit = 0;
        v.t.isArray = 1;
        v.t.lengthOfArray = (yyvsp[-1].intval);
        strcpy(v.name, (yyvsp[-3].strval));
    }
#line 1756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 205 "opl.y" /* yacc.c:1646  */
    {
        variable_was_declared((yyvsp[-6].strval));
        v.line = yylineno;
        check_array_length((yyvsp[-4].intval));
        v.t.isInit = 1;
        v.t.isArray = 1;
        v.t.lengthOfArray = (yyvsp[-4].intval);
        strcpy(v.name, (yyvsp[-6].strval));
    }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 215 "opl.y" /* yacc.c:1646  */
    {
        variable_was_declared((yyvsp[-7].strval));
        v.line = yylineno;
        check_array_length((yyvsp[-5].intval));
        v.t.isInit = 1;
        v.t.isArray = 1;
        v.t.lengthOfArray = (yyvsp[-5].intval);
        strcpy(v.name, (yyvsp[-7].strval));
    }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 229 "opl.y" /* yacc.c:1646  */
    {v.t.isConst = 0;}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 230 "opl.y" /* yacc.c:1646  */
    {v.t.isConst = 1;}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 233 "opl.y" /* yacc.c:1646  */
    {if(isFunction == 0) {v.t.mainType = 0;} else {fun.returnType = 0;}}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 234 "opl.y" /* yacc.c:1646  */
    {if(isFunction == 0) {v.t.mainType = 1;} else {fun.returnType = 1;}}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 235 "opl.y" /* yacc.c:1646  */
    {if(isFunction == 0) {v.t.mainType = 2;} else {fun.returnType = 2;}}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 236 "opl.y" /* yacc.c:1646  */
    {if(isFunction == 0) {v.t.mainType = 3;} else {fun.returnType = 3;}}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 237 "opl.y" /* yacc.c:1646  */
    {if(isFunction == 0) {v.t.mainType = 4;} else {fun.returnType = 4;}}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 240 "opl.y" /* yacc.c:1646  */
    {valueType = 0;}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 241 "opl.y" /* yacc.c:1646  */
    {valueType = 1;}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 242 "opl.y" /* yacc.c:1646  */
    {valueType = 2;}
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 243 "opl.y" /* yacc.c:1646  */
    {valueType = 3;}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 244 "opl.y" /* yacc.c:1646  */
    {valueType = 4;}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 252 "opl.y" /* yacc.c:1646  */
    {
                leftType = v.t.mainType;
                if (leftType != valueType)
                {
                    different_types();
                }
             }
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 260 "opl.y" /* yacc.c:1646  */
    {
                variable_previously_defined((yyvsp[0].strval));
                check_variable_is_init(listOfVariables, (yyvsp[0].strval));
                leftType = v.t.mainType;
                if (leftType != type_of_variable(listOfVariables, (yyvsp[0].strval)))
                {
                    different_types();
                }
                check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
             }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 272 "opl.y" /* yacc.c:1646  */
    {isFunction = 1; strcat(v.scope, "function#\0"); init_variables(&fun.paramTable);}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 273 "opl.y" /* yacc.c:1646  */
    {fun.line = yylineno; isFunction = 0; strcpy(fun.name, (yyvsp[0].strval));}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 276 "opl.y" /* yacc.c:1646  */
    {
                    function_was_declared(listOfFunctions, fun);
                    insert_function(&listOfFunctions, fun);
                    free_variables(&fun.paramTable);
                    update_scope();
                }
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 288 "opl.y" /* yacc.c:1646  */
    {insert_variable(&fun.paramTable, v);}
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 289 "opl.y" /* yacc.c:1646  */
    {insert_variable(&fun.paramTable, v);}
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 293 "opl.y" /* yacc.c:1646  */
    {
            v.t.isArray = 0;
            strcpy(v.name, (yyvsp[0].strval));
        }
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 298 "opl.y" /* yacc.c:1646  */
    {
            leftType = v.t.mainType;
            if (leftType != valueType)
            {
                different_types();
            }
            v.t.isArray = 0;
            strcpy(v.name, (yyvsp[-2].strval));
        }
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 308 "opl.y" /* yacc.c:1646  */
    {
            check_array_length((yyvsp[-1].intval));
            v.t.isArray = 1;
            v.t.lengthOfArray = (yyvsp[-1].intval);
            strcpy(v.name, (yyvsp[-3].strval));
        }
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 315 "opl.y" /* yacc.c:1646  */
    {
            check_array_length((yyvsp[-4].intval));
            v.t.isArray = 1;
            v.t.lengthOfArray = (yyvsp[-4].intval);
            strcpy(v.name, (yyvsp[-6].strval));
        }
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 322 "opl.y" /* yacc.c:1646  */
    {
            check_array_length((yyvsp[-5].intval));
            v.t.isArray = 1;
            v.t.lengthOfArray = (yyvsp[-5].intval);
            strcpy(v.name, (yyvsp[-7].strval));
        }
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 331 "opl.y" /* yacc.c:1646  */
    {
                cl.line = yylineno;
                strcat(v.scope, "class#method#\0");
                strcpy(cl.name, (yyvsp[0].strval));
                init_variables(&cl.attribTable);
                init_functions(&cl.methTable);
            }
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 339 "opl.y" /* yacc.c:1646  */
    {
                insert_class(&listOfClasses, cl);
                free_functions(&cl.methTable);
                free_variables(&cl.attribTable);
                update_scope();
                update_scope();
            }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 359 "opl.y" /* yacc.c:1646  */
    {insert_variable(&cl.attribTable, v);}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 360 "opl.y" /* yacc.c:1646  */
    {insert_variable(&cl.attribTable, v);}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 364 "opl.y" /* yacc.c:1646  */
    {
                class_variable_was_declared(cl.attribTable, (yyvsp[0].strval));
                if (v.t.isConst == 1)
                {
                    printf("Const variable %s (line: %d) must be initialized\n", (yyvsp[0].strval), yylineno);
                    noSemanticErrors = 0;
                }
                v.line = yylineno;
                v.t.isInit = 0;
                v.t.isArray = 0;
                strcpy(v.name, (yyvsp[0].strval));
              }
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 377 "opl.y" /* yacc.c:1646  */
    {
                class_variable_was_declared(cl.attribTable, (yyvsp[-2].strval));
                leftType = v.t.mainType;
                if (leftType != valueType)
                {
                   different_types();
                }
                v.line = yylineno;
                v.t.isInit = 1;
                v.t.isArray = 0;
                strcpy(v.name, (yyvsp[-2].strval));
              }
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 390 "opl.y" /* yacc.c:1646  */
    {
                class_variable_was_declared(cl.attribTable, (yyvsp[-3].strval));
                check_array_length((yyvsp[-1].intval));
                v.line = yylineno;
                if (v.t.isConst == 1)
                {
                    printf("Const variable %s (line: %d) must be initialized\n", (yyvsp[-3].strval), v.line);
                    noSemanticErrors = 0;
                }
                v.t.isInit = 0;
                v.t.isArray = 1;
                v.t.lengthOfArray = (yyvsp[-1].intval);
                strcpy(v.name, (yyvsp[-3].strval));
              }
#line 2063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 405 "opl.y" /* yacc.c:1646  */
    {
                class_variable_was_declared(cl.attribTable, (yyvsp[-6].strval));
                v.line = yylineno;
                check_array_length((yyvsp[-4].intval));
                v.t.isInit = 1;
                v.t.isArray = 1;
                v.t.lengthOfArray = (yyvsp[-4].intval);
                strcpy(v.name, (yyvsp[-6].strval));
              }
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 415 "opl.y" /* yacc.c:1646  */
    {
                class_variable_was_declared(cl.attribTable, (yyvsp[-7].strval));
                v.line = yylineno;
                check_array_length((yyvsp[-5].intval));
                v.t.isInit = 1;
                v.t.isArray = 1;
                v.t.lengthOfArray = (yyvsp[-5].intval);
                strcpy(v.name, (yyvsp[-7].strval));
              }
#line 2091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 426 "opl.y" /* yacc.c:1646  */
    {isFunction = 1;}
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 426 "opl.y" /* yacc.c:1646  */
    {isFunction = 0; fun.line = yylineno; strcpy(fun.name, (yyvsp[0].strval)); init_variables(&fun.paramTable);}
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 429 "opl.y" /* yacc.c:1646  */
    {
                        method_was_declared(cl.methTable, fun);
                        insert_function(&cl.methTable, fun);
                        free_variables(&fun.paramTable);
                     }
#line 2113 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 440 "opl.y" /* yacc.c:1646  */
    {insert_variable(&fun.paramTable, v);}
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 441 "opl.y" /* yacc.c:1646  */
    {insert_variable(&fun.paramTable, v);}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 446 "opl.y" /* yacc.c:1646  */
    {
                if (fun.returnType != valueType)
                {
                    printf("Invalid return type (line: %d)\n", yylineno);
                    noSemanticErrors = 0;
                }
            }
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 454 "opl.y" /* yacc.c:1646  */
    {
                variable_previously_defined((yyvsp[0].strval));
                check_variable_is_init(listOfVariables, (yyvsp[0].strval));
                if (fun.returnType != type_of_variable(listOfVariables, (yyvsp[0].strval)))
                {
                    printf("Invalid return type (line: %d)\n", yylineno);
                    noSemanticErrors = 0;
                }
                check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
            }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 466 "opl.y" /* yacc.c:1646  */
    {strcat(v.scope, "main#\0");}
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 475 "opl.y" /* yacc.c:1646  */
    {
            free_variables(&fun.paramTable);
         }
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 486 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[-2].strval));
        variable_previously_defined((yyvsp[0].strval));
        check_variable_is_init(listOfVariables, (yyvsp[0].strval));
        set_init_variable(&listOfVariables, (yyvsp[-2].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-2].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-2].strval)) != type_of_variable(listOfVariables, (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-2].strval), v.scope);
        check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
      }
#line 2185 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 501 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[0].strval));
        class_variable_previously_defined((yyvsp[-4].strval), (yyvsp[-2].strval));
        check_variable_is_init(listOfVariables, (yyvsp[0].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval)) != type_of_variable(listOfVariables, (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
      }
#line 2203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 515 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[-4].strval));
        class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
        set_init_variable(&listOfVariables, (yyvsp[-4].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-4].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-4].strval)) != type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-4].strval), v.scope);
      }
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 529 "opl.y" /* yacc.c:1646  */
    {
        class_variable_previously_defined((yyvsp[-6].strval), (yyvsp[-4].strval));
        class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval)) != type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval)))
        {
            different_types();
        }
      }
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 542 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[-2].strval));
        set_init_variable(&listOfVariables, (yyvsp[-2].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-2].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-2].strval)) != valueType)
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-2].strval), v.scope);
      }
#line 2254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 554 "opl.y" /* yacc.c:1646  */
    {
        class_variable_previously_defined((yyvsp[-4].strval), (yyvsp[-2].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval)) != valueType)
        {
            different_types();
        }
      }
#line 2269 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 565 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[-2].strval));
        set_init_variable(&listOfVariables, (yyvsp[-2].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-2].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-2].strval)) != arithmeticExprType)
        {
            different_types();
        }
        arithmeticExprType = -2;
        check_scope(listOfVariables, (yyvsp[-2].strval), v.scope);
      }
#line 2286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 578 "opl.y" /* yacc.c:1646  */
    {
        class_variable_previously_defined((yyvsp[-4].strval), (yyvsp[-2].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval)) != arithmeticExprType)
        {
            different_types();
        }
        arithmeticExprType = -2;
      }
#line 2302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 590 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-3].intval));
        variable_previously_defined((yyvsp[-5].strval));
        set_init_variable(&listOfVariables, (yyvsp[-5].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-5].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-5].strval)) != valueType)
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-5].strval), v.scope);
      }
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 603 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-3].intval));
        class_variable_previously_defined((yyvsp[-7].strval), (yyvsp[-5].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval)) != valueType)
        {
            different_types();
        }
      }
#line 2335 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 615 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-3].intval)); 
        variable_previously_defined((yyvsp[-5].strval)); 
        variable_previously_defined((yyvsp[0].strval));
        check_variable_is_init(listOfVariables, (yyvsp[0].strval));
        set_init_variable(&listOfVariables, (yyvsp[-5].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-5].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-5].strval)) != type_of_variable(listOfVariables, (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-5].strval), v.scope);
        check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
      }
#line 2355 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 631 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-3].intval));
        variable_previously_defined((yyvsp[0].strval));
        class_variable_previously_defined((yyvsp[-7].strval), (yyvsp[-5].strval));
        check_variable_is_init(listOfVariables, (yyvsp[0].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval)) != type_of_variable(listOfVariables, (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
      }
#line 2374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 646 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-5].intval));
        variable_previously_defined((yyvsp[-7].strval));
        class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
        set_init_variable(&listOfVariables, (yyvsp[-7].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-7].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-7].strval)) != type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-7].strval), v.scope);
      }
#line 2393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 661 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-5].intval));
        class_variable_previously_defined((yyvsp[-9].strval), (yyvsp[-7].strval));
        class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-9].strval), (yyvsp[-7].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-9].strval), (yyvsp[-7].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-9].strval), (yyvsp[-7].strval)) != type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval)))
        {
            different_types();
        }
      }
#line 2411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 675 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-6].intval));
        check_array_length((yyvsp[-1].intval));
        variable_previously_defined((yyvsp[-8].strval));
        variable_previously_defined((yyvsp[-3].strval));
        check_variable_is_init(listOfVariables, (yyvsp[-3].strval));
        set_init_variable(&listOfVariables, (yyvsp[-8].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-8].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-8].strval)) != type_of_variable(listOfVariables, (yyvsp[-3].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-8].strval), v.scope);
        check_scope(listOfVariables, (yyvsp[-3].strval), v.scope);
      }
#line 2432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 692 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-8].intval)); 
        check_array_length((yyvsp[-1].intval)); 
        variable_previously_defined((yyvsp[-10].strval));
        class_variable_previously_defined((yyvsp[-5].strval), (yyvsp[-3].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-5].strval), (yyvsp[-3].strval));
        set_init_variable(&listOfVariables, (yyvsp[-10].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-10].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-10].strval)) != type_of_class_variable(listOfClasses, (yyvsp[-5].strval), (yyvsp[-3].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-10].strval), v.scope);
      }
#line 2452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 708 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-6].intval));
        check_array_length((yyvsp[-1].intval));
        variable_previously_defined((yyvsp[-3].strval));
        class_variable_previously_defined((yyvsp[-10].strval), (yyvsp[-8].strval));
        check_variable_is_init(listOfVariables, (yyvsp[-3].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-10].strval), (yyvsp[-8].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-10].strval), (yyvsp[-8].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-10].strval), (yyvsp[-8].strval)) != type_of_variable(listOfVariables, (yyvsp[-3].strval)))
        {
            different_types();
        }
        check_scope(listOfVariables, (yyvsp[-3].strval), v.scope);
      }
#line 2472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 724 "opl.y" /* yacc.c:1646  */
    {
        check_array_length((yyvsp[-8].intval));
        check_array_length((yyvsp[-1].intval));
        class_variable_previously_defined((yyvsp[-12].strval), (yyvsp[-10].strval));
        class_variable_previously_defined((yyvsp[-5].strval), (yyvsp[-3].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-5].strval), (yyvsp[-3].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-12].strval), (yyvsp[-10].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-12].strval), (yyvsp[-10].strval));

        if (type_of_class_variable(listOfClasses, (yyvsp[-12].strval), (yyvsp[-10].strval)) != type_of_class_variable(listOfClasses, (yyvsp[-5].strval), (yyvsp[-3].strval)))
        {
            different_types();
        }
      }
#line 2491 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 740 "opl.y" /* yacc.c:1646  */
    {init_variables(&fun.paramTable);}
#line 2497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 741 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[-7].strval));
        function_previously_defined((yyvsp[-4].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-7].strval));
        set_init_variable(&listOfVariables, (yyvsp[-7].strval));

        if (type_of_variable(listOfVariables, (yyvsp[-7].strval)) != type_of_return_function(listOfFunctions, (yyvsp[-4].strval)))
        {
            different_types();
        }
        returnType = type_of_return_function(listOfFunctions, (yyvsp[-4].strval));
        strcpy(fun.name, (yyvsp[-4].strval));
        check_function_signature(listOfFunctions, fun);
        check_scope(listOfVariables, (yyvsp[-7].strval), v.scope);
    }
#line 2517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 756 "opl.y" /* yacc.c:1646  */
    {init_variables(&fun.paramTable);}
#line 2523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 757 "opl.y" /* yacc.c:1646  */
    {
        class_variable_previously_defined((yyvsp[-9].strval), (yyvsp[-7].strval));
        function_previously_defined((yyvsp[-4].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-9].strval), (yyvsp[-7].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-9].strval), (yyvsp[-7].strval));

        if(type_of_class_variable(listOfClasses, (yyvsp[-9].strval), (yyvsp[-7].strval)) != type_of_return_function(listOfFunctions, (yyvsp[-4].strval)))
        {
            different_types();
        }
        returnType = type_of_return_function(listOfFunctions, (yyvsp[-4].strval));
        strcpy(fun.name, (yyvsp[-4].strval));
        check_function_signature(listOfFunctions, fun);
    }
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 771 "opl.y" /* yacc.c:1646  */
    {init_variables(&fun.paramTable);}
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 772 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[-9].strval));
        method_previously_defined((yyvsp[-6].strval), (yyvsp[-4].strval));
        check_variable_is_const(listOfVariables, (yyvsp[-9].strval));
        set_init_variable(&listOfVariables, (yyvsp[-9].strval));

        if(type_of_variable(listOfVariables, (yyvsp[-9].strval)) != type_of_return_method(listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval)))
        {
            different_types();
        }
        returnType = type_of_return_method(listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval));
        strcpy(fun.name, (yyvsp[-4].strval));
        check_method_signature(listOfClasses, (yyvsp[-6].strval), fun);
        check_scope(listOfVariables, (yyvsp[-9].strval), v.scope);
    }
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 787 "opl.y" /* yacc.c:1646  */
    {init_variables(&fun.paramTable);}
#line 2574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 788 "opl.y" /* yacc.c:1646  */
    {
        class_variable_previously_defined((yyvsp[-11].strval), (yyvsp[-9].strval));
        method_previously_defined((yyvsp[-6].strval), (yyvsp[-4].strval));
        check_class_variable_is_const(listOfClasses, (yyvsp[-11].strval), (yyvsp[-9].strval));
        set_init_class_variable(&listOfClasses, (yyvsp[-11].strval), (yyvsp[-9].strval));

        if(type_of_class_variable(listOfClasses, (yyvsp[-11].strval), (yyvsp[-9].strval)) != type_of_return_method(listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval)))
        {
            different_types();
        }
        returnType = type_of_return_method(listOfClasses, (yyvsp[-6].strval), (yyvsp[-4].strval));
        strcpy(fun.name, (yyvsp[-4].strval));
        check_method_signature(listOfClasses, (yyvsp[-6].strval), fun);
    }
#line 2593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 808 "opl.y" /* yacc.c:1646  */
    {insert_variable(&fun.paramTable, v);}
#line 2599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 809 "opl.y" /* yacc.c:1646  */
    {insert_variable(&fun.paramTable, v);}
#line 2605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 813 "opl.y" /* yacc.c:1646  */
    {
        v.t.mainType = valueType;
        v.t.isArray = 0;
     }
#line 2614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 818 "opl.y" /* yacc.c:1646  */
    {
        variable_previously_defined((yyvsp[0].strval));
        check_variable_is_init(listOfVariables, (yyvsp[0].strval));
        v.t.mainType = type_of_variable(listOfVariables, (yyvsp[0].strval));
        v.t.isArray = variable_is_array(listOfVariables, (yyvsp[0].strval));
        check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
     }
#line 2626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 826 "opl.y" /* yacc.c:1646  */
    {
        class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
        check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
        v.t.mainType = type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
        v.t.isArray = class_variable_is_array(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
     }
#line 2637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 839 "opl.y" /* yacc.c:1646  */
    {
            if (arithmeticExprType != -1)
            {
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = valueType;
                }

                if (arithmeticExprType != valueType)
                {
                    arithmeticExprType = -1;
                }
            }
       }
#line 2656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 854 "opl.y" /* yacc.c:1646  */
    {
            variable_previously_defined((yyvsp[0].strval));
            check_variable_is_init(listOfVariables, (yyvsp[0].strval));

            if (arithmeticExprType != -1)
            { 
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = type_of_variable(listOfVariables, (yyvsp[0].strval));
                }

                if (arithmeticExprType != type_of_variable(listOfVariables, (yyvsp[0].strval)))
                {
                    arithmeticExprType = -1;
                }
            }
            check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
       }
#line 2679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 873 "opl.y" /* yacc.c:1646  */
    {
            class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
            check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));

            if (arithmeticExprType != -1)
            {
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));
                }

                if (arithmeticExprType != type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval)))
                {
                    arithmeticExprType = -1;
                }
            }
       }
#line 2701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 891 "opl.y" /* yacc.c:1646  */
    {
            if (arithmeticExprType != -1)
            {
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = returnType;
                }

                if (arithmeticExprType != returnType)
                {
                    arithmeticExprType = -1;
                }
            }
       }
#line 2720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 913 "opl.y" /* yacc.c:1646  */
    {strcat(v.scope, "if#\0");}
#line 2726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 913 "opl.y" /* yacc.c:1646  */
    {update_scope();}
#line 2732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 916 "opl.y" /* yacc.c:1646  */
    {strcat(v.scope, "else#\0");}
#line 2738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 916 "opl.y" /* yacc.c:1646  */
    {update_scope();}
#line 2744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 930 "opl.y" /* yacc.c:1646  */
    {variable_previously_defined((yyvsp[0].strval)); check_variable_is_init(listOfVariables, (yyvsp[0].strval)); check_scope(listOfVariables, (yyvsp[0].strval), v.scope);}
#line 2750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 931 "opl.y" /* yacc.c:1646  */
    {class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval)); check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));}
#line 2756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 932 "opl.y" /* yacc.c:1646  */
    {arithmeticExprType = -2;}
#line 2762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 940 "opl.y" /* yacc.c:1646  */
    {strcat(v.scope, "while#\0");}
#line 2768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 940 "opl.y" /* yacc.c:1646  */
    {update_scope();}
#line 2774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 943 "opl.y" /* yacc.c:1646  */
    {strcat(v.scope, "for#\0");}
#line 2780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 943 "opl.y" /* yacc.c:1646  */
    {update_scope();}
#line 2786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 954 "opl.y" /* yacc.c:1646  */
    {
                expr.line = yylineno;
                expr.result = (yyval.expr_ptr)->intvalue;
                insert_eval(&listOfEval, expr); 
                free_expr((yyval.expr_ptr));
               }
#line 2797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 963 "opl.y" /* yacc.c:1646  */
    { 
                (yyval.expr_ptr) = create_int_expr((yyvsp[-2].expr_ptr)->intvalue + (yyvsp[0].expr_ptr)->intvalue);
                free_expr((yyvsp[-2].expr_ptr)); 
                free_expr((yyvsp[0].expr_ptr));
            }
#line 2807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 969 "opl.y" /* yacc.c:1646  */
    { 
                (yyval.expr_ptr) = create_int_expr((yyvsp[-2].expr_ptr)->intvalue - (yyvsp[0].expr_ptr)->intvalue);
                free_expr((yyvsp[-2].expr_ptr)); 
                free_expr((yyvsp[0].expr_ptr));
            }
#line 2817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 975 "opl.y" /* yacc.c:1646  */
    { 
                (yyval.expr_ptr) = create_int_expr((yyvsp[-2].expr_ptr)->intvalue * (yyvsp[0].expr_ptr)->intvalue);
                free_expr((yyvsp[-2].expr_ptr));
                free_expr((yyvsp[0].expr_ptr));
            }
#line 2827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 981 "opl.y" /* yacc.c:1646  */
    { 
                (yyval.expr_ptr) = create_int_expr((yyvsp[-2].expr_ptr)->intvalue / (yyvsp[0].expr_ptr)->intvalue);
                free_expr((yyvsp[-2].expr_ptr));
                free_expr((yyvsp[0].expr_ptr));
            }
#line 2837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 986 "opl.y" /* yacc.c:1646  */
    {(yyval.expr_ptr) = create_int_expr((yyvsp[0].intval));}
#line 2843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 989 "opl.y" /* yacc.c:1646  */
    {
                    variable_previously_defined((yyvsp[-2].strval));
                    set_init_variable(&listOfVariables, (yyvsp[-2].strval));
                    check_variable_is_const(listOfVariables, (yyvsp[-2].strval));

                    if (type_of_variable(listOfVariables, (yyvsp[-2].strval)) != 3)
                    {
                        different_types();
                    }
                    check_scope(listOfVariables, (yyvsp[-2].strval), v.scope);
                }
#line 2859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1001 "opl.y" /* yacc.c:1646  */
    {
                    variable_previously_defined((yyvsp[-5].strval));
                    set_init_variable(&listOfVariables, (yyvsp[-5].strval));
                    check_variable_is_const(listOfVariables, (yyvsp[-5].strval));

                    if (type_of_variable(listOfVariables, (yyvsp[-5].strval)) != 0)
                    {
                        different_types();
                    }
                    check_scope(listOfVariables, (yyvsp[-5].strval), v.scope);
                }
#line 2875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1013 "opl.y" /* yacc.c:1646  */
    {
                    variable_previously_defined((yyvsp[-5].strval));
                    set_init_variable(&listOfVariables, (yyvsp[-5].strval));
                    check_variable_is_const(listOfVariables, (yyvsp[-5].strval));

                    if (type_of_variable(listOfVariables, (yyvsp[-5].strval)) != 0)
                    {
                        different_types();
                    }
                    check_scope(listOfVariables, (yyvsp[-5].strval), v.scope);
                }
#line 2891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1025 "opl.y" /* yacc.c:1646  */
    {
                    class_variable_previously_defined((yyvsp[-4].strval), (yyvsp[-2].strval));
                    set_init_class_variable(&listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));
                    check_class_variable_is_const(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval));

                    if (type_of_class_variable(listOfClasses, (yyvsp[-4].strval), (yyvsp[-2].strval)) != 3)
                    {
                        different_types();
                    }
                }
#line 2906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1036 "opl.y" /* yacc.c:1646  */
    {
                    class_variable_previously_defined((yyvsp[-7].strval), (yyvsp[-5].strval));
                    set_init_class_variable(&listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));
                    check_class_variable_is_const(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));

                    if (type_of_class_variable(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval)) != 0)
                    {
                        different_types();
                    }
                }
#line 2921 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1047 "opl.y" /* yacc.c:1646  */
    {
                    class_variable_previously_defined((yyvsp[-7].strval), (yyvsp[-5].strval));
                    set_init_class_variable(&listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));
                    check_class_variable_is_const(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval));

                    if (type_of_class_variable(listOfClasses, (yyvsp[-7].strval), (yyvsp[-5].strval)) != 0)
                    {
                        different_types();
                    }
                }
#line 2936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1068 "opl.y" /* yacc.c:1646  */
    {
                variable_previously_defined((yyvsp[0].strval));
                check_variable_is_init(listOfVariables, (yyvsp[0].strval));

                if (type_of_variable(listOfVariables, (yyvsp[0].strval)) != 3)
                {
                    different_types();
                }
                check_scope(listOfVariables, (yyvsp[0].strval), v.scope);
              }
#line 2951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1079 "opl.y" /* yacc.c:1646  */
    {
                class_variable_previously_defined((yyvsp[-2].strval), (yyvsp[0].strval));
                check_class_variable_is_init(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval));

                if (type_of_class_variable(listOfClasses, (yyvsp[-2].strval), (yyvsp[0].strval)) != 3)
                {
                    different_types();
                }
              }
#line 2965 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2969 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
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
  return yyresult;
}
#line 1091 "opl.y" /* yacc.c:1906  */


expr_info* create_int_expr(int value)
{
   expr_info* expr = (expr_info*)malloc(sizeof(expr_info));
   expr->intvalue = value;
   expr->type = 1;
   return expr;
}

expr_info* create_str_expr(char* value1, char* value2) 
{
    expr_info* expr = (expr_info*)malloc(sizeof(expr_info));
    int len2 = value2 ? strlen(value2) : 0;
    expr->strvalue = (char*) malloc(sizeof(char)*(strlen(value1) + len2 + 1)); 
    strcpy(expr->strvalue, value1);
    if(value2)
    {
        strcat(expr->strvalue, value2);
    }
    expr->type = 2;
    return expr;
}

void free_expr(expr_info* expr)
{
    if(expr->type == 2)
    {
        free(expr->strvalue);
    }
    free(expr);
}


void print_expr(expr_info* expr)
{
    if(expr->type == 1) 
    {
        printf("Eval expr(line: %d) with value:%d\n", yylineno, expr->intvalue);
    }
    else
    {
        printf("Str expr with value:%s\n", expr->strvalue); 
    } 
}

void update_scope()
{
    int len = strlen(v.scope);
    v.scope[len - 1] = 0;
    len = len - 2;
    while (v.scope[len] != '#')
    {
        v.scope[len] = 0;
        --len;
    }
}

void check_array_length(int len)
{
    if (len <= 0)
    {
        printf("Invalid array length(line: %d)\n", yylineno);
        noSemanticErrors = 0;
    }
}

void variable_was_declared(char* id)
{
    for (int i = 0; i < listOfVariables.varNumber; ++i)
    {
        if (strcmp(listOfVariables.varTable[i].name, id) == 0)
        {
            printf("Variable %s (line: %d) was already declared (line %d)\n", id, yylineno, listOfVariables.varTable[i].line);
            noSemanticErrors = 0;
        }
    }
}

void class_variable_was_declared(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            printf("Variable %s (line: %d) from class %s was already declared (line %d)\n", id, yylineno, cl.name, arr.varTable[i].line);
            noSemanticErrors = 0;
        }
    }
}

int variable_is_init(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return arr.varTable[i].t.isInit;
        }
    }
}

int class_variable_is_init(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return arr.classTable[i].attribTable.varTable[j].t.isInit;
                }
            }
        }
    }
}

void set_init_variable(VariableTable* arr, char* id)
{
    for (int i = 0; i < arr->varNumber; ++i)
    {
        if (strcmp(arr->varTable[i].name, id) == 0)
        {
            arr->varTable[i].t.isInit = 1;
        }
    }
}

void set_init_class_variable(ClassTable* arr, char* className, char* id)
{
    for (int i = 0; i < arr->classNumber; ++i)
    {
        if (strcmp(arr->classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr->classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr->classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    arr->classTable[i].attribTable.varTable[j].t.isInit = 1;
                }
            }
        }
    }
}

void check_variable_is_init(VariableTable arr, char* id)
{
    if (variable_is_init(arr, id) == 0)
    {
        printf("A variable (%s) appearing in the right side of an expression should have been initialized explicitly (line: %d)\n", id, yylineno);
        noSemanticErrors = 0;
    }
}

void check_class_variable_is_init(ClassTable arr, char* className, char* id)
{
    if (class_variable_is_init(arr, className, id) == 0)
    {
        printf("A variable (%s.%s) appearing in the right side of an expression should have been initialized explicitly (line: %d)\n", className, id, yylineno);
        noSemanticErrors = 0;
    }
}

void variable_previously_defined(char* id)
{
    for (int i = 0; i < listOfVariables.varNumber; ++i)
    {
        if (strcmp(listOfVariables.varTable[i].name, id) == 0)
        {
            return;
        }
    }
    printf("Variable %s (line: %d) has not been previously defined\n", id, yylineno);
    noSemanticErrors = 0;
}

void class_variable_previously_defined(char* className, char* id)
{
    for (int i = 0; i < listOfClasses.classNumber; ++i)
    {
        if (strcmp(listOfClasses.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < listOfClasses.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(listOfClasses.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return;
                }
            }
            printf("Variable %s (line: %d) from class %s has not been previously defined\n", id, yylineno, className);
            noSemanticErrors = 0;
            return;
        }
    }
    printf("Class %s (line: %d) has not been previously defined\n", className, yylineno);
    noSemanticErrors = 0;
}

int compare_params(struct Variable v1, struct Variable v2)
{
    if (v1.t.mainType != v2.t.mainType)
    {
        return 0;
    }
    if (v1.t.isArray != v2.t.isArray)
    {
        return 0;
    }
    return 1;
}

void different_types()
{
    printf("The left side of an assignment must have the same type as the right side (line: %d)\n", yylineno);
    noSemanticErrors = 0;
}

void function_was_declared(FunctionTable arr, struct Function fun)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(fun.name, arr.funcTable[i].name) == 0)
        {
            if (fun.returnType == arr.funcTable[i].returnType)
            {
                if (fun.paramTable.varNumber == arr.funcTable[i].paramTable.varNumber)
                {
                    for (int j = 0; j < fun.paramTable.varNumber; ++j)
                    {
                        if (compare_params(fun.paramTable.varTable[j], arr.funcTable[i].paramTable.varTable[j]) == 0)
                        {
                            return;
                        }
                    }
                    noSemanticErrors = 0;
                    printf("Function %s (line: %d) was already declared (line: %d)\n", fun.name, yylineno, arr.funcTable[i].line);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }
}


void method_was_declared(FunctionTable arr, struct Function fun)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(fun.name, arr.funcTable[i].name) == 0)
        {
            if (fun.returnType == arr.funcTable[i].returnType)
            {
                if (fun.paramTable.varNumber == arr.funcTable[i].paramTable.varNumber)
                {
                    for (int j = 0; j < fun.paramTable.varNumber; ++j)
                    {
                        if (compare_params(fun.paramTable.varTable[j], arr.funcTable[i].paramTable.varTable[j]) == 0)
                        {
                            return;
                        }
                    }
                    noSemanticErrors = 0;
                    printf("Method %s (line: %d) from class %s was already declared (line: %d)\n", fun.name, yylineno, cl.name, arr.funcTable[i].line);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }
}

void function_previously_defined(char* id)
{
    for (int i = 0; i < listOfFunctions.funcNumber; ++i)
    {
        if (strcmp(listOfFunctions.funcTable[i].name, id) == 0)
        {
            return;
        }
    }
    printf("Function %s (line: %d) has not been previously defined\n", id, yylineno);
    noSemanticErrors = 0;
}

void method_previously_defined(char* className, char* id)
{
    for (int i = 0; i < listOfClasses.classNumber; ++i)
    {
        if (strcmp(listOfClasses.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < listOfClasses.classTable[i].methTable.funcNumber; ++j)
            {
                if (strcmp(listOfClasses.classTable[i].methTable.funcTable[j].name, id) == 0)
                {
                    return;
                }
            }
            printf("Method %s (line: %d) from class %s has not been previously defined\n", id, yylineno, className);
            noSemanticErrors = 0;
        }
        return;
    }
    printf("Class %s (line: %d) has not been previously defined\n", className, yylineno);
    noSemanticErrors = 0;
}

int type_of_variable(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return (arr.varTable[i].t.mainType);
        }
    }
}

int type_of_class_variable(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return (arr.classTable[i].attribTable.varTable[j].t.mainType);
                }
            }
        }
    }
}

int type_of_return_function(FunctionTable arr, char* id)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(arr.funcTable[i].name, id) == 0)
        {
            return arr.funcTable[i].returnType;
        }
    }
}

int type_of_return_method(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].methTable.funcNumber; ++j)
            {
                if (strcmp(arr.classTable[i].methTable.funcTable[j].name, id) == 0)
                {
                    return arr.classTable[i].methTable.funcTable[j].returnType;
                }
            }
        }
    }
}

int variable_is_array(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return (arr.varTable[i].t.isArray);
        }
    }
}

int class_variable_is_array(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return (arr.classTable[i].attribTable.varTable[j].t.isArray);
                }
            }
        }
    }
}

void check_function_signature(FunctionTable arr, struct Function fun)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(arr.funcTable[i].name, fun.name) == 0)
        {
            if (fun.paramTable.varNumber == arr.funcTable[i].paramTable.varNumber)
            {
                for (int j = 0; j < fun.paramTable.varNumber; ++j)
                {
                    if (compare_params(fun.paramTable.varTable[j], arr.funcTable[i].paramTable.varTable[j]) == 0)
                    {
                        printf("Wrong type of argument no. %d for function %s (line: %d)\n", (j + 1), fun.name, yylineno);
                        noSemanticErrors = 0;
                        return;
                    }
                }
                return;
            }
            else
            {   
                printf("Wrong number of arguments for function %s (line: %d)\n", fun.name, yylineno);
                noSemanticErrors = 0;
                return;
            }
        }
    }
}

void check_method_signature(ClassTable arr, char* className, struct Function fun)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].methTable.funcNumber; ++j)
            {
                if (strcmp(arr.classTable[i].methTable.funcTable[j].name, fun.name) == 0)
                {
                    if (fun.paramTable.varNumber == arr.classTable[i].methTable.funcTable[j].paramTable.varNumber)
                    {
                        for (int k = 0; j < fun.paramTable.varNumber; ++j)
                        {
                            if (compare_params(fun.paramTable.varTable[k], arr.classTable[i].methTable.funcTable[j].paramTable.varTable[k]) == 0)
                            {
                                printf("Wrong type of argument no. %d for method %s.%s (line: %d)\n", (k + 1), className, fun.name, yylineno);
                                noSemanticErrors = 0;
                                return;
                            }
                        }
                        return;
                    }
                    else
                    {   
                        printf("Wrong number of arguments for method %s.%s (line: %d)\n", className, fun.name, yylineno);
                        noSemanticErrors = 0;
                        return;
                    }
                }
            }
        }
    }
}

int variable_is_const(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return (arr.varTable[i].t.isConst);
        }
    }
}

int class_variable_is_const(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return (arr.classTable[i].attribTable.varTable[j].t.isConst);
                }
            }
        }
    }
}

void check_variable_is_const(VariableTable arr, char* id)
{
    if (variable_is_const(arr, id) == 1)
    {
        printf("Const variable %s cannot be reassigned (line: %d)\n", id, yylineno);
        noSemanticErrors = 0;
    }
}

void check_class_variable_is_const(ClassTable arr, char* className, char* id)
{
    if (class_variable_is_const(arr, className, id) == 1)
    {
        printf("Const variable %s.%s cannot be reassigned (line: %d)\n", className, id, yylineno);
        noSemanticErrors = 0;
    }
}

void check_scope(VariableTable arr, char* id, char* currentScope)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            if (strstr(currentScope, arr.varTable[i].scope) == 0)
            {
                printf("Invalid scope for variable %s(line: %d)\n", id, yylineno);
                noSemanticErrors = 0;
            }
        }
    }
}

int yyerror(char *s)
{
    printf("Error(line %d): %s\n", yylineno, s);
}

int main(int argc, char** argv)
{
    yyin = fopen(argv[1], "r");

    init_variables(&listOfVariables);
    init_functions(&listOfFunctions);
    init_classes(&listOfClasses);
    init_eval(&listOfEval);

    yyparse();

    if (noSyntacticErrors + noSemanticErrors == 2)
    {
        printf("No semantic errors\n");

        for (int i = 0; i < listOfEval.evalNumber; ++i)
        {
            printf("Eval expr(line: %d) with value: %d\n", listOfEval.evalExpressions[i].line, listOfEval.evalExpressions[i].result);
        }
    }

    FILE* f = fopen("symbol_table.txt", "w");
    fclose(f);
    f = fopen("symbol_table.txt", "a");

    if (listOfVariables.varNumber > 0)
    {
        fprintf(f, "Variables:\n");
        for (int i = 0; i < listOfVariables.varNumber; ++i)
        {
            fprintf(f, "%d) name: %s ", (i + 1), listOfVariables.varTable[i].name);
            fprintf(f, "|| scope: ");
            if (strcmp(listOfVariables.varTable[i].scope, "#") == 0)
            {
                fprintf(f, "global ");
            }
            else
            {
                fprintf(f, "%s ", listOfVariables.varTable[i].scope);
            }
            fprintf(f, "|| type: ");
            switch (listOfVariables.varTable[i].t.mainType)
            {
                case 0:
                    fprintf(f, "integer");
                    break;
                case 1:
                    fprintf(f, "float");
                    break;
                case 2:
                    fprintf(f, "char");
                    break;
                case 3:
                    fprintf(f, "string");
                    break;
                case 4:
                    fprintf(f, "bool");
            }

            if (listOfVariables.varTable[i].t.isConst == 1)
            {
                fprintf(f, " || const");
            }

            if (listOfVariables.varTable[i].t.isInit == 1)
            {
                fprintf(f, " || init");
            }

            if (listOfVariables.varTable[i].t.isArray == 1)
            {
                fprintf(f, " || array of length: ");
                char str[10];
                sprintf(str, "%d", listOfVariables.varTable[i].t.lengthOfArray);
                fprintf(f, "%s", str);
            }
            fprintf(f, " || line: %d\n", listOfVariables.varTable[i].line);
        }
        fprintf(f, "\n\n---------------------\n\n\n");
    }

    if (listOfFunctions.funcNumber > 0)
    {
        fprintf(f, "Functions:\n");
        for (int i = 0; i < listOfFunctions.funcNumber; ++i)
        {
            fprintf(f, "%d) name: %s ", (i + 1), listOfFunctions.funcTable[i].name);
            fprintf(f, "|| return type: ");
            switch (listOfFunctions.funcTable[i].returnType)
            {
                case 0:
                    fprintf(f, "integer");
                    break;
                case 1:
                    fprintf(f, "float");
                    break;
                case 2:
                    fprintf(f, "char");
                    break;
                case 3:
                    fprintf(f, "string");
                    break;
                case 4:
                    fprintf(f, "bool");
            }
            fprintf(f, " || line: %d", listOfFunctions.funcTable[i].line);
            fprintf(f, " || parameters: ");

            if (listOfFunctions.funcTable[i].paramTable.varNumber > 0)
            {
                fprintf(f, "\n");
                for (int j = 0; j < listOfFunctions.funcTable[i].paramTable.varNumber; ++j)
                {
                    fprintf(f, ">>> %d.%d) name: %s ", (i + 1), (j + 1), listOfFunctions.funcTable[i].paramTable.varTable[j].name);
                    fprintf(f, "|| type: ");
                    switch (listOfFunctions.funcTable[i].paramTable.varTable[j].t.mainType)
                    {
                        case 0:
                            fprintf(f, "integer");
                            break;
                        case 1:
                            fprintf(f, "float");
                            break;
                        case 2:
                            fprintf(f, "char");
                            break;
                        case 3:
                            fprintf(f, "string");
                            break;
                        case 4:
                            fprintf(f, "bool");
                            break;
                        case 5:
                            fprintf(f, "object");
                    }

                    if (listOfFunctions.funcTable[i].paramTable.varTable[j].t.isConst == 1)
                    {
                        fprintf(f, " || const");
                    }

                    if (listOfFunctions.funcTable[i].paramTable.varTable[j].t.isArray == 1)
                    {
                        fprintf(f, " || array of length: ");
                        char str[10];
                        sprintf(str, "%d", listOfFunctions.funcTable[i].paramTable.varTable[j].t.lengthOfArray);
                        fprintf(f, "%s", str);
                    }
                    fprintf(f, "\n");
                }
            }
            else
            {
                fprintf(f, "no\n");
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n\n---------------------\n\n\n");
    }

    if (listOfClasses.classNumber > 0)
    {
        fprintf(f, "Classes: \n");
        for (int i = 0; i < listOfClasses.classNumber; ++i)
        {
            fprintf(f, "%d) name: %s", (i + 1), listOfClasses.classTable[i].name);
            fprintf(f, " || line: %d\n", listOfClasses.classTable[i].line);
            fprintf(f, "***variables: ");
            if (listOfClasses.classTable[i].attribTable.varNumber > 0)
            {
                fprintf(f, "\n");
                for (int j = 0; j < listOfClasses.classTable[i].attribTable.varNumber; ++j)
                {
                    fprintf(f, ">>>>>> %d.%d) name: %s ", (i + 1), (j + 1), listOfClasses.classTable[i].attribTable.varTable[j].name);
                    fprintf(f, "|| type: ");
                    switch (listOfClasses.classTable[i].attribTable.varTable[j].t.mainType)
                    {
                        case 0:
                            fprintf(f, "integer");
                            break;
                        case 1:
                            fprintf(f, "float");
                            break;
                        case 2:
                            fprintf(f, "char");
                            break;
                        case 3:
                            fprintf(f, "string");
                            break;
                        case 4:
                            fprintf(f, "bool");
                            break;
                    }

                    if (listOfClasses.classTable[i].attribTable.varTable[j].t.isConst == 1)
                    {
                        fprintf(f, " || const");
                    }

                    if (listOfClasses.classTable[i].attribTable.varTable[j].t.isInit == 1)
                    {
                        fprintf(f, " || init");
                    }

                    if (listOfClasses.classTable[i].attribTable.varTable[j].t.isArray == 1)
                    {
                        fprintf(f, " || array of length: ");
                        char str[10];
                        sprintf(str, "%d", listOfClasses.classTable[i].attribTable.varTable[j].t.lengthOfArray);
                        fprintf(f, "%s", str);
                    }
                    fprintf(f, " || line: %d\n", listOfClasses.classTable[i].attribTable.varTable[j].line);
                }
            }
            else
            {
                fprintf(f, "no\n");
            }

            fprintf(f, "***methods: ");
            if (listOfClasses.classTable[i].methTable.funcNumber > 0)
            {
                fprintf(f, "\n");
                for (int j = 0; j < listOfClasses.classTable[i].methTable.funcNumber; ++j)
                {
                    fprintf(f, ">>>>>> %d.%d) name: %s ", (i + 1), (j + 1), listOfClasses.classTable[i].methTable.funcTable[j].name);
                    fprintf(f, "|| return type: ");
                    switch (listOfClasses.classTable[i].methTable.funcTable[j].returnType)
                    {
                        case 0:
                            fprintf(f, "integer");
                            break;
                        case 1:
                            fprintf(f, "float");
                            break;
                        case 2:
                            fprintf(f, "char");
                            break;
                        case 3:
                            fprintf(f, "string");
                            break;
                        case 4:
                            fprintf(f, "bool");
                    }
                    fprintf(f, " || line: %d", listOfClasses.classTable[i].methTable.funcTable[j].line);
                    fprintf(f, " || parameters: ");
                    if (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varNumber > 0)
                    {
                        fprintf(f, "\n");
                        for (int k = 0; k < listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varNumber; ++k)
                        {
                            fprintf(f, ">>>>>>>>> %d.%d.%d) name: %s ", (i + 1), (j + 1), (k + 1), listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].name);
                            fprintf(f, "|| type: ");
                            switch (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.mainType)
                            {
                                case 0:
                                    fprintf(f, "integer");
                                    break;
                                case 1:
                                    fprintf(f, "float");
                                    break;
                                case 2:
                                    fprintf(f, "char");
                                    break;
                                case 3:
                                    fprintf(f, "string");
                                    break;
                                case 4:
                                    fprintf(f, "bool");
                                    break;
                            }

                            if (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.isConst == 1)
                            {
                                fprintf(f, " || const ");
                            }

                            if (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.isArray == 1)
                            {
                                fprintf(f, " || array of length: ");
                                char str[10];
                                sprintf(str, "%d", listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.lengthOfArray);
                                fprintf(f, "%s", str);
                            }
                            fprintf(f, "\n");
                        }
                    }
                    else
                    {
                        fprintf(f, "no\n");
                    }
                }
            }
            else
            {
                fprintf(f, "no\n");
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n\n---------------------\n\n\n");
    }

    fclose(f);

    free_variables(&listOfVariables);
    free_functions(&listOfFunctions);
    free_classes(&listOfClasses);
    free_eval(&listOfEval);
}
