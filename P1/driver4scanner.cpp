#include "driver4scanner.h"
using namespace std;

string tokenNames[] = {"Identifier", "Number", "Begin keyword", "End keyword", "Start keyword", "Finish keyword",
                       "Then keyword", "If keyword", "Loop keyword", "Integer keyword", "Do keyword", "Scan keyword",
                       "Print keyword", "Void keyword", "Return keyword", "Program keyword", "Dummy keyword",
                       "Relational Operator", "Other Operator", "Delimeter", "End of File", "Error"};


void printToken(token t) {
        cout << "Line Num: " << t.lineNum << ", Token ID: " << tokenNames[t.tokenId] << ", Token Instance: " << t.name << "\n";
}

void driver4Scanner(FILE *fp) {
    int lookahead;
    int lineNum = 1;
    while((lookahead = fgetc(fp)) != EOF) {
        ungetc(lookahead, fp);
        token t = scanner(fp, lineNum);
        if(t.tokenId != ERR_tk) {
            printToken(t);
        } else {
            printToken(t);
            return;
        }

    }

    fclose(fp);

}
