%{
#include<stdlib.h>
#include<stdio.h>

#include "AST.c"
#include "hash.h"
#include "decompiler.h"

extern FILE * yyin;
%}

%token KW_WORD  500
%token KW_BOOL     501 
%token KW_BYTE    502
%token KW_IF       503
%token KW_THEN      504	
%token KW_ELSE     505
%token KW_LOOP   506
%token KW_INPUT  507
%token KW_RETURN   508
%token KW_OUTPUT 509

%token OPERATOR_LE 510
%token OPERATOR_GE 511
%token OPERATOR_EQ 512
%token OPERATOR_NE 513
%token OPERATOR_AND 514
%token OPERATOR_OR 515

%token TOKEN_ERROR 

%union
{
	struct hash* symbol;
	struct astree_node *astree;
	int n;

}



%token <symbol>SYMBOL_UNDEFINED 0
%token  <symbol>SYMBOL_LIT_INTEGER 1
%token  <symbol>SYMBOL_LIT_FLOATING 2
%token  <symbol>SYMBOL_LIT_TRUE 3
%token <symbol> SYMBOL_LIT_FALSE 4
%token <symbol>SYMBOL_LIT_CHAR 5
%token <symbol>SYMBOL_LIT_STRING 6 
%token  <symbol>SYMBOL_IDENTIFIER 7

%type <astree> init expression output_rest program  arg command_list simple_command atrib value  flux_control then else option local_var_def_list local_var_def param paramseq symbol_lit_seq commands func_body index_init
%type <n> op type


 
%left KW_IF KW_ELSE



%%
init: program 		{astree = $1;}
	;
program: 					{$$ = 0;}
	|type SYMBOL_IDENTIFIER  func_body program
			{$2->dataType = $1; $$ = astcreate(FUNC_DEF,
					0,
					0,	astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0)
					,$3,$4);}	
	|type SYMBOL_IDENTIFIER ':' value ';' program	
			{$2->dataType = $1; $$ = astcreate(GLOBAL_VAR_DEF_INIT, 0,
				0, astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),
				$4,$6);}	
	|type '$'SYMBOL_IDENTIFIER ':' value ';' program
			{$3->dataType = $1; $$ = astcreate(GLOBAL_VAR_DEF_PTR, 0,
				0,	astcreate(SYMBOL_IDENTIFIER,$3,0,0,0,0),
				$5,$7);}		

	|type SYMBOL_IDENTIFIER '[' SYMBOL_LIT_INTEGER ']'';' program 	
				{$2->dataType = $1;$$ = astcreate(GLOBAL_VAR_DEF_VEC,0,
						0,astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),
						astcreate( SYMBOL_LIT_INTEGER,$4,0,0,0,0),
						$7);}

	|type SYMBOL_IDENTIFIER index_init program
				{$2->dataType = $1; $$ = astcreate(GLOBAL_VAR_DEF_VEC_INIT,0,
						0, astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),
						$3,	$4);}		
	;
	
	index_init: '[' SYMBOL_LIT_INTEGER ']' ':' symbol_lit_seq ';' {$$ = astcreate(INDEX_INIT,0,astcreate(SYMBOL_LIT_INTEGER,$2,0,0,0,0), $5, 0, 0);}
				;
func_body: '(' param ')' local_var_def_list  command_list  {$$ = astcreate(FUNC_BODY,0,$2,$4,$5,0);}
			;

	



command_list: '{' commands '}'		{$$ = astcreate(CMD_LIST,0,$2,0,0,0);}

commands: 				{$$ = 0;}	
	|simple_command ';' commands	{$$ = astcreate(CMDS,0,$1,$3,0,0);}	
	;

simple_command: 					{$$ = 0;}	
	|atrib						{$$ = $1;}	
	|flux_control 					{$$ = $1;}		
	|KW_INPUT SYMBOL_IDENTIFIER 			{$$ = astcreate(KW_INPUT, 0, astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),0,0,0);}
	|KW_OUTPUT expression output_rest 		{$$ = astcreate(KW_OUTPUT,0,$2,$3, 0,0 );}
	|KW_RETURN expression				{$$ = astcreate(KW_RETURN,0,$2,0,0,0);}
	;
