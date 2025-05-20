/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_COOKLANG_TAB_H_INCLUDED
# define YY_YY_COOKLANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 18 "cooklang.y"

  #include "ast.h"

#line 53 "cooklang.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NUMBER = 259,                  /* NUMBER  */
    ASSIGN = 260,                  /* ASSIGN  */
    PLUS = 261,                    /* PLUS  */
    MINUS = 262,                   /* MINUS  */
    TIMES = 263,                   /* TIMES  */
    DIVIDE = 264,                  /* DIVIDE  */
    EQ = 265,                      /* EQ  */
    NEQ = 266,                     /* NEQ  */
    LT = 267,                      /* LT  */
    LE = 268,                      /* LE  */
    GT = 269,                      /* GT  */
    GE = 270,                      /* GE  */
    LPAREN = 271,                  /* LPAREN  */
    RPAREN = 272,                  /* RPAREN  */
    SEMI = 273,                    /* SEMI  */
    SE = 274,                      /* SE  */
    ENTAO = 275,                   /* ENTAO  */
    ENQUANTO = 276,                /* ENQUANTO  */
    FACA = 277,                    /* FACA  */
    ADICIONE = 278,                /* ADICIONE  */
    MISTURE_ATE = 279,             /* MISTURE_ATE  */
    ASSE = 280,                    /* ASSE  */
    SIRVA = 281,                   /* SIRVA  */
    FORNO_QUENTE = 282,            /* FORNO_QUENTE  */
    MASSA_UNIFORME = 283,          /* MASSA_UNIFORME  */
    MASSA_LIQUIDA = 284,           /* MASSA_LIQUIDA  */
    FORNO_DESLIGADO = 285,         /* FORNO_DESLIGADO  */
    PRATO_PRONTO = 286             /* PRATO_PRONTO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "cooklang.y"

  int    num;
  char  *str;
  Expr  *expr;
  Stmt  *stmt;

#line 108 "cooklang.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_COOKLANG_TAB_H_INCLUDED  */
