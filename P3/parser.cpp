#include <iostream>
#include <stdlib.h>
#include "parser.h"

token tk;
FILE *fp = NULL;
int lineNum = 0;
int level = 0;

void error(string s) {
    cout << s << "\t at line: " << lineNum << endl;
    exit(0);
}

node_t *getNode(string s) {
    node_t *node = new node_t;
    node->label = s;
    return node;
}

//<mvars>     ->     empty | , Identifier <mvars>
node_t* mvars_f() {
    node_t *p = getNode("<mvars>");

    if (tk.name == ";") { // empty
        return p;
    } else if (tk.name == ",") { // ,
        tk = scanner(fp, lineNum);
        //don't need to put delimiters in the tree
        if(tk.tokenId == IDENT_tk) { // IDENTIFIER
            p->child1 = getNode("Identifier");
            p->child1->token_t = tk;
            tk = scanner(fp, lineNum);
            p->child2 = mvars_f();
            return p;
        } else {
            error("Got token " + tk.name + ", expected , token\n");
        }
    } else {
        error("Got token " + tk.name + ", expected empty or , token\n");
    }

    return p;
}

//<var>          ->      empty | <type> Identifier <mvars> ;
node_t* var_f() {
    node_t *p = getNode("<var>");

    if(tk.name == "{"|| tk.tokenId == SCAN_tk || tk.tokenId == IF_tk || tk.tokenId == PRINT_tk ||
       tk.tokenId == LOOP_tk || tk.tokenId == IDENT_tk) { // empty
        return p;
    } else if(tk.tokenId == INT_tk) { // INTEGER
        p->child1 = getNode("INTEGER");
        p->child1->token_t = tk;
        tk = scanner(fp, lineNum);
        if(tk.tokenId == IDENT_tk) { // IDENTIFIER
            p->child2 = getNode("IDENTIFIER");
            p->child2->token_t = tk;
            tk = scanner(fp, lineNum);
            p->child3 = mvars_f();
            if (tk.name == ";") { // ;
                //don't need to put delimiters in the tree
                tk = scanner(fp, lineNum);
                return p;
            } else {
                error("Got token " + tk.name + ", expected ; token\n");
            }
        } else {
            error("Got token " + tk.name + ", expected IDENTIFIER token\n");
        }
    } else {
        error("Got token " + tk.name + ", expected empty or INTEGER token\n");
    }
    return p;
}

//<in>              ->      SCAN Identifier ;
node_t* in_f() {
    node_t *p = getNode("<in>");

    if (tk.tokenId == IDENT_tk) { // IDENTIFIER
        p->child1 = getNode("IDENTIFIER");
        p->child1->token_t = tk;
        tk = scanner(fp, lineNum);
        if (tk.name == ";") { // ;
            //don't need to put delimiter in tree
            tk = scanner(fp, lineNum);
            return p;
        } else {
            error("Got token " + tk.name + ", expected ; token\n");
        }
    } else {
        error("Got token " + tk.name + ", expected IDENTIFIER token\n");
    }

    return p;
}

//<out>            ->      PRINT <expr>  ;
node_t* out_f() {
    node_t *p = getNode("<out>");

    p->child1 = expr_f();
    if (tk.name == ";") { // ;
        //don't need to put delimiters in tree
        tk = scanner(fp, lineNum);
        return p;
    } else {
        error("Got token " + tk.name + ", expected ' token\n");
    }

    return p;
}

//<if>               ->      IF ( <expr> <RO> <expr>)  THEN <block>
node_t* if_f() {
    node_t *p = getNode("<if>");

    if (tk.name == "(") { // (
        //don't need to put delimiters in the tree
        tk = scanner(fp, lineNum);
        p->child1 = expr_f();
        p->child2 = RO_f();
        p->child3 = expr_f();
        if (tk.name == ")") { // )
            //don't need to put delimiters in the tree
            tk = scanner(fp, lineNum);
            if (tk.tokenId == THEN_tk) {
                tk = scanner(fp, lineNum);
                p->child4 = block_f();
                return p;
            } else {
                error("Got token " + tk.name = ", expected THEN token\n'");
            }
        } else {
            error("Got token " + tk.name = ", expected ) token\n");
        }
    } else {
        error("Got token " + tk.name = ", expected ( token\n");
    }

    return p;
}

