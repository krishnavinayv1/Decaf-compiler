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
string (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])
hex_digit {digit}|[a-fA-F]


%%
"TRUE"|"FALSE"              {yylval.stringType = strdup(yytext);return BOOL_LITERAL;}
"0x"{hex_digit}+|{digit}+ 	{yylval.stringType = strdup(yytext);return HEX_DIGIT; }
"+" 						{ return ADD; }
"-" 						{ return SUB; }
"/" 						{ return DIV; }
"*" 						{ return MUL; }
"%" 						{ return MOD; }
"<" 						{ return LT; }
">" 						{ return GT; }
"<=" 						{ return LE; }
">=" 						{ return GE; }
"==" 						{ return EQQ; }
"!=" 						{ return NQQ; }
"!" 						{ return NOT; }
"&&" 						{ return AND; }
"||" 						{ return OR; }
"(" 						{return CL;}
")" 						{return OL;}
[0-9][0-9]* 				{yylval.stringType = strdup(yytext);return DECIMAL_LITERAL;}
[a-zA-Z0-9][a-zA-Z0-9]*		{yylval.stringType = strdup(yytext);return ID;}
{character} 				{yylval.stringType = strdup(yytext);return CHAR_LITERAL; }
[ \t]				{ }
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

