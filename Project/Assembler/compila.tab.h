/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
     NUMt = 258,
     ID = 259,
     DIR = 260,
     ADDt = 261,
     SUBt = 262,
     MULt = 263,
     DIVt = 264,
     ASGN = 265,
     OPEN = 266,
     CLOSE = 267,
     RETt = 268,
     EOL = 269,
     EQt = 270,
     NEt = 271,
     LTt = 272,
     LEt = 273,
     GTt = 274,
     GEt = 275,
     ABRE = 276,
     FECHA = 277,
     SEP = 278,
     IF = 279,
     WHILE = 280,
     FUNC = 281,
     ELSE = 282,
     FOR = 283,
     PRINT = 284,
     TERR = 285,
     CRI = 286,
     OCP = 287,
     BAS = 288,
     MOV = 289,
     ATKM = 290,
     ATKS = 291,
     ATKL = 292,
     COL = 293,
     DRP = 294,
     SEEt = 295,
     NEG = 296,
     PWR = 297
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 28 "compila.y"

  double val;
  /* symrec *cod; */
  char cod[30];
  char dir[2];



/* Line 1685 of yacc.c  */
#line 102 "compila.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


