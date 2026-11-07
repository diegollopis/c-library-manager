#include <stdio.h>
#include <string.h>
#include "utils.h"

void clearScreen(void) {
    printf("\033[H\033[2J");
    fflush(stdout);
}

bool readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    size_t len = strcspn(buffer, "\n");
    if (buffer[len] == '\n') {
        buffer[len] = '\0';
    } else {
        clearInput();
    }
    return true;
}

void clearInput(void) {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
