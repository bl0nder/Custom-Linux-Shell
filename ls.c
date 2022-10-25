#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {    

    errno = 0;
    
    DIR* directory;
    struct dirent* readDir;
    
    directory = opendir(".");
    readDir = readdir(directory);


    if (errno != 0) {
        printf("Directory does not exist");
        return -1;
    }
    else {
        while (readDir != NULL) {
            if (readDir -> d_name[0] != '.') {
                if (!strcmp(argv[0], "-m")) {
                    if (readdir(directory) == NULL) {
                        printf("%s", readDir -> d_name);    
                    }
                    else {
                        printf("%s, ", readDir -> d_name);    
                    }
                }
                else {
                    printf("%s ", readDir -> d_name);
                }
            }
            
            readDir = readdir(directory);
        }
        printf("\n");
    }


    return 0;
}