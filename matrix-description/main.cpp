//
//  main.cpp
//  matrix-description
//
//  Created by Luis Sandoval on 12/10/19.
//  Copyright © 2019 Luis Sandoval. All rights reserved.
//

#include <iostream>
#include "abstree.hpp"

extern FILE* yyin;
extern int yyparse();
extern matrix *mresult;

bool parse(const char *fname) {
    yyin = fopen(fname,"r");
    int x = yyparse();
    fclose(yyin);
    
    return x == 0;
}

void show(matrix &M);

int main(int argc, const char * argv[]) {
    if (parse("prueba.txt")) {
        printf("Parsed\n");
        show(*mresult);
    } else {
        printf("Not ok\n");
    }
    return 0;
}

void show(matrix &M) {
    printf("[");
    for(int i = 1; i <= M.n; i++) {
        for(int j = 1; j <= M.m; j++) {
            printf(" %f", M.data[i][j]);
            if (j < M.m) printf(",");
        }
        printf(";");
    }
    printf("]\n");
}
