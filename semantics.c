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
					compare_func_type_return(node);

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
			if(!compatible_types(node->type, param[index]))
			{
				printf("Unmatching types between function parameters and arguments.\n");
				semanticerror = 1;
			}
			break;
		case SYMBOL_IDENTIFIER:
		

			if(!((node->symbol->dataType == KW_BOOL && param[index] == KW_BOOL)||
				((node->symbol->dataType == KW_WORD || node->symbol->dataType == KW_BYTE) && 
				(param[index] == KW_WORD || param[index] == KW_BYTE))))
				{
					semanticerror = 1;
					printf("Unmatching types between function parameters and arguments.\n");				
				}	
			break;			
		}
	}
}

int flag;

void compare_func_type_return(astree_node *node)
{
	int return_type;
	int i;
	if(node == 0)
		return;

	if(node->type == FUNC_DEF)
	{
		flag = 0;
		return_type = find_func_return_type(node->sons[2]->sons[2]->sons[0]);
		//printf("return: %i\n", return_type);
		if(return_type == 0)
		{
			if(!flag)
			{
				semanticerror = 1;
				printf("Every function must have a return statement.\n");		
			}
		}else
		{
		//	printf("returntype: %i, dataType: %i\n", return_type , node->sons[1]->symbol->dataType);
			if(!(
				(compatible_types(return_type , node->sons[1]->symbol->dataType)) || 
				((return_type == KW_BYTE && node->sons[1]->symbol->dataType == KW_WORD) || (node->sons[1]->symbol->dataType == return_type ))
				)
		  	)
			{
				semanticerror = 1;
				printf("Returning type doesn't match function definition type in function '%s'.\n", node->sons[1]->symbol->word);			
			}
		}
	}
	for(i = 0 ; i < 4 ; i++)
	{
		compare_func_type_return(node->sons[i]);
	}
}


int find_func_return_type(astree_node *node)
{
int ret1 = 0, ret2 = 0, i, j;

	if(node==0)
		return 0;
	
	if(node->type == KW_RETURN)
	{
		
		int temp = expression_type(node->sons[0]);
		
		return temp;
	}
	if(node->type == CMDS)
	{	


		ret1 = find_func_return_type(node->sons[0]);
		ret2 = find_func_return_type(node->sons[1]);
		//printf("%i , %i\n" ,ret1, ret2);
		if(ret1 == ret2 && ret1 != 0 && ret2 != 0)
		{
			return ret1;
		}else{ 

			if(ret1 != 0 && ret2 == 0)
				return ret1;
			if(ret1 == 0 && ret2 != 0)
				return ret2;

			return 0;
			}

	}
	
		
	int aux[4];
	
	for(i = 0 ; i < 4 ; i++)
	{
		aux[i] = find_func_return_type(node->sons[i]);
		
	}
/*
	printf("Aux: ");
	
	for(i = 0 ; i < 4 ; i++)
	{
		printf("%i ", aux[i]);
	}
	
	printf("\n");
*/	
	int equals = 1, not_null = 0;
	// o erro está aqui: deveria comparar todos os tipos compativeis
	for(i = 0 ; i < 4 ; i++)
	{
		for(j = i ; j < 4 ; j++)
		{	
			if(aux[i] != 0 && aux[j] != 0)
			{
				not_null = aux[i];
				if(
					!(
						(aux[i] == KW_BYTE && aux[j] == KW_BYTE)
						||(aux[i] == KW_BYTE && aux[j] == KW_WORD)
						||(aux[i] == KW_WORD && aux[j] == KW_BYTE)
						||(aux[i] == KW_WORD && aux[j] == KW_WORD)
						||(aux[i] == KW_BOOL && aux[j] == KW_BOOL)
					)
				  )	
				{
					equals = 0;
					flag = 1;
					semanticerror = 1;
					printf("Every pair of return statements must have compatible types\n");
				}
			}
		}	
	}

	if(equals && not_null)
	{
		return not_null;
	}

	return 0;
}

int expression_type(astree_node* node)
{

	if(node==0)
		return 0;
	switch(node->type)
	{
		case SYMBOL_LIT_INTEGER:
		case SYMBOL_LIT_CHAR:
			return KW_BYTE;
		case SYMBOL_LIT_FALSE:
		case SYMBOL_LIT_TRUE: 
		 	return KW_BOOL; 
		case SYMBOL_LIT_STRING: 
			semanticerror = 1; 
			printf("Strings must be user only in output expressions!");
			return KW_BYTE;
		case EXP_ARRAY_ACCESS:
		case EXP_FUNC_CALL:
		case EXP_ADDR:
		case EXP_PTR:
			return expression_type(node->sons[0]);
		case SYMBOL_IDENTIFIER:
			return node->symbol->dataType;
		case '+':
		case '-':
		case '*':
		case '/':
			return KW_BYTE;
		case OPERATOR_EQ:
		case OPERATOR_GE:
		case OPERATOR_LE:
		case OPERATOR_OR:
		case OPERATOR_AND:
		case OPERATOR_NE:
		case '>':
		case '<':
			return KW_BOOL;
	}
	

	return 0;
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