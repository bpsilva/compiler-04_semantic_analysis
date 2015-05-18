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
				semanticerror = 1;
				//printf("Multple definitions %s\n", node->symbol->word);
			}
			if(node->symbol->defcounter < 1)
			{
				semanticerror = 1;
				//printf("'%s' used but not defined\n", node->symbol->word);
			}
		}
	}	
	return 0;
}

int verifyNature(astree_node *node)
{
	int i;
	if(node !=0)
	{
		for(i = 0 ; i < 4  ; i++)
		{
			verifyNature(node->sons[i]);
		}
	}
	if(node->symbol->natureza == 0)
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

			break;
		default: printf("No rule applies: %i\n", node->type);
		}
	}	


return 0;
}