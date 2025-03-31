CC=gcc
CFLAGS=-Wall -pthread -g -pedantic
BUILD_DIR=build
SRC_DIR=src
MAIN=server
MAIN_C=main.c
MAIN_O=$(BUILD_DIR)/main.o

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all server clean run

all: $(MAIN)

$(MAIN): $(MAIN_O) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_O): $(MAIN_C)
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(MAIN) $(MAIN_O) $(BUILD_DIR)/*.o

run: $(MAIN)
	@./$(MAIN)
