#include <iostream>
#include "ast.h"
#include "parser.tab.h"

extern "C"
{
    int yylex(void);
    int yyparse(void);
}
// extern int yylex(); // Add this line to fix the yylex reference issue
extern int yydebug;
extern Node *root;

int main()
{
    yydebug = 1;
    std::cout << "Parsing..." << std::endl;

    if (yyparse() == 0)
    {
        std::cout << "Parsing successful!" << std::endl;
        if (root)
        {
            root->print();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}
