#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <stdexcept>

enum class TokenType
{
    // Literals
    NUMBER,
    IDENT,
    STRING,
    TRUE,
    FALSE,

    // Keywords
    IF,
    THEN,
    ELSE,
    ELSEIF,
    END,
    WHILE,
    DO,
    FOR,
    IN,
    PRINT,

    // Operators
    PLUS,
    MINUS,
    MULT,
    DIV,
    CONCAT, // ..
    UMINUS,
    EQ,
    NE,
    LT,
    GT,
    LE,
    GE, // ==, ~=, <, >, <=, >=
    AND,
    OR,
    NOT,

    // Delimiters
    LPAREN,
    RPAREN,
    ASSIGN, // =
    COMMA,

    EOF_TOKEN
};

struct Token
{
    TokenType type;
    std::string lexeme;
    int line;

    union
    {
        int intValue;
        bool boolValue;
    };
    std::string stringValue; // For both identifiers and string literals
};

class LexerError : public std::runtime_error
{
public:
    LexerError(const std::string &message, int line)
        : std::runtime_error("Line " + std::to_string(line) + ": " + message) {}
};

class Lexer
{
private:
    std::string source;
    std::vector<Token> tokens;
    size_t start = 0;
    size_t current = 0;
    int line = 1;

    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();
    bool match(char expected);

    void string();
    void number();
    void identifier();
    void scanToken();

public:
    explicit Lexer(const std::string &source) : source(source) {}
    std::vector<Token> scanTokens();
};

#endif