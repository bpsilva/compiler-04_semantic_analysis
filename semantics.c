#include "semantics.h"

int definitionCounter(astree_node *node)
{
	int i = 0;
	if(node !=0)
	{
		for(i = 0 ; i < 4  ; i++)
		{
			definitionCounter(node->sons[i]);
		}
		if(node->type == SYMBOL_IDENTIFIER)
		{
			if(node->symbol->defcounter > 1)
			{

				printf("Multple definitions of '%s'.\n", node->symbol->word);
				node->symbol->defcounter = 1;
				node->symbol->natureza = COUNT_DEF_ERROR;
				semanticerror = 1;
				
			}
			if(node->symbol->defcounter < 1)
			{
				semanticerror = 1;
				node->symbol->natureza = COUNT_DEF_ERROR;
				printf("'%s' used but not defined\n", node->symbol->word);
			}
		}
	}	
	return 0;
}

void newdefinition(struct hash* node, int natureza, int dataType)
{
	node->natureza = natureza;
	node->definitionline[node->defcounter] = node->linenumber;
	node->defcounter++;
	node->dataType = dataType;
}
void natcompare(astree_node* node, char* text, int nat)
{
			if(node->sons[0]->symbol->natureza != nat && node->sons[0]->symbol->natureza != COUNT_DEF_ERROR)
			{semanticerror =1;
				printf("'%s' is used as %s but it was defined as a ", node->sons[0]->symbol->word, text);
			
				switch(node->sons[0]->symbol->natureza)
				{
					case NAT_FUNC:printf("function.\n"); break;
					case NAT_VEC:printf("vector.\n"); break;
					case NAT_ESC:printf("scalar.\n"); break;
					case NAT_PTR:printf("pointer.\n"); break;
					case NAT_PTR_ADDR:printf("pointer address.\n"); break;
				}
			}
}
int verifyNature(astree_node *node)
{

	
	if(node !=0)
	{
		switch(node->type)
		{
		
		case FUNC_DEF:	
		verifyNature(node->sons[2]);//functiuon body
		verifyNature(node->sons[3]);//rest program
			 
			break;
		case FUNC_BODY:	
		verifyNature(node->sons[1]);//local_var_def_list  
		verifyNature(node->sons[2]);//command_list
		
			break;
		case GLOBAL_VAR_DEF_INIT: 
		verifyNature(node->sons[3]);//rest program
			break;
		case GLOBAL_VAR_DEF_PTR:
		verifyNature(node->sons[3]);//rest program
			break;
		case GLOBAL_VAR_DEF_VEC : 
			verifyNature(node->sons[3]);//rest program
			break;
		case GLOBAL_VAR_DEF_VEC_INIT: 
			verifyNature(node->sons[3]);//rest program
			break;
		case INDEX_INIT:
			///
			break;	
		
		case EXP_ARRAY_ACCESS: 
			natcompare(node, "array access", NAT_VEC);
			verifyNature(node->sons[1]);
			break;
		case EXP_FUNC_CALL:
			natcompare(node, "function call", NAT_FUNC);
			verifyNature(node->sons[1]);
			break;
		case ARG_SEQ : 
		verifyNature(node->sons[0]);//arg
		verifyNature(node->sons[1]);//arg
			break;
		case KW_RETURN: 
			
			verifyNature(node->sons[0]);//expression
			break;
		case KW_OUTPUT: 
			verifyNature(node->sons[0]);//expression
			verifyNature(node->sons[1]);//output_rest
			break;
		case KW_INPUT: 
			verifyNature(node->sons[0]);//symbol identifier
			break;
		case OUT_REST: 
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
			break;
		case SYMBOL_LIT_SEQ : 
			///
		break;
		case PARAM : 
			///definition
		break;
		case PARAM_SEQ : 
				//definition
		break;
		case LOCAL_VAR_DEF : 
			///def
		break;
		case LOCAL_VAR_DEF_LIST : 
			///def
		break;
		case LOCAL_VAR_DEF_PTR: 
			///def
			break;
		case CMD_LIST : 
			verifyNature(node->sons[0]);//command list
			break;
		case CMDS :
			verifyNature(node->sons[0]);//rest program
			verifyNature(node->sons[1]);//rest program
			break;
		case PRE_INC : 
			verifyNature(node->sons[0]);
			break;
		case POST_INC: 
			verifyNature(node->sons[0]);
			break;
		case SIMPLE_ATRIB : 
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
			break;
		case INDEX_ATRIB : 
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
			verifyNature(node->sons[2]);
			break;
		case EXP_ADDR : 
			natcompare(node, "pointer address", NAT_PTR_ADDR);
			verifyNature(node->sons[0]);
			break;
		case EXP_PTR: 
			natcompare(node, "pointer", NAT_PTR);
			verifyNature(node->sons[0]);
			break;
		case SYMBOL_IDENTIFIER:
		if(node->symbol->natureza != NAT_ESC && node->symbol->natureza != COUNT_DEF_ERROR)
			{semanticerror =1;
				printf("'%s' is used as scalar but it was defined as a ", node->symbol->word);
			
				switch(node->symbol->natureza)
				{
					case NAT_FUNC:printf("function.\n"); break;
					case NAT_VEC:printf("vector.\n"); break;
					case NAT_ESC:printf("scalar.\n"); break;
					case NAT_PTR:printf("pointer.\n"); break;
					case NAT_PTR_ADDR:printf("pointer address.\n"); break;
				}
			} 

			break;
		case KW_IF: 
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
			break;
		case KW_THEN: 
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
			break;
		case KW_ELSE: 
			verifyNature(node->sons[0]);
			break;
		case KW_LOOP: 
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
			verifyNature(node->sons[2]);
			verifyNature(node->sons[3]);
			break;


		case EXP_ADD:
		case EXP_SUB:
		case EXP_MUL:
		case EXP_DIV:
		case EXP_MORE:
		case EXP_LESS:
		case OPERATOR_EQ:
		case OPERATOR_GE:
		case OPERATOR_LE:
		case OPERATOR_OR:
		case OPERATOR_AND:
		case OPERATOR_NE:
			verifyNature(node->sons[0]);
			verifyNature(node->sons[1]);
		}
	}
	return 0;
}
int count_param(astree_node *node)
{
	if(node==0)
	{
		return 0;
	}
	switch(node->type)
	{
		case FUNC_BODY:	
			return count_param(node->sons[0]);
		case PARAM: 
		case PARAM_SEQ: 
			return 1 + count_param(node->sons[2]);	
	}

	return 1000000;
}
void search_func_def(astree_node *node)
{
	int i = 0;
	if(node !=0)
	{
		if(node->type == FUNC_DEF )
		{

			for(i = 0;i<20;i++)
			{
				node->sons[1]->symbol->param_types[i] = 0;
			}	
			types_param(node, node->sons[2], 0);//preencher lista com os tipos dos parâmetros
			node->sons[1]->symbol->amount_of_param =  count_param(node->sons[2]);

			for(i = 0;i<20;i++)
			{
				printf("%i ", node->sons[1]->symbol->param_types[i]);
			}	
			printf("\n");
		}

		for(i = 0;i<4;i++)
		{
				search_func_def(node->sons[i]);
		}
		
	}
}

