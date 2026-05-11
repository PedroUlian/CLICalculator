#include "lexer.h"
#include <ctype.h>
#include "err.h"
#include <stdio.h>

const char *source;
int position;
char current_char;

void init_lexer(const char *text){

	source = text;
	position = 0;
	current_char = source[position];

}

void advance(){
	position++;
	current_char = source[position];
}

Token create_token(TokenType type, Number value){

	Token token;
	token.type = type;
	token.value = value;
	return token;

}

Token read_number() {
    char buffer[256];
    int i = 0;

    while (isdigit(current_char)) {
        if (i < 255) buffer[i++] = current_char;
        advance();
    }

    if (current_char == '.') {
        if (i < 255) buffer[i++] = current_char;
        advance();

        while (isdigit(current_char)) {
            if (i < 255) buffer[i++] = current_char;
            advance();
        }
    }

    buffer[i] = '\0';

    Number n = create_number(buffer);
    return create_token(TOKEN_NUMBER, n);

}

Token get_next_token(){
	Number null_num = { .number_str = NULL };

	while(current_char != '\0'){

		if(isspace(current_char)){
			advance();
			continue;
		}

		if(isdigit(current_char)){
			return read_number();
		}

		if(current_char == '+'){
			advance();
			return create_token(TOKEN_PLUS, null_num);
		}

		if(current_char == '-'){
			advance();
			return create_token(TOKEN_MINUS, null_num);
		}

		if(current_char == '*'){
			advance();
			return create_token(TOKEN_TIMES, null_num);
		}

		if(current_char == '/'){
			advance();
			return create_token(TOKEN_OVER, null_num);
		}

		if(current_char == '('){
			advance();
			return create_token(TOKEN_LPAREN, null_num);
		}

		if(current_char == ')'){
			advance();
			return create_token(TOKEN_RPAREN, null_num);
		}

		if(current_char == '^'){
			advance();
			return create_token(TOKEN_CARET, null_num);
		}

		if(current_char == 'r'){
			advance();
			return create_token(TOKEN_RADICAL, null_num);
		}

		if (current_char != '\0') {
        last_error = ERROR_INVALID_CHAR;
        printf("Caractere inesperado: %c\n", current_char);
        advance();
        return create_token(TOKEN_EOF, null_num);
    	}
	}

	return create_token(TOKEN_EOF, null_num);

}