#include "calculator.h"
#include "mpdecimal.h"
#include "number.h"
#include "err.h"
#include <stdlib.h>
#include <string.h>

int is_integer_str(const char *str) {
    if (!str || str[0] == '\0') return 0;

    mpd_context_t ctx;
    mpd_maxcontext(&ctx);
    ctx.traps = 0;
    ctx.status = 0;

    mpd_t *val = mpd_new(&ctx);
    mpd_t *floor_val = mpd_new(&ctx);
    
    mpd_set_string(val, str, &ctx);

    mpd_floor(floor_val, val, &ctx);

    int result = (mpd_cmp(val, floor_val, &ctx) == 0);

    mpd_del(val);
    mpd_del(floor_val);
    
    return result;
}

Number evaluate(Node *node) {
    if (!node || last_error != ERROR_NONE) return create_number("0");

    if (node->token.type == TOKEN_NUMBER) {
        return create_number(node->token.value.number_str);
    }

    Number left = evaluate(node->left);
    Number right = evaluate(node->right);
    Number result = create_number("0");

    if (last_error != ERROR_NONE) {
        if (left.number_str) free(left.number_str);
        if (right.number_str) free(right.number_str);
        return create_number("NaN");
    }

    switch(node->token.type) {
        case TOKEN_PLUS:  result = nadd(left, right); break;

        case TOKEN_MINUS: result = nsub(left, right); break;

        case TOKEN_TIMES: result = nmult(left, right); break;

        case TOKEN_OVER:
            if (is_str_zero(right.number_str)) {
                last_error = ERROR_DIV_BY_ZERO;
                result = create_number("NaN");
            } else {
                result = ndiv(left, right);
            }
            break;

        case TOKEN_CARET:   result = npow(left, right); break;

        case TOKEN_RADICAL: result = nroot(left, right); break;

        case TOKEN_EXP:
            if (!is_integer_str(right.number_str)){
                last_error = ERROR_INVALID_EXPONENT;
                result = create_number("NaN");
            } else {
                result = nexp(left, right);
            }
            break;


        default: result = create_number("0");
    }

    if (left.number_str) free(left.number_str);
    if (right.number_str) free(right.number_str);

    return result;
}