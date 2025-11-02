#include "headers.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
        return 1;

    FILE *in = fopen(argv[2], "rb");
    if (!in)
        return 1;
    FILE *out = fopen(argv[3], "wb");
    if (!out)
    {
        fclose(in);
        return 1;
    }

    if (strcmp(argv[1], "encrypt") == 0)
        encrypt(in, out);

    fclose(in);
    fclose(out);
    return 0;
}
