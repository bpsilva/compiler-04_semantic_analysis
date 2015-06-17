#ifndef SEMANTICS_H
#define SEMANTICS_H
#include "hash.h"
#include "AST.h"
#include "y.tab.h"
int definitionCounter(astree_node *node);
int semanticerror;
int verifyNature(astree_node *node);
void newdefinition(struct hash* node, int natureza, int dataType);

int count_param(astree_node *node);
void search_func_def(astree_node *node);
int count_arg(astree_node *node);
void search_func_call(astree_node *node);
void compare_param_args(astree_node *node);
void types_param(astree_node *fun_def, astree_node *node, int index);
void compare_param_args_types(astree_node *node, int param[20], int index);
int expression_type(astree_node* node);
int find_func_return_type(astree_node *node);
void compare_func_type_return(astree_node *node );
#endif
