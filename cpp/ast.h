#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>

class Node
{
public:
    virtual ~Node() = default;
    virtual void print() const = 0;
    virtual std::pair<std::string, std::vector<std::string>> generateIC() = 0;

protected:
    static int tempCount;
    static int labelCount;
    std::string newTemp() { return "t" + std::to_string(tempCount++); }
    std::string newLabel() { return "L" + std::to_string(labelCount++); }
};

// Initialize static members
// int Node::tempCount = 0;
// int Node::labelCount = 0;

class NumNode : public Node
{
public:
    int value;
    NumNode(int v) : value(v) {}
    void print() const override { std::cout << value; }
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        std::string temp = newTemp();
        return {temp, {temp + " = " + std::to_string(value)}};
    }
};

class VarNode : public Node
{
public:
    std::string name;
    VarNode(const std::string &n) : name(n) {}
    void print() const override { std::cout << name; }
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        return {name, {}}; // Just return the variable name, no new code
    }
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
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [leftTemp, leftCode] = left->generateIC();
        auto [rightTemp, rightCode] = right->generateIC();

        std::vector<std::string> code = leftCode;
        code.insert(code.end(), rightCode.begin(), rightCode.end());

        std::string temp = newTemp();
        code.push_back(temp + " = " + leftTemp + " " + op + " " + rightTemp);
        return {temp, code};
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

    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [exprTemp, exprCode] = expr->generateIC();
        exprCode.push_back(name + " = " + exprTemp);
        return {name, exprCode};
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
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [condTemp, condCode] = cond->generateIC();
        auto [_, blockCode] = block->generateIC();

        std::string labelEnd = newLabel();

        std::vector<std::string> code = condCode;
        code.push_back("if " + condTemp + " = 0 goto " + labelEnd);
        code.insert(code.end(), blockCode.begin(), blockCode.end());
        code.push_back(labelEnd + ":");

        return {"", code};
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
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        std::string labelLoop = newLabel();
        std::string labelEnd = newLabel();

        auto [condTemp, condCode] = cond->generateIC();
        auto [_, blockCode] = block->generateIC();

        std::vector<std::string> code;
        code.push_back(labelLoop + ":");
        code.insert(code.end(), condCode.begin(), condCode.end());
        code.push_back("if " + condTemp + " = 0 goto " + labelEnd);
        code.insert(code.end(), blockCode.begin(), blockCode.end());
        code.push_back("goto " + labelLoop);
        code.push_back(labelEnd + ":");

        return {"", code};
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
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [_, firstCode] = first->generateIC();
        auto [__, secondCode] = second->generateIC();

        std::vector<std::string> code = firstCode;
        code.insert(code.end(), secondCode.begin(), secondCode.end());
        return {"", code};
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
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        std::string temp = newTemp();
        return {temp, {temp + " = " + (value ? "1" : "0")}};
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
    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [exprTemp, exprCode] = expr->generateIC();
        std::string temp = newTemp();
        exprCode.push_back(temp + " = " + op + " " + exprTemp);
        return {temp, exprCode};
    }
};

#endif
