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
%token IF ELSE ELSEIF WHILE THEN END DO
%token AND OR NOT
%token FOR COMMA IN
%token LPAREN RPAREN LBRACE RBRACE ASSIGN EQ LT GT PLUS MINUS MULT DIV
%token PRINT
%token <strVal> STRING
%token CONCAT

%token GE LE NE


%type <node> stmt expr block  program bool_expr logic_expr for_stmt elseif_list

/* %left PLUS MINUS
%left MULT DIV
%nonassoc LT GT EQ
%nonassoc IF ELSE */
%left CONCAT
%left OR
%left AND
%right NOT
// Add to token declarations

// Update operator precedence section
%left EQ NE
%left LT GT LE GE
%left PLUS MINUS
%left MULT DIV

%right UMINUS


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
    | IF expr THEN block elseif_list END { $$ = new IfNode($2, $4, $5); }
    | IF expr THEN block elseif_list ELSE block END { $$ = new IfNode($2, $4, $5, $7); }
    | WHILE expr DO block END { $$ = new WhileNode($2, $4); }
    | for_stmt { $$ = $1; }
    | PRINT expr { $$ = new PrintNode($2); }
    ;

elseif_list:
    /* empty */ { $$ = nullptr; }
    | elseif_list ELSEIF expr THEN block { $$ = new ElseIfNode($3, $5, $1); }
    ;

for_stmt:
    FOR IDENT ASSIGN expr COMMA expr DO block END 
        { $$ = new ForNode($2, $4, $6, new NumNode(1), $8); }
    | FOR IDENT ASSIGN expr COMMA expr COMMA expr DO block END 
        { $$ = new ForNode($2, $4, $6, $8, $10); }
    ;

expr:
    bool_expr { $$ = $1; }
    | logic_expr { $$ = $1; }
    | expr PLUS expr { $$ = new BinaryOpNode($1, "+", $3); }
    | expr MINUS expr { $$ = new BinaryOpNode($1, "-", $3); }
    | expr MULT expr { $$ = new BinaryOpNode($1, "*", $3); }
    | expr DIV expr { $$ = new BinaryOpNode($1, "/", $3); }
    | expr CONCAT expr { $$ = new BinaryOpNode($1, "..", $3); }
    | MINUS expr %prec UMINUS { $$ = new UnaryMinusNode($2); }
    | LPAREN expr RPAREN { $$ = $2; }
    | IDENT { $$ = new VarNode($1); }
    | MINUS NUMBER { $$ = new NumNode(-$2); } 
    | NUMBER { $$ = new NumNode($1); }
    | STRING { $$ = new StringNode($1); }
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
    | expr NE expr    { $$ = new BinaryOpNode($1, "~=", $3); }
    | expr LE expr    { $$ = new BinaryOpNode($1, "<=", $3); }
    | expr GE expr    { $$ = new BinaryOpNode($1, ">=", $3); }
    ;

%%
