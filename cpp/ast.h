#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>

class Node
{
public:
    virtual ~Node() = default;
    virtual void print() const = 0;
};

class NumNode : public Node
{
public:
    int value;
    NumNode(int v) : value(v) {}
    void print() const override { std::cout << value; }
};

class VarNode : public Node
{
public:
    std::string name;
    VarNode(const std::string &n) : name(n) {}
    void print() const override { std::cout << name; }
};

class BinaryOpNode : public Node
{
public:
    Node *left;
    std::string op;
    Node *right;

    BinaryOpNode(Node *l, const std::string &o, Node *r)
        : left(l), op(o), right(r) {}

    void print() const override
    {
        std::cout << "(";
        left->print();
        std::cout << " " << op << " ";
        right->print();
        std::cout << ")";
    }
};

class AssignNode : public Node
{
public:
    std::string name;
    Node *expr;

    AssignNode(const std::string &n, Node *e) : name(n), expr(e) {}

    void print() const override
    {
        std::cout << name << " = ";
        expr->print();
    }
};

class IfNode : public Node
{
public:
    Node *cond;
    Node *block;

    IfNode(Node *c, Node *b) : cond(c), block(b) {}

    void print() const override
    {
        std::cout << "if (";
        cond->print();
        std::cout << ") ";
        block->print();
    }
};

class WhileNode : public Node
{
public:
    Node *cond;
    Node *block;

    WhileNode(Node *c, Node *b) : cond(c), block(b) {}

    void print() const override
    {
        std::cout << "while (";
        cond->print();
        std::cout << ") ";
        block->print();
    }
};

class BlockNode : public Node
{
public:
    Node *first;
    Node *second;

    BlockNode(Node *f, Node *s) : first(f), second(s) {}

    void print() const override
    {
        first->print();
        std::cout << "; ";
        second->print();
    }
};

class BoolNode : public Node
{
private:
    bool value;

public:
    BoolNode(bool val) : value(val) {}
    void print() const override
    {
        std::cout << (value ? "true" : "false");
    }
};

class UnaryOpNode : public Node
{
private:
    std::string op;
    Node *expr;

public:
    UnaryOpNode(const std::string &operator_, Node *expression)
        : op(operator_), expr(expression) {}
    void print()const  override
    {
        std::cout << op << "(";
        expr->print();
        std::cout << ")";
    }
};

#endif
