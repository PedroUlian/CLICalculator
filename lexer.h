#ifndef LEXER_H
#define LEXER_H

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
    double value;

} Token;

void init_lexer(const char *text);
Token get_next_token();
Token create_token(TokenType type, double value);

#endif