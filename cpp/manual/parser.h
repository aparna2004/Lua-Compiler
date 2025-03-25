#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include <vector>
#include "lexer.h"
#include <stdexcept>

class ParseError : public std::runtime_error
{
public:
    ParseError(const std::string &message) : std::runtime_error(message) {}
};

class Parser
{
private:
    std::vector<Token> tokens;
    size_t current = 0;

    // Helper methods
    bool isAtEnd() { return peek().type == TokenType::EOF_TOKEN; }
    Token peek() { return tokens[current]; }
    Token previous() { return tokens[current - 1]; }
    Token advance()
    {
        if (!isAtEnd())
            current++;
        return previous();
    }

    bool check(TokenType type)
    {
        if (isAtEnd())
            return false;
        return peek().type == type;
    }

    bool match(TokenType type)
    {
        if (check(type))
        {
            advance();
            return true;
        }
        return false;
    }

    Token consume(TokenType type, const std::string &message)
    {
        if (check(type))
            return advance();
        throw ParseError(message);
    }

    // Parsing methods
    Node *program();
    Node *block();
    Node *statement();
    Node *ifStatement();
    Node *whileStatement();
    Node *forStatement();
    Node *printStatement();
    Node *assignment();
    Node *expression();
    Node *logicalOr();
    Node *logicalAnd();
    Node *equality();
    Node *comparison();
    Node *concat();
    Node *term();
    Node *factor();
    Node *unary();
    Node *primary();

public:
    Parser(const std::vector<Token> &tokens) : tokens(tokens) {}
    Node *parse() { return program(); }
};

#endif