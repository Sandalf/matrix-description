//
//  abstree.cpp
//  matrix-description
//
//  Created by Luis Sandoval on 12/10/19.
//  Copyright © 2019 Luis Sandoval. All rights reserved.
//

#include "abstree.hpp"

matrix *newmatrix(int row, int col) {
    matrix *m = new matrix;
    table *t = new table;
    m -> n = row;
    m -> m = col;
    m -> data = *t;
    return m;
}

node *newnode(tnode t, matrix *m) {
    node *n = new node;
    n -> type = t;
    n -> M = m;
    n -> lft = NULL;
    n -> rgt = NULL;
    return n;
}

node *newnode(tnode t, node * lop, node * rop) {
    node *n = new node;
    n -> type = t;
    n -> M = NULL;
    n -> lft = lop;
    n -> rgt = rop;
    return n;
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

void indent (int deep) {
    while (deep > 0) {
        --deep;
        printf(" ");
    }
}

void traverse(node *p, int deep) {
    indent(deep);
    
    switch (p->type) {
        case _sum:
            printf("+\n");
            traverse(p->lft, deep + 1);
            traverse(p->rgt, deep + 1);
            break;
        case _dif:
            printf("-\n");
            traverse(p->lft, deep + 1);
            traverse(p->rgt, deep + 1);
            break;
        case _mult:
            printf("*\n");
            traverse(p->lft, deep + 1);
            traverse(p->rgt, deep + 1);
            break;
        case _matrix:
            printf("matrix: ");
            show(*p->M);
            break;
        default:
            break;
    }
}

matrix *evaluate(node *p) {
    switch (p->type) {
        case _sum: return add(evaluate(p->lft), evaluate(p->rgt));
        case _dif: return subs(evaluate(p->lft), evaluate(p->rgt));
        case _mult: return mult(evaluate(p->lft), evaluate(p->rgt));
        case _matrix: return p->M;
        default:
            return NULL;
            break;
    }
}

matrix *add(matrix *a, matrix *b) {
    if(a == NULL || b == NULL || a->n != b->n || a->m != b->m) {
        printf("Error trying to add matrices\n");
        return NULL;
    }
    matrix *m = newmatrix(a->n, a->m);
    for(int i = 1; i <= a->n; i++) {
        for(int j = 1; j <= a->m; j++) {
            m->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return m;
}

matrix *subs(matrix *a, matrix *b) {
    if(a == NULL || b == NULL || a->n != b->n || a->m != b->m) {
        printf("Error trying to substract matrices\n");
        return NULL;
    }
    matrix *m = newmatrix(a->n, a->m);
    for(int i = 1; i <= a->n; i++) {
        for(int j = 1; j <= a->m; j++) {
            m->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return m;
}

matrix *mult(matrix *a, matrix *b) {
    if(a == NULL || b == NULL || a->m != b->n) {
        printf("Error trying to multiply matrices\n");
        return NULL;
    }
    matrix *m = newmatrix(a->n, b->m);
    for(int i = 1; i <= a->n; i++) {
        for(int j = 1; j <= b->m; j++) {
            for (int k = 1; k <= a->m; k++) {
                m->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return m;
}
