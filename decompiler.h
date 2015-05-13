
#ifndef _DECOMPILER_H
#define _DECOMPILER_H
#include "AST.h"
#include <string.h>
void asttofile(astree_node* node);
void filewrite(char* text);
void writechar(char c);
void operationwrite(char* text, astree_node *node);
#endif
