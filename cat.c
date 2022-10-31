#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    const char* file = argv[3];
    char* str;
    const int maxSize = 1000;
    FILE *fp = fopen(file, "r");
    // while (fgets(str, maxSize, fp)) {
    //     printf("%s", str);
    // }

    if (fp == NULL) {
        printf("[!] File does not exist.\n");
        exit(-1);
    }

    if (!strcmp(argv[1], "NO") && !strcmp(argv[2], "NO")) {
        while (fgets(str, maxSize, fp)) {
            printf("%s", str);
        }
        fclose(fp);
    }

    else if ((!strcmp(argv[1], "-E") && !strcmp(argv[2], "NO")) || (!strcmp(argv[1], "NO") && !strcmp(argv[2], "-E"))) {
        char c = fgetc(fp);
        while (1) {
            if (c == '\n') {
                printf("$\n");
            }
            else if (feof(fp)) {
                break;
            }
            else {
                printf("%c", c);
            }
            c= fgetc(fp);
        }
    }

    else if ((!strcmp(argv[1], "NO") && !strcmp(argv[2], "-T")) || (!strcmp(argv[1], "-T") && !strcmp(argv[2], "NO"))) {
        char c = fgetc(fp);
        while (1) {
            if (c == '\t') {
                printf("^I");
            }
            else if (feof(fp)) {
                break;
            }
            else {
                printf("%c", c);
            }
            c= fgetc(fp);
        }
    }

    else if ((!strcmp(argv[1], "-E") && !strcmp(argv[2], "-T")) || (!strcmp(argv[1], "-T") && !strcmp(argv[2], "-E"))) {
        char c = fgetc(fp);
        while (1) {
            if (c == '\t') {
                printf("^I");
            }
            else if (c == '\n') {
                printf("$\n");
            }
            else if (feof(fp)) {
                break;
            }
            else {
                printf("%c", c);
            }
            c= fgetc(fp);
        }
    }

    else {
        printf("[!] Invalid flag(s) entered.\n");
        exit(-1);
    }

    return 0;
}