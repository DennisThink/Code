/* Driver template for the LEMON parser generator.
** Copyright 1991-1995 by D. Richard Hipp.
*
* This version is specially modified for use with sqlite.
* @(#) $Id: lempar.c,v 1.1 2000/05/29 14:26:02 drh Exp $
*
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Library General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
** 
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.
** 
** You should have received a copy of the GNU Library General Public
** License along with this library; if not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA  02111-1307, USA.
**
** Modified 1997 to make it suitable for use with makeheaders.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#include <stdio.h>
#line 39 "parse.y"

#include "sqliteInt.h"
#include "parse.h"

#line 34 "parse.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    sqliteParserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is sqliteParserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.
**    sqliteParserARGDECL       is a declaration of a 3rd argument to the
**                       parser, or null if there is no extra argument.
**    sqliteParserKRARGDECL     A version of sqliteParserARGDECL for K&R C.
**    sqliteParserANSIARGDECL   A version of sqliteParserARGDECL for ANSI C.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
/*  */
#define YYCODETYPE unsigned char
#define YYNOCODE 130
#define YYACTIONTYPE int
#define sqliteParserTOKENTYPE Token
typedef union {
  sqliteParserTOKENTYPE yy0;
  ExprList* yy6;
  Expr* yy8;
  Select* yy27;
  IdList* yy34;
  int yy64;
  Token yy180;
  int yy259;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define sqliteParserARGDECL ,pParse
#define sqliteParserXARGDECL Parse *pParse;
#define sqliteParserANSIARGDECL ,Parse *pParse
#define YYNSTATE 305
#define YYNRULE 164
#define YYERRORSYMBOL 93
#define YYERRSYMDT yy259
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)
/* Next is the action table.  Each entry in this table contains
**
**  +  An integer which is the number representing the look-ahead
**     token
**
**  +  An integer indicating what action to take.  Number (N) between
**     0 and YYNSTATE-1 mean shift the look-ahead and go to state N.
**     Numbers between YYNSTATE and YYNSTATE+YYNRULE-1 mean reduce by
**     rule N-YYNSTATE.  Number YYNSTATE+YYNRULE means that a syntax
**     error has occurred.  Number YYNSTATE+YYNRULE+1 means the parser
**     accepts its input.
**
**  +  A pointer to the next entry with the same hash value.
**
** The action table is really a series of hash tables.  Each hash
** table contains a number of entries which is a power of two.  The
** "state" table (which follows) contains information about the starting
** point and size of each hash table.
*/
struct yyActionEntry {
  YYCODETYPE   lookahead;   /* The value of the look-ahead token */
  YYACTIONTYPE action;      /* Action to take for this look-ahead */
  struct yyActionEntry *next; /* Next look-ahead with the same hash, or NULL */
};
static struct yyActionEntry yyActionTable[] = {
/* State 0 */
  {  73, 244, 0                    }, /*                 UPDATE shift  244 */
  {  15, 222, 0                    }, /*                 CREATE shift  222 */
  {  83,   1, 0                    }, /*                cmdlist shift  1 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  39, 256, 0                    }, /*                 INSERT shift  256 */
  {YYNOCODE,0,0}, /* Unused */
  { 105, 470, &yyActionTable[   0] }, /*                  input accept */
  {YYNOCODE,0,0}, /* Unused */
  {  75, 291, 0                    }, /*                 VACUUM shift  291 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  14, 284, 0                    }, /*                   COPY shift  284 */
  { 111,  37, &yyActionTable[   1] }, /*              oneselect shift  37 */
  {YYNOCODE,0,0}, /* Unused */
  {  17, 240, 0                    }, /*                 DELETE shift  240 */
  {  82, 293, 0                    }, /*                    cmd shift  293 */
  { 115, 239, &yyActionTable[   2] }, /*                 select shift  239 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  22, 234, 0                    }, /*                   DROP shift  234 */
  {  23, 295, 0                    }, /*            END_OF_FILE shift  295 */
  {YYNOCODE,0,0}, /* Unused */
  {  89,   6, 0                    }, /*           create_table shift  6 */
  {  26, 294, 0                    }, /*                EXPLAIN shift  294 */
  {YYNOCODE,0,0}, /* Unused */
  {  92, 304, 0                    }, /*                   ecmd shift  304 */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  {  94,   4, 0                    }, /*                explain shift  4 */
  {YYNOCODE,0,0}, /* Unused */
/* State 1 */
  {  62,   2, &yyActionTable[  33] }, /*                   SEMI shift  2 */
  {   0, 305, 0                    }, /*                      $ reduce 0 */
/* State 2 */
  {  73, 244, 0                    }, /*                 UPDATE shift  244 */
  {  17, 240, 0                    }, /*                 DELETE shift  240 */
  {  82, 293, 0                    }, /*                    cmd shift  293 */
  { 115, 239, 0                    }, /*                 select shift  239 */
  {  14, 284, 0                    }, /*                   COPY shift  284 */
  {  15, 222, 0                    }, /*                 CREATE shift  222 */
  {  22, 234, 0                    }, /*                   DROP shift  234 */
  {  39, 256, 0                    }, /*                 INSERT shift  256 */
  {YYNOCODE,0,0}, /* Unused */
  {  89,   6, &yyActionTable[  34] }, /*           create_table shift  6 */
  {  26, 294, 0                    }, /*                EXPLAIN shift  294 */
  {  75, 291, 0                    }, /*                 VACUUM shift  291 */
  {  92,   3, 0                    }, /*                   ecmd shift  3 */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  {  94,   4, &yyActionTable[  38] }, /*                explain shift  4 */
  { 111,  37, &yyActionTable[  39] }, /*              oneselect shift  37 */
/* State 3 */
  {YYNOCODE,0,0}, /* Unused */
/* State 4 */
  {  73, 244, 0                    }, /*                 UPDATE shift  244 */
  {  17, 240, 0                    }, /*                 DELETE shift  240 */
  {  82,   5, 0                    }, /*                    cmd shift  5 */
  { 115, 239, 0                    }, /*                 select shift  239 */
  {  15, 222, 0                    }, /*                 CREATE shift  222 */
  {YYNOCODE,0,0}, /* Unused */
  {  22, 234, 0                    }, /*                   DROP shift  234 */
  {  39, 256, 0                    }, /*                 INSERT shift  256 */
  {YYNOCODE,0,0}, /* Unused */
  {  89,   6, &yyActionTable[  51] }, /*           create_table shift  6 */
  {YYNOCODE,0,0}, /* Unused */
  {  75, 291, 0                    }, /*                 VACUUM shift  291 */
  {YYNOCODE,0,0}, /* Unused */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  {  14, 284, 0                    }, /*                   COPY shift  284 */
  { 111,  37, &yyActionTable[  55] }, /*              oneselect shift  37 */
/* State 5 */
  {YYNOCODE,0,0}, /* Unused */
/* State 6 */
  {  90,   7, &yyActionTable[  69] }, /*      create_table_args shift  7 */
  {  48,   8, 0                    }, /*                     LP shift  8 */
/* State 7 */
  {YYNOCODE,0,0}, /* Unused */
/* State 8 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  {  85,  14, 0                    }, /*               columnid shift  14 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[  71] }, /*                 STRING shift  20 */
  {  84, 221, 0                    }, /*                 column shift  221 */
  { 101, 194, &yyActionTable[  72] }, /*                     id shift  194 */
  {  86,   9, 0                    }, /*             columnlist shift  9 */
  {YYNOCODE,0,0}, /* Unused */
/* State 9 */
  {  88,  10, &yyActionTable[  80] }, /*           conslist_opt shift  10 */
  {  60, 347, 0                    }, /*                     RP reduce 42 */
  {  10,  12, 0                    }, /*                  COMMA shift  12 */
  {YYNOCODE,0,0}, /* Unused */
/* State 10 */
  {  60,  11, 0                    }, /*                     RP shift  11 */
/* State 11 */
  {YYNOCODE,0,0}, /* Unused */
/* State 12 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  {  85,  14, 0                    }, /*               columnid shift  14 */
  {   8, 217, 0                    }, /*                  CHECK shift  217 */
  {  67,  20, &yyActionTable[  85] }, /*                 STRING shift  20 */
  {  84,  13, 0                    }, /*                 column shift  13 */
  { 101, 194, &yyActionTable[  86] }, /*                     id shift  194 */
  {  59, 201, 0                    }, /*                PRIMARY shift  201 */
  {  87, 195, 0                    }, /*               conslist shift  195 */
  {  72, 210, &yyActionTable[  87] }, /*                 UNIQUE shift  210 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  { 123, 220, &yyActionTable[  91] }, /*                  tcons shift  220 */
  { 124, 219, 0                    }, /*                 tcons2 shift  219 */
  {  13, 198, 0                    }, /*             CONSTRAINT shift  198 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 13 */
  {YYNOCODE,0,0}, /* Unused */
/* State 14 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 193, 0                    }, /*                     id shift  193 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[ 102] }, /*                 STRING shift  20 */
  {YYNOCODE,0,0}, /* Unused */
  { 125,  15, &yyActionTable[ 103] }, /*                   type shift  15 */
  { 126, 180, 0                    }, /*               typename shift  180 */
  {YYNOCODE,0,0}, /* Unused */
/* State 15 */
  {  80,  16, 0                    }, /*               carglist shift  16 */
/* State 16 */
  {  72,  30, &yyActionTable[ 113] }, /*                 UNIQUE shift  30 */
  {  81, 167, 0                    }, /*                  ccons shift  167 */
  {  16, 168, &yyActionTable[ 117] }, /*                DEFAULT shift  168 */
  {  59,  25, 0                    }, /*                PRIMARY shift  25 */
  {  52,  23, 0                    }, /*                    NOT shift  23 */
  {  13,  18, 0                    }, /*             CONSTRAINT shift  18 */
  {   8,  31, 0                    }, /*                  CHECK shift  31 */
  {  79,  17, 0                    }, /*                   carg shift  17 */
/* State 17 */
  {YYNOCODE,0,0}, /* Unused */
/* State 18 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101,  21, 0                    }, /*                     id shift  21 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[ 120] }, /*                 STRING shift  20 */
/* State 19 */
  {YYNOCODE,0,0}, /* Unused */
/* State 20 */
  {YYNOCODE,0,0}, /* Unused */
/* State 21 */
  {  72,  30, &yyActionTable[ 128] }, /*                 UNIQUE shift  30 */
  {  81,  22, 0                    }, /*                  ccons shift  22 */
  {   8,  31, 0                    }, /*                  CHECK shift  31 */
  {  59,  25, 0                    }, /*                PRIMARY shift  25 */
  {  52,  23, 0                    }, /*                    NOT shift  23 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 22 */
  {YYNOCODE,0,0}, /* Unused */
/* State 23 */
  {  54,  24, 0                    }, /*                   NULL shift  24 */
/* State 24 */
  {YYNOCODE,0,0}, /* Unused */
/* State 25 */
  {  45,  26, 0                    }, /*                    KEY shift  26 */
/* State 26 */
  {   5,  28, 0                    }, /*                    ASC shift  28 */
  { 121,  27, &yyActionTable[ 138] }, /*              sortorder shift  27 */
  {YYNOCODE,0,0}, /* Unused */
  {  19,  29, 0                    }, /*                   DESC shift  29 */
/* State 27 */
  {YYNOCODE,0,0}, /* Unused */
/* State 28 */
  {YYNOCODE,0,0}, /* Unused */
/* State 29 */
  {YYNOCODE,0,0}, /* Unused */
/* State 30 */
  {YYNOCODE,0,0}, /* Unused */
/* State 31 */
  {  48,  32, 0                    }, /*                     LP shift  32 */
/* State 32 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 148] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 165, 0                    }, /*                   expr shift  165 */
/* State 33 */
  {  64, 417, &yyActionTable[ 164] }, /*                  SLASH reduce 112 */
  {   0, 417, 0                    }, /*                      $ reduce 112 */
  {  66, 417, 0                    }, /*                   STAR reduce 112 */
  {  67, 417, &yyActionTable[ 171] }, /*                 STRING reduce 112 */
  {   4, 417, 0                    }, /*                     AS reduce 112 */
  {   5, 417, 0                    }, /*                    ASC reduce 112 */
  {   6, 417, 0                    }, /*                BETWEEN reduce 112 */
  {  71, 417, 0                    }, /*                  UNION reduce 112 */
  {   3, 417, 0                    }, /*                    AND reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  10, 417, 0                    }, /*                  COMMA reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  12, 417, 0                    }, /*                 CONCAT reduce 112 */
  {  77, 417, 0                    }, /*                  WHERE reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  19, 417, 0                    }, /*                   DESC reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  21, 320, 0                    }, /*                    DOT reduce 15 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24, 417, 0                    }, /*                     EQ reduce 112 */
  {  25, 417, 0                    }, /*                 EXCEPT reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  28, 417, 0                    }, /*                   FROM reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  30, 417, 0                    }, /*                     GE reduce 112 */
  {  31, 417, 0                    }, /*                   GLOB reduce 112 */
  {  32, 417, 0                    }, /*                  GROUP reduce 112 */
  {  33, 417, 0                    }, /*                     GT reduce 112 */
  {  34, 417, 0                    }, /*                 HAVING reduce 112 */
  {  35, 417, 0                    }, /*                     ID reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 417, 0                    }, /*                     IN reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  41, 417, 0                    }, /*              INTERSECT reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44, 417, 0                    }, /*                 ISNULL reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  46, 417, 0                    }, /*                     LE reduce 112 */
  {  47, 417, 0                    }, /*                   LIKE reduce 112 */
  {  48,  34, 0                    }, /*                     LP shift  34 */
  {  49, 417, 0                    }, /*                     LT reduce 112 */
  {  50, 417, 0                    }, /*                  MINUS reduce 112 */
  {  51, 417, 0                    }, /*                     NE reduce 112 */
  {  52, 417, 0                    }, /*                    NOT reduce 112 */
  {  53, 417, 0                    }, /*                NOTNULL reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56, 417, 0                    }, /*                     OR reduce 112 */
  {  57, 417, 0                    }, /*                  ORDER reduce 112 */
  {  58, 417, 0                    }, /*                   PLUS reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 417, 0                    }, /*                     RP reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
  {  62, 417, 0                    }, /*                   SEMI reduce 112 */
  {YYNOCODE,0,0}, /* Unused */
/* State 34 */
  {  96, 120, &yyActionTable[ 234] }, /*               expritem shift  120 */
  {  97, 161, 0                    }, /*               exprlist shift  161 */
  {  66, 163, &yyActionTable[ 236] }, /*                   STAR shift  163 */
  {  67,  35, &yyActionTable[ 239] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 109, 0                    }, /*                   expr shift  109 */
/* State 35 */
  {  64, 422, &yyActionTable[ 244] }, /*                  SLASH reduce 117 */
  {   0, 422, 0                    }, /*                      $ reduce 117 */
  {  66, 422, 0                    }, /*                   STAR reduce 117 */
  {  67, 422, &yyActionTable[ 251] }, /*                 STRING reduce 117 */
  {   4, 422, 0                    }, /*                     AS reduce 117 */
  {   5, 422, 0                    }, /*                    ASC reduce 117 */
  {   6, 422, 0                    }, /*                BETWEEN reduce 117 */
  {  71, 422, 0                    }, /*                  UNION reduce 117 */
  {   3, 422, 0                    }, /*                    AND reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  10, 422, 0                    }, /*                  COMMA reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  12, 422, 0                    }, /*                 CONCAT reduce 117 */
  {  77, 422, 0                    }, /*                  WHERE reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  19, 422, 0                    }, /*                   DESC reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  21, 321, 0                    }, /*                    DOT reduce 16 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24, 422, 0                    }, /*                     EQ reduce 117 */
  {  25, 422, 0                    }, /*                 EXCEPT reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  28, 422, 0                    }, /*                   FROM reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  30, 422, 0                    }, /*                     GE reduce 117 */
  {  31, 422, 0                    }, /*                   GLOB reduce 117 */
  {  32, 422, 0                    }, /*                  GROUP reduce 117 */
  {  33, 422, 0                    }, /*                     GT reduce 117 */
  {  34, 422, 0                    }, /*                 HAVING reduce 117 */
  {  35, 422, 0                    }, /*                     ID reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 422, 0                    }, /*                     IN reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  41, 422, 0                    }, /*              INTERSECT reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44, 422, 0                    }, /*                 ISNULL reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  46, 422, 0                    }, /*                     LE reduce 117 */
  {  47, 422, 0                    }, /*                   LIKE reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  49, 422, 0                    }, /*                     LT reduce 117 */
  {  50, 422, 0                    }, /*                  MINUS reduce 117 */
  {  51, 422, 0                    }, /*                     NE reduce 117 */
  {  52, 422, 0                    }, /*                    NOT reduce 117 */
  {  53, 422, 0                    }, /*                NOTNULL reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56, 422, 0                    }, /*                     OR reduce 117 */
  {  57, 422, 0                    }, /*                  ORDER reduce 117 */
  {  58, 422, 0                    }, /*                   PLUS reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 422, 0                    }, /*                     RP reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
  {  62, 422, 0                    }, /*                   SEMI reduce 117 */
  {YYNOCODE,0,0}, /* Unused */
/* State 36 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  67,  35, &yyActionTable[ 314] }, /*                 STRING shift  35 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  { 115,  38, &yyActionTable[ 308] }, /*                 select shift  38 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {  95, 159, 0                    }, /*                   expr shift  159 */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  {YYNOCODE,0,0}, /* Unused */
  { 111,  37, &yyActionTable[ 316] }, /*              oneselect shift  37 */
/* State 37 */
  {YYNOCODE,0,0}, /* Unused */
/* State 38 */
  {  25, 107, 0                    }, /*                 EXCEPT shift  107 */
  {  41, 106, &yyActionTable[ 324] }, /*              INTERSECT shift  106 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 158, 0                    }, /*                     RP shift  158 */
  {YYNOCODE,0,0}, /* Unused */
  { 110,  39, 0                    }, /*                 joinop shift  39 */
  {  71, 104, 0                    }, /*                  UNION shift  104 */
/* State 39 */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  { 111,  40, &yyActionTable[ 332] }, /*              oneselect shift  40 */
/* State 40 */
  {YYNOCODE,0,0}, /* Unused */
/* State 41 */
  {  20, 156, 0                    }, /*               DISTINCT shift  156 */
  {YYNOCODE,0,0}, /* Unused */
  {   2, 157, 0                    }, /*                    ALL shift  157 */
  {  91,  42, 0                    }, /*               distinct shift  42 */
/* State 42 */
  {  66, 151, 0                    }, /*                   STAR shift  151 */
  { 113, 152, 0                    }, /*                   sclp shift  152 */
  { 114,  43, &yyActionTable[ 339] }, /*             selcollist shift  43 */
  {YYNOCODE,0,0}, /* Unused */
/* State 43 */
  {  28, 143, 0                    }, /*                   FROM shift  143 */
  {  10, 142, 0                    }, /*                  COMMA shift  142 */
  {  98,  44, &yyActionTable[ 344] }, /*                   from shift  44 */
  {YYNOCODE,0,0}, /* Unused */
/* State 44 */
  { 128,  45, 0                    }, /*              where_opt shift  45 */
  {  77, 140, 0                    }, /*                  WHERE shift  140 */
/* State 45 */
  {  32, 137, 0                    }, /*                  GROUP shift  137 */
  {  99,  46, 0                    }, /*            groupby_opt shift  46 */
/* State 46 */
  { 100,  47, &yyActionTable[ 352] }, /*             having_opt shift  47 */
  {  34, 135, 0                    }, /*                 HAVING shift  135 */
/* State 47 */
  { 112,  48, 0                    }, /*            orderby_opt shift  48 */
  {  57,  49, 0                    }, /*                  ORDER shift  49 */
/* State 48 */
  {YYNOCODE,0,0}, /* Unused */
/* State 49 */
  {   7,  50, 0                    }, /*                     BY shift  50 */
/* State 50 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 358] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  { 119, 133, 0                    }, /*               sortitem shift  133 */
  { 120,  51, &yyActionTable[ 366] }, /*               sortlist shift  51 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  55, 0                    }, /*                   expr shift  55 */
/* State 51 */
  {  10,  52, 0                    }, /*                  COMMA shift  52 */
/* State 52 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 375] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  { 119,  53, 0                    }, /*               sortitem shift  53 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  55, 0                    }, /*                   expr shift  55 */
/* State 53 */
  {   5,  28, 0                    }, /*                    ASC shift  28 */
  { 121,  54, &yyActionTable[ 390] }, /*              sortorder shift  54 */
  {YYNOCODE,0,0}, /* Unused */
  {  19,  29, 0                    }, /*                   DESC shift  29 */
/* State 54 */
  {YYNOCODE,0,0}, /* Unused */
/* State 55 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[ 399] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[ 402] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 56 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 428] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  63, 0                    }, /*                   expr shift  63 */
/* State 57 */
  {YYNOCODE,0,0}, /* Unused */
/* State 58 */
  {  21,  59, 0                    }, /*                    DOT shift  59 */
/* State 59 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101,  60, 0                    }, /*                     id shift  60 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[ 445] }, /*                 STRING shift  20 */
/* State 60 */
  {YYNOCODE,0,0}, /* Unused */
/* State 61 */
  {YYNOCODE,0,0}, /* Unused */
/* State 62 */
  {YYNOCODE,0,0}, /* Unused */
/* State 63 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[ 455] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 64 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 485] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  65, 0                    }, /*                   expr shift  65 */
/* State 65 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[ 504] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 66 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 533] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  67, 0                    }, /*                   expr shift  67 */
/* State 67 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  58,  85, &yyActionTable[ 551] }, /*                   PLUS shift  85 */
  {  66,  89, &yyActionTable[ 549] }, /*                   STAR shift  89 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 68 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 557] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  69, 0                    }, /*                   expr shift  69 */
/* State 69 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  58,  85, &yyActionTable[ 575] }, /*                   PLUS shift  85 */
  {  66,  89, &yyActionTable[ 573] }, /*                   STAR shift  89 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 70 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 581] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  71, 0                    }, /*                   expr shift  71 */
/* State 71 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  58,  85, &yyActionTable[ 599] }, /*                   PLUS shift  85 */
  {  66,  89, &yyActionTable[ 597] }, /*                   STAR shift  89 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 72 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 605] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  73, 0                    }, /*                   expr shift  73 */
/* State 73 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  58,  85, &yyActionTable[ 623] }, /*                   PLUS shift  85 */
  {  66,  89, &yyActionTable[ 621] }, /*                   STAR shift  89 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 74 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 629] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  75, 0                    }, /*                   expr shift  75 */
/* State 75 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  49,  66, &yyActionTable[ 647] }, /*                     LT shift  66 */
  {  66,  89, &yyActionTable[ 648] }, /*                   STAR shift  89 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, &yyActionTable[ 649] }, /*                     LE shift  70 */
  {YYNOCODE,0,0}, /* Unused */
/* State 76 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 661] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  77, 0                    }, /*                   expr shift  77 */
/* State 77 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  49,  66, &yyActionTable[ 679] }, /*                     LT shift  66 */
  {  66,  89, &yyActionTable[ 680] }, /*                   STAR shift  89 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, &yyActionTable[ 681] }, /*                     LE shift  70 */
  {YYNOCODE,0,0}, /* Unused */
/* State 78 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 693] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  79, 0                    }, /*                   expr shift  79 */
/* State 79 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  49,  66, &yyActionTable[ 711] }, /*                     LT shift  66 */
  {  66,  89, &yyActionTable[ 712] }, /*                   STAR shift  89 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, &yyActionTable[ 713] }, /*                     LE shift  70 */
  {YYNOCODE,0,0}, /* Unused */
/* State 80 */
  {  31, 121, 0                    }, /*                   GLOB shift  121 */
  {  37, 127, 0                    }, /*                     IN shift  127 */
  {   6, 123, 0                    }, /*                BETWEEN shift  123 */
  {  47,  81, &yyActionTable[ 724] }, /*                   LIKE shift  81 */
/* State 81 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 729] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  82, 0                    }, /*                   expr shift  82 */
/* State 82 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[ 747] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 83 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 777] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  84, 0                    }, /*                   expr shift  84 */
/* State 84 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  49,  66, &yyActionTable[ 795] }, /*                     LT shift  66 */
  {  66,  89, &yyActionTable[ 796] }, /*                   STAR shift  89 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, &yyActionTable[ 797] }, /*                     LE shift  70 */
  {YYNOCODE,0,0}, /* Unused */
/* State 85 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 809] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  86, 0                    }, /*                   expr shift  86 */
/* State 86 */
  {  64,  91, &yyActionTable[ 825] }, /*                  SLASH shift  91 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {YYNOCODE,0,0}, /* Unused */
/* State 87 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 829] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  88, 0                    }, /*                   expr shift  88 */
/* State 88 */
  {  64,  91, &yyActionTable[ 845] }, /*                  SLASH shift  91 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {YYNOCODE,0,0}, /* Unused */
/* State 89 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 849] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  90, 0                    }, /*                   expr shift  90 */
/* State 90 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
/* State 91 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 866] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  92, 0                    }, /*                   expr shift  92 */
/* State 92 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
/* State 93 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 883] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  94, 0                    }, /*                   expr shift  94 */
/* State 94 */
  {YYNOCODE,0,0}, /* Unused */
/* State 95 */
  {YYNOCODE,0,0}, /* Unused */
/* State 96 */
  {YYNOCODE,0,0}, /* Unused */
/* State 97 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 902] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95,  98, 0                    }, /*                   expr shift  98 */
/* State 98 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  99, 0                    }, /*                    AND shift  99 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[ 921] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[ 924] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 99 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[ 950] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 100, 0                    }, /*                   expr shift  100 */
/* State 100 */
  {  64,  91, &yyActionTable[ 966] }, /*                  SLASH shift  91 */
  {   0, 448, 0                    }, /*                      $ reduce 143 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  67, 448, &yyActionTable[ 973] }, /*                 STRING reduce 143 */
  {   4, 448, 0                    }, /*                     AS reduce 143 */
  {   5, 448, 0                    }, /*                    ASC reduce 143 */
  {   6, 448, 0                    }, /*                BETWEEN reduce 143 */
  {  71, 448, 0                    }, /*                  UNION reduce 143 */
  {   3, 448, &yyActionTable[ 974] }, /*                    AND reduce 143 */
  {   3, 425, 0                    }, /*                    AND reduce 120 */
  {  10, 448, 0                    }, /*                  COMMA reduce 143 */
  {  56, 425, 0                    }, /*                     OR reduce 120 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  77, 448, 0                    }, /*                  WHERE reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  19, 448, 0                    }, /*                   DESC reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24, 448, 0                    }, /*                     EQ reduce 143 */
  {  25, 448, 0                    }, /*                 EXCEPT reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  28, 448, 0                    }, /*                   FROM reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31, 448, 0                    }, /*                   GLOB reduce 143 */
  {  32, 448, 0                    }, /*                  GROUP reduce 143 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  34, 448, 0                    }, /*                 HAVING reduce 143 */
  {  35, 448, 0                    }, /*                     ID reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 448, 0                    }, /*                     IN reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  41, 448, 0                    }, /*              INTERSECT reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44, 448, 0                    }, /*                 ISNULL reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47, 448, 0                    }, /*                   LIKE reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51, 448, 0                    }, /*                     NE reduce 143 */
  {  52, 448, 0                    }, /*                    NOT reduce 143 */
  {  53, 448, 0                    }, /*                NOTNULL reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56, 448, &yyActionTable[ 976] }, /*                     OR reduce 143 */
  {  57, 448, 0                    }, /*                  ORDER reduce 143 */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 448, 0                    }, /*                     RP reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
  {  62, 448, 0                    }, /*                   SEMI reduce 143 */
  {YYNOCODE,0,0}, /* Unused */
