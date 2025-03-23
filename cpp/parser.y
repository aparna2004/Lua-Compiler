%{
#include <iostream>
#include <memory>
#include "ast.h"

extern "C"
{
        int yyparse(void);
        int yylex(void);  
        int yywrap()
        {
                return 1;
        }

}
void yyerror(const char *s) { std::cerr << "Parse error: " << s << std::endl; }

Node* root = nullptr;

%}

%union {
    int intVal;
    char* strVal;
    bool boolVal;
    Node* node;
}

%token <intVal> NUMBER
%token <strVal> IDENT
%token <boolVal> TRUE FALSE
%token IF ELSE WHILE THEN END DO
%token AND OR NOT

%token LPAREN RPAREN LBRACE RBRACE ASSIGN EQ LT GT PLUS MINUS MULT DIV

%type <node> stmt expr block  program bool_expr logic_expr

/* %left PLUS MINUS
%left MULT DIV
%nonassoc LT GT EQ
%nonassoc IF ELSE */

%left OR
%left AND
%right NOT
%left EQ
%left LT GT
%left PLUS MINUS
%left MULT DIV


%%

program:
    block { $$ = $1; root = $1; }
    ;

block:
    stmt { $$ = $1; }
    | block stmt { $$ = new BlockNode($1, $2); }
    ;

stmt:
    IDENT ASSIGN expr { $$ = new AssignNode($1, $3); }
    | IF expr THEN block END { $$ = new IfNode($2, $4); }
    | WHILE expr DO block END { $$ = new WhileNode($2, $4); }
    ;


expr:
    bool_expr { $$ = $1; }
    | logic_expr { $$ = $1; }
    | expr PLUS expr { $$ = new BinaryOpNode($1, "+", $3); }
    | expr MINUS expr { $$ = new BinaryOpNode($1, "-", $3); }
    | expr MULT expr { $$ = new BinaryOpNode($1, "*", $3); }
    | expr DIV expr { $$ = new BinaryOpNode($1, "/", $3); }
    | LPAREN expr RPAREN { $$ = $2; }
    | IDENT { $$ = new VarNode($1); }
    | NUMBER { $$ = new NumNode($1); }
    ;

bool_expr:
    TRUE                  { $$ = new BoolNode(true); }
    | FALSE              { $$ = new BoolNode(false); }
    ;

logic_expr:
    expr EQ expr         { $$ = new BinaryOpNode($1, "==", $3); }
    | expr LT expr       { $$ = new BinaryOpNode($1, "<", $3); }
    | expr GT expr       { $$ = new BinaryOpNode($1, ">", $3); }
    | expr AND expr      { $$ = new BinaryOpNode($1, "and", $3); }
    | expr OR expr       { $$ = new BinaryOpNode($1, "or", $3); }
    | NOT expr           { $$ = new UnaryOpNode("not", $2); }
    ;

%%
