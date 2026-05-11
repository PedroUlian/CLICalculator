#ifndef LEXER_H
#define LEXER_H

#include "number.h"

typedef enum {

	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_TIMES,
	TOKEN_OVER,
	TOKEN_CARET,
	TOKEN_RADICAL,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF

} TokenType;

typedef struct {

    TokenType type;
    Number value;

} Token;

void init_lexer(const char *text);
Token get_next_token();
Token create_token(TokenType type, Number value);

#endif