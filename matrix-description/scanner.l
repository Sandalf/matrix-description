%{
// flex -oscanner.cpp scanner.l
#include <stdio.h>
#include <string>
#include "abstree.hpp"
#include "parser.hpp"

extern YYSTYPE yylval;
int contador = 1;

%}

numero  [0-9]+("."[0-9]+)?
op      [-+*/:]
delim   [()\[\],;.]
espacio [ \t]
nlinea  \n
id      [a-zA-Z0-9]*

%%

throw   return THROW;

{numero}  { yylval.val = atof(yytext); return NUM; }
{id}      { yylval.id = (strdup(yytext)); return ID; }
{op}      return *yytext;
{delim}   return *yytext;
{espacio} /* Solo los ignora */;
{nlinea}  contador++;

<<EOF>>   return 0;

%%

int yywrap() { return 1; }
