#include <iostream>
#include "ast.h"
#include "parser.tab.h"
#include <map>

extern "C"
{
    int yylex(void);
    int yyparse(void);
}
// extern int yylex(); // Add this line to fix the yylex reference issue
extern int yydebug;
extern Node *root;

// std::map<std::string, int> symbolTable;

void executeAST(Node *root)
{
    if (root)
    {
        root->evaluate(); // Direct evaluation
    }
}

int main()
{
    // yydebug = 1;
    std::cout << "Parsing..." << std::endl;

    if (yyparse() == 0)
    {
        std::cout << "Parsing successful!" << std::endl;
        if (root)
        {
            root->print();
            std::cout << std::endl;
            std::cout << "\n\nIntermediate Code:" << std::endl;

            auto [_, code] = root->generateIC();
            for (const auto &line : code)
            {
                std::cout << line << std::endl;
            }
            std::cout << "OUTPUT:" << std::endl;
            executeAST(root);
        }
        std::cout << std::endl;
    }
    else
    {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}
