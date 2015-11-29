#include <iostream>
#include <fstream>
#include "parser.h"
#include "treePrint.h"

using namespace std;

int main(int argc, char *argv[]) {
    string fileName;
    int level = 0;

    //If a filename was given
    if (argc == 2) {
        fileName = argv[1];
        fileName.append(".lan");

        fp = fopen(fileName.c_str(), "r");
    } else if (argc == 1) { //read from keyboard and put in temp file "temp.lan"
        string input;
        ofstream tempFile;

        fileName = "temp.lan";
        tempFile.open(fileName.c_str());

        cout << "Please enter alphanumeric character strings and press ctrl+d when finished.\n";
        while (cin >> input) { //read input from keyboard
            //Add word to file
            tempFile << input << "\n";
        }

        tempFile.close();

        fp = fopen(fileName.c_str(), "r");
    } else {
        cout << "No valid input given. Exiting... \nPlease try to run again with the format 'testScanner [filename]'\n";
        return 1;
    }

    //Parse input
    node_t *parseTree = parser();
    //Print parse tree
    printTree(parseTree, level);

    fclose(fp);

    return 0;
}
