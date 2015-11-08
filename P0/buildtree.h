#ifndef BUILDTREE_H
#define BUILDTREE_H
#include <fstream>
#include <iostream>
#include "node.h"

node *buildTree(string fileName);

node *createLeaf(int level, char letter, string word);

void addLeaf(char letter, string word, node *p);

int checkTree(string word, node *p);

#endif
