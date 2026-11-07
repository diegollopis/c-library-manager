#include <string.h>
#include <stdbool.h>
#include "library.h"

static int findBook(const struct Library *lib, int code) {
    for (int i = 0; i < lib->count; i++) {
        if (code == lib->books[i].code) {
            return i;
        }
    }
    return -1;
}

static int nextCode(const struct Library *lib) {
    int max = 0;
    for (int i = 0; i < lib->count; i++) {
        if (lib->books[i].code > max) {
            max = lib->books[i].code;
        }
    }
    return max + 1;
}

static bool isValidText(const char *text) {
    size_t len = strlen(text);
    return len > 0 && len < MAX_NAME && strchr(text, ';') == NULL;
}

enum LibResult addBook(struct Library *lib, const char *title, const char *author, int year) {
    if (lib->count >= MAX_BOOKS) {
        return LIB_FULL;
    }

    if (!isValidText(title) || !isValidText(author)) {
        return LIB_INVALID;
    }

    struct Book book = {nextCode(lib), "", "", year, true};
    strcpy(book.title, title);
    strcpy(book.author, author);

    lib->books[lib->count] = book;
    lib->count++;
    return LIB_OK;
}

enum LibResult lendBook(struct Library *lib, int code) {
    int i = findBook(lib, code);

    if (i == -1) {
        return LIB_NOT_FOUND;
    }

    if (!lib->books[i].isAvailable) {
        return LIB_ALREADY_LENT;
    }

    lib->books[i].isAvailable = false;
    return LIB_OK;
}

enum LibResult returnBook(struct Library *lib, int code) {
    int i = findBook(lib, code);

    if (i == -1) {
        return LIB_NOT_FOUND;
    }

    if (lib->books[i].isAvailable) {
        return LIB_NOT_LENT;
    }

    lib->books[i].isAvailable = true;
    return LIB_OK;
}