int count_arg(astree_node *node)
{

	if(node==0)
	{
		return 0;
	}
	switch(node->type)
	{
		case ARG_SEQ: 
			return 1 + count_arg(node->sons[1]);	
		case SYMBOL_LIT_INTEGER:	
		case SYMBOL_LIT_FALSE:
		case SYMBOL_LIT_TRUE:
		case SYMBOL_LIT_CHAR:
		case SYMBOL_LIT_STRING: 
		case SYMBOL_IDENTIFIER:
			return 1;	
	}

	return 1000000;
}
void search_func_call(astree_node *node)
{
int i = 0, count;
	if(node !=0)
	{
		if(node->type == EXP_FUNC_CALL)
		{
			count = count_arg(node->sons[1]);
			if(node->sons[0]->symbol->amount_of_param == count)
				{
					compare_param_args_types(node->sons[1], node->sons[0]->symbol->param_types, 0);
					//printf("igual: %s\n", node->sons[0]->symbol->word);
				}else{
					semanticerror = 1;
					printf("'%s' is called with %i arguments, but it was defined with %i parameters.\n", node->sons[0]->symbol->word, count, node->sons[0]->symbol->amount_of_param);
				}
			
		}
		for(;i<4;i++)
		{
				search_func_call(node->sons[i]);
		}
		
	}
}

