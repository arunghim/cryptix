#include "headers.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <encrypt|decrypt> input.txt output\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[2], "rb");
    if (!in)
    {
        perror("Failed to open input file");
        return 1;
    }

    FILE *out = fopen(argv[3], "wb");
    if (!out)
    {
        perror("Failed to open output file");
        fclose(in);
        return 1;
    }

    if (strcmp(argv[1], "encrypt") == 0)
        encrypt(in, out);
    else if (strcmp(argv[1], "decrypt") == 0)
        decrypt(in, out);
    else
    {
        printf("Invalid mode: %s. Use 'encrypt' or 'decrypt'.\n", argv[1]);
    }

    fclose(in);
    fclose(out);
    return 0;
}
