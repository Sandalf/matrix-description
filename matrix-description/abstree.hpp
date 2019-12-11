//
//  abstree.hpp
//  matrix-description
//
//  Created by Luis Sandoval on 12/10/19.
//  Copyright © 2019 Luis Sandoval. All rights reserved.
//

#ifndef abstree_hpp
#define abstree_hpp

#include <stdio.h>
#include <map>

typedef std::map<int,float> row;
typedef std::map<int,row> table;

typedef struct {
    int n,m; // Number of rows and columns
    table data; // Content of the matrix
} matrix;

matrix *newmatrix(int, int);

#endif /* abstree_hpp */