void compare_param_args(astree_node *node)
{
	search_func_def(node);
	search_func_call(node);
}

void types_param(astree_node *fun_def, astree_node *node, int index)
{
	if(node!=0)
	switch(node->type)
	{
		case FUNC_BODY:
			types_param(fun_def, node->sons[0], index);
			break;		
		case PARAM:
		case PARAM_SEQ:
			fun_def->sons[1]->symbol->param_types[index] = node->sons[1]->symbol->dataType;
			types_param(fun_def, node->sons[2], index+1);
			break;
	}

}
int compatible_types(int arg, int param)
{
	if((arg == SYMBOL_LIT_INTEGER || arg == SYMBOL_LIT_CHAR) && (param == KW_WORD || param == KW_BYTE))
		return 1;

	if((arg == SYMBOL_LIT_TRUE || arg == SYMBOL_LIT_FALSE) && param == KW_BOOL)
		return 1;

	printf("Unmatching types.\n");
	return 0;
}



void compare_param_args_types(astree_node *node, int param[20], int index)
{
	
	if(node!=0)
	{
	switch(node->type)
	{
		case ARG_SEQ: 
			compare_param_args_types(node->sons[0], param, index);//primeiro parametro da lista
			compare_param_args_types(node->sons[1], param, index+1);//segundo parametro da lista
			break;	
		case SYMBOL_LIT_INTEGER:				
		case SYMBOL_LIT_FALSE:
		case SYMBOL_LIT_TRUE:
		case SYMBOL_LIT_CHAR:
			compatible_types(node->type, param[index]);
			break;
		case SYMBOL_IDENTIFIER:
		printf("%i", node->symbol->type);
			compatible_types(node->symbol->type, param[index]);// ****descobrir como fazer isso****
			
			break;			
		}
	}
	

}


/*if(node->symbol->natureza == 0)
	{
		switch(node->type)
		{
		
		case FUNC_DEF:	
			
			break;
		case FUNC_BODY:	
			
			break;
		case GLOBAL_VAR_DEF_INIT: 

			
			break;
		case GLOBAL_VAR_DEF_PTR:
		
			break;
		case GLOBAL_VAR_DEF_VEC : 
			
			break;
		case GLOBAL_VAR_DEF_VEC_INIT: 
			
			break;
		case INDEX_INIT:
			
			break;	
		
		case EXP_ARRAY_ACCESS: 

			break;
		case EXP_FUNC_CALL: 

			break;
		case ARG_SEQ : 

			break;
		case KW_RETURN: 
			

			break;
		case KW_OUTPUT: 

			break;
		case KW_INPUT: 

			break;
		case OUT_REST: 

			break;
		case SYMBOL_LIT_SEQ : 

		break;
		case PARAM : 

		break;
		case PARAM_SEQ : 

		break;
		case LOCAL_VAR_DEF : 

		break;
		case LOCAL_VAR_DEF_LIST : 

		break;
		case LOCAL_VAR_DEF_PTR: 

			break;
		case CMD_LIST : 

			break;
		case CMDS :

			break;
		case PRE_INC : 

			break;
		case POST_INC: 

			break;
		case SIMPLE_ATRIB : 

			break;
		case INDEX_ATRIB : 
	
			break;
		case OPERATOR_EQ : 

			break;
		case OPERATOR_LE : 

			break;
		case OPERATOR_GE : 

			break;
		case OPERATOR_OR : 

			break;
		case OPERATOR_AND : 

			break;
		case OPERATOR_NE : 

			break;
		case EXP_ADDR : 

			break;
		case EXP_PTR: 

			break;
		case SYMBOL_LIT_INTEGER:
		
			break;
		case SYMBOL_LIT_FALSE:			
	
			break;
		case SYMBOL_LIT_TRUE:
	
			break;
		case SYMBOL_LIT_CHAR:
		
			break;
		case SYMBOL_LIT_STRING:
		
			break;
		case SYMBOL_IDENTIFIER: 

		
			break;
		case KW_IF: 

			break;
		case KW_THEN: 

			break;
		case KW_ELSE: 

			break;
		case KW_LOOP: 
*/