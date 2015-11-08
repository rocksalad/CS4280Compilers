#ifndef NODE_H
#define NODE_H
#include <vector>
#include <string>

using namespace std;

struct node {
    char letter;
    int level;
    vector<string> words;
    node *left;
    node *middle;
    node *right;
    node *parent;
};

#endif