/* State 101 */
  {  48, 102, 0                    }, /*                     LP shift  102 */
/* State 102 */
  {  96, 120, &yyActionTable[1037] }, /*               expritem shift  120 */
  {  97, 116, 0                    }, /*               exprlist shift  116 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  { 115, 103, &yyActionTable[1039] }, /*                 select shift  103 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {  67,  35, &yyActionTable[1042] }, /*                 STRING shift  35 */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  {  95, 109, 0                    }, /*                   expr shift  109 */
  { 111,  37, &yyActionTable[1044] }, /*              oneselect shift  37 */
/* State 103 */
  {  25, 107, 0                    }, /*                 EXCEPT shift  107 */
  {  41, 106, &yyActionTable[1046] }, /*              INTERSECT shift  106 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 108, 0                    }, /*                     RP shift  108 */
  {YYNOCODE,0,0}, /* Unused */
  { 110,  39, 0                    }, /*                 joinop shift  39 */
  {  71, 104, 0                    }, /*                  UNION shift  104 */
/* State 104 */
  {   2, 105, 0                    }, /*                    ALL shift  105 */
  {  61, 362, 0                    }, /*                 SELECT reduce 57 */
/* State 105 */
  {  61, 363, 0                    }, /*                 SELECT reduce 58 */
/* State 106 */
  {  61, 364, 0                    }, /*                 SELECT reduce 59 */
/* State 107 */
  {  61, 365, 0                    }, /*                 SELECT reduce 60 */
/* State 108 */
  {YYNOCODE,0,0}, /* Unused */
/* State 109 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1064] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1067] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 110 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1093] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 111, 0                    }, /*                   expr shift  111 */
/* State 111 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1111] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 112 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1141] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 113, 0                    }, /*                   expr shift  113 */
/* State 113 */
  {YYNOCODE,0,0}, /* Unused */
/* State 114 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1158] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 115, 0                    }, /*                   expr shift  115 */
/* State 115 */
  {YYNOCODE,0,0}, /* Unused */
/* State 116 */
  {  60, 117, &yyActionTable[1175] }, /*                     RP shift  117 */
  {  10, 118, 0                    }, /*                  COMMA shift  118 */
/* State 117 */
  {YYNOCODE,0,0}, /* Unused */
/* State 118 */
  {  96, 119, &yyActionTable[1178] }, /*               expritem shift  119 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1184] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 109, 0                    }, /*                   expr shift  109 */
/* State 119 */
  {YYNOCODE,0,0}, /* Unused */
/* State 120 */
  {YYNOCODE,0,0}, /* Unused */
/* State 121 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1196] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 122, 0                    }, /*                   expr shift  122 */
/* State 122 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1214] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 123 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1244] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 124, 0                    }, /*                   expr shift  124 */
/* State 124 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3, 125, 0                    }, /*                    AND shift  125 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1263] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1266] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 125 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1292] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 126, 0                    }, /*                   expr shift  126 */
/* State 126 */
  {  64,  91, &yyActionTable[1308] }, /*                  SLASH shift  91 */
  {   0, 449, 0                    }, /*                      $ reduce 144 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  67, 449, &yyActionTable[1315] }, /*                 STRING reduce 144 */
  {   4, 449, 0                    }, /*                     AS reduce 144 */
  {   5, 449, 0                    }, /*                    ASC reduce 144 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  71, 449, 0                    }, /*                  UNION reduce 144 */
  {   3, 449, &yyActionTable[1316] }, /*                    AND reduce 144 */
  {   3, 425, 0                    }, /*                    AND reduce 120 */
  {  10, 449, 0                    }, /*                  COMMA reduce 144 */
  {  56, 425, 0                    }, /*                     OR reduce 120 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  77, 449, 0                    }, /*                  WHERE reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  19, 449, 0                    }, /*                   DESC reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {  25, 449, 0                    }, /*                 EXCEPT reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  28, 449, 0                    }, /*                   FROM reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
  {  32, 449, 0                    }, /*                  GROUP reduce 144 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  34, 449, 0                    }, /*                 HAVING reduce 144 */
  {  35, 449, 0                    }, /*                     ID reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  41, 449, 0                    }, /*              INTERSECT reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, 0                    }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56, 449, &yyActionTable[1318] }, /*                     OR reduce 144 */
  {  57, 449, 0                    }, /*                  ORDER reduce 144 */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 449, 0                    }, /*                     RP reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
  {  62, 449, 0                    }, /*                   SEMI reduce 144 */
  {YYNOCODE,0,0}, /* Unused */
