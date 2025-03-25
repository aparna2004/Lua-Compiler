/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20210109

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern FILE* yyin; /* Declare yyin for file input*/
void yyerror(const char* s) { fprintf(stderr, "Error: %s\n", s); }

Node* root;
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 14 "parser.y"
typedef union {
    int num;
    char* str;
    Node* node;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 45 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    2,    2,    2,    4,    5,
    5,    6,    7,    8,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,
};
static const YYINT yylen[] = {                            2,
    1,    2,    0,    2,    1,    1,    1,    2,    3,    7,
   11,    7,   11,    8,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    1,    0,    0,    5,
    6,    7,    0,    0,    0,    0,    0,    0,    2,    4,
    8,    0,   26,   27,   25,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   24,    0,    0,   17,   18,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   12,    0,    0,    0,    0,   14,    0,
    0,    0,    0,   11,   13,
};
static const YYINT yydgoto[] = {                          6,
    7,    8,   26,    9,   10,   11,   12,   13,
};
static const YYINT yysindex[] = {                      -246,
 -256, -238, -221, -270, -193,    0,    0, -246, -202,    0,
    0,    0, -196, -260, -260, -197, -246, -260,    0,    0,
    0, -260,    0,    0,    0, -178, -167, -182, -170, -114,
 -156, -260, -260, -260, -260, -260, -260, -260, -260, -260,
 -191, -158, -260, -132,    0, -220, -220,    0,    0,  -77,
  -77,  -89, -210, -105, -246, -246, -227, -136, -141, -131,
 -197, -260, -121,    0, -127, -145, -102,  -93,    0, -246,
 -246, -106, -104,    0,    0,
};
static const YYINT yyrindex[] = {                       147,
    0,    0,    0,    0,    0,    0,    0,    2,    0,    0,
    0,    0,    0,    0,    0,    0,  -92,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -268,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -203, -192,    0,    0, -138,
 -128, -103, -241,  -91,  -92,  -92,    0,    0,    0,    0,
    0,    0,    1,    0,    0,    0,    0,    0,    0,  -92,
  -92,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
   -8,    0,  -12,   -9,    0,    0,    0,    0,
};
#define YYTABLESIZE 280
static const YYINT yytable[] = {                         19,
   10,    3,   27,   17,    9,   30,   28,    9,   29,   31,
    1,   22,    2,    3,    4,   14,   23,   24,   25,   46,
   47,   48,   49,   50,   51,   52,   53,   54,   22,   22,
   57,   22,    5,   15,   22,   32,   33,   34,   35,   36,
   37,   38,   39,   40,   34,   35,   59,   60,   61,   66,
   16,   65,   32,   33,   34,   35,   36,   37,   38,   15,
   15,   72,   73,   15,   15,   15,   15,   15,   18,   15,
   16,   16,   15,   20,   16,   16,   16,   16,   16,   21,
   16,    5,   55,   16,   32,   33,   34,   35,   36,   37,
   38,   39,   40,   43,   41,   32,   33,   34,   35,   36,
   37,   38,   39,   40,   44,   42,   32,   33,   34,   35,
   36,   37,   38,   39,   40,   56,   45,   32,   33,   34,
   35,   36,   37,   38,   39,   40,   58,   69,   19,   19,
   19,   19,   19,   63,   19,   62,   67,   19,   20,   20,
   20,   20,   20,   64,   20,   68,    3,   20,   32,   33,
   34,   35,   36,   37,   38,   39,   40,   32,   33,   34,
   35,   36,   37,   38,   39,   21,   21,   21,   74,   21,
   75,   70,   21,   32,   33,   34,   35,   36,   37,   23,
   71,   23,    3,    0,   23,   32,   33,   34,   35,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   10,    0,   10,
   10,   10,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   10,    3,    0,    0,   10,
};
static const YYINT yycheck[] = {                          8,
    0,    0,   15,  274,  273,   18,   16,  276,   17,   22,
  257,  272,  259,  260,  261,  272,  277,  278,  279,   32,
   33,   34,   35,   36,   37,   38,   39,   40,  270,  271,
   43,  273,  279,  272,  276,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  265,  266,   55,   56,  276,   62,
  272,   61,  263,  264,  265,  266,  267,  268,  269,  263,
  264,   70,   71,  267,  268,  269,  270,  271,  262,  273,
  263,  264,  276,  276,  267,  268,  269,  270,  271,  276,
  273,  279,  274,  276,  263,  264,  265,  266,  267,  268,
  269,  270,  271,  276,  273,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  275,  273,  263,  264,  265,  266,
  267,  268,  269,  270,  271,  274,  273,  263,  264,  265,
  266,  267,  268,  269,  270,  271,  259,  273,  267,  268,
  269,  270,  271,  275,  273,  272,  258,  276,  267,  268,
  269,  270,  271,  275,  273,  273,    0,  276,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  263,  264,  265,
  266,  267,  268,  269,  270,  269,  270,  271,  275,  273,
  275,  274,  276,  263,  264,  265,  266,  267,  268,  271,
  274,  273,  275,   -1,  276,  263,  264,  265,  266,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,   -1,  259,
  260,  261,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  275,  275,   -1,   -1,  279,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#define YYUNDFTOKEN 290
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"IF","ELSE","WHILE","FOR","DO",
"ASSIGN","PLUS","MINUS","MULT","DIV","LT","GT","EQ","AND","OR","LPAREN",
"RPAREN","LBRACE","RBRACE","SEMICOLON","NUMBER","BOOLEAN","IDENTIFIER",0,0,0,0,
0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : stmt_list",
"stmt_list : stmt stmt_list",
"stmt_list :",
"stmt : assign_stmt SEMICOLON",
"stmt : if_stmt",
"stmt : while_stmt",
"stmt : for_stmt",
"stmt : do_while_stmt SEMICOLON",
"assign_stmt : IDENTIFIER ASSIGN expr",
"if_stmt : IF LPAREN expr RPAREN LBRACE stmt_list RBRACE",
"if_stmt : IF LPAREN expr RPAREN LBRACE stmt_list RBRACE ELSE LBRACE stmt_list RBRACE",
"while_stmt : WHILE LPAREN expr RPAREN LBRACE stmt_list RBRACE",
"for_stmt : FOR LPAREN assign_stmt SEMICOLON expr SEMICOLON assign_stmt RPAREN LBRACE stmt_list RBRACE",
"do_while_stmt : DO LBRACE stmt_list RBRACE WHILE LPAREN expr RPAREN",
"expr : expr PLUS expr",
"expr : expr MINUS expr",
"expr : expr MULT expr",
"expr : expr DIV expr",
"expr : expr LT expr",
"expr : expr GT expr",
"expr : expr EQ expr",
"expr : expr AND expr",
"expr : expr OR expr",
"expr : LPAREN expr RPAREN",
"expr : IDENTIFIER",
"expr : NUMBER",
"expr : BOOLEAN",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 94 "parser.y"

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
#line 351 "y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 1:
#line 38 "parser.y"
	{ root = yystack.l_mark[0].node; }
break;
case 2:
#line 42 "parser.y"
	{ yyval.node = createNode("stmt_list", yystack.l_mark[-1].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 3:
#line 43 "parser.y"
	{ yyval.node = NULL; }
break;
case 4:
#line 47 "parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 5:
#line 48 "parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 6:
#line 49 "parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 7:
#line 50 "parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 8:
#line 51 "parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 9:
#line 55 "parser.y"
	{ yyval.node = createNode("assign", createNode("id", NULL, NULL, NULL, yystack.l_mark[-2].str), yystack.l_mark[0].node, NULL, NULL); }
break;
case 10:
#line 59 "parser.y"
	{ yyval.node = createNode("if", yystack.l_mark[-4].node, yystack.l_mark[-1].node, NULL, NULL); }
break;
case 11:
#line 61 "parser.y"
	{ yyval.node = createNode("if", yystack.l_mark[-8].node, yystack.l_mark[-5].node, yystack.l_mark[-1].node, NULL); }
break;
case 12:
#line 65 "parser.y"
	{ yyval.node = createNode("while", yystack.l_mark[-4].node, yystack.l_mark[-1].node, NULL, NULL); }
break;
case 13:
#line 70 "parser.y"
	{ yyval.node = createNode("for", yystack.l_mark[-8].node, createNode("cond", yystack.l_mark[-6].node, yystack.l_mark[-4].node, NULL, NULL), yystack.l_mark[-1].node, NULL); }
break;
case 14:
#line 74 "parser.y"
	{ yyval.node = createNode("do_while", yystack.l_mark[-5].node, yystack.l_mark[-1].node, NULL, NULL); }
break;
case 15:
#line 78 "parser.y"
	{ yyval.node = createNode("plus", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 16:
#line 79 "parser.y"
	{ yyval.node = createNode("minus", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 17:
#line 80 "parser.y"
	{ yyval.node = createNode("mult", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 18:
#line 81 "parser.y"
	{ yyval.node = createNode("div", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 19:
#line 82 "parser.y"
	{ yyval.node = createNode("lt", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 20:
#line 83 "parser.y"
	{ yyval.node = createNode("gt", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 21:
#line 84 "parser.y"
	{ yyval.node = createNode("eq", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 22:
#line 85 "parser.y"
	{ yyval.node = createNode("and", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 23:
#line 86 "parser.y"
	{ yyval.node = createNode("or", yystack.l_mark[-2].node, yystack.l_mark[0].node, NULL, NULL); }
break;
case 24:
#line 87 "parser.y"
	{ yyval.node = yystack.l_mark[-1].node; }
break;
case 25:
#line 88 "parser.y"
	{ yyval.node = createNode("id", NULL, NULL, NULL, yystack.l_mark[0].str); }
break;
case 26:
#line 89 "parser.y"
	{ char val[16]; sprintf(val, "%d", yystack.l_mark[0].num); yyval.node = createNode("num", NULL, NULL, NULL, strdup(val)); }
break;
case 27:
#line 90 "parser.y"
	{ char val[6]; sprintf(val, "%d", yystack.l_mark[0].num); yyval.node = createNode("bool", NULL, NULL, NULL, strdup(val)); }
break;
#line 658 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
