#include <iostream>
#include "treePrint.h"

string tokenNames[] = {"Identifier", "Number", "Begin keyword", "End keyword", "Start keyword", "Finish keyword",
                       "Then keyword", "If keyword", "Loop keyword", "Integer keyword", "Do keyword", "Scan keyword",
                       "Print keyword", "Void keyword", "Return keyword", "Program keyword", "Dummy keyword",
                       "Relational Operator", "Other Operator", "Delimeter", "End of File", "Error"};

void printTree(node_t *root, int level) {
    if (root == NULL) {
        return;
    } else { //process node
        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        level++;

        cout << root->label << "\t";
        token token = root->token_t;
        if (token.name != "") {
            cout <<  "Token ID: " + tokenNames[token.tokenId] + " Instance: " + token.name << endl;
        }

        cout << "\n";

        //recursively process children
        printTree(root->child1, level);
        printTree(root->child2, level);
        printTree(root->child3, level);
        printTree(root->child4, level);
        printTree(root->child5, level);
    }
}