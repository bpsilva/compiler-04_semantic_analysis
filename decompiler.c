#include "AST.h"
#include "hash.h"
#include "decompiler.h"
#include "y.tab.h"
void asttofile(astree_node* node)
{
	
	if(node!=0)
	{
			
	switch(node->type)
	{
		
		case GLOBAL_VAR_DEF: 
			asttofile(node->sons[0]);
			asttofile(node->sons[1]);
			writechar('\n');
			asttofile(node->sons[2]);
			break;
		case INI_FUNC_DEF:			
			asttofile(node->sons[0]);
			asttofile(node->sons[1]);
			writechar('\n');
			asttofile(node->sons[2]);
			break;
		case FUNC_DEF:	
			filewrite(" ");		
			asttofile(node->sons[0]);
			filewrite("(");
			asttofile(node->sons[1]);
			filewrite(")");
			writechar('\n');
			asttofile(node->sons[2]);
			asttofile(node->sons[3]);
			break;
		case GLOBAL_VAR_DEF_INIT: 
			writechar(' ');	
			asttofile(node->sons[0]);
			writechar(':');
			asttofile(node->sons[1]);
			writechar(';');
			break;
		case GLOBAL_VAR_DEF_PTR:
			writechar(' ');	
			filewrite("$");	
			asttofile(node->sons[0]);
			writechar(':');
			asttofile(node->sons[1]);
			writechar(';');
			break;
		case GLOBAL_VAR_DEF_VEC : 
			writechar(' ');	
			asttofile(node->sons[0]);
			writechar('[');
			asttofile(node->sons[1]);
			writechar(']');
			writechar(';');
			break;
		case GLOBAL_VAR_DEF_VEC_INIT: 
			writechar(' ');	
			asttofile(node->sons[0]);
			writechar('[');
			asttofile(node->sons[1]);
			filewrite("] :");
			asttofile(node->sons[2]);
			writechar(';');
			break;
		case EXP_ADD: 
			operationwrite("+",node);
			break;
		case EXP_SUB : 
			operationwrite("-",node);
			break;
		case EXP_DIV:
			operationwrite("/",node);
			 break;
		case EXP_MUL: 
			operationwrite("*",node);
			break;
		case EXP_LESS: 
			operationwrite("<",node);
			break;
		case EXP_MORE : 
			operationwrite(">",node);
			break;
		case EXP_ARRAY_ACCESS: 
			asttofile(node->sons[0]);
			writechar('[');
			asttofile(node->sons[1]);
			writechar(']');
			break;
		case EXP_FUNC_CALL: 
			asttofile(node->sons[0]);
			writechar('(');
			asttofile(node->sons[1]);
			writechar(')');
			break;
		case ARG_SEQ : 
			asttofile(node->sons[0]);
			filewrite(" , ");
			asttofile(node->sons[1]);
			break;
		case KW_RETURN: 
			filewrite("return ");
			asttofile(node->sons[0]);
			break;
		case KW_OUTPUT: 
			filewrite("output ");
			asttofile(node->sons[0]);
			asttofile(node->sons[1]);
			break;
		case KW_INPUT: 
			filewrite("input ");
			asttofile(node->sons[0]);
			break;
		case OUT_REST: 
			filewrite(", ");
			asttofile(node->sons[0]);
			asttofile(node->sons[1]);
			break;
		case SYMBOL_LIT_SEQ : 
			asttofile(node->sons[0]);
			writechar(' ');
			asttofile(node->sons[1]);
		break;
		case PARAM : 
			asttofile(node->sons[0]);
			writechar(' ');
			asttofile(node->sons[1]);
			asttofile(node->sons[2]);
		break;
		case PARAM_SEQ : 
			filewrite(" , ");
			asttofile(node->sons[0]);
			writechar(' ');
			asttofile(node->sons[1]);
			asttofile(node->sons[2]);
		break;
		case LOCAL_VAR_DEF : 
			asttofile(node->sons[0]);
			filewrite(" ");
			asttofile(node->sons[1]);
			filewrite(": ");
			asttofile(node->sons[2]);
			filewrite(";");
			writechar('\n');
		break;
		case LOCAL_VAR_DEF_LIST : 
			asttofile(node->sons[0]);
			asttofile(node->sons[1]);
		break;
		case LOCAL_VAR_DEF_PTR: 
			asttofile(node->sons[0]);
			filewrite(" $");
			asttofile(node->sons[1]);
			filewrite(": ");
			asttofile(node->sons[2]);
			filewrite(";");
			break;

		case CMD_LIST : 
			filewrite("{");		
			asttofile(node->sons[0]);
			filewrite("}");		
			break;
		case CMDS : 
			asttofile(node->sons[0]);
			filewrite("; ");	
			writechar('\n');
			asttofile(node->sons[1]);
			break;
		case PRE_INC : 
			filewrite("++");
			asttofile(node->sons[0]);
			break;
		case POST_INC: 
			asttofile(node->sons[0]);
			filewrite("++");
			break;
		case SIMPLE_ATRIB : 
			asttofile(node->sons[0]);
			filewrite(" = ");	
			asttofile(node->sons[1]);
			break;
		case INDEX_ATRIB : 
			asttofile(node->sons[0]);
			filewrite("[");	
			asttofile(node->sons[1]);
			filewrite("] = ");	
			asttofile(node->sons[2]);
			break;
		case OPERATOR_EQ : 
			asttofile(node->sons[0]);
			filewrite(" == ");	
			asttofile(node->sons[1]);
			break;
		case OPERATOR_LE : 
			asttofile(node->sons[0]);
			filewrite(" <= ");	
			asttofile(node->sons[1]);
			break;
		case OPERATOR_GE : 
			asttofile(node->sons[0]);
			filewrite(" >= ");	
			asttofile(node->sons[1]);
			break;
		case OPERATOR_OR : 
			asttofile(node->sons[0]);
			filewrite(" || ");	
			asttofile(node->sons[1]);
			break;
		case OPERATOR_AND : 
			asttofile(node->sons[0]);
			filewrite(" && ");	
			asttofile(node->sons[1]);
			break;
		case OPERATOR_NE : 
			asttofile(node->sons[0]);
			filewrite(" != ");	
			asttofile(node->sons[1]);
			break;
		case EXP_ADDR : 
			filewrite("&");	
			asttofile(node->sons[0]);
			break;
		case EXP_PTR: 
			filewrite("$");	
			asttofile(node->sons[0]);
			break;
		case SYMBOL_LIT_INTEGER:
			filewrite(node->symbol->word);
			break;
		case SYMBOL_LIT_FALSE:			
			filewrite("false");
			break;
		case SYMBOL_LIT_TRUE:
			filewrite("true");
			break;
		case SYMBOL_LIT_CHAR:
			filewrite(node->symbol->word);
			break;
		case SYMBOL_LIT_STRING:
			filewrite(node->symbol->word);
			break;
		case SYMBOL_IDENTIFIER: 
			filewrite(node->symbol->word);
			break;
		case KW_WORD: 
			filewrite("word");
			break;
		case KW_BYTE: 
			filewrite("byte");
			break;
		case KW_BOOL: 
			filewrite("bool");
			break;
		case KW_IF: 
			filewrite("if (");
			asttofile(node->sons[0]);
			filewrite(") ");
			asttofile(node->sons[1]);
			break;
		case KW_THEN: 
			filewrite("then ");
			asttofile(node->sons[0]);
			filewrite(" ");
			asttofile(node->sons[1]);
			break;
		case KW_ELSE: 
			filewrite("else ");
			asttofile(node->sons[0]);
			break;
		case KW_LOOP: 
			filewrite("loop (");
			asttofile(node->sons[0]);
			filewrite(" ; ");
			asttofile(node->sons[1]);
			filewrite(" ; ");
			asttofile(node->sons[2]);
			filewrite(") ");
			writechar('\n');
			asttofile(node->sons[3]);
			break;
		default: printf("No rule applies");
	}
	}


}
void filewrite(char* text)
{
	
	//fprintf(file, "%s", text);
	fputs(text, file);

	
}
void operationwrite(char* text, astree_node *node)
{
	filewrite(" ");			
	asttofile(node->sons[0]);
	filewrite(" ");			
	filewrite(text);
	filewrite(" ");			
	asttofile(node->sons[1]);
}

void writechar(char c)
{
	fprintf(file, "%c", c);
}


