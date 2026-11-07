#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "library.h"

static void testAddBook(void) {
    struct Library lib = {0};

    assert(addBook(&lib, "Dom Casmurro", "Machado de Assis", 1899) == LIB_OK);
    assert(lib.count == 1);
    assert(lib.books[0].code == 1);
    assert(strcmp(lib.books[0].title, "Dom Casmurro") == 0);
    assert(strcmp(lib.books[0].author, "Machado de Assis") == 0);
    assert(lib.books[0].year == 1899);
    assert(lib.books[0].isAvailable);
}

static void testInvalidData(void) {
    struct Library lib = {0};
    char tooLong[MAX_NAME + 1];
    memset(tooLong, 'a', MAX_NAME);
    tooLong[MAX_NAME] = '\0';

    assert(addBook(&lib, "", "Autor", 2000) == LIB_INVALID);
    assert(addBook(&lib, "Título", "", 2000) == LIB_INVALID);
    assert(addBook(&lib, "A;B", "Autor", 2000) == LIB_INVALID);
    assert(addBook(&lib, "Título", "A;B", 2000) == LIB_INVALID);
    assert(addBook(&lib, tooLong, "Autor", 2000) == LIB_INVALID);
    assert(lib.count == 0);
}

static void testFullShelf(void) {
    struct Library lib = {0};

    for (int i = 0; i < MAX_BOOKS; i++) {
        assert(addBook(&lib, "Livro", "Autor", 2000) == LIB_OK);
    }
    assert(addBook(&lib, "Sobrando", "Autor", 2000) == LIB_FULL);
    assert(lib.count == MAX_BOOKS);
}

static void testLendAndReturn(void) {
    struct Library lib = {0};
    addBook(&lib, "Iracema", "José de Alencar", 1865);

    assert(lendBook(&lib, 1) == LIB_OK);
    assert(!lib.books[0].isAvailable);
    assert(lendBook(&lib, 1) == LIB_ALREADY_LENT);

    assert(returnBook(&lib, 1) == LIB_OK);
    assert(lib.books[0].isAvailable);
    assert(returnBook(&lib, 1) == LIB_NOT_LENT);
}

static void testNotFound(void) {
    struct Library lib = {0};
    addBook(&lib, "Iracema", "José de Alencar", 1865);

    assert(lendBook(&lib, 99) == LIB_NOT_FOUND);
    assert(returnBook(&lib, 99) == LIB_NOT_FOUND);
}

static void testNextCode(void) {
    struct Library lib = {0};
    lib.books[0].code = 5;
    lib.books[1].code = 2;
    lib.count = 2;

    assert(addBook(&lib, "Novo", "Autor", 2000) == LIB_OK);
    assert(lib.books[2].code == 6);
}

int main(void) {
    testAddBook();
    testInvalidData();
    testFullShelf();
    testLendAndReturn();
    testNotFound();
    testNextCode();

    printf("test_library: todos os testes passaram.\n");
    return 0;
}
