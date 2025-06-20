CC=gcc
CFLAGS=-Wall -pthread -g -pedantic -Iinclude/
BUILD_DIR=build
SRC_DIR=src
MAIN=$(BUILD_DIR)/client
MAIN_O=$(BUILD_DIR)/main.o

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all server clean run

all: $(MAIN)

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf ${BUILD_DIR}

run: $(MAIN)
	@./run
