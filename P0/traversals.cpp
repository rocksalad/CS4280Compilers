#include "traversals.h"

void traverseInorder(node *root) {
    if(root == NULL) {
        return;
    } else {
        traverseInorder(root->left);
        traverseInorder(root->middle);

        for (int i = 0; i < root->level; i++){
            cout << " ";
        }

        cout << root->letter << ":\t";

        for (int i = 0; i < (int) root->words.size(); i++) {
            cout << root->words[i] << " ";
        }

        cout << "\n";

        traverseInorder(root->right);
    }
}

void traversePreorder(node *root) {
    if (root == NULL) {
        return;
    } else {
        for (int i = 0; i < root->level; i++) {
            cout << " ";
        }

        cout << root->letter << ":\t";

        for (int i = 0; i < (int) root->words.size(); i++) {
            cout << root->words[i] << " ";
        }

        cout << "\n";

        traverseInorder(root->left);
        traverseInorder(root->middle);
        traverseInorder(root->right);
    }
}

void traversePostorder(node *root) {
    if (root == NULL) {
        return;
    } else {
        traverseInorder(root->left);
        traverseInorder(root->middle);
        traverseInorder(root->right);
        for (int i = 0; i < root->level; i++) {
            cout << " ";
        }

        cout << root->letter << ":\t";

        for (int i = 0; i < (int) root->words.size(); i++) {
            cout << root->words[i] << " ";
        }

        cout << "\n";
    }
}
