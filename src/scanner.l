%{
#include "parser.tab.h"
int lineno = 0;
%}

digit [0-9]
letter [a-zA-Z]
alpha [0-9a-zA-Z]
delim [ \t]+
char [ -~]
character   \'{char}\'


%%
"TRUE"|"FALSE"              {yylval.stringType = strdup(yytext);return BOOL_LITERAL;}
0[xX][0-9a-fA-F]+		 	{yylval.stringType = strdup(yytext);return HEX_LITERAL 	; }
"+" 						{ return ADD; }
"-" 						{ return SUB; }
"/" 						{ return DIV; }
"*" 						{ return MUL; }
"%" 						{ return MOD; }
"<=" 						{ return LE; }
">=" 						{ return GE; }
"<" 						{ return LT; }
">" 						{ return GT; }
"==" 						{ return EQQ; }
"!=" 						{ return NQQ; }
"!" 						{ return NOT; }
"&&" 						{ return AND; }
"||" 						{ return OR; }
"(" 						{return CL;}
")" 						{return OL;}
[0-9][0-9]* 				{yylval.stringType = strdup(yytext);return DECIMAL_LITERAL;}
[0-9a-zA-Z][a-zA-Z0-9]*		{yylval.stringType = strdup(yytext);return ID;}
{character} 				{yylval.stringType = strdup(yytext);return CHAR_LITERAL; }
[ \t]				{ }
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

