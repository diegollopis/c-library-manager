#ifndef BOOK_H
#define BOOK_H

#include <stdbool.h>

#define MAX_NAME 50

struct Book {
    int code;
    char title[MAX_NAME];
    char author[MAX_NAME];
    int year;
    bool isAvailable;
};

#endif
