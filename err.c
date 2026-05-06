#include "err.h"
#include <stdio.h>

// Definição da variável global
CalcError last_error = ERROR_NONE;

void print_error() {
    // Se não houver erro, não faz nada
    if (last_error == ERROR_NONE) return;

    printf("\033[1;31m[ERRO] "); // Início da cor vermelha

    switch (last_error) {
        case ERROR_SYNTAX:
            printf("Sintaxe invalida. Verifique a ordem dos operadores e operandos.");
            break;
        case ERROR_DIV_BY_ZERO:
            printf("Divisao por zero detectada.");
            break;
        case ERROR_INVALID_CHAR:
            printf("Caractere nao reconhecido na expressao.");
            break;
        case ERROR_UNBALANCED_PAREN:
            printf("Parenteses nao balanceados (abertos ou fechados incorretamente).");
            break;
        case ERROR_UNDEFINED_NODE:
            printf("Operacao ou no nao definido na arvore de expressao.");
            break;
        default:
            printf("Erro desconhecido.");
            break;
    }

    printf("\033[0m\n"); // Reseta a cor para o padrão do terminal
}