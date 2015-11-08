#include "buildtree.h"

using namespace std;

node *root = NULL;

node *createLeaf(int level, char letter, string word) {
    node *p = new node;

    p->left = NULL;
    p->middle = NULL;
    p->right = NULL;
    p->parent = NULL;

    p->letter = letter;
    p->words.push_back(word);
    p->level = level;
    return p;
}

void addLeaf(char letter, string word, node *p) {
    if (root == NULL) {
        root = createLeaf(0, letter, word);
        root->parent = root;
    } else if (letter < p->letter) {
        if (p->left == NULL) {
            p->left = createLeaf((p->level + 1), letter, word);
            p->left->parent = p;
        } else {
            if (p->middle == NULL) {
                if (letter == p->left->letter) {
                    if (checkTree(word, p->left) != 0) {
                        p->left->words.push_back(word);
                    }
                } else {
                    p->middle = createLeaf((p->level + 1), letter, word);
                    p->middle->parent = p;
                    if (p->left->letter > p->middle->letter) {
                        node *tNode = p->left;
                        p->left = p->middle;
                        p->middle = tNode;
                    }
                }
            } else {
                if (letter < p->middle->letter) {
                    if (letter == p->left->letter) {
                        if (checkTree(word, p->left) != 0) {
                            p->left->words.push_back(word);
                        }
                    } else {
                        addLeaf(letter, word, p->left);
                    }
                } else if (letter == p->middle->letter) {
                    if (checkTree(word, p->middle) != 0) {
                        p->middle->words.push_back(word);
                    }
                } else {
                    addLeaf(letter, word, p->middle);
                }
            }
        }
    } else if (letter == p->letter) {
        if (checkTree(word, p) != 0) {
            p->words.push_back(word);
        }
    } else {
        if (p->right == NULL) {
            p->right = createLeaf((p->level + 1), letter, word);
        } else if (letter == p->right->letter) {
            if (checkTree(word, p->right) != 0) {
                p->right->words.push_back(word);
            }
        } else {
            addLeaf(letter, word, p->right);
        }
    }
}

int checkTree(string word, node *p) {
    if (p->words.size() > 0) {
        for (int i = 0; i < p->words.size(); i++) {
            if (p->words[i].compare(word) == 0) {
                return 0;
            } else {
                return 1;
            }
        }
    }
    return 0;
}

node *nRoot() {
    return root;
}
