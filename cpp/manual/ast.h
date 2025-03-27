#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <variant>

using Value = std::variant<int, bool, std::string>;
using ICResult = std::pair<std::string, std::vector<std::string>>;

class Node
{
public:
    virtual ~Node() = default;
    virtual void print(int indent = 0) const = 0;
    virtual ICResult generateIC() = 0;
    virtual Value evaluate() = 0;

protected:
    static int tempCount;
    static int labelCount;
    static int indent;
    std::string newTemp() { return "t" + std::to_string(tempCount++); }
    std::string newLabel() { return "L" + std::to_string(labelCount++); }
    void printIndent() const
    {
        for (int i = 0; i < Node::indent; i++)
        {
            std::cout << "  ";
        }
    }
};

// Expression nodes
class NumNode : public Node
{
public:
    int value;
    NumNode(int v) : value(v) {}

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << value;
    }

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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << name;
    }

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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << op << "\n";
        left->print(indent + 1);
        std::cout << "\n";
        right->print(indent + 1);
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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "=\n";
        Node::indent++;
        printIndent();
        std::cout << var << "\n";
        expr->print(indent + 1);
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
    Node *condition;
    Node *thenBlock;
    Node *elseifList;
    Node *elseBlock;

    IfNode(Node *cond, Node *then, Node *elseif = nullptr, Node *else_block = nullptr)
        : condition(cond), thenBlock(then), elseifList(elseif), elseBlock(else_block) {}

    Value evaluate() override;

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "if\n";
        condition->print(indent + 1);
        std::cout << "\n";
        thenBlock->print(indent + 1);
        if (elseifList)
        {
            std::cout << "\n";
            elseifList->print(indent);
        }
        if (elseBlock)
        {
            std::cout << "\n";
            Node::indent = indent;
            printIndent();
            std::cout << "else\n";
            elseBlock->print(indent + 1);
        }
    }

    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [condTemp, condCode] = condition->generateIC();
        auto [_, thenCode] = thenBlock->generateIC();

        std::string labelElseif = newLabel();
        std::string labelEnd = newLabel();

        std::vector<std::string> code = condCode;
        code.push_back("if " + condTemp + " = 0 goto " + labelElseif);
        code.insert(code.end(), thenCode.begin(), thenCode.end());
        code.push_back("goto " + labelEnd);

        code.push_back(labelElseif + ":");
        if (elseifList)
        {
            auto [__, elseifCode] = elseifList->generateIC();
            code.insert(code.end(), elseifCode.begin(), elseifCode.end());
        }

        if (elseBlock)
        {
            auto [___, elseCode] = elseBlock->generateIC();
            code.insert(code.end(), elseCode.begin(), elseCode.end());
        }

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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "while\n";
        cond->print(indent + 1);
        std::cout << "\n";
        block->print(indent + 1);
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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "for\n";
        Node::indent++;
        printIndent();
        std::cout << var << "\n";
        start->print(indent + 1);
        std::cout << "\n";
        end->print(indent + 1);
        std::cout << "\n";
        step->print(indent + 1);
        std::cout << "\n";
        body->print(indent + 1);
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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "print\n";
        expr->print(indent + 1);
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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        first->print(indent);
        if (second)
        {
            std::cout << "\n";
            second->print(indent);
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
    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "-\n";
        expr->print(indent + 1);
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

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << op << "\n";
        expr->print(indent + 1);
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
// Add StringNode class
class StringNode : public Node
{
    std::string value;

public:
    StringNode(const std::string &v) : value(v) {}

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "\"" << value << "\"";
    }

    Value evaluate() override
    {
        return value;
    }

    ICResult generateIC() override
    {
        std::string temp = newTemp();
        return {temp, {temp + " = \"" + value + "\""}};
    }
};

class ElseIfNode : public Node
{
public:
    Node *condition;
    Node *body;
    Node *next; // Next elseif in chain

    ElseIfNode(Node *cond, Node *body, Node *next = nullptr)
        : condition(cond), body(body), next(next) {}

    Value evaluate() override;

    void print(int indent = 0) const override
    {
        Node::indent = indent;
        printIndent();
        std::cout << "elseif\n";
        condition->print(indent + 1);
        std::cout << "\n";
        body->print(indent + 1);
        if (next)
        {
            std::cout << "\n";
            next->print(indent);
        }
    }

    std::pair<std::string, std::vector<std::string>> generateIC() override
    {
        auto [condTemp, condCode] = condition->generateIC();
        auto [_, bodyCode] = body->generateIC();

        std::string labelNext = newLabel();
        std::string labelEnd = newLabel();

        std::vector<std::string> code = condCode;
        code.push_back("if " + condTemp + " = 0 goto " + labelNext);
        code.insert(code.end(), bodyCode.begin(), bodyCode.end());
        code.push_back("goto " + labelEnd);
        code.push_back(labelNext + ":");

        if (next)
        {
            auto [__, nextCode] = next->generateIC();
            code.insert(code.end(), nextCode.begin(), nextCode.end());
        }

        code.push_back(labelEnd + ":");
        return {"", code};
    }
};
#endif
