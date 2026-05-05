#include "calculator.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if(argc > 1){
        init_lexer(argv[1]);
        init_parser();

        Node *tree = parse_expression();
        double result = evaluate(tree);

        printf("%f\n", result);
    }
    else{
        char input[256];

        while(1){
            printf("calc> ");

            if(!fgets(input, sizeof(input), stdin))
                break;

            input[strcspn(input, "\n")] = 0;

            if(strcmp(input, "exit") == 0)
                break;

            init_lexer(input);
            init_parser();

            Node *tree = parse_expression();
            double result = evaluate(tree);

            printf("%f\n", result);
        }
    }

    return 0;
}