/* State 127 */
  {  48, 128, 0                    }, /*                     LP shift  128 */
/* State 128 */
  {  96, 120, &yyActionTable[1379] }, /*               expritem shift  120 */
  {  97, 131, 0                    }, /*               exprlist shift  131 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  { 115, 129, &yyActionTable[1381] }, /*                 select shift  129 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {  67,  35, &yyActionTable[1384] }, /*                 STRING shift  35 */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  {  95, 109, 0                    }, /*                   expr shift  109 */
  { 111,  37, &yyActionTable[1386] }, /*              oneselect shift  37 */
/* State 129 */
  {  25, 107, 0                    }, /*                 EXCEPT shift  107 */
  {  41, 106, &yyActionTable[1388] }, /*              INTERSECT shift  106 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 130, 0                    }, /*                     RP shift  130 */
  {YYNOCODE,0,0}, /* Unused */
  { 110,  39, 0                    }, /*                 joinop shift  39 */
  {  71, 104, 0                    }, /*                  UNION shift  104 */
/* State 130 */
  {YYNOCODE,0,0}, /* Unused */
/* State 131 */
  {  60, 132, &yyActionTable[1398] }, /*                     RP shift  132 */
  {  10, 118, 0                    }, /*                  COMMA shift  118 */
/* State 132 */
  {YYNOCODE,0,0}, /* Unused */
/* State 133 */
  {   5,  28, 0                    }, /*                    ASC shift  28 */
  { 121, 134, &yyActionTable[1400] }, /*              sortorder shift  134 */
  {YYNOCODE,0,0}, /* Unused */
  {  19,  29, 0                    }, /*                   DESC shift  29 */
/* State 134 */
  {YYNOCODE,0,0}, /* Unused */
/* State 135 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1406] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 136, 0                    }, /*                   expr shift  136 */
/* State 136 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1425] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1428] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 137 */
  {   7, 138, 0                    }, /*                     BY shift  138 */
/* State 138 */
  {  96, 120, &yyActionTable[1461] }, /*               expritem shift  120 */
  {  97, 139, 0                    }, /*               exprlist shift  139 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1463] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 109, 0                    }, /*                   expr shift  109 */
/* State 139 */
  {  10, 118, 0                    }, /*                  COMMA shift  118 */
/* State 140 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1472] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 141, 0                    }, /*                   expr shift  141 */
/* State 141 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1491] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1494] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 142 */
  {YYNOCODE,0,0}, /* Unused */
/* State 143 */
  { 122, 146, &yyActionTable[1521] }, /*             stl_prefix shift  146 */
  { 116, 144, 0                    }, /*             seltablist shift  144 */
/* State 144 */
  {  10, 145, 0                    }, /*                  COMMA shift  145 */
/* State 145 */
  {YYNOCODE,0,0}, /* Unused */
/* State 146 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 147, 0                    }, /*                     id shift  147 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1524] }, /*                 STRING shift  20 */
/* State 147 */
  {  32, 380, &yyActionTable[1529] }, /*                  GROUP reduce 75 */
  {   0, 380, 0                    }, /*                      $ reduce 75 */
  {  34, 380, 0                    }, /*                 HAVING reduce 75 */
  {  67, 375, &yyActionTable[1533] }, /*                 STRING reduce 70 */
  {   4, 148, 0                    }, /*                     AS shift  148 */
  {  35, 375, 0                    }, /*                     ID reduce 70 */
  {  41, 380, &yyActionTable[1536] }, /*              INTERSECT reduce 75 */
  {  71, 380, 0                    }, /*                  UNION reduce 75 */
  {  25, 380, 0                    }, /*                 EXCEPT reduce 75 */
  {  57, 380, &yyActionTable[1534] }, /*                  ORDER reduce 75 */
  {  10, 380, 0                    }, /*                  COMMA reduce 75 */
  {  62, 380, 0                    }, /*                   SEMI reduce 75 */
  {  60, 380, 0                    }, /*                     RP reduce 75 */
  {  77, 380, 0                    }, /*                  WHERE reduce 75 */
  {  78, 149, &yyActionTable[1539] }, /*                     as shift  149 */
  {YYNOCODE,0,0}, /* Unused */
/* State 148 */
  {YYNOCODE,0,0}, /* Unused */
/* State 149 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 150, 0                    }, /*                     id shift  150 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1545] }, /*                 STRING shift  20 */
/* State 150 */
  {YYNOCODE,0,0}, /* Unused */
/* State 151 */
  {YYNOCODE,0,0}, /* Unused */
/* State 152 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1552] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 153, 0                    }, /*                   expr shift  153 */
/* State 153 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {  67, 375, &yyActionTable[1574] }, /*                 STRING reduce 70 */
  {   4, 148, 0                    }, /*                     AS shift  148 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  35, 375, &yyActionTable[1575] }, /*                     ID reduce 70 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  10, 373, 0                    }, /*                  COMMA reduce 68 */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  44,  95, &yyActionTable[1576] }, /*                 ISNULL shift  95 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {  78, 154, &yyActionTable[1578] }, /*                     as shift  154 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1580] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  28, 373, 0                    }, /*                   FROM reduce 68 */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 154 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 155, 0                    }, /*                     id shift  155 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1599] }, /*                 STRING shift  20 */
/* State 155 */
  {YYNOCODE,0,0}, /* Unused */
/* State 156 */
  {YYNOCODE,0,0}, /* Unused */
/* State 157 */
  {YYNOCODE,0,0}, /* Unused */
/* State 158 */
  {YYNOCODE,0,0}, /* Unused */
/* State 159 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1611] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1614] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 160, 0                    }, /*                     RP shift  160 */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 160 */
  {YYNOCODE,0,0}, /* Unused */
/* State 161 */
  {  60, 162, &yyActionTable[1641] }, /*                     RP shift  162 */
  {  10, 118, 0                    }, /*                  COMMA shift  118 */
/* State 162 */
  {YYNOCODE,0,0}, /* Unused */
/* State 163 */
  {  60, 164, 0                    }, /*                     RP shift  164 */
/* State 164 */
  {YYNOCODE,0,0}, /* Unused */
/* State 165 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1649] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1652] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {  60, 166, 0                    }, /*                     RP shift  166 */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 166 */
  {YYNOCODE,0,0}, /* Unused */
/* State 167 */
  {YYNOCODE,0,0}, /* Unused */
/* State 168 */
  {  40, 171, 0                    }, /*                INTEGER shift  171 */
  {  50, 175, 0                    }, /*                  MINUS shift  175 */
  {  58, 172, &yyActionTable[1680] }, /*                   PLUS shift  172 */
  {  67, 169, &yyActionTable[1683] }, /*                 STRING shift  169 */
  {  35, 170, &yyActionTable[1684] }, /*                     ID shift  170 */
  {  27, 178, 0                    }, /*                  FLOAT shift  178 */
  {  54, 179, 0                    }, /*                   NULL shift  179 */
  {YYNOCODE,0,0}, /* Unused */
/* State 169 */
  {YYNOCODE,0,0}, /* Unused */
/* State 170 */
  {YYNOCODE,0,0}, /* Unused */
/* State 171 */
  {YYNOCODE,0,0}, /* Unused */
/* State 172 */
  {  40, 173, 0                    }, /*                INTEGER shift  173 */
  {  27, 174, 0                    }, /*                  FLOAT shift  174 */
/* State 173 */
  {YYNOCODE,0,0}, /* Unused */
/* State 174 */
  {YYNOCODE,0,0}, /* Unused */
/* State 175 */
  {  40, 176, 0                    }, /*                INTEGER shift  176 */
  {  27, 177, 0                    }, /*                  FLOAT shift  177 */
/* State 176 */
  {YYNOCODE,0,0}, /* Unused */
/* State 177 */
  {YYNOCODE,0,0}, /* Unused */
/* State 178 */
  {YYNOCODE,0,0}, /* Unused */
/* State 179 */
  {YYNOCODE,0,0}, /* Unused */
/* State 180 */
  {  48, 181, 0                    }, /*                     LP shift  181 */
  { 101, 192, 0                    }, /*                     id shift  192 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  {  67,  20, &yyActionTable[1702] }, /*                 STRING shift  20 */
/* State 181 */
  {  40, 187, 0                    }, /*                INTEGER shift  187 */
  {  58, 188, &yyActionTable[1707] }, /*                   PLUS shift  188 */
  { 118, 182, &yyActionTable[1705] }, /*                 signed shift  182 */
  {  50, 190, 0                    }, /*                  MINUS shift  190 */
/* State 182 */
  {  60, 183, &yyActionTable[1709] }, /*                     RP shift  183 */
  {  10, 184, 0                    }, /*                  COMMA shift  184 */
/* State 183 */
  {YYNOCODE,0,0}, /* Unused */
/* State 184 */
  {  40, 187, 0                    }, /*                INTEGER shift  187 */
  {  58, 188, &yyActionTable[1714] }, /*                   PLUS shift  188 */
  { 118, 185, &yyActionTable[1712] }, /*                 signed shift  185 */
  {  50, 190, 0                    }, /*                  MINUS shift  190 */
/* State 185 */
  {  60, 186, 0                    }, /*                     RP shift  186 */
/* State 186 */
  {YYNOCODE,0,0}, /* Unused */
/* State 187 */
  {YYNOCODE,0,0}, /* Unused */
/* State 188 */
  {  40, 189, 0                    }, /*                INTEGER shift  189 */
/* State 189 */
  {YYNOCODE,0,0}, /* Unused */
/* State 190 */
  {  40, 191, 0                    }, /*                INTEGER shift  191 */
/* State 191 */
  {YYNOCODE,0,0}, /* Unused */
/* State 192 */
  {YYNOCODE,0,0}, /* Unused */
/* State 193 */
  {YYNOCODE,0,0}, /* Unused */
/* State 194 */
  {YYNOCODE,0,0}, /* Unused */
/* State 195 */
  {  60, 348, &yyActionTable[1726] }, /*                     RP reduce 43 */
  {  10, 196, 0                    }, /*                  COMMA shift  196 */
/* State 196 */
  {  72, 210, &yyActionTable[1728] }, /*                 UNIQUE shift  210 */
  {   8, 217, 0                    }, /*                  CHECK shift  217 */
  {  59, 201, 0                    }, /*                PRIMARY shift  201 */
  { 123, 197, &yyActionTable[1729] }, /*                  tcons shift  197 */
  { 124, 219, 0                    }, /*                 tcons2 shift  219 */
  {  13, 198, 0                    }, /*             CONSTRAINT shift  198 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
/* State 197 */
  {YYNOCODE,0,0}, /* Unused */
/* State 198 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 199, 0                    }, /*                     id shift  199 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1736] }, /*                 STRING shift  20 */
/* State 199 */
  { 124, 200, &yyActionTable[1741] }, /*                 tcons2 shift  200 */
  {  72, 210, &yyActionTable[1742] }, /*                 UNIQUE shift  210 */
  {   8, 217, 0                    }, /*                  CHECK shift  217 */
  {  59, 201, 0                    }, /*                PRIMARY shift  201 */
/* State 200 */
  {YYNOCODE,0,0}, /* Unused */
/* State 201 */
  {  45, 202, 0                    }, /*                    KEY shift  202 */
/* State 202 */
  {  48, 203, 0                    }, /*                     LP shift  203 */
/* State 203 */
  { 104, 204, 0                    }, /*                idxlist shift  204 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1748] }, /*                 STRING shift  20 */
  {YYNOCODE,0,0}, /* Unused */
  { 101, 208, 0                    }, /*                     id shift  208 */
  {YYNOCODE,0,0}, /* Unused */
  { 103, 209, 0                    }, /*                idxitem shift  209 */
/* State 204 */
  {  60, 205, &yyActionTable[1756] }, /*                     RP shift  205 */
  {  10, 206, 0                    }, /*                  COMMA shift  206 */
/* State 205 */
  {YYNOCODE,0,0}, /* Unused */
/* State 206 */
  {  67,  20, &yyActionTable[1760] }, /*                 STRING shift  20 */
  { 101, 208, 0                    }, /*                     id shift  208 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 103, 207, &yyActionTable[1758] }, /*                idxitem shift  207 */
/* State 207 */
  {YYNOCODE,0,0}, /* Unused */
/* State 208 */
  {YYNOCODE,0,0}, /* Unused */
/* State 209 */
  {YYNOCODE,0,0}, /* Unused */
/* State 210 */
  {  48, 211, 0                    }, /*                     LP shift  211 */
/* State 211 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 216, 0                    }, /*                     id shift  216 */
  { 102, 212, 0                    }, /*                 idlist shift  212 */
  {  67,  20, &yyActionTable[1766] }, /*                 STRING shift  20 */
/* State 212 */
  {  60, 213, &yyActionTable[1771] }, /*                     RP shift  213 */
  {  10, 214, 0                    }, /*                  COMMA shift  214 */
/* State 213 */
  {YYNOCODE,0,0}, /* Unused */
/* State 214 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 215, 0                    }, /*                     id shift  215 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1773] }, /*                 STRING shift  20 */
/* State 215 */
  {YYNOCODE,0,0}, /* Unused */
/* State 216 */
  {YYNOCODE,0,0}, /* Unused */
/* State 217 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1780] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 218, 0                    }, /*                   expr shift  218 */
/* State 218 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1799] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1802] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 219 */
  {YYNOCODE,0,0}, /* Unused */
/* State 220 */
  {YYNOCODE,0,0}, /* Unused */
/* State 221 */
  {YYNOCODE,0,0}, /* Unused */
/* State 222 */
  {  72, 233, &yyActionTable[1831] }, /*                 UNIQUE shift  233 */
  {  68, 223, 0                    }, /*                  TABLE shift  223 */
  {  38, 460, 0                    }, /*                  INDEX reduce 155 */
  { 127, 225, 0                    }, /*             uniqueflag shift  225 */
/* State 223 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 224, 0                    }, /*                     id shift  224 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1834] }, /*                 STRING shift  20 */
/* State 224 */
  {  48, 314, 0                    }, /*                     LP reduce 9 */
/* State 225 */
  {  38, 226, 0                    }, /*                  INDEX shift  226 */
/* State 226 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 227, 0                    }, /*                     id shift  227 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1840] }, /*                 STRING shift  20 */
/* State 227 */
  {  55, 228, 0                    }, /*                     ON shift  228 */
/* State 228 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 229, 0                    }, /*                     id shift  229 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1845] }, /*                 STRING shift  20 */
/* State 229 */
  {  48, 230, 0                    }, /*                     LP shift  230 */
/* State 230 */
  { 104, 231, 0                    }, /*                idxlist shift  231 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1851] }, /*                 STRING shift  20 */
  {YYNOCODE,0,0}, /* Unused */
  { 101, 208, 0                    }, /*                     id shift  208 */
  {YYNOCODE,0,0}, /* Unused */
  { 103, 209, 0                    }, /*                idxitem shift  209 */
/* State 231 */
  {  60, 232, &yyActionTable[1859] }, /*                     RP shift  232 */
  {  10, 206, 0                    }, /*                  COMMA shift  206 */
/* State 232 */
  {YYNOCODE,0,0}, /* Unused */
/* State 233 */
  {  38, 459, 0                    }, /*                  INDEX reduce 154 */
/* State 234 */
  {  68, 235, &yyActionTable[1863] }, /*                  TABLE shift  235 */
  {  38, 237, 0                    }, /*                  INDEX shift  237 */
/* State 235 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 236, 0                    }, /*                     id shift  236 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1864] }, /*                 STRING shift  20 */
/* State 236 */
  {YYNOCODE,0,0}, /* Unused */
/* State 237 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 238, 0                    }, /*                     id shift  238 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1869] }, /*                 STRING shift  20 */
/* State 238 */
  {YYNOCODE,0,0}, /* Unused */
