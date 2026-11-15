/**
 * copy.c
 *
 * Compile:
 *  cc -o bin/copy lib/sandbox.c copy.c
 *
 */

#include <stdio.h>
#include <string.h>

#include "../lib/sandbox.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: ./%s <src> <dst>\n", argv[0]);
        return 1;
    }

    char *src = argv[1];
    char *dst = argv[2];
    if(sandbox_check_path(dst) != 0) {
        fprintf(stderr, "refusing to write outside sandbox/: %s\n", dst);
        return 1;
    }

    /* do not copy a file onto itself */
    size_t src_len = strlen(src);
    if(strncmp(src, dst, src_len) == 0) {
        fprintf(stderr, "refusing to copy a file onto itself: %s\n", src);
        return 1;
    }

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

    size_t n = 0;
    int status = 0;
    char buffer[4096] = {0};
    while((n = fread(buffer, 1, sizeof buffer, sfp)) > 0) {
        if(fwrite(buffer, 1, n, dfp) != n) {
            perror(dst);
            status = 1;
            break;
        }
    }

    if(status == 0 && ferror(sfp)) {
        perror("sfp");
        status = 1;
    }
    if(ferror(dfp)) {
        perror("dfp");
        status = 1;
    }
    if(fclose(sfp) != 0) {
        perror("close sfp");
        status = 1;
    }
    if(fclose(dfp) != 0) {
        perror("close dfp");
        status = 1;
    }

    return status;
}

