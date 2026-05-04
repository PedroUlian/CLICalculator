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

Node *parse_term(){
	Node *left = parse_factor();

	while(current_token.type == TOKEN_TIMES || current_token.type == TOKEN_OVER){
		Token op_token = current_token;

		eat(current_token.type);

		Node *right = parse_factor();
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