/* State 239 */
  {  25, 107, 0                    }, /*                 EXCEPT shift  107 */
  {  41, 106, &yyActionTable[1874] }, /*              INTERSECT shift  106 */
  { 110,  39, 0                    }, /*                 joinop shift  39 */
  {  71, 104, 0                    }, /*                  UNION shift  104 */
/* State 240 */
  {  28, 241, 0                    }, /*                   FROM shift  241 */
/* State 241 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 242, 0                    }, /*                     id shift  242 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1879] }, /*                 STRING shift  20 */
/* State 242 */
  { 128, 243, 0                    }, /*              where_opt shift  243 */
  {  77, 140, 0                    }, /*                  WHERE shift  140 */
/* State 243 */
  {YYNOCODE,0,0}, /* Unused */
/* State 244 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 245, 0                    }, /*                     id shift  245 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1886] }, /*                 STRING shift  20 */
/* State 245 */
  {  63, 246, 0                    }, /*                    SET shift  246 */
/* State 246 */
  { 101, 253, 0                    }, /*                     id shift  253 */
  { 117, 247, &yyActionTable[1891] }, /*                setlist shift  247 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  {  67,  20, &yyActionTable[1893] }, /*                 STRING shift  20 */
/* State 247 */
  { 128, 248, 0                    }, /*              where_opt shift  248 */
  {  77, 140, 0                    }, /*                  WHERE shift  140 */
  {  10, 249, 0                    }, /*                  COMMA shift  249 */
  {YYNOCODE,0,0}, /* Unused */
/* State 248 */
  {YYNOCODE,0,0}, /* Unused */
/* State 249 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 250, 0                    }, /*                     id shift  250 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[1900] }, /*                 STRING shift  20 */
/* State 250 */
  {  24, 251, 0                    }, /*                     EQ shift  251 */
/* State 251 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1906] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 252, 0                    }, /*                   expr shift  252 */
/* State 252 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1925] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1928] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 253 */
  {  24, 254, 0                    }, /*                     EQ shift  254 */
/* State 254 */
  {  48,  36, 0                    }, /*                     LP shift  36 */
  {  35,  33, 0                    }, /*                     ID shift  33 */
  {  50, 112, 0                    }, /*                  MINUS shift  112 */
  {  67,  35, &yyActionTable[1955] }, /*                 STRING shift  35 */
  {  52, 110, 0                    }, /*                    NOT shift  110 */
  { 101,  58, 0                    }, /*                     id shift  58 */
  {  54,  57, 0                    }, /*                   NULL shift  57 */
  {YYNOCODE,0,0}, /* Unused */
  {  40,  61, 0                    }, /*                INTEGER shift  61 */
  {YYNOCODE,0,0}, /* Unused */
  {  58, 114, 0                    }, /*                   PLUS shift  114 */
  {  27,  62, 0                    }, /*                  FLOAT shift  62 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  95, 255, 0                    }, /*                   expr shift  255 */
/* State 255 */
  {  64,  91, 0                    }, /*                  SLASH shift  91 */
  {  33,  68, 0                    }, /*                     GT shift  68 */
  {  66,  89, 0                    }, /*                   STAR shift  89 */
  {   3,  56, 0                    }, /*                    AND shift  56 */
  {  12,  93, 0                    }, /*                 CONCAT shift  93 */
  {  37, 101, 0                    }, /*                     IN shift  101 */
  {   6,  97, 0                    }, /*                BETWEEN shift  97 */
  {  24,  76, 0                    }, /*                     EQ shift  76 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  44,  95, &yyActionTable[1974] }, /*                 ISNULL shift  95 */
  {YYNOCODE,0,0}, /* Unused */
  {  46,  70, 0                    }, /*                     LE shift  70 */
  {  47,  78, 0                    }, /*                   LIKE shift  78 */
  {YYNOCODE,0,0}, /* Unused */
  {  49,  66, 0                    }, /*                     LT shift  66 */
  {  50,  87, 0                    }, /*                  MINUS shift  87 */
  {  51,  74, 0                    }, /*                     NE shift  74 */
  {  52,  80, 0                    }, /*                    NOT shift  80 */
  {  53,  96, 0                    }, /*                NOTNULL shift  96 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  56,  64, &yyActionTable[1977] }, /*                     OR shift  64 */
  {YYNOCODE,0,0}, /* Unused */
  {  58,  85, 0                    }, /*                   PLUS shift  85 */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {YYNOCODE,0,0}, /* Unused */
  {  30,  72, 0                    }, /*                     GE shift  72 */
  {  31,  83, 0                    }, /*                   GLOB shift  83 */
/* State 256 */
  {  42, 257, 0                    }, /*                   INTO shift  257 */
/* State 257 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 258, 0                    }, /*                     id shift  258 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[2003] }, /*                 STRING shift  20 */
/* State 258 */
  {  48, 278, 0                    }, /*                     LP shift  278 */
  { 107, 259, 0                    }, /*         inscollist_opt shift  259 */
/* State 259 */
  {  76, 261, 0                    }, /*                 VALUES shift  261 */
  {  61,  41, 0                    }, /*                 SELECT shift  41 */
  { 111,  37, 0                    }, /*              oneselect shift  37 */
  { 115, 260, &yyActionTable[2011] }, /*                 select shift  260 */
/* State 260 */
  {  25, 107, 0                    }, /*                 EXCEPT shift  107 */
  {  41, 106, &yyActionTable[2013] }, /*              INTERSECT shift  106 */
  { 110,  39, 0                    }, /*                 joinop shift  39 */
  {  71, 104, 0                    }, /*                  UNION shift  104 */
/* State 261 */
  {  48, 262, 0                    }, /*                     LP shift  262 */
/* State 262 */
  {  40, 267, 0                    }, /*                INTEGER shift  267 */
  {  50, 271, 0                    }, /*                  MINUS shift  271 */
  {  58, 268, &yyActionTable[2019] }, /*                   PLUS shift  268 */
  {  67, 275, &yyActionTable[2025] }, /*                 STRING shift  275 */
  { 108, 277, 0                    }, /*                   item shift  277 */
  { 109, 263, 0                    }, /*               itemlist shift  263 */
  {  54, 276, 0                    }, /*                   NULL shift  276 */
  {  27, 274, 0                    }, /*                  FLOAT shift  274 */
/* State 263 */
  {  60, 264, &yyActionTable[2027] }, /*                     RP shift  264 */
  {  10, 265, 0                    }, /*                  COMMA shift  265 */
/* State 264 */
  {YYNOCODE,0,0}, /* Unused */
/* State 265 */
  {  40, 267, 0                    }, /*                INTEGER shift  267 */
  {  50, 271, 0                    }, /*                  MINUS shift  271 */
  {  58, 268, &yyActionTable[2030] }, /*                   PLUS shift  268 */
  {  67, 275, &yyActionTable[2034] }, /*                 STRING shift  275 */
  { 108, 266, 0                    }, /*                   item shift  266 */
  {  27, 274, 0                    }, /*                  FLOAT shift  274 */
  {  54, 276, 0                    }, /*                   NULL shift  276 */
  {YYNOCODE,0,0}, /* Unused */
/* State 266 */
  {YYNOCODE,0,0}, /* Unused */
/* State 267 */
  {YYNOCODE,0,0}, /* Unused */
/* State 268 */
  {  40, 269, 0                    }, /*                INTEGER shift  269 */
  {  27, 270, 0                    }, /*                  FLOAT shift  270 */
/* State 269 */
  {YYNOCODE,0,0}, /* Unused */
/* State 270 */
  {YYNOCODE,0,0}, /* Unused */
/* State 271 */
  {  40, 272, 0                    }, /*                INTEGER shift  272 */
  {  27, 273, 0                    }, /*                  FLOAT shift  273 */
/* State 272 */
  {YYNOCODE,0,0}, /* Unused */
/* State 273 */
  {YYNOCODE,0,0}, /* Unused */
/* State 274 */
  {YYNOCODE,0,0}, /* Unused */
/* State 275 */
  {YYNOCODE,0,0}, /* Unused */
/* State 276 */
  {YYNOCODE,0,0}, /* Unused */
/* State 277 */
  {YYNOCODE,0,0}, /* Unused */
/* State 278 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 283, 0                    }, /*                     id shift  283 */
  { 106, 279, 0                    }, /*             inscollist shift  279 */
  {  67,  20, &yyActionTable[2051] }, /*                 STRING shift  20 */
/* State 279 */
  {  60, 280, &yyActionTable[2056] }, /*                     RP shift  280 */
  {  10, 281, 0                    }, /*                  COMMA shift  281 */
/* State 280 */
  {YYNOCODE,0,0}, /* Unused */
/* State 281 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 282, 0                    }, /*                     id shift  282 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[2058] }, /*                 STRING shift  20 */
/* State 282 */
  {YYNOCODE,0,0}, /* Unused */
/* State 283 */
  {YYNOCODE,0,0}, /* Unused */
/* State 284 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 285, 0                    }, /*                     id shift  285 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[2064] }, /*                 STRING shift  20 */
/* State 285 */
  {  28, 286, 0                    }, /*                   FROM shift  286 */
/* State 286 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 287, 0                    }, /*                     id shift  287 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[2069] }, /*                 STRING shift  20 */
/* State 287 */
  {  74, 288, 0                    }, /*                  USING shift  288 */
/* State 288 */
  {  18, 289, 0                    }, /*             DELIMITERS shift  289 */
/* State 289 */
  {  67, 290, 0                    }, /*                 STRING shift  290 */
/* State 290 */
  {YYNOCODE,0,0}, /* Unused */
/* State 291 */
  {  35,  19, 0                    }, /*                     ID shift  19 */
  { 101, 292, 0                    }, /*                     id shift  292 */
  {YYNOCODE,0,0}, /* Unused */
  {  67,  20, &yyActionTable[2077] }, /*                 STRING shift  20 */
/* State 292 */
  {YYNOCODE,0,0}, /* Unused */
/* State 293 */
  {YYNOCODE,0,0}, /* Unused */
/* State 294 */
  {YYNOCODE,0,0}, /* Unused */
/* State 295 */
  {  36, 296, 0                    }, /*                ILLEGAL shift  296 */
/* State 296 */
  {  65, 297, 0                    }, /*                  SPACE shift  297 */
/* State 297 */
  {  70, 298, 0                    }, /*        UNCLOSED_STRING shift  298 */
/* State 298 */
  {  11, 299, 0                    }, /*                COMMENT shift  299 */
/* State 299 */
  {  29, 300, 0                    }, /*               FUNCTION shift  300 */
/* State 300 */
  {  69, 301, 0                    }, /*                 UMINUS shift  301 */
/* State 301 */
  {   9, 302, 0                    }, /*                 COLUMN shift  302 */
/* State 302 */
  {   1, 303, 0                    }, /*           AGG_FUNCTION shift  303 */
/* State 303 */
  {   0, 306, 0                    }, /*                      $ reduce 1 */
/* State 304 */
  {YYNOCODE,0,0}, /* Unused */
};

