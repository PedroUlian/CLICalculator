#include "parser.h"
#include "lexer.h"
#include "node.h"
#include <stddef.h>

Token current_token;

void init_parser(){
    current_token = get_next_token();
}

int eat(TokenType type){

    if(current_token.type == type){

        current_token = get_next_token();
        return 0;

    } else {
        return 1;
    }
}

Node *parse_factor(){
	if(current_token.type == TOKEN_NUMBER){
		Node *node = create_node(current_token);
		eat(TOKEN_NUMBER);
		return node;
	}

	if(current_token.type == TOKEN_LPAREN){

        eat(TOKEN_LPAREN);

        Node *node = parse_expression();

        eat(TOKEN_RPAREN);

        return node;
    }

	return NULL;
}

Node *parse_power();
Node *parse_unary(){

    if(current_token.type == TOKEN_MINUS ||
       current_token.type == TOKEN_PLUS)
    {
        Token op_token = current_token;

        eat(op_token.type);

        Node *right = parse_unary();

        Node *zero = create_node(
            create_token(TOKEN_NUMBER, 0)
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

	while(current_token.type == TOKEN_TIMES || current_token.type == TOKEN_OVER){
		Token op_token = current_token;

		eat(current_token.type);

		Node *right = parse_unary();
		Node *op = create_node(op_token);

		op->left = left;
		op->right = right;

		left = op;
	}

	return left;
}

Node *parse_expression(){
	Node *left = parse_term();

	while(current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS){
		Token op_token = current_token;

		eat(current_token.type);

		Node *right = parse_term();
		Node *op = create_node(op_token);

		op->left = left;
		op->right = right;

		left = op;
	}

	return left;
}