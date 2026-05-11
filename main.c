#include "calculator.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include "err.h"
#include <string.h>

// Função auxiliar para evitar duplicar a lógica de execução
void process_expression(const char *input) {
    last_error = ERROR_NONE; // Garante que começamos sem erros antigos

    init_lexer(input);
    init_parser();

    // Se o lexer/parser inicial já pegou um caractere inválido, para aqui
    if (last_error != ERROR_NONE) {
        print_error();
        return;
    }

    Node *tree = parse_expression();
    
    // Verifica se houve erro de sintaxe durante o parsing
    if (last_error != ERROR_NONE) {
        print_error();
        return;
    }

    Number result = evaluate(tree);
    
    // Verifica se houve erro em tempo de execução (Ex: divisão por zero)
    if (last_error != ERROR_NONE) {
        print_error();
    } else {
        printf("Resultado: %s\n", result.number_str);
    }
}

int main(int argc, char const *argv[])
{
    if (argc > 1) {
        // Execução direta por argumento: ./calculadora "2 + 2"
        process_expression(argv[1]);
    }
    else {
        // Modo interativo (REPL)
        char input[256];

        while (1) {
            printf("calc> ");
            fflush(stdout);

            if (!fgets(input, sizeof(input), stdin))
                break;

            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, "exit") == 0)
                break;

            // Se o usuário só apertar Enter, ignora e vai para a próxima linha
            if (strlen(input) == 0)
                continue;

            process_expression(input);
        }
    }

    return 0;
}
