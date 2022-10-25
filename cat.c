#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

    const char* file = argv[2];
    printf("%s %s %s\n", argv[0], argv[1], file);
    FILE *fp = fopen(file, "r");

    if (fp == NULL) {
        printf("[!] File does not exist\n");        
        exit(-1);
    }

    else {
        char* str;
        const int maxSize = 2000;
        if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "\0")) {
            printf("GELoihniuhNDUH");
            while (fgets(str, maxSize, fp)) {
                printf("%s", str);
            }
        }

        else if (!strcmp(argv[0], "-e") && !strcmp(argv[1], "\0")) {
            // char c = fgetc(fp);
            // while (!feof(fp)) {
            //     if (c == '\n') {
            //         printf("$");
            //     }
            //     printf("%c", c);
            // }
            while (fgets(str, maxSize, fp)) {
                char* token = strtok(str, "\n");
                if (!strcmp(token, str)) {
                    printf("%s", str);
                }
                else {
                    printf("%s$\n", token);
                }
            }
        }
    }

    return 0;
}