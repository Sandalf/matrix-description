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
extern node *tree;

bool parse(const char *fname) {
    yyin = fopen(fname,"r");
    int x = yyparse();
    fclose(yyin);
    
    return x == 0;
}

int main(int argc, const char * argv[]) {
    parse("prueba.txt");
    return 0;
}
