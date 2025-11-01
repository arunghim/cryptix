#include <stdio.h>
#include <stdlib.h>

void encrypt(FILE *in, FILE *out);

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;

    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");
    if (!in || !out) return 1;

    encrypt(in, out);

    fclose(in);
    fclose(out);
    return 0;
}
