#include "ast.h"
#include <map>

// Initialize static members
int Node::tempCount = 0;
int Node::labelCount = 0;
int Node::indent = 0;
bool Node::debug = false;
int Node::depth = 0;

// Global symbol table for variable storage
std::map<std::string, Value> symbolTable;

Value VarNode::evaluate()
{
    tracePrint("VarNode");
    TraceGuard guard;
    if (symbolTable.find(name) == symbolTable.end())
    {
        throw std::runtime_error("Undefined variable: " + name);
    }
    return symbolTable[name];
}

Value BinaryOpNode::evaluate()
{
    tracePrint("BinaryOpNode");
    TraceGuard guard;
    Value leftVal = left->evaluate();
    Value rightVal = right->evaluate();

    // Arithmetic operations (require integers)
    if (op == "..")
    {
        try
        {
            std::string result;

            // Convert left value to string
            if (std::holds_alternative<std::string>(leftVal))
            {
                result = std::get<std::string>(leftVal);
            }
            else if (std::holds_alternative<int>(leftVal))
            {
                result = std::to_string(std::get<int>(leftVal));
            }
            else if (std::holds_alternative<bool>(leftVal))
            {
                result = std::get<bool>(leftVal) ? "true" : "false";
            }

            // Convert and concatenate right value
            if (std::holds_alternative<std::string>(rightVal))
            {
                result += std::get<std::string>(rightVal);
            }
            else if (std::holds_alternative<int>(rightVal))
            {
                result += std::to_string(std::get<int>(rightVal));
            }
            else if (std::holds_alternative<bool>(rightVal))
            {
                result += std::get<bool>(rightVal) ? "true" : "false";
            }

            return result;
        }
        catch (const std::bad_variant_access &)
        {
            throw std::runtime_error("Invalid types for concatenation");
        }
    }

    if (op == "+" || op == "-" || op == "*" || op == "/")
    {
        try
        {
            int l = std::get<int>(leftVal);
            int r = std::get<int>(rightVal);

            if (op == "+")
                return l + r;
            if (op == "-")
                return l - r;
            if (op == "*")
                return l * r;
            if (op == "/")
            {
                if (r == 0)
                    throw std::runtime_error("Division by zero");
                return l / r;
            }
        }
        catch (const std::bad_variant_access &)
        {
            throw std::runtime_error("Arithmetic operations require numbers");
        }
    }

    // Comparison operations (can compare integers)
    if (op == "<" || op == ">" || op == "==" || op == "~=" || op == "<=" || op == ">=")
    {
        try
        {
            int l = std::get<int>(leftVal);
            int r = std::get<int>(rightVal);

            if (op == "<")
                return l < r;
            if (op == ">")
                return l > r;
            if (op == "==")
                return l == r;
            if (op == "~=")
                return l != r;
            if (op == "<=")
                return l <= r;
            if (op == ">=")
                return l >= r;
        }
        catch (const std::bad_variant_access &)
        {
            throw std::runtime_error("Comparison requires compatible types");
        }
    }

    // Logical operations (require booleans)
    if (op == "and" || op == "or")
    {
        bool l, r;

        // Convert left value to boolean
        if (std::holds_alternative<bool>(leftVal))
        {
            l = std::get<bool>(leftVal);
        }
        else if (std::holds_alternative<int>(leftVal))
        {
            l = std::get<int>(leftVal) != 0;
        }

        // Convert right value to boolean
        if (std::holds_alternative<bool>(rightVal))
        {
            r = std::get<bool>(rightVal);
        }
        else if (std::holds_alternative<int>(rightVal))
        {
            r = std::get<int>(rightVal) != 0;
        }

        if (op == "and")
            return bool(l && r);
        if (op == "or")
            return bool(l || r);
    }

    throw std::runtime_error("Unknown operator: " + op);
}

