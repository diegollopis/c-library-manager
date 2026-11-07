CC      = cc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
SRC     = $(wildcard src/*.c)
HDR     = $(wildcard include/*.h)
BUILD   = build
TARGET  = $(BUILD)/main

$(TARGET): $(SRC) $(HDR) | $(BUILD)
	$(CC) $(CFLAGS) $(SRC) -o $@

$(BUILD)/test_library: tests/test_library.c src/library.c $(HDR) | $(BUILD)
	$(CC) $(CFLAGS) tests/test_library.c src/library.c -o $@

$(BUILD)/test_storage: tests/test_storage.c src/storage.c src/library.c $(HDR) | $(BUILD)
	$(CC) $(CFLAGS) tests/test_storage.c src/storage.c src/library.c -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

test: $(BUILD)/test_library $(BUILD)/test_storage
	./$(BUILD)/test_library
	./$(BUILD)/test_storage

clean:
	rm -rf $(BUILD)

.PHONY: run test clean
