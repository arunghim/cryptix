CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c encrypt.c decrypt.c
TARGET = main
INPUT_FILE = input/basic.txt
OUTPUT_DIR = output
ENCRYPTED_FILE = $(OUTPUT_DIR)/encrypted.bin
DECRYPTED_FILE = $(OUTPUT_DIR)/decrypted.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o $(ENCRYPTED_FILE) $(DECRYPTED_FILE)

run-encrypt: $(TARGET)
	@test -f $(INPUT_FILE) || { echo "Error: $(INPUT_FILE) not found"; exit 1; }
	@mkdir -p $(OUTPUT_DIR)
	@echo "Encrypting $(INPUT_FILE) → $(ENCRYPTED_FILE)"
	./$(TARGET) encrypt $(INPUT_FILE) $(ENCRYPTED_FILE)

run-decrypt: $(TARGET)
	@test -f $(ENCRYPTED_FILE) || { echo "Error: $(ENCRYPTED_FILE) not found"; exit 1; }
	@mkdir -p $(OUTPUT_DIR)
	@echo "Decrypting $(ENCRYPTED_FILE) → $(DECRYPTED_FILE)"
	./$(TARGET) decrypt $(ENCRYPTED_FILE) $(DECRYPTED_FILE)

test: run-encrypt run-decrypt
	@diff $(INPUT_FILE) $(DECRYPTED_FILE) > /dev/null && echo "Files match" || echo "Files differ"
