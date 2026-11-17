#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: ./%s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "rb");
    if(fp1 == NULL) {
        perror(argv[1]);
        return 1;
    }
    fp2 = fopen(argv[2], "rb");
    if(fp2 == NULL) {
        perror(argv[2]);
        return 1;
    }


    unsigned long int offset = 0;
    int result = 0;

    int byte1, byte2;
    for(;;) {
        byte1 = fgetc(fp1);
        byte2 = fgetc(fp2);

        // an read error on a file is not a difference on the two bytes
        if(ferror(fp1) || ferror(fp2)) {
            if(ferror(fp1)) {
                perror(argv[1]);
                result = 2;
                break;
            }
            if(ferror(fp2)) {
                perror(argv[2]);
                result = 2;
                break;
            }
        }

        // reached end of file on both  files
        if(byte1 == EOF &&  byte2 == EOF) {
            break;
        }

        if(byte1 != byte2) {
            if(byte1 == EOF || byte2 == EOF) {
                fprintf(stderr, "%s end of file differs at %lu\n", (byte1 == EOF)? argv[1]: argv[2], offset);
                result = 2;
            } else {
                fprintf(stderr, "files differ at offset %lu with bytes %02x vs %02x\n", offset, byte1 & 0xff, byte2 & 0xff);
            }
            result = 2;
            break;
        }
        offset++;
    }
    
    if(fclose(fp1) != 0) {
        perror(argv[1]);
        return 1;
    }
    if(fclose(fp2) != 0) {
        perror(argv[2]);
        return 1;
    }

    return 0;
}

