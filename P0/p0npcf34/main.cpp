#include <iostream>
#include <fstream>
#include "buildtree.h"
#include "traversals.h"

using namespace std;

int main(int argc, char *argv[]) {
    char letter;
    string input;
    string fileName;

    //If a filename was given
    if (argc == 2) {
        fileName = argv[1];
        fileName.append(".dat");
        ifstream file(fileName.c_str());

        if (file.is_open()) { //if we can open the file
            while (file >> input) { //read in input word by word
                for (int i = 0; i < input.size(); i++) {
                    if (!isalpha(input.at((unsigned int) i))) { //make sure character is valid input
                        cout << "Exiting... \nProgram encountered invalid character " << input.at((unsigned int) i)
                        << " for input.\n";
                        return 1;
                    }
                }

                //Add word to tree
                letter = input.at(0);
                addLeaf(letter, input, nRoot());
            }

            //Finishing up, close the file.
            file.close();
        } else {
            cout << "File " << fileName <<
            " not found. Exiting...\n Please try to run again using 'run [filename]'\n";
            return 1;
        }
    } else if (argc == 1) {
        cout << "Please enter alphanumeric character strings and press ctrl+d when finished.\n";
        while (cin >> input) { //read input from keyboard
            for (int i = 0; i < input.size(); i++) {
                if (!isalpha(input.at((unsigned int) i))) { //make sure character is valid input
                    cout << "Exiting... \nProgram encountered invalid character " << input.at((unsigned int) i)
                    << " for input.\n";
                    return 1;
                }
            }

            //Add word to tree
            letter = input.at(0);
            addLeaf(letter, input, nRoot());
        }
    } else {
        cout << "No valid input given. Exiting... \nPlease try to run again with the format 'run [filename]'\n";
        return 1;
    }

    //Display traversals
    node *root = nRoot();
    cout << "In Order Traversal\n .......................\n";
    inOrder(root);
    cout << "Post Order Traversal\n .......................\n";
    postOrder(root);
    cout << "Pre Order Traversal\n .......................\n";
    preOrder(root);

    return 0;
}

