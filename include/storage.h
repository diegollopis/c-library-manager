#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include "library.h"

enum LoadResult {
    LOAD_OK,
    LOAD_NO_FILE,
    LOAD_PARTIAL
};

enum LoadResult loadBooks(struct Library *lib, const char *path);
bool saveBooks(const struct Library *lib, const char *path);

#endif
