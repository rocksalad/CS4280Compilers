#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <ctype.h>
#include <string>

using namespace std;

enum tokenID {IDENT_tk, NUM_tk, BEGIN_tk, END_tk, START_tk, FIN_tk, THEN_tk, IF_tk, LOOP_tk, INT_tk, DO_TK, SCAN_tk,
    PRINT_tk, VOID_tk, RETURN_tk, PROG_tk, DUM_tk, REL_tk, OP_tk, DEL_tk, EOF_tk, ERR_tk};

struct token {
    tokenID tokenId;
    string name;
    int lineNum;
};

token scanner(FILE *fp);


#endif
