#include "parser.h"

Node *Parser::program()
{
    Node *first = statement();
    if (!first)
        return nullptr;

    if (isAtEnd())
        return first;
    return new BlockNode(first, program());
}

Node *Parser::statement()
{
    if (match(TokenType::IF))
        return ifStatement();
    if (match(TokenType::WHILE))
        return whileStatement();
    if (match(TokenType::FOR))
        return forStatement();
    if (match(TokenType::PRINT))
        return printStatement();
    return assignment();
}

Node *Parser::ifStatement()
{
    Node *condition = expression();
    consume(TokenType::THEN, "Expected 'then' after if condition");

    // Store statements in order
    std::vector<Node *> thenStatements;

    // Parse all statements until 'end' or 'else'
    while (!check(TokenType::END) && !check(TokenType::ELSE) &&
           !check(TokenType::ELSEIF) && !isAtEnd())
    {
        thenStatements.push_back(statement());
    }

    // Build then block from back to front
    Node *thenBranch = nullptr;
    for (auto it = thenStatements.rbegin(); it != thenStatements.rend(); ++it)
    {
        if (!thenBranch)
        {
            thenBranch = *it;
        }
        else
        {
            thenBranch = new BlockNode(*it, thenBranch);
        }
    }

    Node *elseifList = nullptr;
    while (match(TokenType::ELSEIF))
    {
        Node *elseifCond = expression();
        consume(TokenType::THEN, "Expected 'then' after elseif condition");

        // Handle elseif body statements
        std::vector<Node *> elseifStatements;
        while (!check(TokenType::END) && !check(TokenType::ELSE) &&
               !check(TokenType::ELSEIF) && !isAtEnd())
        {
            elseifStatements.push_back(statement());
        }

        // Build elseif block
        Node *elseifBody = nullptr;
        for (auto it = elseifStatements.rbegin(); it != elseifStatements.rend(); ++it)
        {
            if (!elseifBody)
            {
                elseifBody = *it;
            }
            else
            {
                elseifBody = new BlockNode(*it, elseifBody);
            }
        }

        elseifList = new ElseIfNode(elseifCond, elseifBody, elseifList);
    }

    Node *elseBranch = nullptr;
    if (match(TokenType::ELSE))
    {
        std::vector<Node *> elseStatements;
        while (!check(TokenType::END) && !isAtEnd())
        {
            elseStatements.push_back(statement());
        }

        // Build else block
        for (auto it = elseStatements.rbegin(); it != elseStatements.rend(); ++it)
        {
            if (!elseBranch)
            {
                elseBranch = *it;
            }
            else
            {
                elseBranch = new BlockNode(*it, elseBranch);
            }
        }
    }

    consume(TokenType::END, "Expected 'end' after if statement");
    return new IfNode(condition, thenBranch, elseifList, elseBranch);
}
Node *Parser::whileStatement()
{
    Node *condition = expression();
    consume(TokenType::DO, "Expected 'do' after while condition");

    // Store statements in order
    std::vector<Node *> bodyStatements;

    while (!check(TokenType::END) && !isAtEnd())
    {
        bodyStatements.push_back(statement());
    }

    // Build block from back to front to maintain correct order
    Node *body = nullptr;
    for (auto it = bodyStatements.rbegin(); it != bodyStatements.rend(); ++it)
    {
        if (!body)
        {
            body = *it;
        }
        else
        {
            body = new BlockNode(*it, body);
        }
    }

    consume(TokenType::END, "Expected 'end' after while body");
    return new WhileNode(condition, body);
}

Node *Parser::forStatement()
{
    std::string var = consume(TokenType::IDENT, "Expected variable name").stringValue;
    consume(TokenType::ASSIGN, "Expected '=' after for variable");

    Node *start = expression();
    consume(TokenType::COMMA, "Expected ',' after start value");
    Node *end = expression();

    Node *step = nullptr;
    if (match(TokenType::COMMA))
    {
        step = expression();
    }
    else
    {
        step = new NumNode(1);
    }

    consume(TokenType::DO, "Expected 'do' after for loop declaration");

    // Create vector to store statements in order
    std::vector<Node *> bodyStatements;

    while (!check(TokenType::END) && !isAtEnd())
    {
        bodyStatements.push_back(statement());
    }

    // Build block from back to front to maintain correct order
    Node *body = nullptr;
    for (auto it = bodyStatements.rbegin(); it != bodyStatements.rend(); ++it)
    {
        if (!body)
        {
            body = *it;
        }
        else
        {
            body = new BlockNode(*it, body);
        }
    }

    consume(TokenType::END, "Expected 'end' after for body");
    return new ForNode(var, start, end, step, body);
}