/* The state table contains information needed to look up the correct
** action in the action table, given the current state of the parser.
** Information needed includes:
**
**  +  A pointer to the start of the action hash table in yyActionTable.
**
**  +  A mask used to hash the look-ahead token.  The mask is an integer
**     which is one less than the size of the hash table.  
**
**  +  The default action.  This is the action to take if no entry for
**     the given look-ahead is found in the action hash table.
*/
struct yyStateEntry {
  struct yyActionEntry *hashtbl; /* Start of the hash table in yyActionTable */
  int mask;                      /* Mask used for hashing the look-ahead */
  YYACTIONTYPE actionDefault;    /* Default action if look-ahead not found */
};
static struct yyStateEntry yyStateTable[] = {
  { &yyActionTable[0], 31, 311},
  { &yyActionTable[32], 1, 469},
  { &yyActionTable[34], 15, 311},
  { &yyActionTable[50], 0, 308},
  { &yyActionTable[51], 15, 469},
  { &yyActionTable[67], 0, 309},
  { &yyActionTable[68], 1, 469},
  { &yyActionTable[70], 0, 313},
  { &yyActionTable[71], 7, 469},
  { &yyActionTable[79], 3, 469},
  { &yyActionTable[83], 0, 469},
  { &yyActionTable[84], 0, 315},
  { &yyActionTable[85], 15, 469},
  { &yyActionTable[101], 0, 316},
  { &yyActionTable[102], 7, 469},
  { &yyActionTable[110], 0, 331},
  { &yyActionTable[111], 7, 318},
  { &yyActionTable[119], 0, 330},
  { &yyActionTable[120], 3, 469},
  { &yyActionTable[124], 0, 320},
  { &yyActionTable[125], 0, 321},
  { &yyActionTable[126], 7, 469},
  { &yyActionTable[134], 0, 332},
  { &yyActionTable[135], 0, 469},
  { &yyActionTable[136], 0, 343},
  { &yyActionTable[137], 0, 469},
  { &yyActionTable[138], 3, 389},
  { &yyActionTable[142], 0, 344},
  { &yyActionTable[143], 0, 387},
  { &yyActionTable[144], 0, 388},
  { &yyActionTable[145], 0, 345},
  { &yyActionTable[146], 0, 469},
  { &yyActionTable[147], 15, 469},
  { &yyActionTable[163], 63, 469},
  { &yyActionTable[227], 15, 457},
  { &yyActionTable[243], 63, 469},
  { &yyActionTable[307], 15, 469},
  { &yyActionTable[323], 0, 360},
  { &yyActionTable[324], 7, 469},
  { &yyActionTable[332], 1, 469},
  { &yyActionTable[334], 0, 361},
  { &yyActionTable[335], 3, 369},
  { &yyActionTable[339], 3, 371},
  { &yyActionTable[343], 3, 469},
  { &yyActionTable[347], 1, 395},
  { &yyActionTable[349], 1, 390},
  { &yyActionTable[351], 1, 392},
  { &yyActionTable[353], 1, 382},
  { &yyActionTable[355], 0, 366},
  { &yyActionTable[356], 0, 469},
  { &yyActionTable[357], 15, 469},
  { &yyActionTable[373], 0, 383},
  { &yyActionTable[374], 15, 469},
  { &yyActionTable[390], 3, 389},
  { &yyActionTable[394], 0, 384},
  { &yyActionTable[395], 31, 386},
  { &yyActionTable[427], 15, 469},
  { &yyActionTable[443], 0, 418},
  { &yyActionTable[444], 0, 469},
  { &yyActionTable[445], 3, 469},
  { &yyActionTable[449], 0, 419},
  { &yyActionTable[450], 0, 420},
  { &yyActionTable[451], 0, 421},
  { &yyActionTable[452], 31, 425},
  { &yyActionTable[484], 15, 469},
  { &yyActionTable[500], 31, 426},
  { &yyActionTable[532], 15, 469},
  { &yyActionTable[548], 7, 427},
  { &yyActionTable[556], 15, 469},
  { &yyActionTable[572], 7, 428},
  { &yyActionTable[580], 15, 469},
  { &yyActionTable[596], 7, 429},
  { &yyActionTable[604], 15, 469},
  { &yyActionTable[620], 7, 430},
  { &yyActionTable[628], 15, 469},
  { &yyActionTable[644], 15, 431},
  { &yyActionTable[660], 15, 469},
  { &yyActionTable[676], 15, 432},
  { &yyActionTable[692], 15, 469},
  { &yyActionTable[708], 15, 433},
  { &yyActionTable[724], 3, 469},
  { &yyActionTable[728], 15, 469},
  { &yyActionTable[744], 31, 434},
  { &yyActionTable[776], 15, 469},
  { &yyActionTable[792], 15, 435},
  { &yyActionTable[808], 15, 469},
  { &yyActionTable[824], 3, 437},
  { &yyActionTable[828], 15, 469},
  { &yyActionTable[844], 3, 438},
  { &yyActionTable[848], 15, 469},
  { &yyActionTable[864], 0, 439},
  { &yyActionTable[865], 15, 469},
  { &yyActionTable[881], 0, 440},
  { &yyActionTable[882], 15, 469},
  { &yyActionTable[898], 0, 441},
  { &yyActionTable[899], 0, 442},
  { &yyActionTable[900], 0, 443},
  { &yyActionTable[901], 15, 469},
  { &yyActionTable[917], 31, 469},
  { &yyActionTable[949], 15, 469},
  { &yyActionTable[965], 63, 469},
  { &yyActionTable[1029], 0, 469},
  { &yyActionTable[1030], 15, 457},
  { &yyActionTable[1046], 7, 469},
  { &yyActionTable[1054], 1, 469},
  { &yyActionTable[1056], 0, 469},
  { &yyActionTable[1057], 0, 469},
  { &yyActionTable[1058], 0, 469},
  { &yyActionTable[1059], 0, 451},
  { &yyActionTable[1060], 31, 456},
  { &yyActionTable[1092], 15, 469},
  { &yyActionTable[1108], 31, 444},
  { &yyActionTable[1140], 15, 469},
  { &yyActionTable[1156], 0, 445},
  { &yyActionTable[1157], 15, 469},
  { &yyActionTable[1173], 0, 446},
  { &yyActionTable[1174], 1, 469},
  { &yyActionTable[1176], 0, 450},
  { &yyActionTable[1177], 15, 457},
  { &yyActionTable[1193], 0, 454},
  { &yyActionTable[1194], 0, 455},
  { &yyActionTable[1195], 15, 469},
  { &yyActionTable[1211], 31, 436},
  { &yyActionTable[1243], 15, 469},
  { &yyActionTable[1259], 31, 469},
  { &yyActionTable[1291], 15, 469},
  { &yyActionTable[1307], 63, 469},
  { &yyActionTable[1371], 0, 469},
  { &yyActionTable[1372], 15, 457},
  { &yyActionTable[1388], 7, 469},
  { &yyActionTable[1396], 0, 453},
  { &yyActionTable[1397], 1, 469},
  { &yyActionTable[1399], 0, 452},
  { &yyActionTable[1400], 3, 389},
  { &yyActionTable[1404], 0, 385},
  { &yyActionTable[1405], 15, 469},
  { &yyActionTable[1421], 31, 393},
  { &yyActionTable[1453], 0, 469},
  { &yyActionTable[1454], 15, 457},
  { &yyActionTable[1470], 0, 391},
  { &yyActionTable[1471], 15, 469},
  { &yyActionTable[1487], 31, 396},
  { &yyActionTable[1519], 0, 370},
  { &yyActionTable[1520], 1, 379},
  { &yyActionTable[1522], 0, 377},
  { &yyActionTable[1523], 0, 378},
  { &yyActionTable[1524], 3, 469},
  { &yyActionTable[1528], 15, 469},
  { &yyActionTable[1544], 0, 376},
  { &yyActionTable[1545], 3, 469},
  { &yyActionTable[1549], 0, 381},
  { &yyActionTable[1550], 0, 372},
  { &yyActionTable[1551], 15, 469},
  { &yyActionTable[1567], 31, 469},
  { &yyActionTable[1599], 3, 469},
  { &yyActionTable[1603], 0, 374},
  { &yyActionTable[1604], 0, 367},
  { &yyActionTable[1605], 0, 368},
  { &yyActionTable[1606], 0, 447},
  { &yyActionTable[1607], 31, 469},
  { &yyActionTable[1639], 0, 416},
  { &yyActionTable[1640], 1, 469},
  { &yyActionTable[1642], 0, 423},
  { &yyActionTable[1643], 0, 469},
  { &yyActionTable[1644], 0, 424},
  { &yyActionTable[1645], 31, 469},
  { &yyActionTable[1677], 0, 346},
  { &yyActionTable[1678], 0, 333},
  { &yyActionTable[1679], 7, 469},
  { &yyActionTable[1687], 0, 334},
  { &yyActionTable[1688], 0, 335},
  { &yyActionTable[1689], 0, 336},
  { &yyActionTable[1690], 1, 469},
  { &yyActionTable[1692], 0, 337},
  { &yyActionTable[1693], 0, 340},
  { &yyActionTable[1694], 1, 469},
  { &yyActionTable[1696], 0, 338},
  { &yyActionTable[1697], 0, 341},
  { &yyActionTable[1698], 0, 339},
  { &yyActionTable[1699], 0, 342},
  { &yyActionTable[1700], 3, 322},
  { &yyActionTable[1704], 3, 469},
  { &yyActionTable[1708], 1, 469},
  { &yyActionTable[1710], 0, 323},
  { &yyActionTable[1711], 3, 469},
  { &yyActionTable[1715], 0, 469},
  { &yyActionTable[1716], 0, 324},
  { &yyActionTable[1717], 0, 327},
  { &yyActionTable[1718], 0, 469},
  { &yyActionTable[1719], 0, 328},
  { &yyActionTable[1720], 0, 469},
  { &yyActionTable[1721], 0, 329},
  { &yyActionTable[1722], 0, 326},
  { &yyActionTable[1723], 0, 325},
  { &yyActionTable[1724], 0, 319},
  { &yyActionTable[1725], 1, 469},
  { &yyActionTable[1727], 7, 469},
  { &yyActionTable[1735], 0, 349},
  { &yyActionTable[1736], 3, 469},
  { &yyActionTable[1740], 3, 469},
  { &yyActionTable[1744], 0, 351},
  { &yyActionTable[1745], 0, 469},
  { &yyActionTable[1746], 0, 469},
  { &yyActionTable[1747], 7, 469},
  { &yyActionTable[1755], 1, 469},
  { &yyActionTable[1757], 0, 353},
  { &yyActionTable[1758], 3, 469},
  { &yyActionTable[1762], 0, 461},
  { &yyActionTable[1763], 0, 463},
  { &yyActionTable[1764], 0, 462},
  { &yyActionTable[1765], 0, 469},
  { &yyActionTable[1766], 3, 469},
  { &yyActionTable[1770], 1, 469},
  { &yyActionTable[1772], 0, 354},
  { &yyActionTable[1773], 3, 469},
  { &yyActionTable[1777], 0, 356},
  { &yyActionTable[1778], 0, 357},
  { &yyActionTable[1779], 15, 469},
  { &yyActionTable[1795], 31, 355},
  { &yyActionTable[1827], 0, 352},
  { &yyActionTable[1828], 0, 350},
  { &yyActionTable[1829], 0, 317},
  { &yyActionTable[1830], 3, 469},
  { &yyActionTable[1834], 3, 469},
  { &yyActionTable[1838], 0, 469},
  { &yyActionTable[1839], 0, 469},
  { &yyActionTable[1840], 3, 469},
  { &yyActionTable[1844], 0, 469},
  { &yyActionTable[1845], 3, 469},
  { &yyActionTable[1849], 0, 469},
  { &yyActionTable[1850], 7, 469},
  { &yyActionTable[1858], 1, 469},
  { &yyActionTable[1860], 0, 458},
  { &yyActionTable[1861], 0, 469},
  { &yyActionTable[1862], 1, 469},
  { &yyActionTable[1864], 3, 469},
  { &yyActionTable[1868], 0, 358},
  { &yyActionTable[1869], 3, 469},
  { &yyActionTable[1873], 0, 464},
  { &yyActionTable[1874], 3, 359},
  { &yyActionTable[1878], 0, 469},
  { &yyActionTable[1879], 3, 469},
  { &yyActionTable[1883], 1, 395},
  { &yyActionTable[1885], 0, 394},
  { &yyActionTable[1886], 3, 469},
  { &yyActionTable[1890], 0, 469},
  { &yyActionTable[1891], 3, 469},
  { &yyActionTable[1895], 3, 395},
  { &yyActionTable[1899], 0, 397},
  { &yyActionTable[1900], 3, 469},
  { &yyActionTable[1904], 0, 469},
  { &yyActionTable[1905], 15, 469},
  { &yyActionTable[1921], 31, 398},
  { &yyActionTable[1953], 0, 469},
  { &yyActionTable[1954], 15, 469},
  { &yyActionTable[1970], 31, 399},
  { &yyActionTable[2002], 0, 469},
  { &yyActionTable[2003], 3, 469},
  { &yyActionTable[2007], 1, 412},
  { &yyActionTable[2009], 3, 469},
  { &yyActionTable[2013], 3, 401},
  { &yyActionTable[2017], 0, 469},
  { &yyActionTable[2018], 7, 469},
  { &yyActionTable[2026], 1, 469},
  { &yyActionTable[2028], 0, 400},
  { &yyActionTable[2029], 7, 469},
  { &yyActionTable[2037], 0, 402},
  { &yyActionTable[2038], 0, 404},
  { &yyActionTable[2039], 1, 469},
  { &yyActionTable[2041], 0, 405},
  { &yyActionTable[2042], 0, 408},
  { &yyActionTable[2043], 1, 469},
  { &yyActionTable[2045], 0, 406},
  { &yyActionTable[2046], 0, 409},
  { &yyActionTable[2047], 0, 407},
  { &yyActionTable[2048], 0, 410},
  { &yyActionTable[2049], 0, 411},
  { &yyActionTable[2050], 0, 403},
  { &yyActionTable[2051], 3, 469},
  { &yyActionTable[2055], 1, 469},
  { &yyActionTable[2057], 0, 413},
  { &yyActionTable[2058], 3, 469},
  { &yyActionTable[2062], 0, 414},
  { &yyActionTable[2063], 0, 415},
  { &yyActionTable[2064], 3, 469},
  { &yyActionTable[2068], 0, 469},
  { &yyActionTable[2069], 3, 469},
  { &yyActionTable[2073], 0, 466},
  { &yyActionTable[2074], 0, 469},
  { &yyActionTable[2075], 0, 469},
  { &yyActionTable[2076], 0, 465},
  { &yyActionTable[2077], 3, 467},
  { &yyActionTable[2081], 0, 468},
  { &yyActionTable[2082], 0, 310},
  { &yyActionTable[2083], 0, 312},
  { &yyActionTable[2084], 0, 469},
  { &yyActionTable[2085], 0, 469},
  { &yyActionTable[2086], 0, 469},
  { &yyActionTable[2087], 0, 469},
  { &yyActionTable[2088], 0, 469},
  { &yyActionTable[2089], 0, 469},
  { &yyActionTable[2090], 0, 469},
  { &yyActionTable[2091], 0, 469},
  { &yyActionTable[2092], 0, 469},
  { &yyActionTable[2093], 0, 307},
};

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  int stateno;       /* The state-number */
  int major;         /* The major token value.  This is the code
                     ** number for the token at this stack level */
  YYMINORTYPE minor; /* The user-supplied minor token value.  This
                     ** is the value of the token  */
};

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int idx;                            /* Index of top element in stack */
  int errcnt;                         /* Shifts left before out of the error */
  struct yyStackEntry *top;           /* Pointer to the top stack element */
  struct yyStackEntry stack[YYSTACKDEPTH];  /* The parser's stack */
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;

/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
/* SQLITE MODIFICATION: Give the function file scope */
void sqliteParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}

/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static char *yyTokenName[] = { 
  "$",             "AGG_FUNCTION",  "ALL",           "AND",         
  "AS",            "ASC",           "BETWEEN",       "BY",          
  "CHECK",         "COLUMN",        "COMMA",         "COMMENT",     
  "CONCAT",        "CONSTRAINT",    "COPY",          "CREATE",      
  "DEFAULT",       "DELETE",        "DELIMITERS",    "DESC",        
  "DISTINCT",      "DOT",           "DROP",          "END_OF_FILE", 
  "EQ",            "EXCEPT",        "EXPLAIN",       "FLOAT",       
  "FROM",          "FUNCTION",      "GE",            "GLOB",        
  "GROUP",         "GT",            "HAVING",        "ID",          
  "ILLEGAL",       "IN",            "INDEX",         "INSERT",      
  "INTEGER",       "INTERSECT",     "INTO",          "IS",          
  "ISNULL",        "KEY",           "LE",            "LIKE",        
  "LP",            "LT",            "MINUS",         "NE",          
  "NOT",           "NOTNULL",       "NULL",          "ON",          
  "OR",            "ORDER",         "PLUS",          "PRIMARY",     
  "RP",            "SELECT",        "SEMI",          "SET",         
  "SLASH",         "SPACE",         "STAR",          "STRING",      
  "TABLE",         "UMINUS",        "UNCLOSED_STRING",  "UNION",       
  "UNIQUE",        "UPDATE",        "USING",         "VACUUM",      
  "VALUES",        "WHERE",         "as",            "carg",        
  "carglist",      "ccons",         "cmd",           "cmdlist",     
  "column",        "columnid",      "columnlist",    "conslist",    
  "conslist_opt",  "create_table",  "create_table_args",  "distinct",    
  "ecmd",          "error",         "explain",       "expr",        
  "expritem",      "exprlist",      "from",          "groupby_opt", 
  "having_opt",    "id",            "idlist",        "idxitem",     
  "idxlist",       "input",         "inscollist",    "inscollist_opt",
  "item",          "itemlist",      "joinop",        "oneselect",   
  "orderby_opt",   "sclp",          "selcollist",    "select",      
  "seltablist",    "setlist",       "signed",        "sortitem",    
  "sortlist",      "sortorder",     "stl_prefix",    "tcons",       
  "tcons2",        "type",          "typename",      "uniqueflag",  
  "where_opt",   
};
#define YYTRACE(X) if( yyTraceFILE ) fprintf(yyTraceFILE,"%sReduce [%s].\n",yyTracePrompt,X);
#else
#define YYTRACE(X)
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to sqliteParser and sqliteParserFree.
*/
/* SQLITE MODIFICATION: Give the function file scope */
void *sqliteParserAlloc(void *(*mallocProc)()){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( sizeof(yyParser), __FILE__, __LINE__ );
  if( pParser ){
    pParser->idx = -1;
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 95:
#line 302 "parse.y"
{sqliteExprDelete((yypminor->yy8));}
#line 3000 "parse.c"
      break;
    case 96:
#line 416 "parse.y"
{sqliteExprDelete((yypminor->yy8));}
#line 3005 "parse.c"
      break;
    case 97:
#line 414 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3010 "parse.c"
      break;
    case 98:
#line 188 "parse.y"
{sqliteIdListDelete((yypminor->yy34));}
#line 3015 "parse.c"
      break;
    case 99:
#line 224 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3020 "parse.c"
      break;
    case 100:
#line 229 "parse.y"
{sqliteExprDelete((yypminor->yy8));}
#line 3025 "parse.c"
      break;
    case 104:
#line 431 "parse.y"
{sqliteIdListDelete((yypminor->yy34));}
#line 3030 "parse.c"
      break;
    case 106:
#line 284 "parse.y"
{sqliteIdListDelete((yypminor->yy34));}
#line 3035 "parse.c"
      break;
    case 107:
#line 282 "parse.y"
{sqliteIdListDelete((yypminor->yy34));}
#line 3040 "parse.c"
      break;
    case 108:
#line 262 "parse.y"
{sqliteExprDelete((yypminor->yy8));}
#line 3045 "parse.c"
      break;
    case 109:
#line 260 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3050 "parse.c"
      break;
    case 111:
#line 140 "parse.y"
{sqliteSelectDelete((yypminor->yy27));}
#line 3055 "parse.c"
      break;
    case 112:
#line 199 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3060 "parse.c"
      break;
    case 113:
#line 173 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3065 "parse.c"
      break;
    case 114:
#line 171 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3070 "parse.c"
      break;
    case 115:
#line 138 "parse.y"
{sqliteSelectDelete((yypminor->yy27));}
#line 3075 "parse.c"
      break;
    case 116:
#line 184 "parse.y"
{sqliteIdListDelete((yypminor->yy34));}
#line 3080 "parse.c"
      break;
    case 117:
#line 244 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3085 "parse.c"
      break;
    case 119:
#line 203 "parse.y"
{sqliteExprDelete((yypminor->yy8));}
#line 3090 "parse.c"
      break;
    case 120:
#line 201 "parse.y"
{sqliteExprListDelete((yypminor->yy6));}
#line 3095 "parse.c"
      break;
    case 122:
#line 186 "parse.y"
{sqliteIdListDelete((yypminor->yy34));}
#line 3100 "parse.c"
      break;
    case 128:
#line 238 "parse.y"
{sqliteExprDelete((yypminor->yy8));}
#line 3105 "parse.c"
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;

  if( pParser->idx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->idx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[pParser->top->major]);
  }
#endif
  yymajor = pParser->top->major;
  yy_destructor( yymajor, &pParser->top->minor);
  pParser->idx--;
  pParser->top--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from sqliteParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
/* SQLITE MODIFICATION: Give the function file scope */
void sqliteParserFree(
  void *p,               /* The parser to be deleted */
  void (*freeProc)()     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->idx>=0 ) yy_pop_parser_stack(pParser);
  (*freeProc)(pParser, __FILE__, __LINE__);
}