atrib: 
	'+''+'SYMBOL_IDENTIFIER				{$$ = astcreate(PRE_INC,0,astcreate(SYMBOL_IDENTIFIER,$3,0,0,0,0),0,0,0);}
	|SYMBOL_IDENTIFIER '+''+'			{$$ = astcreate(POST_INC,0,astcreate(SYMBOL_IDENTIFIER,$1,0,0,0,0),0,0,0);}
	|SYMBOL_IDENTIFIER '=' expression		{$$ = astcreate(SIMPLE_ATRIB,0, astcreate(SYMBOL_IDENTIFIER, $1,0,0,0,0),$3,0,0);}
	| SYMBOL_IDENTIFIER '[' expression ']' '=' expression  {$$ = astcreate(INDEX_ATRIB,0, astcreate(SYMBOL_IDENTIFIER, $1,0,0,0,0),$3,$6,0);}
	;


expression:
	expression op expression			{$$ = astcreate($2,0,$1,$3,0,0);}
	//|expression '-'expression			{$$ = astcreate(EXP_SUB,0,$1,$3,0,0);}
	//|expression '*' expression			{$$ = astcreate(EXP_MUL,0,$1,$3,0,0);}
	//|expression '/' expression			{$$ = astcreate(EXP_DIV,0,$1,$3,0,0);}
	//|expression '>' expression 			{$$ = astcreate(EXP_MORE,0,$1,$3,0,0);}
	//|expression OPERATOR_LE expression 			{$$ = astcreate(OPERATOR_LE,0,$1,$3,0,0);}
	//|expression '<' expression 			{$$ = astcreate(EXP_LESS,0,$1,$3,0,0);}
	//|expression "||" expression 			{$$ = astcreate(EXP_OR,0,$1,$3,0,0);}
	//|expression "&&" expression 			{$$ = astcreate(EXP_AND,0,$1,$3,0,0);}
	|SYMBOL_IDENTIFIER '[' expression ']' 		{$$ = astcreate(EXP_ARRAY_ACCESS,0,astcreate(SYMBOL_IDENTIFIER,$1,0,0,0,0),$3,0,0);}
	|SYMBOL_IDENTIFIER				{$$ = astcreate(SYMBOL_IDENTIFIER,$1,0,0,0,0);}
	|value						{$$ = $1;}
	|SYMBOL_IDENTIFIER '(' arg ')'			{$$ = astcreate(EXP_FUNC_CALL,0,astcreate(SYMBOL_IDENTIFIER,$1,0,0,0,0),$3,0,0);}
	|'&'SYMBOL_IDENTIFIER				{$$ = astcreate(EXP_ADDR,0,astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),0,0,0);} 
	|'$'SYMBOL_IDENTIFIER  				{$$ = astcreate(EXP_PTR,0,astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),0,0,0);} 
	;



op: '+' 	{$$ = EXP_ADD; }
	|'-' 	{$$=EXP_SUB; }
	|'*'	{$$=EXP_MUL;}
	|'/'	{$$=EXP_DIV;}
	| '>' 	{$$=EXP_MORE;}
	|'<'	{$$=EXP_LESS;}
	|OPERATOR_EQ	{$$=OPERATOR_EQ;}
	|OPERATOR_GE	{$$=OPERATOR_GE;}
	|OPERATOR_LE {$$=OPERATOR_LE;}
	|OPERATOR_OR {$$=OPERATOR_OR;}
	|OPERATOR_AND {$$=OPERATOR_AND;}
	|OPERATOR_NE {$$=OPERATOR_NE;}
	;


arg: 							{$$ = 0;}
	|value ',' arg					{$$ = astcreate(ARG_SEQ,0,$1,$3,0,0);}
	|SYMBOL_IDENTIFIER ',' arg			{$$ = astcreate(ARG_SEQ,0,astcreate(SYMBOL_IDENTIFIER,$1,0,0,0,0),$3,0,0);}
	|SYMBOL_IDENTIFIER 				{$$ = astcreate(SYMBOL_IDENTIFIER,$1,0,0,0,0);}
	|value 						{$$ = $1;}
	;


