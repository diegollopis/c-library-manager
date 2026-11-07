#include <stdio.h>
#include <stdbool.h>
#include "library.h"
#include "storage.h"
#include "menu.h"
#include "utils.h"

#define DATA_FILE "library.txt"

static bool runOperation(struct Library *lib, int option, enum LibResult *result) {
    switch (option) {
    case OPT_ADD: {
        char title[MAX_NAME];
        char author[MAX_NAME];
        int year;
        if (!askBookData(title, author, &year)) {
            return false;
        }
        *result = addBook(lib, title, author, year);
        return true;
    }
    case OPT_LEND:
    case OPT_RETURN: {
        int code;
        if (!askBookCode(&code)) {
            return false;
        }
        *result = (option == OPT_LEND) ? lendBook(lib, code) : returnBook(lib, code);
        return true;
    }
    default:
        *result = LIB_INVALID;
        return true;
    }
}

int main(void) {
    struct Library lib = {0};

    enum LoadResult loaded = loadBooks(&lib, DATA_FILE);
    bool canSave = (loaded != LOAD_PARTIAL);

    do {
        clearScreen();
        showLoadResult(loaded);
        printLibraryIntro();
        showMenu();
        int option = askOption();

        if (option == OPT_EXIT) {
            break;
        }

        if (option == OPT_LIST) {
            showShelf(&lib);
        } else {
            enum LibResult r;
            if (!runOperation(&lib, option, &r)) {
                break;
            }
            if (r == LIB_OK && (!canSave || !saveBooks(&lib, DATA_FILE))) {
                r = LIB_SAVE_FAILED;
            }
            showResult(r);
        }
    } while (askRetry() == 1);

    printf("Até logo!\n");
    return 0;
}