/*
** Find the appropriate action for a parser given the look-ahead token.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_parser_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead             /* The look-ahead token */
){
  struct yyStateEntry *pState;   /* Appropriate entry in the state table */
  struct yyActionEntry *pAction; /* Action appropriate for the look-ahead */
 
  /* if( pParser->idx<0 ) return YY_NO_ACTION;  */
  pState = &yyStateTable[pParser->top->stateno];
  if( iLookAhead!=YYNOCODE ){
    pAction = &pState->hashtbl[iLookAhead & pState->mask];
    while( pAction ){
      if( pAction->lookahead==iLookAhead ) return pAction->action;
      pAction = pAction->next;
    }
  }else if( pState->mask!=0 || pState->hashtbl->lookahead!=YYNOCODE ){
    return YY_NO_ACTION;
  }
  return pState->actionDefault;
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer ot the minor token to shift in */
){
  yypParser->idx++;
  yypParser->top++;
  if( yypParser->idx>=YYSTACKDEPTH ){
     yypParser->idx--;
     yypParser->top--;
#ifndef NDEBUG
     if( yyTraceFILE ){
       fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
     }
#endif
     while( yypParser->idx>=0 ) yy_pop_parser_stack(yypParser);
     /* Here code is inserted which will execute if the parser
     ** stack every overflows */
     return;
  }
  yypParser->top->stateno = yyNewState;
  yypParser->top->major = yyMajor;
  yypParser->top->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->idx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->idx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->stack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 105, 1 },
  { 105, 9 },
  { 83, 1 },
  { 83, 3 },
  { 92, 2 },
  { 92, 1 },
  { 92, 0 },
  { 94, 1 },
  { 82, 2 },
  { 89, 3 },
  { 90, 4 },
  { 86, 3 },
  { 86, 1 },
  { 84, 3 },
  { 85, 1 },
  { 101, 1 },
  { 101, 1 },
  { 125, 1 },
  { 125, 4 },
  { 125, 6 },
  { 126, 1 },
  { 126, 2 },
  { 118, 1 },
  { 118, 2 },
  { 118, 2 },
  { 80, 2 },
  { 80, 0 },
  { 79, 3 },
  { 79, 1 },
  { 79, 2 },
  { 79, 2 },
  { 79, 2 },
  { 79, 3 },
  { 79, 3 },
  { 79, 2 },
  { 79, 3 },
  { 79, 3 },
  { 79, 2 },
  { 81, 2 },
  { 81, 3 },
  { 81, 1 },
  { 81, 4 },
  { 88, 0 },
  { 88, 2 },
  { 87, 3 },
  { 87, 1 },
  { 123, 3 },
  { 123, 1 },
  { 124, 5 },
  { 124, 4 },
  { 124, 2 },
  { 102, 3 },
  { 102, 1 },
  { 82, 3 },
  { 82, 1 },
  { 115, 1 },
  { 115, 3 },
  { 110, 1 },
  { 110, 2 },
  { 110, 1 },
  { 110, 1 },
  { 111, 8 },
  { 91, 1 },
  { 91, 1 },
  { 91, 0 },
  { 113, 2 },
  { 113, 0 },
  { 114, 1 },
  { 114, 2 },
  { 114, 4 },
  { 78, 0 },
  { 78, 1 },
  { 98, 2 },
  { 122, 2 },
  { 122, 0 },
  { 116, 2 },
  { 116, 4 },
  { 112, 0 },
  { 112, 3 },
  { 120, 4 },
  { 120, 2 },
  { 119, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 0 },
  { 99, 0 },
  { 99, 3 },
  { 100, 0 },
  { 100, 2 },
  { 82, 4 },
  { 128, 0 },
  { 128, 2 },
  { 82, 5 },
  { 117, 5 },
  { 117, 3 },
  { 82, 8 },
  { 82, 5 },
  { 109, 3 },
  { 109, 1 },
  { 108, 1 },
  { 108, 2 },
  { 108, 2 },
  { 108, 1 },
  { 108, 2 },
  { 108, 2 },
  { 108, 1 },
  { 108, 1 },
  { 107, 0 },
  { 107, 3 },
  { 106, 3 },
  { 106, 1 },
  { 95, 3 },
  { 95, 1 },
  { 95, 1 },
  { 95, 3 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 4 },
  { 95, 4 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 4 },
  { 95, 3 },
  { 95, 4 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 3 },
  { 95, 2 },
  { 95, 2 },
  { 95, 2 },
  { 95, 2 },
  { 95, 2 },
  { 95, 3 },
  { 95, 5 },
  { 95, 6 },
  { 95, 5 },
  { 95, 5 },
  { 95, 6 },
  { 95, 6 },
  { 97, 3 },
  { 97, 1 },
  { 96, 1 },
  { 96, 0 },
  { 82, 9 },
  { 127, 1 },
  { 127, 0 },
  { 104, 3 },
  { 104, 1 },
  { 103, 1 },
  { 82, 3 },
  { 82, 7 },
  { 82, 4 },
  { 82, 1 },
  { 82, 2 },
};

static void yy_accept();  /* Forward declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
  sqliteParserANSIARGDECL
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  struct yyStackEntry *yymsp;     /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  yymsp = yypParser->top;
  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **     YYTRACE("<text of the rule>");
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0:
        YYTRACE("input ::= cmdlist")
        /* No destructor defined for cmdlist */
        break;
      case 1:
        YYTRACE("input ::= END_OF_FILE ILLEGAL SPACE UNCLOSED_STRING COMMENT FUNCTION UMINUS COLUMN AGG_FUNCTION")
        /* No destructor defined for END_OF_FILE */
        /* No destructor defined for ILLEGAL */
        /* No destructor defined for SPACE */
        /* No destructor defined for UNCLOSED_STRING */
        /* No destructor defined for COMMENT */
        /* No destructor defined for FUNCTION */
        /* No destructor defined for UMINUS */
        /* No destructor defined for COLUMN */
        /* No destructor defined for AGG_FUNCTION */
        break;
      case 2:
        YYTRACE("cmdlist ::= ecmd")
        /* No destructor defined for ecmd */
        break;
      case 3:
        YYTRACE("cmdlist ::= cmdlist SEMI ecmd")
        /* No destructor defined for cmdlist */
        /* No destructor defined for SEMI */
        /* No destructor defined for ecmd */
        break;
      case 4:
        YYTRACE("ecmd ::= explain cmd")
#line 59 "parse.y"
{sqliteExec(pParse);}
#line 3457 "parse.c"
        /* No destructor defined for explain */
        /* No destructor defined for cmd */
        break;
      case 5:
        YYTRACE("ecmd ::= cmd")
#line 60 "parse.y"
{sqliteExec(pParse);}
#line 3465 "parse.c"
        /* No destructor defined for cmd */
        break;
      case 6:
        YYTRACE("ecmd ::=")
        break;
      case 7:
        YYTRACE("explain ::= EXPLAIN")
#line 62 "parse.y"
{pParse->explain = 1;}
#line 3475 "parse.c"
        /* No destructor defined for EXPLAIN */
        break;
      case 8:
        YYTRACE("cmd ::= create_table create_table_args")
        /* No destructor defined for create_table */
        /* No destructor defined for create_table_args */
        break;
      case 9:
        YYTRACE("create_table ::= CREATE TABLE id")
#line 67 "parse.y"
{sqliteStartTable(pParse,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy180);}
#line 3487 "parse.c"
        /* No destructor defined for TABLE */
        break;
      case 10:
        YYTRACE("create_table_args ::= LP columnlist conslist_opt RP")
#line 69 "parse.y"
{sqliteEndTable(pParse,&yymsp[0].minor.yy0);}
#line 3494 "parse.c"
        /* No destructor defined for LP */
        /* No destructor defined for columnlist */
        /* No destructor defined for conslist_opt */
        break;
      case 11:
        YYTRACE("columnlist ::= columnlist COMMA column")
        /* No destructor defined for columnlist */
        /* No destructor defined for COMMA */
        /* No destructor defined for column */
        break;
      case 12:
        YYTRACE("columnlist ::= column")
        /* No destructor defined for column */
        break;
      case 13:
        YYTRACE("column ::= columnid type carglist")
        /* No destructor defined for columnid */
        /* No destructor defined for type */
        /* No destructor defined for carglist */
        break;
      case 14:
        YYTRACE("columnid ::= id")
#line 78 "parse.y"
{sqliteAddColumn(pParse,&yymsp[0].minor.yy180);}
#line 3519 "parse.c"
        break;
      case 15:
        YYTRACE("id ::= ID")
#line 80 "parse.y"
{yygotominor.yy180 = yymsp[0].minor.yy0;}
#line 3525 "parse.c"
        break;
      case 16:
        YYTRACE("id ::= STRING")
#line 81 "parse.y"
{yygotominor.yy180 = yymsp[0].minor.yy0;}
#line 3531 "parse.c"
        break;
      case 17:
        YYTRACE("type ::= typename")
        /* No destructor defined for typename */
        break;
      case 18:
        YYTRACE("type ::= typename LP signed RP")
        /* No destructor defined for typename */
        /* No destructor defined for LP */
        /* No destructor defined for signed */
        /* No destructor defined for RP */
        break;
      case 19:
        YYTRACE("type ::= typename LP signed COMMA signed RP")
        /* No destructor defined for typename */
        /* No destructor defined for LP */
        /* No destructor defined for signed */
        /* No destructor defined for COMMA */
        /* No destructor defined for signed */
        /* No destructor defined for RP */
        break;
      case 20:
        YYTRACE("typename ::= id")
        /* No destructor defined for id */
        break;
      case 21:
        YYTRACE("typename ::= typename id")
        /* No destructor defined for typename */
        /* No destructor defined for id */
        break;
      case 22:
        YYTRACE("signed ::= INTEGER")
        /* No destructor defined for INTEGER */
        break;
      case 23:
        YYTRACE("signed ::= PLUS INTEGER")
        /* No destructor defined for PLUS */
        /* No destructor defined for INTEGER */
        break;
      case 24:
        YYTRACE("signed ::= MINUS INTEGER")
        /* No destructor defined for MINUS */
        /* No destructor defined for INTEGER */
        break;
      case 25:
        YYTRACE("carglist ::= carglist carg")
        /* No destructor defined for carglist */
        /* No destructor defined for carg */
        break;
      case 26:
        YYTRACE("carglist ::=")
        break;
      case 27:
        YYTRACE("carg ::= CONSTRAINT id ccons")
        /* No destructor defined for CONSTRAINT */
        /* No destructor defined for id */
        /* No destructor defined for ccons */
        break;
      case 28:
        YYTRACE("carg ::= ccons")
        /* No destructor defined for ccons */
        break;
      case 29:
        YYTRACE("carg ::= DEFAULT STRING")
#line 94 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,0);}
#line 3598 "parse.c"
        /* No destructor defined for DEFAULT */
        break;
      case 30:
        YYTRACE("carg ::= DEFAULT ID")
#line 95 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,0);}
#line 3605 "parse.c"
        /* No destructor defined for DEFAULT */
        break;
      case 31:
        YYTRACE("carg ::= DEFAULT INTEGER")
#line 96 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,0);}
#line 3612 "parse.c"
        /* No destructor defined for DEFAULT */
        break;
      case 32:
        YYTRACE("carg ::= DEFAULT PLUS INTEGER")
#line 97 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,0);}
#line 3619 "parse.c"
        /* No destructor defined for DEFAULT */
        /* No destructor defined for PLUS */
        break;
      case 33:
        YYTRACE("carg ::= DEFAULT MINUS INTEGER")
#line 98 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,1);}
#line 3627 "parse.c"
        /* No destructor defined for DEFAULT */
        /* No destructor defined for MINUS */
        break;
      case 34:
        YYTRACE("carg ::= DEFAULT FLOAT")
#line 99 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,0);}
#line 3635 "parse.c"
        /* No destructor defined for DEFAULT */
        break;
      case 35:
        YYTRACE("carg ::= DEFAULT PLUS FLOAT")
#line 100 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,0);}
#line 3642 "parse.c"
        /* No destructor defined for DEFAULT */
        /* No destructor defined for PLUS */
        break;
      case 36:
        YYTRACE("carg ::= DEFAULT MINUS FLOAT")
#line 101 "parse.y"
{sqliteAddDefaultValue(pParse,&yymsp[0].minor.yy0,1);}
#line 3650 "parse.c"
        /* No destructor defined for DEFAULT */
        /* No destructor defined for MINUS */
        break;
      case 37:
        YYTRACE("carg ::= DEFAULT NULL")
        /* No destructor defined for DEFAULT */
        /* No destructor defined for NULL */
        break;
      case 38:
        YYTRACE("ccons ::= NOT NULL")
        /* No destructor defined for NOT */
        /* No destructor defined for NULL */
        break;
      case 39:
        YYTRACE("ccons ::= PRIMARY KEY sortorder")
#line 107 "parse.y"
{sqliteCreateIndex(pParse,0,0,0,0,0);}
#line 3668 "parse.c"
        /* No destructor defined for PRIMARY */
        /* No destructor defined for KEY */
        /* No destructor defined for sortorder */
        break;
      case 40:
        YYTRACE("ccons ::= UNIQUE")
        /* No destructor defined for UNIQUE */
        break;
      case 41:
        YYTRACE("ccons ::= CHECK LP expr RP")
        /* No destructor defined for CHECK */
        /* No destructor defined for LP */
  yy_destructor(95,&yymsp[-1].minor);
        /* No destructor defined for RP */
        break;
      case 42:
        YYTRACE("conslist_opt ::=")
        break;
      case 43:
        YYTRACE("conslist_opt ::= COMMA conslist")
        /* No destructor defined for COMMA */
        /* No destructor defined for conslist */
        break;
      case 44:
        YYTRACE("conslist ::= conslist COMMA tcons")
        /* No destructor defined for conslist */
        /* No destructor defined for COMMA */
        /* No destructor defined for tcons */
        break;
      case 45:
        YYTRACE("conslist ::= tcons")
        /* No destructor defined for tcons */
        break;
      case 46:
        YYTRACE("tcons ::= CONSTRAINT id tcons2")
        /* No destructor defined for CONSTRAINT */
        /* No destructor defined for id */
        /* No destructor defined for tcons2 */
        break;
      case 47:
        YYTRACE("tcons ::= tcons2")
        /* No destructor defined for tcons2 */
        break;
      case 48:
        YYTRACE("tcons2 ::= PRIMARY KEY LP idxlist RP")
#line 120 "parse.y"
{sqliteCreateIndex(pParse,0,0,yymsp[-1].minor.yy34,0,0);}
#line 3716 "parse.c"
        /* No destructor defined for PRIMARY */
        /* No destructor defined for KEY */
        /* No destructor defined for LP */
        /* No destructor defined for RP */
        break;
      case 49:
        YYTRACE("tcons2 ::= UNIQUE LP idlist RP")
        /* No destructor defined for UNIQUE */
        /* No destructor defined for LP */
        /* No destructor defined for idlist */
        /* No destructor defined for RP */
        break;
      case 50:
        YYTRACE("tcons2 ::= CHECK expr")
        /* No destructor defined for CHECK */
  yy_destructor(95,&yymsp[0].minor);
        break;
      case 51:
        YYTRACE("idlist ::= idlist COMMA id")
        /* No destructor defined for idlist */
        /* No destructor defined for COMMA */
        /* No destructor defined for id */
        break;
      case 52:
        YYTRACE("idlist ::= id")
        /* No destructor defined for id */
        break;
      case 53:
        YYTRACE("cmd ::= DROP TABLE id")
