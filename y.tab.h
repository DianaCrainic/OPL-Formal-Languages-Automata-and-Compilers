/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 84 "opl.y" /* yacc.c:1909  */

    int intval;
    char* strval;
    struct expr_info* expr_ptr;

#line 142 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
