#ifndef NODE_H
#define NODE_H

#include <string>
#include "scanner.h"

using namespace std;

struct node_t {
    string label;
    node_t *child1, *child2, *child3, *child4;
    token token_t;
};

#endif
