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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    CALLOUT = 258,
    STRING = 259,
    ID = 260,
    CHAR_LITERAL = 261,
    DECIMAL_LITERAL = 262,
    BOOL_LITERAL = 263,
    HEX_LITERAL = 264,
    EQQ = 265,
    NQQ = 266,
    EQ = 267,
    AND = 268,
    OR = 269,
    LT = 270,
    GT = 271,
    LE = 272,
    GE = 273,
    ADD = 274,
    SUB = 275,
    MUL = 276,
    DIV = 277,
    MOD = 278,
    NOT = 279,
    OL = 280,
    CL = 281,
    OS = 282,
    CS = 283,
    CB = 284,
    OB = 285,
    CLASS = 286,
    PROGRAM = 287,
    TYPE = 288,
    SC = 289,
    COMMA = 290,
    VOID = 291,
    IF = 292,
    FOR = 293,
    BREAK = 294,
    CONTINUE = 295,
    ELSE = 296,
    RETURN = 297,
    PLUSONE = 298,
    SUBONE = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 9 "parser.y" /* yacc.c:1909  */

	char* stringType;

#line 103 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
