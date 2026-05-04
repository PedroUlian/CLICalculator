#include "lexer.h"
#include <ctype.h>

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

Token create_token(TokenType type, double value){

	Token token;
	token.type = type;
	token.value = value;
	return token;

}

Token read_number(){
	double number = 0;

	while(isdigit(current_char)){
		number = number*10+(current_char - '0');
		advance();
	}
	
	return create_token(TOKEN_NUMBER, number);
}

Token get_next_token(){

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
			return create_token(TOKEN_PLUS, 0);
		}

		if(current_char == '-'){
			advance();
			return create_token(TOKEN_MINUS, 0);
		}

		if(current_char == '*'){
			advance();
			return create_token(TOKEN_TIMES, 0);
		}

		if(current_char == '/'){
			advance();
			return create_token(TOKEN_OVER, 0);
		}

		if(current_char == '('){
			advance();
			return create_token(TOKEN_LPAREN, 0);
		}

		if(current_char == ')'){
			advance();
			return create_token(TOKEN_RPAREN, 0);
		}
	}

	return create_token(TOKEN_EOF, 0);

}