#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {    

    errno = 0;
    
    DIR* directory;
    struct dirent* readDir;
    
    printf("cwd: %s\n", argv[2]);
    directory = opendir(".");
    readDir = readdir(directory);

    struct stat fileStats;

    if (errno != 0) {
        printf("Directory does not exist\n");
        exit(-1);
    }
    else {
        int counter = 1;
        while (readDir != NULL) {
            if (readDir -> d_name[0] != '.') {
                
                if (!strcmp(argv[1], "-i")) {
                    stat(readDir -> d_name, &fileStats);
                    if (errno != 0) {
                        printf ("[!] Could not retrieve file statistics\n");
                        exit(-1);
                    }
                }

                if (!strcmp(argv[0], "-m") && !strcmp(argv[1], "-i")) {
                    if (counter == 1) {
                        printf("%d %s", fileStats.st_ino, readDir -> d_name);    
                    }
                    else {
                        printf(", %d %s", fileStats.st_ino, readDir -> d_name);    
                    }
                    counter++;
                }

                else if (!strcmp(argv[0], "-m") && !strcmp(argv[1], "\0")) {
                    if (counter == 1) {
                        printf("%s", readDir -> d_name);    
                    }
                    else {
                        printf(", %s", readDir -> d_name);    
                    }   
                    counter++; 
                }

                else if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "-i")) {
                    printf("%d %s ", fileStats.st_ino, readDir -> d_name);
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