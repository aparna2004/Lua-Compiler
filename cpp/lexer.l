%{
#include <iostream>
#include "ast.h"
#include "parser.tab.h"   
extern "C" int yylex();
%}

%option noyywrap c++


%%
[ \t\r\n]+               ;     // Ignore whitespace
"--".*                    ;     // Ignore comments

"if"                      { return IF; }
"else"                    { return ELSE; }
"elseif"                   { return ELSEIF; }


"while"                   { return WHILE; }
"then"                    { return THEN; }
"do"                      { return DO; }
"end"                     { return END; }

"for"                     { return FOR; }
"in"                      { return IN; }
","                       { return COMMA; }
"print"                   { return PRINT; }
".."                      { return CONCAT; } 

"true"                    { yylval.boolVal = true; return TRUE; }
"false"                   { yylval.boolVal = false; return FALSE; }
"and"                     { return AND; }
"or"                      { return OR; }
"not"                     { return NOT; }

\"[^\"]*\"  { 
    std::string str = yytext;
    // Remove the quotes
    str = str.substr(1, str.length() - 2);
    yylval.strVal = strdup(str.c_str());
    return STRING; 
}
[0-9]+                     { yylval.intVal = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*      { yylval.strVal = strdup(yytext); return IDENT; }

"("                        { return LPAREN; }
")"                        { return RPAREN; }
"{"                        { return LBRACE; }
"}"                        { return RBRACE; }
"="                        { return ASSIGN; }
"=="                       { return EQ; }
">="                       { return GE; }
"<="                       { return LE; }
"~="                       { return NE; }
"<"                        { return LT; }
">"                        { return GT; }
"+"                        { return PLUS; }
"-"                        { return MINUS; }
"*"                        { return MULT; }
"/"                        { return DIV; }

.                          { std::cerr << "Unexpected character: " << yytext << std::endl; }
%%
// Add this section at the bottom
int yylex(void) {
    static FlexLexer* lexer = new yyFlexLexer;
    return lexer->yylex();
}