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

%token <stringType> ID
%token <stringType> CHAR_LITERAL
%token <stringType> DECIMAL_LITERAL
%token <stringType> BOOL_LITERAL
%token <stringType> HEX_LITERAL
%token EQQ NQQ
%token AND OR
%token LT GT LE GE
%token ADD SUB
%token MUL DIV MOD
%token NOT OL CL

%left EQQ NQQ
%left AND OR
%left LT GT LE GE
%left ADD SUB
%left MUL DIV MOD
%left NOT


%%
main_expr : expr main_expr | expr ;

location : ID {printf("location:%s ",$1);};

expr : CL expr OL 
	 |  location 
	 |  literal 
	 |  expr bin_op expr {printf("\n");}
	 |  SUB expr
	 |  NOT expr
	 ;

bin_op : arith_op | rel_op | eq_op  | cond_op;

arith_op : ADD {printf("Add ");} | SUB {printf("sub ");} | MUL {printf("mul ");} | DIV {printf("div ");} | MOD {printf("mod ");};

rel_op : LT {printf("less than ");} | GT {printf("greater than ");} | GE {printf("great equal ");} | LE {printf("less equal ");};

eq_op : EQQ {printf("EQUAL TO(==) ");} | NQQ;

cond_op : AND {printf("AND ");}| OR {printf("OR ");};

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