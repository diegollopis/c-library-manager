#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

#define MAX_BOOKS 100

struct Library {
    struct Book books[MAX_BOOKS];
    int count;
};

enum LibResult {
    LIB_OK,
    LIB_FULL,
    LIB_INVALID,
    LIB_NOT_FOUND,
    LIB_ALREADY_LENT,
    LIB_NOT_LENT,
    LIB_SAVE_FAILED
};

enum LibResult addBook(struct Library *lib, const char *title, const char *author, int year);
enum LibResult lendBook(struct Library *lib, int code);
enum LibResult returnBook(struct Library *lib, int code);

#endif
