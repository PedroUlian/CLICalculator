# Terminal Calculator Engine

Uma calculadora poderosa e flexível de linha de comando escrita em C para executar diretamente no terminal. O motor suporta desde operações básicas até expressões matemáticas complexas, agrupamentos por parênteses, números negativos, potências, decimais e extração de raízes de qualquer índice (raízes enésimas).

## Funcionalidades

- **Aritmética Avançada:** Suporte completo para adição (`+`), subtração (`-`), multiplicação (`*`), divisão (`/`), exponenciação (`^`) e extração de qualquer raiz (`r`, ex: `3r64` para raiz cúbica de 64).
- **Suporte Nativo a Decimais:** Tokenização e análise sintática completas para literais de ponto flutuante (`.`), permitindo operações matemáticas com precisão decimal contínua.
- **Suporte a Sinais (Unários):** Manipulação encadeada de números negativos e operadores unários (ex: `-5 + +3` ou `5 + - - 3`).
- **Agrupamento de Expressões:** Suporte total a parênteses `()` para gerenciar e impor a ordem correta de operações complexas ou aninhadas.
- **Dois Modos de Execução:** Modo interativo (REPL) com prompt de comando ou passagem direta de expressões por argumentos de inicialização.

## Arquitetura de Tratamento de Erros e Estabilidade

O motor conta com uma estrutura robusta de propagação de erros em cascata que valida a integridade da expressão em tempo de compilação/execução, eliminando vazamentos de memória, travamentos ou *Segmentation Faults*:

- **Validação de Fluxo Estrita:** Captura imediata de erros sintáticos órfãos (ex: `5 + * 3` ou `5 + 3 -`).
- **Balanço de Parênteses:** Identificação ativa de agrupamentos abertos ou fechados incorretamente (ex: `(5 + 3`).
- **Validação de Fim de Linha (EOF):** Rejeição estrita de tokens excedentes ou lixo matemático ao final da expressão legítima (ex: `5 + 3 )` ou `5 (3 + 2)`).
- **Segurança em Tempo de Execução:** Interrupção imediata da árvore de avaliação ao detectar divisões por zero aritméticas (ex: `10 / 0` ou `5 / (3 - 3)`).
- **Resiliência do REPL:** Sistema automático de reset de flags de erro a cada nova linha digitada, permitindo que o usuário se recupere de uma falha de digitação instantaneamente sem derrubar o programa.

---

## Exemplos de Sintaxe

| Operação | Sintaxe | Exemplo | Resultado |
| ----------- | ----------- | ----------- | ----------- |
| Exponenciação | `base ^ expoente` | `2^3` | `8.000000` |
| Raiz Quadrada | `2 r número` | `2r16` | `4.000000` |
| Raiz Cúbica | `3 r número` | `3r64` | `4.000000` |
| Raiz Enésima (Qualquer) | `índice r número` | `4r16` | `2.000000` |
| Valores Decimais | `número.decimal` | `5.5 + 4.5` | `10.000000` |
| Expressão Complexa | (operadores + parênteses) | `(5 + 3) * 2` | `16.000000` |

---

## Roadmap / Próximos Passos
O núcleo do interpretador está estável, seguro contra entradas maliciosas e preciso. O roadmap futuro de evolução foca em recursos adicionais de conveniência e engenharia de software:

- **Suporte a Variáveis e Memória:** Permitir o armazenamento de resultados temporários (ex: x = 5 + 3 e posterior utilização x * 2).
- **Funções Trigonométricas e Logarítmicas:** Expandir o Lexer e o Avaliador para mapear tokens de texto como sin(), cos(), tan() e log().
- **Histórico de Comandos:** Implementar navegação de comandos anteriores no REPL utilizando as setas do teclado (integração com readline ou buffer interno).
- **Validação de Raiz Negativa:** Adicionar barramento semântico para impedir cálculos de raízes com base negativa e índice par no conjunto dos números reais.

---

## Como Usar

O programa pode ser utilizado de duas maneiras diferentes no terminal:

### 1. Modo Interativo (Shell da Calculadora REPL)
Basta abrir o programa sem argumentos. Ele iniciará um prompt interativo onde você pode digitar sucessivas contas e ver mensagens informativas em caso de erro:

```bash
$ ./Calc
calc> 2^3
Resultado: 8.000000
calc> 10 / 0
[ERRO] Divisao por zero detectada.
calc> 1 + 1
Resultado: 2.000000
calc> exit
```

### 2. Execução Direta por Argumento
Você pode passar a expressão matemática diretamente como argumento ao chamar o programa, envolvendo a conta entre aspas:

```bash
$ ./Calc "-(2^3r64+(5--2)*3^2-(2r(16)+4/(1+1))*-3)+2^(1+2^-2)"
-94.621586
```
