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