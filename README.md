# Cryptix

Cryptix is a simple C program that allows you to encrypt and decrypt text in a way that ensures all output remains readable as printable ASCII characters. It is designed for demonstrating bit-level manipulation, block encryption, and ASCII mapping in C programming.

## Features

- Encrypts data in 8-byte blocks.
- Uses the last byte of each block to modify the first 7 bytes.
- Ensures all output bytes are printable ASCII (32–126).
- Handles partial blocks (less than 8 bytes) by writing them directly.
- Provides a Makefile for easy compilation, running, and cleaning.

---

## Project Structure

```
cryptix/
├─ main.c       # Entry point, handles file I/O
├─ encrypt.c    # Encryption logic
├─ headers.h    # Function declarations
├─ Makefile     # Build, run, and clean targets
├─ README.md    # Project documentation
└─ input/       # Example input files
```

## Encryption Overview

Each byte consists of 8 bits (MSB → LSB):

```
Before Encryption                   After Encryption
─────────────────────────────    ─────────────────────────────
I1: 0 a1 a2 a3 a4 a5 a6 a7    →    I1: h7 a1 a2 a3 a4 a5 a6 a7
I2: 0 b1 b2 b3 b4 b5 b6 b7    →    I2: b1 h6 b2 b3 b4 b5 b6 b7
I3: 0 c1 c2 c3 c4 c5 c6 c7    →    I3: c1 c2 h5 c3 c4 c5 c6 c7
I4: 0 d1 d2 d3 d4 d5 d6 d7    →    I4: d1 d2 d3 h4 d4 d5 d6 d7
I5: 0 e1 e2 e3 e4 e5 e6 e7    →    I5: e1 e2 e3 e4 h3 e5 e6 e7
I6: 0 f1 f2 f3 f4 f5 f6 f7    →    I6: f1 f2 f3 f4 f5 h2 f6 f7
I7: 0 g1 g2 g3 g4 g5 g6 g7    →    I7: g1 g2 g3 g4 g5 g6 h1 g7
I8: 0 h1 h2 h3 h4 h5 h6 h7    →    bits used above, not stored
```

1. This encryption only works on characters where the most significant bit (MSB) is 0.
2. The 8th byte (I8) is used only to generate the new bits (h1–h7) for the first 7 bytes.
3. Only the first 7 bytes of each block are written to the output.
4. This bit-striping ensures the encrypted output remains printable ASCII.

---

## Decryption Overview

Each byte consists of 8 bits (MSB → LSB). The decryption process is simply the inverse of encryption, restoring the original 8-byte blocks

```
Encrypted Output                   After Decryption
─────────────────────────────    ─────────────────────────────
I1: h7 a1 a2 a3 a4 a5 a6 a7    →    I1: 0 a1 a2 a3 a4 a5 a6 a7
I2: b1 h6 b2 b3 b4 b5 b6 b7    →    I2: 0 b1 b2 b3 b4 b5 b6 b7
I3: c1 c2 h5 c3 c4 c5 c6 c7    →    I3: 0 c1 c2 c3 c4 c5 c6 c7
I4: d1 d2 d3 h4 d4 d5 d6 d7    →    I4: 0 d1 d2 d3 d4 d5 d6 d7
I5: e1 e2 e3 e4 h3 e5 e6 e7    →    I5: 0 e1 e2 e3 e4 e5 e6 e7
I6: f1 f2 f3 f4 f5 h2 f6 f7    →    I6: 0 f1 f2 f3 f4 f5 f6 f7
I7: g1 g2 g3 g4 g5 g6 h1 g7    →    I7: 0 g1 g2 g3 g4 g5 g6 g7
I8: (not stored)                →    I8: 0 h1 h2 h3 h4 h5 h6 h7

```

1. Extract h1–h7 from the positions in bytes 1–7.
2. Reconstruct the 8th byte (I8) from these bits.
3. Restore each byte to its original 8-bit form (MSB = 0).
4. Repeat for each 8-byte block in the encrypted file.

## How to use

This guide details the steps required to compile, run, and test the encryption and decryption program using the provided Makefile.

---

#### 1. Compile the Program

Use the provided Makefile to compile:

```
make all
```

#### 2. Prepare Input

Place the text file you want to encrypt in the **input/** folder.

```
input/basic.txt
```

Note: By default, the program expects the input file to be named input/basic.txt

#### 3. Encrypt a file

Run the encryption target from the Makefile:

```
make run-encrypt
```

Note: The encrypted file will be saved in the output/ folder and named encrypted.bin

#### 4. Decrypt a file

Run the decryption target from the Makefile:

```
make run-decrypt
```

Note: The decrypted file will be saved in the output/ folder and named decrypted.txt

#### 5. Test Encryption + Decryption

To verify that the decrypted file matches the original input:

```
make test
```

#### 6. Clean Up

Remove compiled binaries and output files:

```
make clean
```

#### 7. Optional

You can also encrypt/decrypt a different file by changing the INPUT_FILE variable in the Makefile or creating a new target.

---
