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

typedef enum {
    _sum,
    _dif,
    _mult,
    _matrix
} tnode;

typedef std::map<int,float> row;
typedef std::map<int,row> table;

typedef struct {
    int n,m; // Number of rows and columns
    table data; // Content of the matrix
} matrix;

typedef struct x {
    int type; // Node type ('+', '-', '*' or 'M')
    matrix *M; // Matrix associated to the node
    struct x *lft; // Link to left sub-tree
    struct x *rgt; // Link to right sub-tree
} node;

matrix *newmatrix(int, int);
node *newnode(tnode, matrix *);
node *newnode(tnode, node *, node *);
void traverse(node *, int);
void show(matrix &M);

#endif /* abstree_hpp */
