#include "calculator.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	init_lexer(argv[1]);
	init_parser();

	Node *tree = parse_expression();
	double result = evaluate(tree);
	
	printf("%f\n", result);

	return 0;
}