#ifndef SEMANTICS_H
#define SEMANTICS_H
#include "hash.h"
#include "AST.h"
#include "y.tab.h"
int definitionCounter(astree_node *node);
int semanticerror;
int verifyNature(astree_node *node);
void newdefinition(struct hash* node, int natureza, int dataType);
#endif
