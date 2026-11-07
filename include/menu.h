#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "library.h"
#include "storage.h"

enum MenuOption {
    OPT_ADD = 1,
    OPT_LIST,
    OPT_LEND,
    OPT_RETURN,
    OPT_EXIT
};

void printLibraryIntro(void);
void showMenu(void);
bool askInt(const char *prompt, int min, int max, int *value);
int askOption(void);
int askRetry(void);
bool askBookData(char *title, char *author, int *year);
bool askBookCode(int *code);
void showShelf(const struct Library *lib);
void showResult(enum LibResult r);
void showLoadResult(enum LoadResult r);

#endif
