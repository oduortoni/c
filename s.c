#include <stdio.h>

int main() {
    FILE *fp;

    fp = fopen("sandbox/empty.txt", "rb");
    if(fp == NULL) {
        perror("unable to open file");
        return 1;
    }

   size_t ch = 0;
    while((ch = fgetc(fp)) != EOF) {
        printf("%c ", (char)ch);
    }

    if(feof(fp)) {
        puts("Yeah! End of stream!");
    }

    return 0;
}

