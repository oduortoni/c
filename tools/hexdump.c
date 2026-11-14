#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        perror("Usage: ./hexdump <file>");
        return 1;
    }

    FILE *fp;
    fp = fopen(argv[1], "rb");
    if(fp == NULL) {
        perror("error opening file");
        return 1;
    }

    size_t n, offset = 0;
    unsigned char buffer[16];
    printf("\n\n");
    while((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        printf("\n%08zx: ", offset);

        for(size_t i = 0; i < sizeof(buffer); i++) {
            if(i < n) {
                printf("%02x ", buffer[i]);
            } else {
                printf("    ");
            }
            if(i == 7) {
                printf(" ");
            }
        }

        printf(" |    ");
        for(size_t i = 0; i < n; i++) {
            unsigned char c = buffer[i];
            putchar(c >= 0x20 && c <= 0x7e? c: '.');
        }

        offset += n;
    }
    printf("\n\n");

    if(ferror(fp)) {
        perror(argv[1]);
        fclose(fp);
        return 1;
    }

    if(fclose(fp) != 0) {
        perror(argv[1]);
        return 1;
    }

    return 0;
}

