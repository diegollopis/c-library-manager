#include <stdio.h>
#include <string.h>
#include "storage.h"

enum LoadResult loadBooks(struct Library *lib, const char *path) {
    int code;
    char title[MAX_NAME];
    char author[MAX_NAME];
    int year;
    int number;

    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return LOAD_NO_FILE;
    }

    enum LoadResult result = LOAD_OK;
    char line[2 * MAX_NAME + 32];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (lib->count >= MAX_BOOKS) {
            result = LOAD_PARTIAL;
            break;
        }

        if (sscanf(line, "%d;%49[^;];%49[^;];%d;%d", &code, title, author, &year, &number) != 5) {
            result = LOAD_PARTIAL;
            continue;
        }
        struct Book book = {code, "", "", year, number == 1};
        strcpy(book.title, title);
        strcpy(book.author, author);

        lib->books[lib->count] = book;
        lib->count++;
    }
    fclose(file);
    return result;
}

bool saveBooks(const struct Library *lib, const char *path) {
    char tmpPath[FILENAME_MAX];

    if (snprintf(tmpPath, sizeof(tmpPath), "%s.tmp", path) >= (int)sizeof(tmpPath)) {
        return false;
    }

    FILE *file = fopen(tmpPath, "w");

    if (file == NULL) {
        return false;
    }

    for (int i = 0; i < lib->count; i++) {
        fprintf(file, "%d;%s;%s;%d;%d\n",
            lib->books[i].code,
            lib->books[i].title,
            lib->books[i].author,
            lib->books[i].year,
            lib->books[i].isAvailable ? 1 : 0);
    }

    bool ok = !ferror(file);
    if (fclose(file) != 0) {
        ok = false;
    }

    if (!ok || rename(tmpPath, path) != 0) {
        remove(tmpPath);
        return false;
    }
    return true;
}
