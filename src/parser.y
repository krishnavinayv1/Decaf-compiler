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
	 | CLASS PROGRAM CB OB;
	 | CLASS PROGRAM CB method_declarations OB;
	 | CLASS PROGRAM CB field_declarations  OB;

field_declarations : field_declaration SC | field_declarations field_declaration SC {printf("field_declarations done\n");};
				   
field_declaration  : TYPE variables;

variables 		   : variable | variables COMMA variable;

variable           : ID | ID CS int_literal OS { printf("dsff\n");};

method_declarations : method_declaration | method_declarations method_declaration;

method_declaration  : TYPE ID args block | VOID ID args block;

args               : CL OL | CL TYPE ID OL | CL TYPE ID arg OL;

arg                : COMMA TYPE ID | COMMA TYPE ID arg;

block              : CB var_declarations statements OB;
				   | CB statements OB;
				   | CB var_declarations OB;

var_declarations   : var_declaration SC | var_declaration SC var_declarations;

var_declaration    : TYPE location | TYPE location var_names;

var_names          : COMMA location | COMMA location var_names;

statements         : statement | statements statement;

statement: assignment
		 | function_call SC
		 | IF CL expr OL block
		 | IF CL expr OL block ELSE block  
		 | { printf("For loop starting\n");} FOR identifier EQ expr COMMA expr block 
		 | RETURN SC 
		 | RETURN expr SC 
		 | BREAK SC 
		 | CONTINUE SC 
		 | block;

assignment: location EQ {printf("EQUALS \n");} expr SC  
		  | location PLUSONE expr SC 
	      | location SUBONE expr SC;


function_call: ID CL pars OL
			 | CALLOUT CL STRING callout_args OL;

pars         : expr 
			 | pars COMMA expr;

identifier   : ID {printf("location:%s\n ",$1);}

location : ID {printf("location:%s\n ",$1);}
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
	 |  NOT expr
	 |  expr DIV expr 
	 |  expr MUL expr
	 |  expr ADD expr
	 |  SUB {printf("sub expression \n");} expr 
	 ;

literal : int_literal {printf("int literal \n");} | CHAR_LITERAL | BOOL_LITERAL;

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