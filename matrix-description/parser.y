%{
// bison -d parser.y -o parser.cpp
#include <cstdio>
#include <string>
#include "abstree.hpp"

extern int contador;
extern int yylex();

int yyerror(char *);

// float resultado = 0.0;
matrix *mresult = NULL;
matrix *mtemp = NULL;
int ncol = 0;
int nrow = 0;
node *tree = NULL;
ids identifiers;

%}

%union {
    float val;
    matrix *mptr;
    node *node; 
    char *id;
}

%token <val> NUM
%token <id> ID
%token THROW

%type <val> exp term fact // numeric expressions
%type <mptr> mdef rowseq row // matrix description
%type <node> mfact mterm mexp // matrix expressions
%type thowing assign st stseq

%%

main: stseq '.';

stseq:
    stseq ';' st
    | st
    ;

st:
    assign
    | thowing
    ;

assign:
    ID ':' mexp {
        std::string str($1);
        matrix *m = evaluate($3);
        identifiers[str] = m;
    }
    ;

thowing:
    THROW mexp {
        matrix *m = evaluate($2);
        if (m != NULL) {
            printf("Result:\n");
            show(*m);
        } else {
            printf("Error: Null matrix\n");
        }
    }
    ;

mexp:
    mexp '+' mterm { $$ = newnode(_sum, $1, $3); } 
    | mexp '-' mterm { $$ = newnode(_dif, $1, $3); } 
    | mterm { $$ = $1; }
    ;

mterm:
    mterm '*' mfact { $$ = newnode(_mult, $1, $3); }
    | mfact { $$ = $1; }
    ;

mfact:
    '(' mexp ')' { $$ = $2; }
    | mdef { $$ = newnode(_matrix, mtemp); }
    | ID {
        std::string str($1);

        if(identifiers.count(str) > 0) {
            $$ = newnode(_matrix, identifiers.find(str)->second);
        } else {
            printf("Error: Identifier is undefined\n");
        }
    }   
    ;

mdef:
    '[' { ncol = 1; nrow = 1; mtemp = newmatrix(ncol,nrow); } rowseq ']' { $$ = $3; }
    ;

rowseq:
    rowseq ';' { nrow++; mtemp->n = nrow; ncol = 1; } row { $$ = mtemp; }
    | row { $$ = $1; }
    ;

row:
    row ',' { ncol++; mtemp->m = ncol; } exp { mtemp->data[nrow][ncol] = $4; $$ = mtemp; }
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
