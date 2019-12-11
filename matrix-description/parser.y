%{
// bison -d parser.y -o parser.cpp
#include <cstdio>
#include "abstree.hpp"

extern int contador;
extern int yylex();

int yyerror(char *);

// float resultado = 0.0;
matrix *mresult = NULL;
matrix *mtemp = NULL;
int ncol = 0;
int nrow = 0;

%}

%union {
    float val;
    matrix *mptr;
}

%token <val> NUM
%type <val> exp term fact // numeric expressions
%type <mptr> mdef rowseq row // matrix description

%%

begin: mdef { mresult = $1; };

mdef:
    '[' { ncol = 1; nrow = 1; mtemp = newmatrix(ncol,nrow); } rowseq ']' { $$ = $3; }
    ;

rowseq:
    rowseq ';' { nrow++; mtemp->n = nrow; mtemp->m = ncol; ncol = 1; } row { $$ = mtemp; }
    | row { $$ = $1; }
    ;

row:
    row ',' { ncol++; } exp { mtemp->data[nrow][ncol] = $4; $$ = mtemp; }
    | exp { mtemp->data[nrow][ncol] = $1;  $$ = mtemp; }
    ;

exp:
    exp '+' term { $$ = $1 + $3; }
    | exp '-' term { $$ = $1 - $3; }
    | term { $$ = $1; };

term:
    term '*' fact { $$ = $1 * $3; }
    | term '/' fact { $$ = $1 / $3; }
    | fact { $$ = $1; };

fact:
    '(' exp ')' { $$ = $2; }
    | '-' fact { $$ = - $2; }
    | NUM { $$ = $1; };

%%

int yyerror(char *mssg) {
    printf("[%i] %s\n", contador, mssg);
    return 0;
}
