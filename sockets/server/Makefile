CC=gcc
CFLAGS=-Wall -pthread -g -pedantic
BUILD_DIR=build
SRC_DIR=src
MAIN=server
MAIN_C=main.c
MAIN_O=main.o

# Collect all the source files
SOURCES=$(wildcard $(SRC_DIR)/*.c)

# Generate object files from source files
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all server clean run

# Default target
all: $(MAIN)

# Linking the object files to create the final executable
$(MAIN): $(MAIN_O) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile main.c into main.o
$(MAIN_O): $(MAIN_C)
	$(CC) $(CFLAGS) -o $@ -c $<

# Compile each source file into its corresponding object file in the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Clean target to remove build artifacts
clean:
	rm -rf $(MAIN) $(MAIN_O) $(BUILD_DIR)/*.o

run: $(MAIN)
	@./$(MAIN)
