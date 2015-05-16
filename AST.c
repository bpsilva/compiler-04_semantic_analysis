
#include "AST.h"
#include "hash.h"
#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>


astree_node* astcreate(int type, struct hash *symbol,  astree_node *son0,  astree_node *son1,  astree_node *son2, astree_node *son3)
{
	astree_node *newnode = 0;
	newnode = (astree_node*)calloc(1, sizeof(astree_node));
	newnode->symbol = symbol;
	newnode->type = type;
	newnode->sons[0] = son0;
	newnode->sons[1] = son1;
	newnode->sons[2] = son2;
	newnode->sons[3] = son3;
	
	return newnode;
}

void printast(astree_node* node, int num)
{	int i;
	
	for (i = 0; i<num;i++)
		printf(" ");

	switch(node->type)
	{
	case PROGRAM: printf("Program\n");break;
	case GLOBAL_VAR_DEF: printf("GLOBAL_VAR_DEF\n");break;
	case FUNC_DEF: printf("FUNC_DEF\n");break;
	case GLOBAL_VAR_DEF_INIT: printf("GLOBAL_VAR_DEF_INIT\n");break;
	case GLOBAL_VAR_DEF_PTR: printf("GLOBAL_VAR_DEF_PTR\n");break;
	case GLOBAL_VAR_DEF_VEC: printf("GLOBAL_VAR_DEF_VEC\n");break;
	case GLOBAL_VAR_DEF_VEC_INIT: printf("GLOBAL_VAR_DEF_VEC_INIT\n");break;
	case EXP_ADD: printf("EXP_ADD\n");break;
	case EXP_SUB :printf("EXP_SUB\n");break;
	case EXP_DIV :printf("EXP_DIV\n");break;
	case EXP_MUL :printf("EXP_MUL\n");break;
	case EXP_OR :printf("EXP_OR\n");break;
	case EXP_AND :printf("EXP_AND\n");break;
	case EXP_LESS :printf("EXP_LESS\n");break;
	case EXP_MORE :printf("EXP_MORE\n");break;
	case SYMBOL_LIT_INTEGER :printf("INTEGER\n");break;
	case KW_WORD :printf("KW_WORD\n");break;
	}
	for(i = 0 ; i < 4 &&  node->sons[i] != 0 ; i++)
		printast(node->sons[i], num+1);



}


