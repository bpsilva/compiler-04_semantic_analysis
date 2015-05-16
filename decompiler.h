
#ifndef _DECOMPILER_H
#define _DECOMPILER_H
#include "AST.h"
#include <string.h>
void asttofile(astree_node* node);
void filewrite(char* text);
void writechar(char c);
void print_type(astree_node* node);
void operationwrite(char* text, astree_node *node);
#endif
