#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "node.h"

extern FILE* fp;
extern int lineNum;

/*
 * Helper functions that need to be pre-declared
 */
node_t* block_f();

node_t* expr_f() ;

node_t* RO_f() ;

// Parser function
node_t* parser();

#endif