Node *Parser::printStatement()
{
    Node *value = expression();
    return new PrintNode(value);
}

Node *Parser::assignment()
{
    if (match(TokenType::IDENT))
    {
        std::string name = previous().stringValue;
        if (match(TokenType::ASSIGN))
        {
            Node *value = expression();
            return new AssignNode(name, value);
        }
        current--; // Backtrack if not an assignment
    }
    return expression();
}

Node *Parser::expression()
{
    return logicalOr();
}

Node *Parser::logicalOr()
{
    Node *expr = logicalAnd();
    while (match(TokenType::OR))
    {
        Node *right = logicalAnd();
        expr = new BinaryOpNode(expr, "or", right);
    }
    return expr;
}

// Continue with other parsing methods...
// ...existing code...

Node *Parser::logicalAnd()
{
    Node *expr = equality();
    while (match(TokenType::AND))
    {
        Node *right = equality();
        expr = new BinaryOpNode(expr, "and", right);
    }
    return expr;
}

Node *Parser::equality()
{
    Node *expr = comparison();
    while (match(TokenType::EQ) || match(TokenType::NE))
    {
        std::string op = previous().type == TokenType::EQ ? "==" : "~=";
        Node *right = comparison();
        expr = new BinaryOpNode(expr, op, right);
    }
    return expr;
}

Node *Parser::comparison()
{
    Node *expr = concat();
    while (match(TokenType::LT) || match(TokenType::GT) ||
           match(TokenType::LE) || match(TokenType::GE))
    {
        std::string op;
        switch (previous().type)
        {
        case TokenType::LT:
            op = "<";
            break;
        case TokenType::GT:
            op = ">";
            break;
        case TokenType::LE:
            op = "<=";
            break;
        case TokenType::GE:
            op = ">=";
            break;
        default:
            break;
        }
        Node *right = concat();
        expr = new BinaryOpNode(expr, op, right);
    }
    return expr;
}

Node *Parser::concat()
{
    Node *expr = term();
    while (match(TokenType::CONCAT))
    {
        Node *right = term();
        expr = new BinaryOpNode(expr, "..", right);
    }
    return expr;
}

Node *Parser::term()
{
    Node *expr = factor();
    while (match(TokenType::PLUS) || match(TokenType::MINUS))
    {
        std::string op = previous().type == TokenType::PLUS ? "+" : "-";
        Node *right = factor();
        expr = new BinaryOpNode(expr, op, right);
    }
    return expr;
}

Node *Parser::factor()
{
    Node *expr = unary();
    while (match(TokenType::MULT) || match(TokenType::DIV))
    {
        std::string op = previous().type == TokenType::MULT ? "*" : "/";
        Node *right = unary();
        expr = new BinaryOpNode(expr, op, right);
    }
    return expr;
}

Node *Parser::unary()
{
    if (match(TokenType::MINUS))
    {
        Token op = previous();
        Node *right = unary(); // Use unary recursively for cases like --x
        return new UnaryMinusNode(right);
    }
    if (match(TokenType::NOT))
    {
        Node *right = unary();
        return new UnaryOpNode("not", right);
    }
    return primary();
}

Node *Parser::primary()
{
    if (match(TokenType::NUMBER))
    {
        return new NumNode(previous().intValue);
    }
    if (match(TokenType::STRING))
    {
        return new StringNode(previous().stringValue);
    }
    if (match(TokenType::TRUE))
    {
        return new BoolNode(true);
    }
    if (match(TokenType::FALSE))
    {
        return new BoolNode(false);
    }
    if (match(TokenType::IDENT))
    {
        return new VarNode(previous().stringValue);
    }
    if (match(TokenType::LPAREN))
    {
        Node *expr = expression();
        consume(TokenType::RPAREN, "Expected ')' after expression");
        return expr;
    }

    throw ParseError("Expected expression");
}