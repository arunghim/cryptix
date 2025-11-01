#include "headers.h"

#define BLOCK_SIZE 8

void encrypt(FILE *in, FILE *out) {
    unsigned char block[BLOCK_SIZE];
    size_t n;

    while ((n = fread(block, 1, BLOCK_SIZE, in)) > 0) {
        if (n < BLOCK_SIZE) {
            for (size_t i = 0; i < n; ++i)
                fputc((block[i] % 95) + 32, out);
            break;
        }

        unsigned char enc[BLOCK_SIZE - 1];
        unsigned char src = block[7];

        int h[8];
        for (int i = 1; i <= 7; ++i)
            h[i] = (src >> (7 - i)) & 1;

        for (int i = 0; i < 7; ++i) {
            int bitPos = 7 - i;
            int bitVal = h[7 - i];
            unsigned char b = block[i];
            unsigned char result = 0;

            for (int bit = 7; bit > bitPos; --bit)
                result |= ((b >> (bit - 1)) & 1) << bit;
            result |= (bitVal << bitPos);
            for (int bit = bitPos - 1; bit >= 0; --bit)
                result |= ((b >> bit) & 1) << bit;

            enc[i] = (result % 95) + 32;
        }

        fwrite(enc, 1, 7, out);
    }
}
