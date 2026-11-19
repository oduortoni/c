#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: ./%s <file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL) {
        perror(filename);
        return 0;
    }

    unsigned long long size = 0;
    while(fgetc(fp) != EOF) {
        size++;
    }

    if(ferror(fp)) {
        fclose(fp);
        perror(filename);
        return 1;
    }

    if(fclose(fp) != 0) {
        perror(filename);
        return 1;
    }

    printf("\nFile '%s' is %llu bytes long\n\n", filename, size);

    return 0;
}

