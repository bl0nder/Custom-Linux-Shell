#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    
    for (int i=0; i<sizeof(argv)/sizeof(char *); i++) {
        printf("%s", argv[i]);
    }

    
    printf("Hello world :)\n");
    return 0;
}