#line 128 "parse.y"
{sqliteDropTable(pParse,&yymsp[0].minor.yy180);}
#line 3748 "parse.c"
        /* No destructor defined for DROP */
        /* No destructor defined for TABLE */
        break;
      case 54:
        YYTRACE("cmd ::= select")
#line 132 "parse.y"
{
  sqliteSelect(pParse, yymsp[0].minor.yy27, SRT_Callback, 0);
  sqliteSelectDelete(yymsp[0].minor.yy27);
}
#line 3759 "parse.c"
        break;
      case 55:
        YYTRACE("select ::= oneselect")
#line 142 "parse.y"
{yygotominor.yy27 = yymsp[0].minor.yy27;}
#line 3765 "parse.c"
        break;
      case 56:
        YYTRACE("select ::= select joinop oneselect")
#line 143 "parse.y"
{
    yymsp[0].minor.yy27->op = yymsp[-1].minor.yy64;
    yymsp[0].minor.yy27->pPrior = yymsp[-2].minor.yy27;
    yygotominor.yy27 = yymsp[0].minor.yy27;
}
#line 3775 "parse.c"
        break;
      case 57:
        YYTRACE("joinop ::= UNION")
#line 149 "parse.y"
{yygotominor.yy64 = TK_UNION;}
#line 3781 "parse.c"
        /* No destructor defined for UNION */
        break;
      case 58:
        YYTRACE("joinop ::= UNION ALL")
#line 150 "parse.y"
{yygotominor.yy64 = TK_ALL;}
#line 3788 "parse.c"
        /* No destructor defined for UNION */
        /* No destructor defined for ALL */
        break;
      case 59:
        YYTRACE("joinop ::= INTERSECT")
#line 151 "parse.y"
{yygotominor.yy64 = TK_INTERSECT;}
#line 3796 "parse.c"
        /* No destructor defined for INTERSECT */
        break;
      case 60:
        YYTRACE("joinop ::= EXCEPT")
#line 152 "parse.y"
{yygotominor.yy64 = TK_EXCEPT;}
#line 3803 "parse.c"
        /* No destructor defined for EXCEPT */
        break;
      case 61:
        YYTRACE("oneselect ::= SELECT distinct selcollist from where_opt groupby_opt having_opt orderby_opt")
#line 154 "parse.y"
{
  yygotominor.yy27 = sqliteSelectNew(yymsp[-5].minor.yy6,yymsp[-4].minor.yy34,yymsp[-3].minor.yy8,yymsp[-2].minor.yy6,yymsp[-1].minor.yy8,yymsp[0].minor.yy6,yymsp[-6].minor.yy64);
}
#line 3812 "parse.c"
        /* No destructor defined for SELECT */
        break;
      case 62:
        YYTRACE("distinct ::= DISTINCT")
#line 162 "parse.y"
{yygotominor.yy64 = 1;}
#line 3819 "parse.c"
        /* No destructor defined for DISTINCT */
        break;
      case 63:
        YYTRACE("distinct ::= ALL")
#line 163 "parse.y"
{yygotominor.yy64 = 0;}
#line 3826 "parse.c"
        /* No destructor defined for ALL */
        break;
      case 64:
        YYTRACE("distinct ::=")
#line 164 "parse.y"
{yygotominor.yy64 = 0;}
#line 3833 "parse.c"
        break;
      case 65:
        YYTRACE("sclp ::= selcollist COMMA")
#line 174 "parse.y"
{yygotominor.yy6 = yymsp[-1].minor.yy6;}
#line 3839 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 66:
        YYTRACE("sclp ::=")
#line 175 "parse.y"
{yygotominor.yy6 = 0;}
#line 3846 "parse.c"
        break;
      case 67:
        YYTRACE("selcollist ::= STAR")
#line 176 "parse.y"
{yygotominor.yy6 = 0;}
#line 3852 "parse.c"
        /* No destructor defined for STAR */
        break;
      case 68:
        YYTRACE("selcollist ::= sclp expr")
#line 177 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(yymsp[-1].minor.yy6,yymsp[0].minor.yy8,0);}
#line 3859 "parse.c"
        break;
      case 69:
        YYTRACE("selcollist ::= sclp expr as id")
#line 178 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(yymsp[-3].minor.yy6,yymsp[-2].minor.yy8,&yymsp[0].minor.yy180);}
#line 3865 "parse.c"
        /* No destructor defined for as */
        break;
      case 70:
        YYTRACE("as ::=")
        break;
      case 71:
        YYTRACE("as ::= AS")
        /* No destructor defined for AS */
        break;
      case 72:
        YYTRACE("from ::= FROM seltablist")
#line 190 "parse.y"
{yygotominor.yy34 = yymsp[0].minor.yy34;}
#line 3879 "parse.c"
        /* No destructor defined for FROM */
        break;
      case 73:
        YYTRACE("stl_prefix ::= seltablist COMMA")
#line 191 "parse.y"
{yygotominor.yy34 = yymsp[-1].minor.yy34;}
#line 3886 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 74:
        YYTRACE("stl_prefix ::=")
#line 192 "parse.y"
{yygotominor.yy34 = 0;}
#line 3893 "parse.c"
        break;
      case 75:
        YYTRACE("seltablist ::= stl_prefix id")
#line 193 "parse.y"
{yygotominor.yy34 = sqliteIdListAppend(yymsp[-1].minor.yy34,&yymsp[0].minor.yy180);}
#line 3899 "parse.c"
        break;
      case 76:
        YYTRACE("seltablist ::= stl_prefix id as id")
#line 195 "parse.y"
{yygotominor.yy34 = sqliteIdListAppend(yymsp[-3].minor.yy34,&yymsp[-2].minor.yy180);
    sqliteIdListAddAlias(yygotominor.yy34,&yymsp[0].minor.yy180);}
#line 3906 "parse.c"
        /* No destructor defined for as */
        break;
      case 77:
        YYTRACE("orderby_opt ::=")
#line 205 "parse.y"
{yygotominor.yy6 = 0;}
#line 3913 "parse.c"
        break;
      case 78:
        YYTRACE("orderby_opt ::= ORDER BY sortlist")
#line 206 "parse.y"
{yygotominor.yy6 = yymsp[0].minor.yy6;}
#line 3919 "parse.c"
        /* No destructor defined for ORDER */
        /* No destructor defined for BY */
        break;
      case 79:
        YYTRACE("sortlist ::= sortlist COMMA sortitem sortorder")
#line 207 "parse.y"
{
  yygotominor.yy6 = sqliteExprListAppend(yymsp[-3].minor.yy6,yymsp[-1].minor.yy8,0);
  yygotominor.yy6->a[yygotominor.yy6->nExpr-1].sortOrder = yymsp[0].minor.yy64;   /* 0 for ascending order, 1 for decending */
}
#line 3930 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 80:
        YYTRACE("sortlist ::= sortitem sortorder")
#line 211 "parse.y"
{
  yygotominor.yy6 = sqliteExprListAppend(0,yymsp[-1].minor.yy8,0);
  yygotominor.yy6->a[0].sortOrder = yymsp[0].minor.yy64;
}
#line 3940 "parse.c"
        break;
      case 81:
        YYTRACE("sortitem ::= expr")
#line 215 "parse.y"
{yygotominor.yy8 = yymsp[0].minor.yy8;}
#line 3946 "parse.c"
        break;
      case 82:
        YYTRACE("sortorder ::= ASC")
#line 219 "parse.y"
{yygotominor.yy64 = 0;}
#line 3952 "parse.c"
        /* No destructor defined for ASC */
        break;
      case 83:
        YYTRACE("sortorder ::= DESC")
#line 220 "parse.y"
{yygotominor.yy64 = 1;}
#line 3959 "parse.c"
        /* No destructor defined for DESC */
        break;
      case 84:
        YYTRACE("sortorder ::=")
#line 221 "parse.y"
{yygotominor.yy64 = 0;}
#line 3966 "parse.c"
        break;
      case 85:
        YYTRACE("groupby_opt ::=")
#line 225 "parse.y"
{yygotominor.yy6 = 0;}
#line 3972 "parse.c"
        break;
      case 86:
        YYTRACE("groupby_opt ::= GROUP BY exprlist")
#line 226 "parse.y"
{yygotominor.yy6 = yymsp[0].minor.yy6;}
#line 3978 "parse.c"
        /* No destructor defined for GROUP */
        /* No destructor defined for BY */
        break;
      case 87:
        YYTRACE("having_opt ::=")
#line 230 "parse.y"
{yygotominor.yy8 = 0;}
#line 3986 "parse.c"
        break;
      case 88:
        YYTRACE("having_opt ::= HAVING expr")
#line 231 "parse.y"
{yygotominor.yy8 = yymsp[0].minor.yy8;}
#line 3992 "parse.c"
        /* No destructor defined for HAVING */
        break;
      case 89:
        YYTRACE("cmd ::= DELETE FROM id where_opt")
#line 235 "parse.y"
{sqliteDeleteFrom(pParse, &yymsp[-1].minor.yy180, yymsp[0].minor.yy8);}
#line 3999 "parse.c"
        /* No destructor defined for DELETE */
        /* No destructor defined for FROM */
        break;
      case 90:
        YYTRACE("where_opt ::=")
#line 240 "parse.y"
{yygotominor.yy8 = 0;}
#line 4007 "parse.c"
        break;
      case 91:
        YYTRACE("where_opt ::= WHERE expr")
#line 241 "parse.y"
{yygotominor.yy8 = yymsp[0].minor.yy8;}
#line 4013 "parse.c"
        /* No destructor defined for WHERE */
        break;
      case 92:
        YYTRACE("cmd ::= UPDATE id SET setlist where_opt")
#line 247 "parse.y"
{sqliteUpdate(pParse,&yymsp[-3].minor.yy180,yymsp[-1].minor.yy6,yymsp[0].minor.yy8);}
#line 4020 "parse.c"
        /* No destructor defined for UPDATE */
        /* No destructor defined for SET */
        break;
      case 93:
        YYTRACE("setlist ::= setlist COMMA id EQ expr")
#line 250 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(yymsp[-4].minor.yy6,yymsp[0].minor.yy8,&yymsp[-2].minor.yy180);}
#line 4028 "parse.c"
        /* No destructor defined for COMMA */
        /* No destructor defined for EQ */
        break;
      case 94:
        YYTRACE("setlist ::= id EQ expr")
#line 251 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(0,yymsp[0].minor.yy8,&yymsp[-2].minor.yy180);}
#line 4036 "parse.c"
        /* No destructor defined for EQ */
        break;
      case 95:
        YYTRACE("cmd ::= INSERT INTO id inscollist_opt VALUES LP itemlist RP")
#line 254 "parse.y"
{sqliteInsert(pParse, &yymsp[-5].minor.yy180, yymsp[-1].minor.yy6, 0, yymsp[-4].minor.yy34);}
#line 4043 "parse.c"
        /* No destructor defined for INSERT */
        /* No destructor defined for INTO */
        /* No destructor defined for VALUES */
        /* No destructor defined for LP */
        /* No destructor defined for RP */
        break;
      case 96:
        YYTRACE("cmd ::= INSERT INTO id inscollist_opt select")
#line 256 "parse.y"
{sqliteInsert(pParse, &yymsp[-2].minor.yy180, 0, yymsp[0].minor.yy27, yymsp[-1].minor.yy34);}
#line 4054 "parse.c"
        /* No destructor defined for INSERT */
        /* No destructor defined for INTO */
        break;
      case 97:
        YYTRACE("itemlist ::= itemlist COMMA item")
#line 264 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(yymsp[-2].minor.yy6,yymsp[0].minor.yy8,0);}
#line 4062 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 98:
        YYTRACE("itemlist ::= item")
#line 265 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(0,yymsp[0].minor.yy8,0);}
#line 4069 "parse.c"
        break;
      case 99:
        YYTRACE("item ::= INTEGER")
#line 266 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_INTEGER, 0, 0, &yymsp[0].minor.yy0);}
#line 4075 "parse.c"
        break;
      case 100:
        YYTRACE("item ::= PLUS INTEGER")
#line 267 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_INTEGER, 0, 0, &yymsp[0].minor.yy0);}
#line 4081 "parse.c"
        /* No destructor defined for PLUS */
        break;
      case 101:
        YYTRACE("item ::= MINUS INTEGER")
#line 268 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_UMINUS, 0, 0, 0);
  yygotominor.yy8->pLeft = sqliteExpr(TK_INTEGER, 0, 0, &yymsp[0].minor.yy0);
}
#line 4091 "parse.c"
        /* No destructor defined for MINUS */
        break;
      case 102:
        YYTRACE("item ::= FLOAT")
#line 272 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_FLOAT, 0, 0, &yymsp[0].minor.yy0);}
#line 4098 "parse.c"
        break;
      case 103:
        YYTRACE("item ::= PLUS FLOAT")
#line 273 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_FLOAT, 0, 0, &yymsp[0].minor.yy0);}
#line 4104 "parse.c"
        /* No destructor defined for PLUS */
        break;
      case 104:
        YYTRACE("item ::= MINUS FLOAT")
#line 274 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_UMINUS, 0, 0, 0);
  yygotominor.yy8->pLeft = sqliteExpr(TK_FLOAT, 0, 0, &yymsp[0].minor.yy0);
}
#line 4114 "parse.c"
        /* No destructor defined for MINUS */
        break;
      case 105:
        YYTRACE("item ::= STRING")
#line 278 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_STRING, 0, 0, &yymsp[0].minor.yy0);}
#line 4121 "parse.c"
        break;
      case 106:
        YYTRACE("item ::= NULL")
#line 279 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_NULL, 0, 0, 0);}
#line 4127 "parse.c"
        /* No destructor defined for NULL */
        break;
      case 107:
        YYTRACE("inscollist_opt ::=")
#line 286 "parse.y"
{yygotominor.yy34 = 0;}
#line 4134 "parse.c"
        break;
      case 108:
        YYTRACE("inscollist_opt ::= LP inscollist RP")
#line 287 "parse.y"
{yygotominor.yy34 = yymsp[-1].minor.yy34;}
#line 4140 "parse.c"
        /* No destructor defined for LP */
        /* No destructor defined for RP */
        break;
      case 109:
        YYTRACE("inscollist ::= inscollist COMMA id")
#line 288 "parse.y"
{yygotominor.yy34 = sqliteIdListAppend(yymsp[-2].minor.yy34,&yymsp[0].minor.yy180);}
#line 4148 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 110:
        YYTRACE("inscollist ::= id")
#line 289 "parse.y"
{yygotominor.yy34 = sqliteIdListAppend(0,&yymsp[0].minor.yy180);}
#line 4155 "parse.c"
        break;
      case 111:
        YYTRACE("expr ::= LP expr RP")
#line 304 "parse.y"
{yygotominor.yy8 = yymsp[-1].minor.yy8; sqliteExprSpan(yygotominor.yy8,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);}
#line 4161 "parse.c"
        break;
      case 112:
        YYTRACE("expr ::= ID")
#line 305 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 4167 "parse.c"
        break;
      case 113:
        YYTRACE("expr ::= NULL")
#line 306 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_NULL, 0, 0, &yymsp[0].minor.yy0);}
#line 4173 "parse.c"
        break;
      case 114:
        YYTRACE("expr ::= id DOT id")
#line 307 "parse.y"
{
  Expr *temp1 = sqliteExpr(TK_ID, 0, 0, &yymsp[-2].minor.yy180);
  Expr *temp2 = sqliteExpr(TK_ID, 0, 0, &yymsp[0].minor.yy180);
  yygotominor.yy8 = sqliteExpr(TK_DOT, temp1, temp2, 0);
}
#line 4183 "parse.c"
        /* No destructor defined for DOT */
        break;
      case 115:
        YYTRACE("expr ::= INTEGER")
#line 312 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_INTEGER, 0, 0, &yymsp[0].minor.yy0);}
#line 4190 "parse.c"
        break;
      case 116:
        YYTRACE("expr ::= FLOAT")
#line 313 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_FLOAT, 0, 0, &yymsp[0].minor.yy0);}
#line 4196 "parse.c"
        break;
      case 117:
        YYTRACE("expr ::= STRING")
