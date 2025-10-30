#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char *buffer = malloc(length + 1);
    if (!buffer) return 1;

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    printf("%s", buffer);

    free(buffer);
    return 0;
}
