#include "calculator.h"
#include "math.h"
#include "err.h"

double evaluate(Node *node) {
    if (!node || last_error != ERROR_NONE) return 0;

    if (node->token.type == TOKEN_NUMBER) {
        return node->token.value;
    }

    double left = evaluate(node->left);
    double right = evaluate(node->right);

    switch(node->token.type) {
        case TOKEN_OVER:
            if (right == 0) {
                last_error = ERROR_DIV_BY_ZERO;
                return 0;
            }
            return left / right;

        case TOKEN_CARET:
			return pow(left, right);

		case TOKEN_RADICAL:
			return pow(right, 1.0/left);

		case TOKEN_PLUS:
			return left+right;

		case TOKEN_MINUS:
			return left-right;

		case TOKEN_TIMES:
			return left*right;
    }
    return 0;
}