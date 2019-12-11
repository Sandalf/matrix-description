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
