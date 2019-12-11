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
//extern matrix *mresult;
extern node *tree;

bool parse(const char *fname) {
    yyin = fopen(fname,"r");
    int x = yyparse();
    fclose(yyin);
    
    return x == 0;
}

int main(int argc, const char * argv[]) {
    if (parse("prueba.txt")) {
        printf("Parsed\n");
//        show(*mresult);
//        show(*tree->M);
        traverse(tree, 0);
        printf("Result:\n");
        show(*evaluate(tree));
    } else {
        printf("Not ok\n");
    }
    return 0;
}
