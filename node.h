#ifndef NODE_H
#define NODE_H
#include "lexer.h"

typedef struct Node {

    Token token;

    struct Node *left;
    struct Node *right;

} Node;

Node *create_node(Token token);

#endif