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
    BEGIN_FNC = 266,
    END_FNC = 267,
    BEGIN_CALL = 268,
    END_CALL = 269,
    BEGIN_CLASS = 270,
    END_CLASS = 271,
    BEGIN_MAIN = 272,
    END_MAIN = 273,
    ID = 274,
    UNSIGNED_NUMBER = 275,
    INTEGER_NUMBER = 276,
    FLOAT_NUMBER = 277,
    STRING_VALUE = 278,
    BOOL_VALUE = 279,
    CHAR_VALUE = 280,
    FNC = 281,
    CALL = 282,
    CLASS = 283,
    PUBLIC = 284,
    PRIVATE = 285,
    PROTECTED = 286,
    RET = 287
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
#define BEGIN_FNC 266
#define END_FNC 267
#define BEGIN_CALL 268
#define END_CALL 269
#define BEGIN_CLASS 270
#define END_CLASS 271
#define BEGIN_MAIN 272
#define END_MAIN 273
#define ID 274
#define UNSIGNED_NUMBER 275
#define INTEGER_NUMBER 276
#define FLOAT_NUMBER 277
#define STRING_VALUE 278
#define BOOL_VALUE 279
#define CHAR_VALUE 280
#define FNC 281
#define CALL 282
#define CLASS 283
#define PUBLIC 284
#define PRIVATE 285
#define PROTECTED 286
#define RET 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
