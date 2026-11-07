#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "menu.h"
#include "utils.h"

void printLibraryIntro(void) {
    printf("====================================\n");
    printf("      DIEGO'S PUBLIC LIBRARY\n");
    printf("====================================\n");
    printf("Olá! Seja bem-vindo(a).\n");
    printf("Selecione uma das opções abaixo (1, 2, 3, 4 ou 5).\n\n");
}

void showMenu(void) {
    const char *options[] = {
        "1. Cadastrar livro",
        "2. Listar livros",
        "3. Emprestar livro",
        "4. Devolver livro",
        "5. Sair"
    };
    int numberOfOptions = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < numberOfOptions; i++) {
        printf("%s\n", options[i]);
    }
}

bool askInt(const char *prompt, int min, int max, int *value) {
    char input[32];

    while (1) {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            return false;
        }

        if (strchr(input, '\n') == NULL) {
            clearInput();
            printf("Entrada inválida. Digite um número de %d a %d.\n", min, max);
            continue;
        }

        char *end;
        errno = 0;
        long number = strtol(input, &end, 10);

        if (isdigit((unsigned char)input[0]) && *end == '\n' && errno == 0
                && number >= min && number <= max) {
            *value = (int)number;
            return true;
        }

        printf("Entrada inválida. Digite um número de %d a %d.\n", min, max);
    }
}

int askOption(void) {
    int option;
    if (!askInt("\nOpção: ", OPT_ADD, OPT_EXIT, &option)) {
        return OPT_EXIT;
    }
    return option;
}

int askRetry(void) {
    int answer;
    if (!askInt("\nDeseja realizar nova operação (1 - Sim, 0 - Não)? ", 0, 1, &answer)) {
        return 0;
    }
    return answer;
}

bool askBookData(char *title, char *author, int *year) {
    printf("Adicione um livro\n");

    printf("Título: ");
    if (!readLine(title, MAX_NAME)) {
        printf("\n");
        return false;
    }

    printf("Autor: ");
    if (!readLine(author, MAX_NAME)) {
        printf("\n");
        return false;
    }

    return askInt("Ano de publicação: ", 1, 2100, year);
}

bool askBookCode(int *code) {
    return askInt("Código do livro: ", 1, INT_MAX, code);
}

static void showBook(const struct Book *b) {
    printf("%d - %s (%s, %d): %s\n\n",
        b->code,
        b->title,
        b->author,
        b->year,
        b->isAvailable ? "DISPONÍVEL" : "EMPRESTADO");
}

void showShelf(const struct Library *lib) {
    printf("\n=== ESTANTE ===\n\n");

    if (lib->count == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    for (int i = 0; i < lib->count; i++) {
        showBook(&lib->books[i]);
    }
}

void showResult(enum LibResult r) {
    switch (r) {
    case LIB_OK:
        printf("Operação realizada com sucesso!\n");
        break;
    case LIB_FULL:
        printf("Estante cheia! Não é possível cadastrar mais livros.\n");
        break;
    case LIB_INVALID:
        printf("Dados inválidos! Título e autor não podem ser vazios nem conter ';'.\n");
        break;
    case LIB_NOT_FOUND:
        printf("Livro não encontrado!\n");
        break;
    case LIB_ALREADY_LENT:
        printf("Este livro já está emprestado!\n");
        break;
    case LIB_NOT_LENT:
        printf("Este livro não está emprestado!\n");
        break;
    case LIB_SAVE_FAILED:
        printf("Alteração não salva no arquivo! Ela vale só até fechar o programa.\n");
        break;
    }
}

void showLoadResult(enum LoadResult r) {
    switch (r) {
    case LOAD_OK:
    case LOAD_NO_FILE:
        break;
    case LOAD_PARTIAL:
        printf("ATENÇÃO: o arquivo tem livros que não puderam ser carregados\n");
        printf("(linhas inválidas ou mais de %d livros).\n", MAX_BOOKS);
        printf("Para não apagá-los, nenhuma alteração será salva nesta sessão.\n\n");
        break;
    }
}
