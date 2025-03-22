%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern FILE* yyin; // Declare yyin for file input
void yyerror(const char* s) { fprintf(stderr, "Error: %s\n", s); }

Node* root;
%}

%union {
    int num;
    char* str;
    Node* node;
}

%token IF ELSE WHILE FOR DO
%token ASSIGN PLUS MINUS MULT DIV LT GT EQ AND OR
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token <num> NUMBER BOOLEAN
%token <str> IDENTIFIER

%left OR
%left AND
%left EQ
%left LT GT
%left PLUS MINUS
%left MULT DIV

%type <node> program stmt_list stmt expr assign_stmt if_stmt while_stmt for_stmt do_while_stmt

%%

program:
    stmt_list              { root = $1; }
    ;

stmt_list:
    stmt stmt_list         { $$ = createNode("stmt_list", $1, $2, NULL, NULL); }
    | /* empty */          { $$ = NULL; }
    ;

stmt:
    assign_stmt SEMICOLON  { $$ = $1; }
    | if_stmt              { $$ = $1; }
    | while_stmt           { $$ = $1; }
    | for_stmt             { $$ = $1; }
    | do_while_stmt SEMICOLON { $$ = $1; }
    ;

assign_stmt:
    IDENTIFIER ASSIGN expr { $$ = createNode("assign", createNode("id", NULL, NULL, NULL, $1), $3, NULL, NULL); }
    ;

if_stmt:
    IF LPAREN expr RPAREN LBRACE stmt_list RBRACE              { $$ = createNode("if", $3, $6, NULL, NULL); }
    | IF LPAREN expr RPAREN LBRACE stmt_list RBRACE ELSE LBRACE stmt_list RBRACE
                                                        { $$ = createNode("if", $3, $6, $10, NULL); }
    ;

while_stmt:
    WHILE LPAREN expr RPAREN LBRACE stmt_list RBRACE    { $$ = createNode("while", $3, $6, NULL, NULL); }
    ;

for_stmt:
    FOR LPAREN assign_stmt SEMICOLON expr SEMICOLON assign_stmt RPAREN LBRACE stmt_list RBRACE
                                                        { $$ = createNode("for", $3, createNode("cond", $5, $7, NULL, NULL), $10, NULL); }
    ;

do_while_stmt:
    DO LBRACE stmt_list RBRACE WHILE LPAREN expr RPAREN { $$ = createNode("do_while", $3, $7, NULL, NULL); }
    ;

expr:
    expr PLUS expr          { $$ = createNode("plus", $1, $3, NULL, NULL); }
    | expr MINUS expr       { $$ = createNode("minus", $1, $3, NULL, NULL); }
    | expr MULT expr        { $$ = createNode("mult", $1, $3, NULL, NULL); }
    | expr DIV expr         { $$ = createNode("div", $1, $3, NULL, NULL); }
    | expr LT expr          { $$ = createNode("lt", $1, $3, NULL, NULL); }
    | expr GT expr          { $$ = createNode("gt", $1, $3, NULL, NULL); }
    | expr EQ expr          { $$ = createNode("eq", $1, $3, NULL, NULL); }
    | expr AND expr         { $$ = createNode("and", $1, $3, NULL, NULL); }
    | expr OR expr          { $$ = createNode("or", $1, $3, NULL, NULL); }
    | LPAREN expr RPAREN    { $$ = $2; }
    | IDENTIFIER            { $$ = createNode("id", NULL, NULL, NULL, $1); }
    | NUMBER                { char val[16]; sprintf(val, "%d", $1); $$ = createNode("num", NULL, NULL, NULL, strdup(val)); }
    | BOOLEAN               { char val[6]; sprintf(val, "%d", $1); $$ = createNode("bool", NULL, NULL, NULL, strdup(val)); }
    ;

%%

// Function implementations moved to a separate .c file (see Step 4)
int main() {
    FILE* input = fopen("input.lua", "r");
    if (!input) {
        fprintf(stderr, "Failed to open input.lua\n");
        return 1;
    }
    yyin = input;

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed\n");
        fclose(input);
        return 1;
    }

    FILE* astOutput = fopen("ast.txt", "w");
    if (!astOutput) {
        fprintf(stderr, "Failed to open ast.txt\n");
        fclose(input);
        freeAST(root);
        return 1;
    }
    if (root) printAST(root, 0, astOutput);
    fclose(astOutput);

    ICList* icList = createICList(100);
    int tempCounter = 1;
    int labelCounter = 1;
    generateIC(root, icList, &tempCounter, &labelCounter);

    FILE* icOutput = fopen("ic.txt", "w");
    if (!icOutput) {
        fprintf(stderr, "Failed to open ic.txt\n");
        fclose(input);
        freeAST(root);
        freeICList(icList);
        return 1;
    }
    printIC(icList, icOutput);
    fclose(icOutput);

    fclose(input);
    freeAST(root);
    freeICList(icList);
    return 0;
}
