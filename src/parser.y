%{
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
extern char* yytext;
%}

%union
{
	char* stringType;
}
%start prom

%token CALLOUT STRING
%token <stringType> ID
%token <stringType> CHAR_LITERAL
%token <stringType> DECIMAL_LITERAL
%token <stringType> BOOL_LITERAL
%token <stringType> HEX_LITERAL
%token EQQ NQQ EQ
%token AND OR
%token LT GT LE GE
%token ADD SUB
%token MUL DIV MOD 
%token NOT OL CL OS CS CB OB
%token CLASS PROGRAM TYPE SC COMMA VOID
%token IF FOR BREAK CONTINUE ELSE RETURN
%token PLUSONE SUBONE	


%left EQQ NQQ
%left AND OR
%left LT GT LE GE
%left ADD SUB
%left MUL DIV MOD
%left NOT


%%

prom : CLASS PROGRAM CB field_declarations method_declarations OB;

field_declarations : | field_declarations field_declaration SC {printf("field_declarations done\n");};
				   
field_declaration  : TYPE variables;

variables 		   : variable | variables COMMA variable;

variable           : ID | ID CS int_literal OS;

method_declarations : | method_declarations method_declaration;

method_declaration  : TYPE ID args block | VOID ID args block;

args               : CL OL | CL TYPE ID	arg OL;

arg                : | COMMA TYPE ID arg;

block              : CB var_declarations statements OB;

var_declarations   : | var_declaration SC var_declarations;

var_declaration    : TYPE ID var_names;

var_names          : | COMMA ID var_names;

statements         : | statements statement;

statement: assignment
		 | function_call SC
		 | IF CL expr OL block
		 | IF CL expr OL block ELSE block  
		 | FOR ID EQ expr COMMA expr block 
		 | RETURN SC 
		 | RETURN expr SC 
		 | BREAK SC 
		 | CONTINUE SC 
		 | block;

assignment: location EQ expr SC {printf("EQUALS Expression done\n");} 
		  | location PLUSONE expr SC 
	      | location SUBONE expr SC;


function_call: ID CL pars OL
			 | CALLOUT CL STRING callout_args OL;

pars         : expr 
			 | pars COMMA expr;

location : ID {printf("location:%s ",$1);}
		 | ID CS expr OS;

callout_args: | callout_args COMMA callout_arg;

callout_arg: expr 
		   | STRING;

expr : CL expr OL 
	 |  location 
	 |  literal
	 |  expr SUB expr
	 |  expr OR expr
	 |  expr AND expr 
	 |  expr NQQ expr
	 |  expr EQQ expr
	 |  expr GE expr
	 |  expr LE expr
	 |  expr GT expr
	 |  expr LT expr
	 |  expr MOD expr
	 |  expr DIV expr { printf("division done\n");}
	 |  expr MUL expr
	 |  expr ADD expr
	 //|  SUB expr
	 |  NOT expr
	 ;

literal : int_literal {printf("int literal ");} | CHAR_LITERAL | BOOL_LITERAL;

int_literal : DECIMAL_LITERAL | HEX_LITERAL;


%%

main(int argc, char **argv)
{
	if(argc == 1)
    {
		fprintf(stderr, "Store the input expressions in a file name and give it as a argument\n");
		exit(1);
	}
	printf("Parsing started\n");
	yyin = fopen(argv[1], "r");
	yyparse();
	printf("THE END\n");
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}