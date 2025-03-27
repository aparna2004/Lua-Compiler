#include "lexer.h"
#include <unordered_map>

static std::unordered_map<std::string, TokenType> keywords = {
    {"and", TokenType::AND},
    {"or", TokenType::OR},
    {"not", TokenType::NOT},
    {"if", TokenType::IF},
    {"then", TokenType::THEN},
    {"else", TokenType::ELSE},
    {"elseif", TokenType::ELSEIF},
    {"end", TokenType::END},
    {"while", TokenType::WHILE},
    {"do", TokenType::DO},
    {"for", TokenType::FOR},
    {"in", TokenType::IN},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"print", TokenType::PRINT}};

bool Lexer::isAtEnd() { return current >= source.length(); }

char Lexer::advance() { return source[current++]; }

char Lexer::peek() { return isAtEnd() ? '\0' : source[current]; }

char Lexer::peekNext()
{
    return (current + 1 >= source.length()) ? '\0' : source[current + 1];
}

bool Lexer::match(char expected)
{
    if (isAtEnd() || source[current] != expected)
        return false;
    current++;
    return true;
}

void Lexer::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (isAtEnd())
    {
        throw LexerError("Unterminated string", line);
    }

    advance(); // Closing quote

    std::string value = source.substr(start + 1, current - start - 2);
    Token token{TokenType::STRING, source.substr(start, current - start), line};
    token.stringValue = value;
    tokens.push_back(token);
}

void Lexer::number()
{
    while (std::isdigit(peek()))
        advance();

    int value = std::stoi(source.substr(start, current - start));
    Token token{TokenType::NUMBER, source.substr(start, current - start), line};
    token.intValue = value;
    tokens.push_back(token);
}

void Lexer::identifier()
{
    while (std::isalnum(peek()) || peek() == '_')
        advance();

    std::string text = source.substr(start, current - start);
    auto it = keywords.find(text);
    TokenType type = it != keywords.end() ? it->second : TokenType::IDENT;

    Token token{type, text, line};
    if (type == TokenType::TRUE || type == TokenType::FALSE)
    {
        token.boolValue = (type == TokenType::TRUE);
    }
    if (type == TokenType::IDENT)
    {
        token.stringValue = text;
    }
    tokens.push_back(token);
}

void Lexer::scanToken()
{
    char c = advance();
    switch (c)
    {
    case '(':
        tokens.push_back({TokenType::LPAREN, "(", line});
        break;
    case ')':
        tokens.push_back({TokenType::RPAREN, ")", line});
        break;
    case ',':
        tokens.push_back({TokenType::COMMA, ",", line});
        break;
    case '-':
        if (match('-'))
        {
            // Comment
            while (peek() != '\n' && !isAtEnd())
                advance();
        }
        else
        {
            tokens.push_back({TokenType::MINUS, "-", line});
        }
        break;

    case '+':
        tokens.push_back({TokenType::PLUS, "+", line});
        break;
    case '*':
        tokens.push_back({TokenType::MULT, "*", line});
        break;
    case '/':
        tokens.push_back({TokenType::DIV, "/", line});
        break;

    case '=':
        tokens.push_back({match('=') ? TokenType::EQ : TokenType::ASSIGN,
                          source.substr(start, current - start),
                          line});
        break;

    case '<':
        tokens.push_back({match('=') ? TokenType::LE : TokenType::LT,
                          source.substr(start, current - start),
                          line});
        break;

    case '>':
        tokens.push_back({match('=') ? TokenType::GE : TokenType::GT,
                          source.substr(start, current - start),
                          line});
        break;

    case '~':
        if (match('='))
        {
            tokens.push_back({TokenType::NE, "~=", line});
        }
        else
        {
            throw LexerError("Expected '=' after '~'", line);
        }
        break;

    case '.':
        if (match('.'))
        {
            tokens.push_back({TokenType::CONCAT, "..", line});
        }
        else
        {
            throw LexerError("Expected '.' after '.'", line);
        }
        break;

    case '"':
        string();
        break;

    case ' ':
    case '\r':
    case '\t':
        break;

    case '\n':
        line++;
        break;

        // case '-':

    default:
        if (std::isdigit(c))
        {
            number();
        }
        else if (std::isalpha(c) || c == '_')
        {
            identifier();
        }
        else
        {
            throw LexerError("Unexpected character", line);
        }
        break;
    }
}

// Lexer::Lexer(const std::string &source) : source(source) {}

std::vector<Token> Lexer::scanTokens()
{
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    tokens.push_back({TokenType::EOF_TOKEN, "", line});
    return tokens;
}