//<loop>          ->      LOOP ( <expr> <RO> <expr> ) <block>
node_t* loop_f() {
    node_t *p = getNode("<loop>");

    if(tk.name == "(") { // (
        //don't need to put delimiters in the tree
        tk = scanner(fp, lineNum);
        p->child1 = expr_f();
        p->child2 = RO_f();
        p->child3 = expr_f();
        if (tk.name == ")") { // )
            //don't need to put delimiters in the tree
            tk = scanner(fp, lineNum);
            p->child4 = block_f();
            return p;
        } else {
            error("Got token " + tk.name = ", expected ) token\n");
        }
    } else {
        error("Got token " + tk.name = ", expected ( token\n");
    }

    return p;
}

//<assign>       ->      Identifier = <expr> .
node_t* assign_f() {
    node_t *p = getNode("<assign>");

    if(tk.tokenId == IDENT_tk) {
        p->child1 = getNode("IDENTIFIER");
        p->child1->token_t = tk;
        tk = scanner(fp, lineNum);
        if (tk.name == "=") { // =
            p->child2 = getNode("=");
            tk = scanner(fp, lineNum);
            p->child3 = expr_f();
            if (tk.name == ".") { // .
                //don't need to put delimiters in the tree
                tk = scanner(fp, lineNum);
                return p;
            } else {
                error("Got token " + tk.name = ", expected . token\n");
            }
        } else {
            error("Got token " + tk.name = ", expected = token\n");
        }
    } else {
        error("Got token " + tk.name = ", expected IDENTIFIER token\n");
    }

    return p;
}

//<stat>           ->      <in> | <out> | <block> | <if> | <loop> | <assign>
node_t* stat_f() {
    node_t *p = getNode("<stat>");

    if (tk.tokenId == SCAN_tk) { // <in>
        p->child1 = getNode("SCAN");
        tk = scanner(fp, lineNum);
        p->child2 = in_f();
        return p;
    } else if (tk.tokenId == PRINT_tk) { // <out>
        p->child1 = getNode("PRINT");
        tk = scanner(fp, lineNum);
        p->child2 = out_f();
        return p;
    } else if (tk.name == "{") { // <block>
        //don't need to put delimiters in the tree
        p->child1 = block_f();
        return p;
    } else if (tk.tokenId == IF_tk) { // <if>
        p->child1 = getNode("IF");
        tk = scanner(fp, lineNum);
        p->child2 = if_f();
        return p;
    } else if (tk.tokenId == LOOP_tk) { // <loop>
        p->child1 = getNode("LOOP");
        tk = scanner(fp, lineNum);
        p->child2 = loop_f();
        return p;
    } else if (tk.tokenId == IDENT_tk) { // <assign>
        p->child1 = assign_f();
        return p;
    } else {
        error("Got token " + tk.name + ", expected SCAN, PRINT, {, IF, LOOP, or IDENTIFIER token\n");
    }

    return p;
}

//<mStat>       ->      empty | <stat>  <mStat>
node_t* mStat_f() {
    node_t *p = getNode("mStat");

    if (tk.name == "}") { // empty
        //don't need to put delimiters in tree
        return p;
    } else {
        p->child1 = stat_f();
        p->child2 = mStat_f();
        return p;
    }
}

//<stats>         ->      <stat>  <mStat>
node_t* stats_f() {
    node_t *p = getNode("<stats>");

    p->child1 = stat_f();
    p->child2 = mStat_f();
    return p;
}

//<block>       ->      { <var> <stats> }
node_t* block_f() {
    node_t *p = getNode("<block>");

    if (tk.name == "{") { // {
        //don't need to put delimiters in the tree
        tk = scanner(fp, lineNum);
        p->child1 = var_f();
        p->child2 = stats_f();
        if (tk.name == "}") { // }
            //don't need to put delimiters in the tree
            tk = scanner(fp, lineNum);
            return p;
        } else {
            error("Got token " + tk.name + ", expected } token");
        }
    } else {
        error("Got token " + tk.name + ", expected { token");
    }

    return p;
}

