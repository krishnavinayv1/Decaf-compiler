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

%%
"class" 					{ return CLASS;}
"Program"					{ return PROGRAM;}	
"void" 						{ return VOID; }
"callout" 					{ return CALLOUT; }
"int" 						{ return TYPE; }
"boolean" 					{ return TYPE; }
"break" 					{ return BREAK; }
"continue"					{ return CONTINUE; }
"return" 					{ return RETURN; }
"for" 						{ return FOR; }
"if" 						{ return IF; }
"else" 						{ return ELSE; }
"TRUE"|"FALSE"              {yylval.stringType = strdup(yytext);return BOOL_LITERAL;}
0[xX][0-9a-fA-F]+		 	{yylval.stringType = strdup(yytext);return HEX_LITERAL 	; }
";" 						{ return SC; }
"," 						{ return COMMA; }
"-=" 						{ return SUBONE; }
"+=" 						{ return PLUSONE; }
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
"="							{ return EQ;}
"!" 						{ return NOT; }
"&&" 						{ return AND; }
"||" 						{ return OR; }
"(" 						{return CL;}
")" 						{return OL;}
"[" 						{return CS;}
"]" 						{return OS;}
"{" 						{return CB;}
"}" 						{return OB;}
[0-9][0-9]* 				{yylval.stringType = strdup(yytext);return DECIMAL_LITERAL;}
[0-9a-zA-Z][a-zA-Z0-9]*		{yylval.stringType = strdup(yytext);return ID;}
{character} 				{yylval.stringType = strdup(yytext);return CHAR_LITERAL; }
\"{string}*\" 				{ return STRING; }
[ \t]				{ }
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

