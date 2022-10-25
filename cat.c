#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
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
            while (fgets(str, maxSize, fp)) {
                printf("%s", str);
            }
        }
    }

    return 0;
}