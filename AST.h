#ifndef _AST_H
#define _AST_H
#include "hash.h"
#include <stdio.h>
#define MAX_SONS 4
typedef struct astree_node
{
	int type;
	struct hash *symbol;
	struct astree_node *sons[MAX_SONS];
}astree_node;

astree_node* astree;
FILE *file;
#define PROGRAM 10 
#define GLOBAL_VAR_DEF 12
#define FUNC_DEF 13
#define GLOBAL_VAR_DEF_INIT 14
#define GLOBAL_VAR_DEF_PTR 15
#define GLOBAL_VAR_DEF_VEC 16
#define GLOBAL_VAR_DEF_VEC_INIT 17
#define EXP_ADD 18
#define EXP_SUB 19
#define EXP_DIV 20
#define EXP_MUL 21
#define EXP_OR 22
#define EXP_AND 23
#define EXP_LESS 24
#define EXP_MORE 25
#define EXP_ARRAY_ACCESS 26
#define EXP_FUNC_CALL 27
#define ARG_SEQ 28
#define OUT_REST 29 //output sequence
#define SYMBOL_LIT_SEQ 30
#define PARAM 31
#define PARAM_SEQ 32
#define LOCAL_VAR_DEF 33
#define LOCAL_VAR_DEF_LIST 34
#define LOCAL_VAR_DEF_PTR 35
#define CMD 36
#define CMD_LIST 37
#define CMDS 38
#define PRE_INC 39
#define POST_INC 40
#define SIMPLE_ATRIB 41
#define INDEX_ATRIB 42
#define EXP_ADDR 43
#define EXP_PTR 44
#define INI_FUNC_DEF 45
#define EXP_COMPARE 46
astree_node* astcreate(int type, struct hash *symbol, astree_node *son0, astree_node *son1, astree_node *son2, astree_node *son3);
void printast(astree_node* astree, int num);

#endif