value:	SYMBOL_LIT_INTEGER 				{$$ = astcreate(SYMBOL_LIT_INTEGER,$1,0,0,0,0);}
	|SYMBOL_LIT_FALSE 					{$$ = astcreate(SYMBOL_LIT_FALSE,$1,0,0,0,0);}
	|SYMBOL_LIT_TRUE	  				{$$ = astcreate(SYMBOL_LIT_TRUE,$1,0,0,0,0);}
	|SYMBOL_LIT_CHAR   					{$$ = astcreate(SYMBOL_LIT_CHAR,$1,0,0,0,0);}
	|SYMBOL_LIT_STRING					{$$ = astcreate(SYMBOL_LIT_STRING,$1,0,0,0,0);}
	;
	
output_rest:							{$$ = 0;}
	|',' expression output_rest			{$$ = astcreate(OUT_REST,0,$2,$3,0,0);}
	;


flux_control: 
	KW_IF '('expression')' then			{$$ = astcreate(KW_IF,0,$3,$5,0,0);}
	|KW_LOOP '(' simple_command ';' expression ';' simple_command ')' command_list {$$ = astcreate(KW_LOOP,0,$3,$5,$7,$9);}
	;

then: 
	KW_THEN option else 			{$$ = astcreate(KW_THEN,0,$2,$3,0,0);}
	;
else: 								{$$ = 0;}
	| KW_ELSE option 				{$$ = astcreate(KW_ELSE,0,$2,0,0,0);}
	;

option: 
	command_list 					{$$ = $1;}
	|simple_command 				{$$ = $1;}
	;

local_var_def_list:					{$$ = 0;}
	|local_var_def local_var_def_list		{$$ = astcreate(LOCAL_VAR_DEF_LIST,0,$1,$2, 0,0);}
	;

local_var_def: type SYMBOL_IDENTIFIER ':' value ';' 	{$2->dataType = $1;$$ = astcreate(LOCAL_VAR_DEF,0,0,astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0), $4,0);}
	|type '$'SYMBOL_IDENTIFIER ':' value ';'	{$3->dataType = $1;$$ = astcreate(LOCAL_VAR_DEF_PTR,0,0,astcreate(SYMBOL_IDENTIFIER,$3,0,0,0,0), $5,0);}
	;		
param: 							{$$ = 0;}
	|type SYMBOL_IDENTIFIER paramseq		{$2->dataType = $1;$$ = astcreate(PARAM,0,0,astcreate(SYMBOL_IDENTIFIER,$2,0,0,0,0),$3,0);}
	;

paramseq: 						{$$ = 0;}
	| ',' type SYMBOL_IDENTIFIER paramseq		{$3->dataType = $2;$$ = astcreate(PARAM_SEQ,0,0,astcreate(SYMBOL_IDENTIFIER,$3,0,0,0,0),$4,0);}
	;

symbol_lit_seq:  
	value						{$$ = $1;}
	|value symbol_lit_seq				{$$ = astcreate(SYMBOL_LIT_SEQ,0,$1,$2,0,0);}
	; 
type: 	KW_WORD		{$$ = KW_WORD;}	
	| KW_BOOL	{$$ = KW_BOOL;}	
	| KW_BYTE	{$$ = KW_BYTE;}	
	;
%%

int main(int argc, char **argv)
{

	int out;
	astree = 0;

	if(argc < 3)
	{
		printf("****Missing parameters***\n");
		exit(1);
	}
		


	yyin = fopen(argv[1], "r");
	if (yyin==NULL)
  	{
    	printf("File \"%s\" not found!!\n", argv[1]);
    	exit(2);
  	}

	file = fopen(argv[2], "w+");

	out = yyparse();
	//printast(astree, 0);
	asttofile(astree);
	exit (out);

}

yyerror(s) char *s; {
       fprintf( stderr, "Syntax error. Line: %i\n", getLineNumber() );
	exit(3);
       }
