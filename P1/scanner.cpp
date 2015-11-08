#include <iostream>
#include "scanner.h"

struct alphabetKey {
    int key;
    int value;
};

typedef struct {
    int key;
    tokenID name;
}tkMap;


int stateTable[10][24] = {
        {5,6,6,7,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,1,2,0,-99},
        {1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1,1000,1000,0},
        {1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,2,1001,0},
        {1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,0},
        {1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,0},
        {9,9,9,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,0},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,0},
        {8,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,0},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,0}
};

alphabetKey charLookup[19] = {
        {'=', 0},
        {'<', 1},
        {'>', 2},
        {'!', 3},
        {':', 4},
        {'+', 5},
        {'-', 6},
        {'*', 7},
        {'/', 8},
        {'%', 9},
        {'.', 10},
        {'(', 11},
        {')', 12},
        {',', 13},
        {'{', 14},
        {'}', 15},
        {';', 16},
        {'[', 17},
        {']', 18}
};

token keywordLookup[15] = {
        {BEGIN_tk, "begin", 0},
        {END_tk, "end", 0},
        {START_tk, "start", 0},
        {FIN_tk, "finish", 0},
        {THEN_tk, "then", 0},
        {IF_tk, "if", 0},
        {LOOP_tk, "loop", 0},
        {INT_tk, "integer", 0},
        {DO_TK, "do", 0},
        {SCAN_tk, "scan", 0},
        {PRINT_tk, "print", 0},
        {VOID_tk, "void", 0},
        {RETURN_tk, "return", 0},
        {PROG_tk, "program", 0},
        {DUM_tk, "dummy", 0}
};

tkMap tokenLookupTable[6] = {
        {-99,  EOF_tk},
        {1000, IDENT_tk},
        {1001, NUM_tk},
        {1002, OP_tk},
        {1003, DEL_tk},
        {1004, REL_tk}
};

token tokenLookup(int val, string word) {
    token t;

    for (int i = 0; i < 6; i++) {
        if (val == 1) {
            for (int j = 0; j < 15; j++) {
                if (keywordLookup[j].name == word) {
                    t.tokenId = keywordLookup[j].tokenId;
                    t.name = word;
                    t.lineNum = 7;
                }
            }
        }

        if (tokenLookupTable[i].key == val) {
            t.tokenId = tokenLookupTable[i].name;
            t.name = word;
            t.lineNum = 6;
        }
    }

    return t;
}

int colLookup(char lookAhead) {
    for (int i = 0; i < 19; i++) {
        if(charLookup[i].key == lookAhead) {
            return charLookup[i].value;
        }
    }

    if (isalpha(lookAhead)) {
        return 19;
    } else if (isdigit(lookAhead)) {
        return 20;
    } else if (isspace(lookAhead)) {
        return 21;
    } else if (lookAhead == EOF) {
        return 22;
    } else {
        return 23;
    }
}

token scanner(FILE *fp, int &lineNum) {
    int lookahead;
    int stateCol;
    int currState = 0, nextState = 0;
    string word;
    token t;

    while (currState < 1000 && currState >= 0) {
        lookahead = fgetc(fp);

        if(lookahead == '#') {
            cout << "comment\n";
            while (lookahead != '\n') {
                lookahead = fgetc(fp);
            }
            lineNum++;
        }

        stateCol = colLookup(lookahead);
        nextState = stateTable[currState][stateCol];

        if (nextState >= 1000 || nextState == -99) {
            if (lookahead == '\n') {
                lineNum++;
            }

            if (nextState == -99) {
                ungetc(lookahead, fp);
                t.tokenId = EOF_tk;
                t.lineNum = lineNum;
                t.name = "EOF";
                return t;
            } else if (nextState >= 1000) {
                t = tokenLookup(nextState, word);
                t.lineNum = lineNum;
                ungetc(lookahead, fp);
                return t;
            } else {
                cout << "Error: Line " << lineNum << " value: " << static_cast<char>(lookahead) << "\n";
                t.tokenId = ERR_tk;
                t.lineNum = lineNum;
                t.name = "Error";
                return t;
            }
        } else {
            char value = static_cast<char>(lookahead);

            if (!isspace(value)) {
                word += value;
            }
            if (nextState == 7){
                int lookahead2 = fgetc(fp);
                if (lookahead2 == '=') {
                    word += static_cast<char>(lookahead2);
                } else {
                    ungetc(lookahead2, fp);
                    t.tokenId = ERR_tk;
                    t.lineNum = lineNum;
                    t.name = "Error with ! operator";
                    return t;
                }
            }
            currState = nextState;
        }

    }
    t.tokenId = ERR_tk;
    t.lineNum = lineNum;
    t.name = "Scanner didn't do anything";
    return t;
}
