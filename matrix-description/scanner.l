%{
// flex -oscanner.cpp scanner.l
#include <stdio.h>
#include "abstree.hpp"
#include "parser.hpp"

extern YYSTYPE yylval;
int contador = 1;

%}

numero  [0-9]+("."[0-9]+)?
op      [-+*/]
delim   [()\[\],;]
espacio [ \t]
nlinea  \n

%%

throw   return THROW;

{numero}  { yylval.val = atof(yytext); return NUM; }
{op}      return *yytext;
{delim}   return *yytext;
{espacio} /* Solo los ignora */;
{nlinea}  contador++;

<<EOF>>   return 0;

%%

int yywrap() { return 1; }
