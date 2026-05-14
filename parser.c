#include "parser.h"
#include "lexer.h"
#include "node.h"
#include <stddef.h>
#include "err.h"

Token current_token;

void init_parser(){
    current_token = get_next_token();
}

int eat(TokenType type){

    if(current_token.type == type){

        current_token = get_next_token();
        return 0;

    } else {
        last_error = ERROR_SYNTAX;
        return 1;
    }
}

Node *parse_expression_internal();
Node *parse_unary();
Node *parse_factor(){
    if (last_error != ERROR_NONE) return NULL;
    
    Node *node = NULL;

    // 1. Pega o número base ou o parênteses
    if(current_token.type == TOKEN_NUMBER){
        node = create_node(current_token);
        eat(TOKEN_NUMBER);
    } 
    else if(current_token.type == TOKEN_LPAREN){
        eat(TOKEN_LPAREN);
        node = parse_expression_internal();
        if (current_token.type != TOKEN_RPAREN) {
            last_error = ERROR_UNBALANCED_PAREN;
            return node;
        }
        eat(TOKEN_RPAREN);
    } 
    else {
        last_error = ERROR_SYNTAX;
        return NULL;
    }

    if (current_token.type == TOKEN_EXP) {
        Token op_token = current_token;
        eat(TOKEN_EXP);

        Node *right = parse_unary(); 
        
        Node *op = create_node(op_token);
        op->left = node;
        op->right = right;
        return op;
    }

    return node;
}

Node *parse_power();
Node *parse_unary(){
    if (last_error != ERROR_NONE) return NULL;

    if(current_token.type == TOKEN_MINUS ||
       current_token.type == TOKEN_PLUS)
    {
        Token op_token = current_token;
        eat(op_token.type);

        Node *right = parse_unary();
        
        Number zero_num = create_number("0"); 
        Node *zero = create_node(
            create_token(TOKEN_NUMBER, zero_num)
        );

        Node *op = create_node(op_token);
        op->left = zero;
        op->right = right;

        return op;
    }

    return parse_power();
}

Node *parse_power(){

    Node *left = parse_factor();
    if (!left || last_error != ERROR_NONE) return NULL;

    if(current_token.type == TOKEN_CARET ||
       current_token.type == TOKEN_RADICAL)
    {
        Token op_token = current_token;

        eat(op_token.type);

        Node *right = parse_unary();

        Node *op = create_node(op_token);

        op->left = left;
        op->right = right;

        return op;
    }

    return left;
}

Node *parse_term(){
    Node *left = parse_unary();
    if (!left || last_error != ERROR_NONE) return NULL;

    while(current_token.type == TOKEN_TIMES || current_token.type == TOKEN_OVER){
        Token op_token = current_token;

        eat(current_token.type);
        if (last_error != ERROR_NONE) return left;

        Node *right = parse_unary();
        if (!right || last_error != ERROR_NONE) return left;

        Node *op = create_node(op_token);

        op->left = left;
        op->right = right;

        left = op;
    }

    return left;
}

Node *parse_expression_internal(){
    Node *left = parse_term();
    if (!left || last_error != ERROR_NONE) return NULL;

    while(current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS){
        Token op_token = current_token;

        eat(current_token.type);
        if (last_error != ERROR_NONE) return left;

        Node *right = parse_term();
        if (!right || last_error != ERROR_NONE) return left;

        Node *op = create_node(op_token);
        op->left = left;
        op->right = right;
        left = op;
    }

    return left;
}


Node *parse_expression(){

    Node *left = parse_expression_internal();

    if (current_token.type != TOKEN_EOF && last_error == ERROR_NONE) {
        last_error = ERROR_SYNTAX;
    }

    return left;
}