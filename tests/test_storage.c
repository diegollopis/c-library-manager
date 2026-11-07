#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "storage.h"

#define TEST_FILE "build/test_storage.txt"

static void writeFile(const char *content) {
    FILE *file = fopen(TEST_FILE, "w");
    assert(file != NULL);
    fputs(content, file);
    fclose(file);
}

static void testSaveAndLoad(void) {
    struct Library saved = {0};
    addBook(&saved, "Dom Casmurro", "Machado de Assis", 1899);
    addBook(&saved, "Iracema", "José de Alencar", 1865);
    lendBook(&saved, 2);

    assert(saveBooks(&saved, TEST_FILE));

    struct Library loaded = {0};
    assert(loadBooks(&loaded, TEST_FILE) == LOAD_OK);
    assert(loaded.count == 2);

    for (int i = 0; i < saved.count; i++) {
        assert(loaded.books[i].code == saved.books[i].code);
        assert(strcmp(loaded.books[i].title, saved.books[i].title) == 0);
        assert(strcmp(loaded.books[i].author, saved.books[i].author) == 0);
        assert(loaded.books[i].year == saved.books[i].year);
        assert(loaded.books[i].isAvailable == saved.books[i].isAvailable);
    }
}

static void testFileFormat(void) {
    struct Library lib = {0};
    addBook(&lib, "Iracema", "José de Alencar", 1865);
    lendBook(&lib, 1);
    assert(saveBooks(&lib, TEST_FILE));

    char line[128];
    FILE *file = fopen(TEST_FILE, "r");
    assert(file != NULL);
    assert(fgets(line, sizeof(line), file) != NULL);
    fclose(file);
    assert(strcmp(line, "1;Iracema;José de Alencar;1865;0\n") == 0);
}

static void testNoFile(void) {
    remove(TEST_FILE);
    struct Library lib = {0};
    assert(loadBooks(&lib, TEST_FILE) == LOAD_NO_FILE);
    assert(lib.count == 0);
}

static void testInvalidLine(void) {
    writeFile("1;Iracema;Alencar;1865;1\nlinha quebrada\n2;Dom Casmurro;Machado;1899;1\n");
    struct Library lib = {0};
    assert(loadBooks(&lib, TEST_FILE) == LOAD_PARTIAL);
    assert(lib.count == 2);
}

static void testTooManyBooks(void) {
    FILE *file = fopen(TEST_FILE, "w");
    assert(file != NULL);
    for (int i = 1; i <= MAX_BOOKS + 1; i++) {
        fprintf(file, "%d;Livro;Autor;2000;1\n", i);
    }
    fclose(file);

    struct Library lib = {0};
    assert(loadBooks(&lib, TEST_FILE) == LOAD_PARTIAL);
    assert(lib.count == MAX_BOOKS);
}

int main(void) {
    testSaveAndLoad();
    testFileFormat();
    testNoFile();
    testInvalidLine();
    testTooManyBooks();

    remove(TEST_FILE);
    printf("test_storage: todos os testes passaram.\n");
    return 0;
}
