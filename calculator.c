#include "calculator.h"
#include "number.h"
#include "math.h"
#include "err.h"
#include <stdlib.h>

Number evaluate(Node *node) {
    if (!node || last_error != ERROR_NONE) return create_number("0");

    if (node->token.type == TOKEN_NUMBER) {
        return create_number(node->token.value.number_str);
    }

    Number left = evaluate(node->left);
    Number right = evaluate(node->right);
    Number result;

    switch(node->token.type) {
        case TOKEN_PLUS:  result = nadd(left, right); break;

        case TOKEN_MINUS: result = nsub(left, right); break;

        case TOKEN_TIMES: result = nmult(left, right); break;

        case TOKEN_OVER:
            if (to_double(right) == 0) {
                last_error = ERROR_DIV_BY_ZERO;
                result = create_number("NaN");
            } else {
                result = ndiv(left, right);
            }
            break;

        case TOKEN_CARET:   result = npow(left, right); break;

        case TOKEN_RADICAL: result = nroot(left, right); break;

        default: result = create_number("0");
    }

    free(left.number_str);
    free(right.number_str);

    return result;
}