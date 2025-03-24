#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <variant>

using Value = std::variant<int, bool>;
using ICResult = std::pair<std::string, std::vector<std::string>>;

class Node
{
public:
    virtual ~Node() = default;
    virtual void print() const = 0;
    virtual ICResult generateIC() = 0;
    virtual Value evaluate() = 0;

protected:
    static int tempCount;
    static int labelCount;
    std::string newTemp() { return "t" + std::to_string(tempCount++); }
    std::string newLabel() { return "L" + std::to_string(labelCount++); }
};

// Expression nodes
class NumNode : public Node
{
public:
    int value;
    NumNode(int v) : value(v) {}

    void print() const override { std::cout << value; }

    Value evaluate() override { return value; }

    ICResult generateIC() override
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

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        return {name, {}};
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

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
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

    Value evaluate() override { return value; }

    ICResult generateIC() override
    {
        std::string temp = newTemp();
        return {temp, {temp + " = " + (value ? "1" : "0")}};
    }
};

// Statement nodes
class AssignNode : public Node
{
public:
    std::string var;
    Node *expr;

    AssignNode(const std::string &v, Node *e) : var(v), expr(e) {}

    void print() const override
    {
        std::cout << var << " = ";
        expr->print();
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [exprTemp, exprCode] = expr->generateIC();
        exprCode.push_back(var + " = " + exprTemp);
        return {var, exprCode};
    }
};

class IfNode : public Node
{
public:
    Node *cond;
    Node *thenBlock;
    Node *elseBlock;

    IfNode(Node *c, Node *t, Node *e = nullptr)
        : cond(c), thenBlock(t), elseBlock(e) {}

    void print() const override
    {
        std::cout << "if ";
        cond->print();
        std::cout << " then ";
        thenBlock->print();
        if (elseBlock)
        {
            std::cout << " else ";
            elseBlock->print();
        }
        std::cout << " end";
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [condTemp, condCode] = cond->generateIC();
        auto [_, thenCode] = thenBlock->generateIC();

        std::string labelElse = newLabel();
        std::string labelEnd = newLabel();

        std::vector<std::string> code = condCode;
        code.push_back("if " + condTemp + " = 0 goto " + labelElse);
        code.insert(code.end(), thenCode.begin(), thenCode.end());

        if (elseBlock)
        {
            auto [__, elseCode] = elseBlock->generateIC();
            code.push_back("goto " + labelEnd);
            code.push_back(labelElse + ":");
            code.insert(code.end(), elseCode.begin(), elseCode.end());
            code.push_back(labelEnd + ":");
        }
        else
        {
            code.push_back(labelElse + ":");
        }

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
        std::cout << "while ";
        cond->print();
        std::cout << " do ";
        block->print();
        std::cout << " end";
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
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

class ForNode : public Node
{
public:
    std::string var;
    Node *start;
    Node *end;
    Node *step;
    Node *body;

    ForNode(const std::string &v, Node *s, Node *e, Node *st, Node *b)
        : var(v), start(s), end(e), step(st), body(b) {}

    void print() const override
    {
        std::cout << "for " << var << " = ";
        start->print();
        std::cout << ", ";
        end->print();
        std::cout << ", ";
        step->print();
        std::cout << " do ";
        body->print();
        std::cout << " end";
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [startTemp, startCode] = start->generateIC();
        auto [endTemp, endCode] = end->generateIC();
        auto [stepTemp, stepCode] = step->generateIC();
        auto [_, bodyCode] = body->generateIC();

        std::string labelLoop = newLabel();
        std::string labelEnd = newLabel();
        std::string labelCheckGE = newLabel();
        std::string condTemp = newTemp();
        std::string stepCheckTemp = newTemp();
        std::string comparisonTemp = newTemp();

        std::vector<std::string> code;
        code.insert(code.end(), startCode.begin(), startCode.end());
        code.insert(code.end(), stepCode.begin(), stepCode.end());
        code.push_back(var + " = " + startTemp);
        code.push_back(labelLoop + ":");
        code.push_back(stepCheckTemp + " = " + stepTemp + " >= 0");
        code.push_back("if " + stepCheckTemp + " = 0 goto " + labelCheckGE);
        code.push_back(comparisonTemp + " = " + var + " <= " + endTemp);
        code.push_back("goto " + labelEnd);
        code.push_back(labelCheckGE + ":");
        code.push_back(comparisonTemp + " = " + var + " >= " + endTemp);
        code.push_back("if " + comparisonTemp + " = 0 goto " + labelEnd);
        code.insert(code.end(), bodyCode.begin(), bodyCode.end());
        code.push_back(var + " = " + var + " + " + stepTemp);
        code.push_back("goto " + labelLoop);
        code.push_back(labelEnd + ":");

        return {"", code};
    }
};

class PrintNode : public Node
{
public:
    Node *expr;

    PrintNode(Node *e) : expr(e) {}

    void print() const override
    {
        std::cout << "print(";
        expr->print();
        std::cout << ")";
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [exprTemp, exprCode] = expr->generateIC();
        std::vector<std::string> code = exprCode;
        code.push_back("param " + exprTemp);
        code.push_back("call print, 1");
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
        if (second)
        {
            std::cout << "; ";
            second->print();
        }
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [_, firstCode] = first->generateIC();
        std::vector<std::string> code = firstCode;

        if (second)
        {
            auto [__, secondCode] = second->generateIC();
            code.insert(code.end(), secondCode.begin(), secondCode.end());
        }

        return {"", code};
    }
};

class UnaryMinusNode : public Node
{
private:
    Node *expr;

public:
    UnaryMinusNode(Node *e) : expr(e) {}

    void print() const override
    {
        std::cout << "(-";
        expr->print();
        std::cout << ")";
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [exprTemp, exprCode] = expr->generateIC();
        std::string resultTemp = newTemp();
        std::vector<std::string> code = exprCode;
        code.push_back(resultTemp + " = -" + exprTemp);
        return {resultTemp, code};
    }
};

class UnaryOpNode : public Node
{
private:
    std::string op;
    Node *expr;

public:
    UnaryOpNode(const std::string &o, Node *e) : op(o), expr(e) {}

    void print() const override
    {
        std::cout << op << "(";
        expr->print();
        std::cout << ")";
    }

    Value evaluate() override; // Implemented in cpp file

    ICResult generateIC() override
    {
        auto [exprTemp, exprCode] = expr->generateIC();
        std::string resultTemp = newTemp();
        std::vector<std::string> code = exprCode;
        code.push_back(resultTemp + " = " + op + " " + exprTemp);
        return {resultTemp, code};
    }
};

#endif