#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {    
    for (int i=0; i<3; i++) {
        printf("%s\n", argv[i]);
    }
    printf("Hello world :)\n");
    return 0;
}