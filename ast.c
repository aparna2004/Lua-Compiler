// ast.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"

Node* createNode(const char* type, Node* left, Node* right, Node* extra, const char* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = strdup(type);
    node->left = left;
    node->right = right;
    node->extra = extra;
    node->value = value ? strdup(value) : NULL;
    return node;
}

void printAST(Node* node, int depth, FILE* out) {
    if (!node) return;
    for (int i = 0; i < depth; i++) fprintf(out, "  ");
    fprintf(out, "%s", node->type);
    if (node->value) fprintf(out, "(%s)", node->value);
    fprintf(out, "\n");
    printAST(node->left, depth + 1, out);
    printAST(node->right, depth + 1, out);
    printAST(node->extra, depth + 1, out);
}

void freeAST(Node* node) {
    if (!node) return;
    freeAST(node->left);
    freeAST(node->right);
    freeAST(node->extra);
    free(node->type);
    if (node->value) free(node->value);
    free(node);
}

ICList* createICList(int initialCapacity) {
    ICList* list = (ICList*)malloc(sizeof(ICList));
    list->instructions = (ThreeAddressCode*)malloc(initialCapacity * sizeof(ThreeAddressCode));
    list->size = 0;
    list->capacity = initialCapacity;
    return list;
}

void addInstruction(ICList* list, const char* result, const char* op, const char* arg1, const char* arg2) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->instructions = (ThreeAddressCode*)realloc(list->instructions, list->capacity * sizeof(ThreeAddressCode));
    }
    ThreeAddressCode* instr = &list->instructions[list->size++];
    instr->result = result ? strdup(result) : NULL;
    instr->op = strdup(op);
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
}

void freeICList(ICList* list) {
    for (int i = 0; i < list->size; i++) {
        free(list->instructions[i].result);
        free(list->instructions[i].op);
        free(list->instructions[i].arg1);
        free(list->instructions[i].arg2);
    }
    free(list->instructions);
    free(list);
}

char* newTemp(int* counter) {
    char temp[16];
    sprintf(temp, "t%d", (*counter)++);
    return strdup(temp);
}

char* newLabel(int* counter) {
    char label[16];
    sprintf(label, "L%d", (*counter)++);
    return strdup(label);
}

void printIC(ICList* list, FILE* out) {
    for (int i = 0; i < list->size; i++) {
        ThreeAddressCode* instr = &list->instructions[i];
        if (strcmp(instr->op, "goto") == 0 || strcmp(instr->op, "label") == 0) {
            fprintf(out, "%s %s\n", instr->op, instr->arg1);
        }
        else if(strcmp(instr->op,"=") == 0){
//            fprintf(out,"res '%s' a1 '%s' op '%s' a2 '%s'\n", instr->result, instr->arg1, instr->op, instr->arg2 ? instr->arg2 : "");
            fprintf(out, "%s = %s \n", instr->result, instr->arg1);

        }
        else if(strcmp(instr->op,"if") == 0){
//            fprintf(out,"res '%s' a1 '%s' op '%s' a2 '%s'\n", instr->result, instr->arg1, instr->op, instr->arg2 ? instr->arg2 : "");
            fprintf(out, "if %s goto %s \n", instr->arg1, instr->arg2);

        }
        else {
//            fprintf(out,"res '%s' a1 '%s' op '%s' a2 '%s'\n", instr->result, instr->arg1, instr->op, instr->arg2 ? instr->arg2 : "");
            fprintf(out, "%s = %s %s %s\n", instr->result, instr->arg1, instr->op, instr->arg2 ? instr->arg2 : "");
        }
    }
}

void generateIC(Node* node, ICList* list, int* tempCounter, int* labelCounter) {
    if (!node) return;

    if (strcmp(node->type, "stmt_list") == 0) {
        generateIC(node->left, list, tempCounter, labelCounter);
        generateIC(node->right, list, tempCounter, labelCounter);
    }
    else if (strcmp(node->type, "assign") == 0) {
        char* rhs = newTemp(tempCounter);
        generateIC(node->right, list, tempCounter, labelCounter);
        addInstruction(list, rhs, node->right->type, node->right->left ? node->right->left->value : node->right->value, 
                       node->right->right ? node->right->right->value : NULL);
        addInstruction(list, node->left->value, "=", rhs, NULL);
        free(rhs);
    }
    else if (strcmp(node->type, "if") == 0) {
        char* condTemp = newTemp(tempCounter);
        generateIC(node->left, list, tempCounter, labelCounter);
        addInstruction(list, condTemp, node->left->type, node->left->left->value, node->left->right->value);

        char* labelTrue = newLabel(labelCounter);
        char* labelFalse = newLabel(labelCounter);
        char* labelEnd = node->extra ? newLabel(labelCounter) : labelFalse;

        addInstruction(list, NULL, "if", condTemp, labelTrue);
        addInstruction(list, NULL, "goto", labelFalse, NULL);

        addInstruction(list, NULL, "label", labelTrue, NULL);
        generateIC(node->right, list, tempCounter, labelCounter);
        if (node->extra) addInstruction(list, NULL, "goto", labelEnd, NULL);

        addInstruction(list, NULL, "label", labelFalse, NULL);
        if (node->extra) {
            generateIC(node->extra, list, tempCounter, labelCounter);
            addInstruction(list, NULL, "label", labelEnd, NULL);
        }

        free(condTemp); free(labelTrue); free(labelFalse);
        if (node->extra) free(labelEnd);
    }
    else if (strcmp(node->type, "while") == 0) {
        char* labelStart = newLabel(labelCounter);
        char* labelTrue = newLabel(labelCounter);
        char* labelEnd = newLabel(labelCounter);

        addInstruction(list, NULL, "label", labelStart, NULL);
        char* condTemp = newTemp(tempCounter);
        generateIC(node->left, list, tempCounter, labelCounter);
        addInstruction(list, condTemp, node->left->type, node->left->left->value, node->left->right->value);

        addInstruction(list, NULL, "if", condTemp, labelTrue);
        addInstruction(list, NULL, "goto", labelEnd, NULL);

        addInstruction(list, NULL, "label", labelTrue, NULL);
        generateIC(node->right, list, tempCounter, labelCounter);
        addInstruction(list, NULL, "goto", labelStart, NULL);

        addInstruction(list, NULL, "label", labelEnd, NULL);

        free(condTemp); free(labelStart); free(labelTrue); free(labelEnd);
    }
}
