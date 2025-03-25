#define IF 257
#define ELSE 258
#define WHILE 259
#define FOR 260
#define DO 261
#define ASSIGN 262
#define PLUS 263
#define MINUS 264
#define MULT 265
#define DIV 266
#define LT 267
#define GT 268
#define EQ 269
#define AND 270
#define OR 271
#define LPAREN 272
#define RPAREN 273
#define LBRACE 274
#define RBRACE 275
#define SEMICOLON 276
#define NUMBER 277
#define BOOLEAN 278
#define IDENTIFIER 279
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    int num;
    char* str;
    Node* node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
