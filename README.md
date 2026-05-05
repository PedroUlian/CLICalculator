# Terminal Calculator Engine

Uma calculadora poderosa e flexível de linha de comando escrita para executar diretamente no terminal. O motor suporta expressões matemáticas complexas, agrupamentos por parênteses, números negativos, potências e extração de raízes de qualquer índice (raízes enésimas).

## Funcionalidades

- **Aritmética Avançada:** Suporte completo para adição (`+`), subtração (`-`), multiplicação (`*`), divisão (`/`), exponenciação (`^`) e extração de qualquer raiz (`r`, ex: `3r64` para raiz cúbica de 64).
- **Suporte a Sinais e Decimais:** Manipulação nativa de números negativos, operadores unários e valores de ponto flutuante (decimais).
- **Agrupamento de Expressões:** Suporte total a parênteses `()` para gerenciar e impor a ordem correta de operações complexas ou aninhadas.
- **Dois Modos de Execução:** Modo interativo (REPL) ou passagem direta por argumentos.

---
## Exemplos de Sintaxe
| Operação | Sintaxe | Exemplo | Resultado |
| ----------- | ----------- | ----------- | ----------- |
| Exponenciação |	base ^ expoente	| 2^3	| 8 |
| Raiz Quadrada	| 2 r número | 2r16	| 4 |
| Raiz Cúbica	| 3 r número | 3r64	| 4 |
| Exponenciação |	base ^ expoente	| 2^3	| 8 |
| Raiz Enésima (Qualquer)	| índice r número | 4r16 | 2 |
| Expressão Complexa | (operadores + parênteses) | (5--2)*3^2 | 63 |

---

## Roadmap / Próximos Passos
O motor de cálculo está funcional e avalia expressões matemáticas com precisão. O desenvolvimento segue ativo com as seguintes metas:

- Tratamento de Erros Adequado: Implementar validações robustas para capturar erros de sintaxe (parênteses não fechados, operadores duplicados) e erros matemáticos (divisão por zero, raiz de número negativo com índice par) antes da avaliação do motor.

- Melhorar as mensagens de feedback visual no terminal quando uma expressão for inválida.

---

## Como Usar

O programa pode ser utilizado de duas maneiras diferentes no terminal:

### 1. Modo Interativo (Shell da Calculadora)
Basta abrir o programa sem argumentos. Ele iniciará um prompt interativo onde você pode digitar sucessivas contas:

```bash
$ ./Calc
calc> 2^3
8
calc> 3r64
4
calc>
```

### 2. Execução Direta por Argumento
Você pode passar a expressão matemática diretamente como argumento ao chamar o programa, envolvendo a conta entre aspas:

```bash
$ ./Calc "-(2^3r64+(5--2)*3^2-(2r(16)+4/(1+1))*-3)+2^(1+2^-2)"
-94.621586
```