//<program>  ->     PROGRAM <var> <block>
node_t* prog_f() {
    node_t *p = getNode("<program>");

    if(tk.tokenId == PROG_tk) { // PROGRAM
        p->child1 = getNode("PROGRAM");
        tk = scanner(fp, lineNum);
        p->child2 = var_f();
        p->child3 = block_f();
        return p;
    } else {
        error("Got token " + tk.name + ", expected PROGRAM token\n");
    }

    return p;
}

//<R>              ->      (<expr>) | Identifier | Number
node_t* R_f() {
    node_t *p = getNode("<R>");

    if (tk.name == "(") { // (
        //don't need to put delimiters in tree
        tk = scanner(fp, lineNum);
        p->child1 = expr_f();
        if (tk.name == ")") { // )
            //don't need to put delimiters in tree
            tk = scanner(fp, lineNum);
            return p;
        }
    } else if (tk.tokenId == IDENT_tk) { // IDENTIFIER
        p->child1 = getNode("IDENTIFIER");
        p->child1->token_t = tk;
        tk = scanner(fp, lineNum);
        return p;
    } else if (tk.tokenId == NUM_tk) { // NUMBER
        p->child1 = getNode("NUMBER");
        p->child1->token_t = tk;
        tk = scanner(fp, lineNum);
        return p;
    } else {
        error("Got token " + tk.name = ", expected (, IDENTIFIER, or NUMBER token\n");
    }

    return p;
}

//<F>              ->      - <F> | <R>
node_t* F_f() {
    node_t *p = getNode("<F>");

    if(tk.name == "-") { // -<F>
        p->child1 = getNode("-");
        tk = scanner(fp, lineNum);
        p->child2 = F_f();
        return p;
    } else if((tk.name == "(") || tk.tokenId == IDENT_tk || tk.tokenId == NUM_tk) { // <R>
        p->child1 = R_f();
        return p;
    } else {
        error("Got token " + tk.name + " expected (, ID, NUM, or - token\n");
    }

    return p;
}

//<T>              ->      <F> * <T> | <F> / <T> | <F>
node_t* T_f() {
    node_t *p = getNode("<T>");

    p->child1 = F_f();
    if(tk.name == "*") { // *<T>
        p->child2 = getNode("*");
        tk = scanner(fp, lineNum);
        p->child3 = T_f();
        return p;
    } else if(tk.name == "/") { // /<T>
        p->child2 = getNode("/");
        tk = scanner(fp, lineNum);
        p->child3 = T_f();
        return p;
    } else { //<F>
        return p;
    }
}

//<expr>        ->      <T> + <expr> | <T> - <expr> | <T>
node_t* expr_f() {
    node_t *p = getNode("<expr>");

    p->child1 = T_f();
    if (tk.name == "+") { // +<expr>
        p->child2 = getNode("+");
        tk = scanner(fp, lineNum);
        p->child3 = expr_f();
        return p;
    } else if(tk.name == "-") { // -<expr>
        p->child2 = getNode("-");
        tk = scanner(fp, lineNum);
        p->child3 = expr_f();
        return p;
    } else { // <T>
        return p;
    }
}

//<RO>            ->      => | =< | == |  > | <  |  !=
node_t* RO_f() {
    node_t *p = getNode("<RO>");

    if(tk.tokenId == REL_tk) {
        if (tk.name == "=>") { // =>
            p->child1 = getNode("=>");
            tk = scanner(fp, lineNum);
            return p;
        } else if (tk.name == "=<") { //=<
            p->child1 = getNode("=<");
            tk = scanner(fp, lineNum);
            return p;
        } else if (tk.name == "==") { // ==
            p->child1 = getNode("==");
            tk = scanner(fp, lineNum);
            return p;
        } else if (tk.name == ">") { // >
            p->child1 = getNode(">");
            tk = scanner(fp, lineNum);
            return p;
        } else if (tk.name == "<") { // <
            p->child1 = getNode("<");
            tk = scanner(fp, lineNum);
            return p;
        } else if (tk.name == "!=") { // !=
            p->child1 = getNode("!=");
            tk = scanner(fp, lineNum);
            return p;
        }
    } else {
        error("Got token " + tk.name + ", expected =>, =<, ==, >, <, or != token\n");
    }

    return p;
}

//Parser, returns parse tree
node_t* parser() {
    node_t *treep;
    tk = scanner(fp, lineNum);
    treep = prog_f();

    cout << "Parse OK\n";
    return treep;
}
