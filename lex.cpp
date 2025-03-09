#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_set>
#include <iomanip>  =

using namespace std;

// Lua Keywords
unordered_set<string> keywords = {"and", "break", "do", "else", "elseif", "end", "false", "for", "function", "if", "in", "local", "nil", "not", "or", "repeat", "return", "then", "true", "until", "while"};

// Operators and symbols
unordered_set<string> operators = {"+", "-", "*", "/", "%", "^", "#", "==", "~=", "<=", ">=", "<", ">", "=", "(", ")", "{", "}", "[", "]", ";", ":", ",", "..", "...", ".", ".."};

// Function to classify token type
string classifyToken(const string &token) {
    if (keywords.find(token) != keywords.end()) return "Keyword";
    if (operators.find(token) != operators.end()) return "Operator";
    if (regex_match(token, regex("[a-zA-Z_][a-zA-Z0-9_]*"))) return "Identifier";
    if (regex_match(token, regex("[0-9]+(\\.[0-9]+)?"))) return "Number";
    if (token[0] == '"' && token[token.size() - 1] == '"') return "String";
    return "Unknown";
}

// Lexical Analyzer Function
void lexicalAnalyzer(const string &code) {
    regex token_regex(R"([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+(\.[0-9]+)?|[+\-*/%^#=<>!~;:{}\[\](),.]|(\.\.|\.{3})|\"[^\"]*\")");
    auto words_begin = sregex_iterator(code.begin(), code.end(), token_regex);
    auto words_end = sregex_iterator();

    cout << "-----------------------------------\n";
    cout << "Lexeme\t\t\tToken\n";
    cout << "-----------------------------------\n";
    
    for (auto i = words_begin; i != words_end; ++i) {
        string token = i->str();
        cout << setw(15) << left << token << "\t\t" << classifyToken(token) << endl;
    }
}

int main() {
    string filename = "input.lua";
    ifstream file(filename);
    
    if (!file) {
        cerr << "No such file(make sure u have input.lua with sample lua program in it.)" << endl;
        return 1;
    }
    
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    lexicalAnalyzer(code);
    return 0;
}
