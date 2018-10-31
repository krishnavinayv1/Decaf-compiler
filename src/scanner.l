%{
#include "parser.tab.hpp"
#define YY_DECL extern "C" int yylex()
	using namespace std;
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
"void" 						{ yylval.stringType = strdup(yytext); return VOID; }
"callout" 					{ return CALLOUT; }
"int" 						{ yylval.stringType = strdup(yytext); return TYPE; }
"boolean" 					{ yylval.stringType = strdup(yytext); return TYPE; }
"break" 					{ return BREAK; }
"continue"					{ return CONTINUE; }
"return" 					{ return RETURN; }
"for" 						{ return FOR; }
"if" 						{ return IF; }
"else" 						{ return ELSE; }
"TRUE"|"FALSE"              {yylval.stringType = strdup(yytext);return BOOL_LITERAL;}
0[xX][0-9a-fA-F]+		 	{yylval.number = atoi(yytext);return INT_LITERAL; }
[0-9][0-9]* 				{yylval.number = atoi(yytext); return INT_LITERAL;}
";" 						{ return SC; }
"," 						{ return COMMA; }
"-=" 						{yylval.stringType = strdup(yytext); return SUBONE; }
"+=" 						{yylval.stringType = strdup(yytext); return PLUSONE; }
"+" 						{yylval.stringType = strdup(yytext); return ADD; }
"-" 						{yylval.stringType = strdup(yytext); return SUB; }
"/" 						{yylval.stringType = strdup(yytext); return DIV; }
"*" 						{yylval.stringType = strdup(yytext); return MUL; }
"%" 						{yylval.stringType = strdup(yytext); return MOD; }
"<=" 						{yylval.stringType = strdup(yytext); return LE; }
">=" 						{yylval.stringType = strdup(yytext); return GE; }
"<" 						{yylval.stringType = strdup(yytext); return LT; }
">" 						{yylval.stringType = strdup(yytext); return GT; }
"==" 						{yylval.stringType = strdup(yytext); return EQQ; }
"!=" 						{yylval.stringType = strdup(yytext); return NQQ; }
"="							{yylval.stringType = strdup(yytext); return EQ;}
"!" 						{yylval.stringType = strdup(yytext); return NOT; }
"&&" 						{yylval.stringType = strdup(yytext); return AND; }
"||" 						{yylval.stringType = strdup(yytext); return OR; }
"(" 						{return CL;}
")" 						{return OL;}
"[" 						{return CS;}
"]" 						{return OS;}
"{" 						{return CB;}
"}" 						{return OB;}
[0-9a-zA-Z_][a-zA-Z0-9_]*		{yylval.stringType = strdup(yytext);return ID;}
{character} 				{yylval.stringType = strdup(yytext);return CHAR_LITERAL; }
\"{string}*\" 				{ return STRING; }
[ \t]				{ }
\n		     		{++lineno;}
.					{ printf("Line No %d: Unrecognized Character\n", lineno); }

%%