Value AssignNode::evaluate()
{
    tracePrint("AssignNode");
    TraceGuard guard;
    Value exprValue = expr->evaluate();
    symbolTable[var] = exprValue; // Store the Value directly
    return exprValue;
}

// Value IfNode::evaluate()
// {
//     if (std::get<bool>(cond->evaluate()))
//     {
//         return thenBlock->evaluate();
//     }
//     else if (elseBlock)
//     {
//         return elseBlock->evaluate();
//     }
//     return 0;
// }
Value IfNode::evaluate()
{
    tracePrint("IfNode");
    TraceGuard guard;
    Value condResult = condition->evaluate();
    bool condValue;

    if (std::holds_alternative<bool>(condResult))
    {
        condValue = std::get<bool>(condResult);
    }
    else if (std::holds_alternative<int>(condResult))
    {
        condValue = std::get<int>(condResult) != 0;
    }
    else
    {
        throw std::runtime_error("Condition must evaluate to boolean or number");
    }

    if (condValue)
    {
        return thenBlock->evaluate();
    }
    else if (elseifList)
    {
        return elseifList->evaluate();
    }
    else if (elseBlock)
    {
        return elseBlock->evaluate();
    }
    return 0;
}

Value ElseIfNode::evaluate()
{
    tracePrint("ElseIfNode");
    TraceGuard guard;
    Value condResult = condition->evaluate();
    bool condValue;

    if (std::holds_alternative<bool>(condResult))
    {
        condValue = std::get<bool>(condResult);
    }
    else if (std::holds_alternative<int>(condResult))
    {
        condValue = std::get<int>(condResult) != 0;
    }
    else
    {
        throw std::runtime_error("Condition must evaluate to boolean or number");
    }

    if (condValue)
    {
        return body->evaluate();
    }
    else if (next)
    {
        return next->evaluate();
    }
    return 0;
}

Value WhileNode::evaluate()
{
    tracePrint("WhileNode");
    TraceGuard guard;
    while (std::get<bool>(cond->evaluate()))
    {
        block->evaluate();
    }
    return 0;
}

Value ForNode::evaluate()
{
    tracePrint("ForNode");
    TraceGuard guard;
    int startVal = std::get<int>(start->evaluate());
    int endVal = std::get<int>(end->evaluate());
    int stepVal = std::get<int>(step->evaluate());

    symbolTable[var] = startVal;

    if (stepVal > 0)
    {
        for (int i = startVal; i <= endVal; i += stepVal)
        {
            symbolTable[var] = Value(i);
            body->evaluate();
        }
    }
    else
    {
        for (int i = startVal; i >= endVal; i += stepVal)
        {
            symbolTable[var] = Value(i);
            body->evaluate();
        }
    }
    return 0;
}

Value BlockNode::evaluate()
{
    tracePrint("BlockNode");
    TraceGuard guard;
    first->evaluate();
    if (second)
        second->evaluate();
    return 0;
}

Value PrintNode::evaluate()
{
    tracePrint("PrintNode");
    TraceGuard guard;
    Value val = expr->evaluate();
    if (std::holds_alternative<std::string>(val))
    {
        std::cout << std::get<std::string>(val) << std::endl;
    }
    else if (std::holds_alternative<int>(val))
    {
        std::cout << std::get<int>(val) << std::endl;
    }
    else if (std::holds_alternative<bool>(val))
    {
        std::cout << (std::get<bool>(val) ? "true" : "false") << std::endl;
    }
    return val;
}

Value UnaryMinusNode::evaluate()
{
    tracePrint("UnaryMinusNode");
    TraceGuard guard;
    return -std::get<int>(expr->evaluate());
}

Value UnaryOpNode::evaluate()
{
    tracePrint("UnaryOpNode");
    TraceGuard guard;
    if (op == "not")
    {
        return !std::get<bool>(expr->evaluate());
    }
    throw std::runtime_error("Unknown unary operator: " + op);
}