#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: ./%s <src> <dst>\n", argv[0]);
        return 1;
    }

    char *src = argv[1];
    char *dst = argv[2];
    FILE *sfp, *dfp;

    sfp = fopen(src, "rb");
    if(sfp == NULL) {
        perror(argv[1]);
        return 1;
    }

    dfp = fopen(dst, "wb");
    if(dfp == NULL) {
        perror(argv[2]);
        return 1;
    }

    int ch;
    while((ch = fgetc(sfp)) != EOF) {
        fputc(ch, dfp);
    }

    if(ferror(sfp)) {
        perror("sfp");
        return 1;
    }

    if(ferror(dfp)) {
        perror("dfp");
        return 1;
    }

    if(fclose(sfp) != 0) {
        perror("close sfp");
        return 1;
    }

    if(fclose(dfp) != 0) {
        perror("close dfp");
        return 1;
    }

    return 0;
}

