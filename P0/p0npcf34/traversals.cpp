#include "traversals.h"

void inOrder(node *root) {
    if(root == NULL) {
        return;
    } else {
        inOrder(root->left);
        inOrder(root->middle);

        for (int i = 0; i < root->level; i++){
            cout << " ";
        }

        cout << root->letter << ":\t";

        for (int i = 0; i < (int) root->words.size(); i++) {
            cout << root->words[i] << " ";
        }

        cout << "\n";

        inOrder(root->right);
    }
}

void preOrder(node *root) {
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

        inOrder(root->left);
        inOrder(root->middle);
        inOrder(root->right);
    }
}

void postOrder(node *root) {
    if (root == NULL) {
        return;
    } else {
        inOrder(root->left);
        inOrder(root->middle);
        inOrder(root->right);
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
