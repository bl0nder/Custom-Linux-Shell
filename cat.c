#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("%s %s %s\n", argv[0], argv[1], argv[2]);
    const char* file = argv[2];
    FILE *fp = fopen(file, "r");

    if (fp == NULL) {
        printf("[!] File does not exist\n");        
        exit(-1);
    }

    else {
        char* str;
        const int maxSize = 2000;
        if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "\0")) {
            while (str != NULL) {
                fgets(str, maxSize, fp);   
                printf("%s", str);
            }
        }
    }

    return 0;
}