#line 314 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_STRING, 0, 0, &yymsp[0].minor.yy0);}
#line 4202 "parse.c"
        break;
      case 118:
        YYTRACE("expr ::= ID LP exprlist RP")
#line 315 "parse.y"
{
  yygotominor.yy8 = sqliteExprFunction(yymsp[-1].minor.yy6, &yymsp[-3].minor.yy0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 4211 "parse.c"
        /* No destructor defined for LP */
        break;
      case 119:
        YYTRACE("expr ::= ID LP STAR RP")
#line 319 "parse.y"
{
  yygotominor.yy8 = sqliteExprFunction(0, &yymsp[-3].minor.yy0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 4221 "parse.c"
        /* No destructor defined for LP */
        /* No destructor defined for STAR */
        break;
      case 120:
        YYTRACE("expr ::= expr AND expr")
#line 323 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_AND, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4229 "parse.c"
        /* No destructor defined for AND */
        break;
      case 121:
        YYTRACE("expr ::= expr OR expr")
#line 324 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_OR, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4236 "parse.c"
        /* No destructor defined for OR */
        break;
      case 122:
        YYTRACE("expr ::= expr LT expr")
#line 325 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_LT, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4243 "parse.c"
        /* No destructor defined for LT */
        break;
      case 123:
        YYTRACE("expr ::= expr GT expr")
#line 326 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_GT, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4250 "parse.c"
        /* No destructor defined for GT */
        break;
      case 124:
        YYTRACE("expr ::= expr LE expr")
#line 327 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_LE, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4257 "parse.c"
        /* No destructor defined for LE */
        break;
      case 125:
        YYTRACE("expr ::= expr GE expr")
#line 328 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_GE, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4264 "parse.c"
        /* No destructor defined for GE */
        break;
      case 126:
        YYTRACE("expr ::= expr NE expr")
#line 329 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_NE, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4271 "parse.c"
        /* No destructor defined for NE */
        break;
      case 127:
        YYTRACE("expr ::= expr EQ expr")
#line 330 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_EQ, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4278 "parse.c"
        /* No destructor defined for EQ */
        break;
      case 128:
        YYTRACE("expr ::= expr LIKE expr")
#line 331 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_LIKE, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4285 "parse.c"
        /* No destructor defined for LIKE */
        break;
      case 129:
        YYTRACE("expr ::= expr NOT LIKE expr")
#line 332 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_LIKE, yymsp[-3].minor.yy8, yymsp[0].minor.yy8, 0);
  yygotominor.yy8 = sqliteExpr(TK_NOT, yygotominor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-3].minor.yy8->span,&yymsp[0].minor.yy8->span);
}
#line 4296 "parse.c"
        /* No destructor defined for NOT */
        /* No destructor defined for LIKE */
        break;
      case 130:
        YYTRACE("expr ::= expr GLOB expr")
#line 337 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_GLOB,yymsp[-2].minor.yy8,yymsp[0].minor.yy8,0);}
#line 4304 "parse.c"
        /* No destructor defined for GLOB */
        break;
      case 131:
        YYTRACE("expr ::= expr NOT GLOB expr")
#line 338 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_GLOB, yymsp[-3].minor.yy8, yymsp[0].minor.yy8, 0);
  yygotominor.yy8 = sqliteExpr(TK_NOT, yygotominor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-3].minor.yy8->span,&yymsp[0].minor.yy8->span);
}
#line 4315 "parse.c"
        /* No destructor defined for NOT */
        /* No destructor defined for GLOB */
        break;
      case 132:
        YYTRACE("expr ::= expr PLUS expr")
#line 343 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_PLUS, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4323 "parse.c"
        /* No destructor defined for PLUS */
        break;
      case 133:
        YYTRACE("expr ::= expr MINUS expr")
#line 344 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_MINUS, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4330 "parse.c"
        /* No destructor defined for MINUS */
        break;
      case 134:
        YYTRACE("expr ::= expr STAR expr")
#line 345 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_STAR, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4337 "parse.c"
        /* No destructor defined for STAR */
        break;
      case 135:
        YYTRACE("expr ::= expr SLASH expr")
#line 346 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_SLASH, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4344 "parse.c"
        /* No destructor defined for SLASH */
        break;
      case 136:
        YYTRACE("expr ::= expr CONCAT expr")
#line 347 "parse.y"
{yygotominor.yy8 = sqliteExpr(TK_CONCAT, yymsp[-2].minor.yy8, yymsp[0].minor.yy8, 0);}
#line 4351 "parse.c"
        /* No destructor defined for CONCAT */
        break;
      case 137:
        YYTRACE("expr ::= expr ISNULL")
#line 348 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_ISNULL, yymsp[-1].minor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-1].minor.yy8->span,&yymsp[0].minor.yy0);
}
#line 4361 "parse.c"
        break;
      case 138:
        YYTRACE("expr ::= expr NOTNULL")
#line 352 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_NOTNULL, yymsp[-1].minor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-1].minor.yy8->span,&yymsp[0].minor.yy0);
}
#line 4370 "parse.c"
        break;
      case 139:
        YYTRACE("expr ::= NOT expr")
#line 356 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_NOT, yymsp[0].minor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy8->span);
}
#line 4379 "parse.c"
        break;
      case 140:
        YYTRACE("expr ::= MINUS expr")
#line 360 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_UMINUS, yymsp[0].minor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy8->span);
}
#line 4388 "parse.c"
        break;
      case 141:
        YYTRACE("expr ::= PLUS expr")
#line 364 "parse.y"
{
  yygotominor.yy8 = yymsp[0].minor.yy8;
  sqliteExprSpan(yygotominor.yy8,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy8->span);
}
#line 4397 "parse.c"
        break;
      case 142:
        YYTRACE("expr ::= LP select RP")
#line 368 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_SELECT, 0, 0, 0);
  yygotominor.yy8->pSelect = yymsp[-1].minor.yy27;
  sqliteExprSpan(yygotominor.yy8,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
}
#line 4407 "parse.c"
        break;
      case 143:
        YYTRACE("expr ::= expr BETWEEN expr AND expr")
#line 373 "parse.y"
{
  ExprList *pList = sqliteExprListAppend(0, yymsp[-2].minor.yy8, 0);
  pList = sqliteExprListAppend(pList, yymsp[0].minor.yy8, 0);
  yygotominor.yy8 = sqliteExpr(TK_BETWEEN, yymsp[-4].minor.yy8, 0, 0);
  yygotominor.yy8->pList = pList;
  sqliteExprSpan(yygotominor.yy8,&yymsp[-4].minor.yy8->span,&yymsp[0].minor.yy8->span);
}
#line 4419 "parse.c"
        /* No destructor defined for BETWEEN */
        /* No destructor defined for AND */
        break;
      case 144:
        YYTRACE("expr ::= expr NOT BETWEEN expr AND expr")
#line 380 "parse.y"
{
  ExprList *pList = sqliteExprListAppend(0, yymsp[-2].minor.yy8, 0);
  pList = sqliteExprListAppend(pList, yymsp[0].minor.yy8, 0);
  yygotominor.yy8 = sqliteExpr(TK_BETWEEN, yymsp[-5].minor.yy8, 0, 0);
  yygotominor.yy8->pList = pList;
  yygotominor.yy8 = sqliteExpr(TK_NOT, yygotominor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-5].minor.yy8->span,&yymsp[0].minor.yy8->span);
}
#line 4434 "parse.c"
        /* No destructor defined for NOT */
        /* No destructor defined for BETWEEN */
        /* No destructor defined for AND */
        break;
      case 145:
        YYTRACE("expr ::= expr IN LP exprlist RP")
#line 388 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_IN, yymsp[-4].minor.yy8, 0, 0);
  yygotominor.yy8->pList = yymsp[-1].minor.yy6;
  sqliteExprSpan(yygotominor.yy8,&yymsp[-4].minor.yy8->span,&yymsp[0].minor.yy0);
}
#line 4447 "parse.c"
        /* No destructor defined for IN */
        /* No destructor defined for LP */
        break;
      case 146:
        YYTRACE("expr ::= expr IN LP select RP")
#line 393 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_IN, yymsp[-4].minor.yy8, 0, 0);
  yygotominor.yy8->pSelect = yymsp[-1].minor.yy27;
  sqliteExprSpan(yygotominor.yy8,&yymsp[-4].minor.yy8->span,&yymsp[0].minor.yy0);
}
#line 4459 "parse.c"
        /* No destructor defined for IN */
        /* No destructor defined for LP */
        break;
      case 147:
        YYTRACE("expr ::= expr NOT IN LP exprlist RP")
#line 398 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_IN, yymsp[-5].minor.yy8, 0, 0);
  yygotominor.yy8->pList = yymsp[-1].minor.yy6;
  yygotominor.yy8 = sqliteExpr(TK_NOT, yygotominor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-5].minor.yy8->span,&yymsp[0].minor.yy0);
}
#line 4472 "parse.c"
        /* No destructor defined for NOT */
        /* No destructor defined for IN */
        /* No destructor defined for LP */
        break;
      case 148:
        YYTRACE("expr ::= expr NOT IN LP select RP")
#line 404 "parse.y"
{
  yygotominor.yy8 = sqliteExpr(TK_IN, yymsp[-5].minor.yy8, 0, 0);
  yygotominor.yy8->pSelect = yymsp[-1].minor.yy27;
  yygotominor.yy8 = sqliteExpr(TK_NOT, yygotominor.yy8, 0, 0);
  sqliteExprSpan(yygotominor.yy8,&yymsp[-5].minor.yy8->span,&yymsp[0].minor.yy0);
}
#line 4486 "parse.c"
        /* No destructor defined for NOT */
        /* No destructor defined for IN */
        /* No destructor defined for LP */
        break;
      case 149:
        YYTRACE("exprlist ::= exprlist COMMA expritem")
#line 419 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(yymsp[-2].minor.yy6,yymsp[0].minor.yy8,0);}
#line 4495 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 150:
        YYTRACE("exprlist ::= expritem")
#line 420 "parse.y"
{yygotominor.yy6 = sqliteExprListAppend(0,yymsp[0].minor.yy8,0);}
#line 4502 "parse.c"
        break;
      case 151:
        YYTRACE("expritem ::= expr")
#line 421 "parse.y"
{yygotominor.yy8 = yymsp[0].minor.yy8;}
#line 4508 "parse.c"
        break;
      case 152:
        YYTRACE("expritem ::=")
#line 422 "parse.y"
{yygotominor.yy8 = 0;}
#line 4514 "parse.c"
        break;
      case 153:
        YYTRACE("cmd ::= CREATE uniqueflag INDEX id ON id LP idxlist RP")
#line 426 "parse.y"
{sqliteCreateIndex(pParse, &yymsp[-5].minor.yy180, &yymsp[-3].minor.yy180, yymsp[-1].minor.yy34, &yymsp[-8].minor.yy0, &yymsp[0].minor.yy0);}
#line 4520 "parse.c"
        /* No destructor defined for uniqueflag */
        /* No destructor defined for INDEX */
        /* No destructor defined for ON */
        /* No destructor defined for LP */
        break;
      case 154:
        YYTRACE("uniqueflag ::= UNIQUE")
        /* No destructor defined for UNIQUE */
        break;
      case 155:
        YYTRACE("uniqueflag ::=")
        break;
      case 156:
        YYTRACE("idxlist ::= idxlist COMMA idxitem")
#line 435 "parse.y"
{yygotominor.yy34 = sqliteIdListAppend(yymsp[-2].minor.yy34,&yymsp[0].minor.yy180);}
#line 4537 "parse.c"
        /* No destructor defined for COMMA */
        break;
      case 157:
        YYTRACE("idxlist ::= idxitem")
#line 437 "parse.y"
{yygotominor.yy34 = sqliteIdListAppend(0,&yymsp[0].minor.yy180);}
#line 4544 "parse.c"
        break;
      case 158:
        YYTRACE("idxitem ::= id")
#line 438 "parse.y"
{yygotominor.yy180 = yymsp[0].minor.yy180;}
#line 4550 "parse.c"
        break;
      case 159:
        YYTRACE("cmd ::= DROP INDEX id")
#line 440 "parse.y"
{sqliteDropIndex(pParse, &yymsp[0].minor.yy180);}
#line 4556 "parse.c"
        /* No destructor defined for DROP */
        /* No destructor defined for INDEX */
        break;
      case 160:
        YYTRACE("cmd ::= COPY id FROM id USING DELIMITERS STRING")
#line 443 "parse.y"
{sqliteCopy(pParse,&yymsp[-5].minor.yy180,&yymsp[-3].minor.yy180,&yymsp[0].minor.yy0);}
#line 4564 "parse.c"
        /* No destructor defined for COPY */
        /* No destructor defined for FROM */
        /* No destructor defined for USING */
        /* No destructor defined for DELIMITERS */
        break;
      case 161:
        YYTRACE("cmd ::= COPY id FROM id")
#line 445 "parse.y"
{sqliteCopy(pParse,&yymsp[-2].minor.yy180,&yymsp[0].minor.yy180,0);}
#line 4574 "parse.c"
        /* No destructor defined for COPY */
        /* No destructor defined for FROM */
        break;
      case 162:
        YYTRACE("cmd ::= VACUUM")
#line 447 "parse.y"
{sqliteVacuum(pParse,0);}
#line 4582 "parse.c"
        /* No destructor defined for VACUUM */
        break;
      case 163:
        YYTRACE("cmd ::= VACUUM id")
#line 448 "parse.y"
{sqliteVacuum(pParse,&yymsp[0].minor.yy180);}
#line 4589 "parse.c"
        /* No destructor defined for VACUUM */
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->idx -= yysize;
  yypParser->top -= yysize;
  yyact = yy_find_parser_action(yypParser,yygoto);
  if( yyact < YYNSTATE ){
    yy_shift(yypParser,yyact,yygoto,&yygotominor);
  }else if( yyact == YYNSTATE + YYNRULE + 1 ){
    yy_accept(yypParser sqliteParserARGDECL);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
  sqliteParserANSIARGDECL              /* Extra arguments (if any) */
){
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->idx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
  sqliteParserANSIARGDECL               /* Extra arguments (if any) */
){
#define TOKEN (yyminor.yy0)
#line 34 "parse.y"

  sqliteSetString(&pParse->zErrMsg,"syntax error",0);
  pParse->sErrToken = TOKEN;

#line 4637 "parse.c"
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
  sqliteParserANSIARGDECL              /* Extra arguments (if any) */
){
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->idx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "sqliteParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
/* SQLITE MODIFICATION: Give the function file scope */
void sqliteParser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  sqliteParserTOKENTYPE yyminor       /* The value for the token */
  sqliteParserANSIARGDECL
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->idx<0 ){
    if( yymajor==0 ) return;
    yypParser->idx = 0;
    yypParser->errcnt = -1;
    yypParser->top = &yypParser->stack[0];
    yypParser->top->stateno = 0;
    yypParser->top->major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_parser_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->errcnt--;
      if( yyendofinput && yypParser->idx>=0 ){
        yymajor = 0;
      }else{
        yymajor = YYNOCODE;
      }
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE sqliteParserARGDECL);
    }else if( yyact == YY_ERROR_ACTION ){
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->errcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion sqliteParserARGDECL);
      }
      if( yypParser->top->major==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->idx >= 0 &&
          yypParser->top->major != YYERRORSYMBOL &&
          (yyact = yy_find_parser_action(yypParser,YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->idx < 0 || yymajor==0 ){
          yy_destructor(yymajor,&yyminorunion);
          yy_parse_failed(yypParser sqliteParserARGDECL);
          yymajor = YYNOCODE;
        }else if( yypParser->top->major!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->errcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->errcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion sqliteParserARGDECL);
      }
      yypParser->errcnt = 3;
      yy_destructor(yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser sqliteParserARGDECL);
      }
      yymajor = YYNOCODE;
#endif
    }else{
      yy_accept(yypParser sqliteParserARGDECL);
      yymajor = YYNOCODE;
    }
  }while( yymajor!=YYNOCODE && yypParser->idx>=0 );
  return;
}
