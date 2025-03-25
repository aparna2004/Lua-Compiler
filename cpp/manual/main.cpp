#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Error: Could not open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    std::stringstream input;
    input << file.rdbuf();
    std::string source = input.str();

    try
    {
        Lexer lexer(source);
        auto tokens = lexer.scanTokens();

        Parser parser(tokens);
        Node *root = parser.parse();

        if (root)
        {
            root->evaluate();
        }
    }
    catch (const LexerError &e)
    {
        std::cerr << "Lexer error: " << e.what() << std::endl;
        return 1;
    }
    catch (const ParseError &e)
    {
        std::cerr << "Parser error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}