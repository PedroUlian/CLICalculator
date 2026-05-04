#include <stdlib.h>
#include "node.h"

Node *create_node(Token token){

    Node *node = malloc(sizeof(Node));

    node->token = token;

    node->left = NULL;
    node->right = NULL;

    return node;
}