#include "calculator.h"
#include "math.h"

double evaluate(Node *node){

	if(node->token.type == TOKEN_NUMBER){
		return node->token.value;
	}

	double left = evaluate(node->left);
	double right = evaluate(node->right);

	switch(node->token.type){

		case TOKEN_PLUS:
			return left+right;

		case TOKEN_MINUS:
			return left-right;

		case TOKEN_TIMES:
			return left*right;

		case TOKEN_OVER:
			return left/right;

		case TOKEN_CARET:
			return pow(left, right);

		case TOKEN_RADICAL:
			return pow(right, 1.0/left);
	}
	return 0;
}
