#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {

    const char* file = argv[2];
    char* str;
    const int maxSize = 1000;
    // while (fgets(str, maxSize, fp)) {
    //     printf("%s", str);
    // }
    if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "\0")) {
        FILE *fp = fopen(file, "r");
        while (fgets(str, maxSize, fp)) {
            printf("%s", str);
        }
        fclose(fp);
    }

    else if (!strcmp(argv[0], "-e") && !strcmp(argv[1], "\0")) {
        FILE *fp = fopen(file, "r");
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
        fclose(fp);
    }

    return 0;
}