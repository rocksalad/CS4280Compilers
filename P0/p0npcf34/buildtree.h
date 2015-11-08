#ifndef BUILDTREE_H
#define BUILDTREE_H
#include "node.h"

node *createLeaf(int level, char letter, string word);

void addLeaf(char letter, string word, node *p);

int checkTree(string word, node *p);

node *nRoot();

#endif
