#ifndef ERR_H
#define ERR_H

typedef enum {
    ERROR_NONE = 0,
    ERROR_SYNTAX,          // Ex: "5 ++ 2"
    ERROR_DIV_BY_ZERO,     // Ex: "5 / 0"
    ERROR_INVALID_CHAR,    // Ex: "5 @ 2"
    ERROR_UNBALANCED_PAREN, // Ex: "(5 + 2"
    ERROR_UNDEFINED_NODE
} CalcError;

// Variável global para armazenar o último erro (simples e eficaz para CLI)
extern CalcError last_error;

void print_error();

#endif