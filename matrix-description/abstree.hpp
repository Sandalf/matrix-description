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
#include <string>

typedef enum {
    _sum,
    _dif,
    _mult,
    _matrix
} tnode;

typedef std::map<int,float> row;
typedef std::map<int,row> table;

typedef struct {
    int n = 0;
    int m = 0; // Number of rows and columns
    table data; // Content of the matrix
} matrix;

typedef std::map<std::string,matrix*> ids;

typedef struct x {
    int type; // Node type ('+', '-', '*' or 'M')
    matrix *M; // Matrix associated to the node
    struct x *lft; // Link to left sub-tree
    struct x *rgt; // Link to right sub-tree
} node;

// Build tree
matrix *newmatrix(int, int);
node *newnode(tnode, matrix *);
node *newnode(tnode, node *, node *);

// Work with tree
matrix *evaluate(node *p);
void traverse(node *, int);
void show(matrix &M);
void destroy(node *p);
matrix *add(matrix *a, matrix *b);
matrix *subs(matrix *a, matrix *b);
matrix *mult(matrix *a, matrix *b);

#endif /* abstree_hpp */
