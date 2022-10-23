#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argv[0] == "hello") {
        printf("Hello received");
    }
    printf("Hello world :)\n");
    return 0;
}