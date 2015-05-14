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
#define PROGRAM 101 
#define GLOBAL_VAR_DEF 121
#define FUNC_DEF 131
#define GLOBAL_VAR_DEF_INIT 141
#define GLOBAL_VAR_DEF_PTR 151
#define GLOBAL_VAR_DEF_VEC 161
#define GLOBAL_VAR_DEF_VEC_INIT 171
#define EXP_ADD 181
#define EXP_SUB 191
#define EXP_DIV 201
#define EXP_MUL 211
#define EXP_OR 221
#define EXP_AND 231
#define EXP_LESS 241
#define EXP_MORE 251
#define EXP_ARRAY_ACCESS 261
#define EXP_FUNC_CALL 271
#define ARG_SEQ 281
#define OUT_REST 291 //output sequence
#define SYMBOL_LIT_SEQ 301
#define PARAM 311
#define PARAM_SEQ 321
#define LOCAL_VAR_DEF 331
#define LOCAL_VAR_DEF_LIST 341
#define LOCAL_VAR_DEF_PTR 351
#define CMD 361
#define CMD_LIST 371
#define CMDS 381
#define PRE_INC 391
#define POST_INC 401
#define SIMPLE_ATRIB 411
#define INDEX_ATRIB 421
#define EXP_ADDR 431
#define EXP_PTR 441
#define INI_FUNC_DEF 451
#define EXP_COMPARE 461
#define FUNC_BODY 471
#define INDEX_INIT 481
astree_node* astcreate(int type, struct hash *symbol, astree_node *son0, astree_node *son1, astree_node *son2, astree_node *son3);
void printast(astree_node* astree, int num);

#endif
