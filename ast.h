// ast.h
#ifndef AST_H
#define AST_H
#include <stdio.h>
typedef struct Node {
    char* type;
    struct Node* left;
    struct Node* right;
    struct Node* extra;
    char* value;
} Node;

typedef struct {
    char* result;
    char* op;
    char* arg1;
    char* arg2;
} ThreeAddressCode;

typedef struct {
    ThreeAddressCode* instructions;
    int size;
    int capacity;
} ICList;

Node* createNode(const char* type, Node* left, Node* right, Node* extra, const char* value);
void printAST(Node* node, int depth, FILE* out);
void freeAST(Node* node);
ICList* createICList(int initialCapacity);
void addInstruction(ICList* list, const char* result, const char* op, const char* arg1, const char* arg2);
void freeICList(ICList* list);
void generateIC(Node* node, ICList* list, int* tempCounter, int* labelCounter);
char* newTemp(int* counter);
char* newLabel(int* counter);
void printIC(ICList* list, FILE* out);

#endif
