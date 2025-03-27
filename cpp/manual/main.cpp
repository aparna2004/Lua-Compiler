#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
// Add after includes
std::string getTokenTypeName(TokenType type)
{
    switch (type)
    {
    // Literals
    case TokenType::NUMBER:
        return "NUMBER";
    case TokenType::IDENT:
        return "IDENT";
    case TokenType::STRING:
        return "STRING";
    case TokenType::TRUE:
        return "TRUE";
    case TokenType::FALSE:
        return "FALSE";

    // Keywords
    case TokenType::IF:
        return "IF";
    case TokenType::THEN:
        return "THEN";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::ELSEIF:
        return "ELSEIF";
    case TokenType::END:
        return "END";
    case TokenType::WHILE:
        return "WHILE";
    case TokenType::DO:
        return "DO";
    case TokenType::FOR:
        return "FOR";
    case TokenType::IN:
        return "IN";
    case TokenType::PRINT:
        return "PRINT";

    // Operators
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULT:
        return "MULT";
    case TokenType::DIV:
        return "DIV";
    case TokenType::CONCAT:
        return "CONCAT";
    case TokenType::UMINUS:
        return "UMINUS";
    case TokenType::EQ:
        return "EQ";
    case TokenType::NE:
        return "NE";
    case TokenType::LT:
        return "LT";
    case TokenType::GT:
        return "GT";
    case TokenType::LE:
        return "LE";
    case TokenType::GE:
        return "GE";
    case TokenType::AND:
        return "AND";
    case TokenType::OR:
        return "OR";
    case TokenType::NOT:
        return "NOT";

    // Delimiters
    case TokenType::LPAREN:
        return "LPAREN";
    case TokenType::RPAREN:
        return "RPAREN";
    case TokenType::ASSIGN:
        return "ASSIGN";
    case TokenType::COMMA:
        return "COMMA";
    case TokenType::EOF_TOKEN:
        return "EOF";

    default:
        return "UNKNOWN";
    }
}

// Modify the operator<< to use the token type name
std::ostream &operator<<(std::ostream &os, const Token &token)
{
    os << std::left
       << std::setw(30) << token.lexeme
       << std::setw(15) << getTokenTypeName(token.type)
       << "Line " << token.line;
    return os;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename> [--parsetree] [--tokens]" << std::endl;
        return 1;
    }

    bool showParseTree = false;
    bool showTokens = false;

    // Parse command line arguments
    for (int i = 2; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--parsetree")
            showParseTree = true;
        if (arg == "--tokens")
            showTokens = true;
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

        if (showTokens)
        {
            std::cout << "\nTokens:\n";
            std::cout << std::left
                      << std::setw(15) << "Lexeme"
                      << std::setw(15) << "Token Type"
                      << "Position" << std::endl;
            std::cout << std::string(45, '-') << std::endl;

            for (const auto &token : tokens)
            {
                std::cout << token << std::endl;
            }
            std::cout << std::endl;
        }

        Parser parser(tokens);
        Node *root = parser.parse();

        if (root)
        {
            if (showParseTree)
            {
                std::cout << "\nParse Tree:\n";
                root->print();
                std::cout << std::endl
                          << std::endl;
            }
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