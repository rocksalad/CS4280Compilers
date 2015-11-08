#include <iostream>
#include <fstream>
#include "buildtree.h"
#include "traversals.h"

using namespace std;

int main(int argc, char *argv[]) {
    string fileName;

    //If a filename was given
    if (argc == 2) {
        fileName = argv[1];
        fileName.append(".dat");
    } else if (argc == 1) { //read from keyboard and put in temp file "temp.dat"
        string input;
        ofstream tempFile;

        fileName = "temp.dat";
        tempFile.open(fileName.c_str());

        cout << "Please enter alphanumeric character strings and press ctrl+d when finished.\n";
        while (cin >> input) { //read input from keyboard
            //Add word to file
            tempFile << input << " ";
        }

        tempFile.close();
    } else {
        cout << "No valid input given. Exiting... \nPlease try to run again with the format 'run [filename]'\n";
        return 1;
    }

    //Display traversals
    node *root = buildTree(fileName);
    //if something went wrong terminate program, already have proper exit message.
    if(root == NULL) {
        return 1;
    }

    cout << "In Order Traversal\n .......................\n";
    traverseInorder(root);
    cout << "Post Order Traversal\n .......................\n";
    traversePostorder(root);
    cout << "Pre Order Traversal\n .......................\n";
    traversePreorder(root);

    return 0;
}
