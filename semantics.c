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
				printf("Multple definitions %s\n", node->symbol->word);
			if(node->symbol->defcounter < 1)
				printf("'%s' used but not defined\n", node->symbol->word);
		}
	}	
	return 0;
}