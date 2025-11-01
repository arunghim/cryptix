# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Source files
SRC = main.c encrypt.c

# Output executable
TARGET = main

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean build files
clean:
	rm -f $(TARGET) *.o

# Optional: run program (replace input/sample.txt and output.enc as needed)
run: $(TARGET)
	./$(TARGET) input/sample.txt output.enc
