#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {    
    printf("%s\n", argv[1]);
    errno = 0;
    
    DIR* directory;
    struct dirent* readDir;

    char currentDir[100];
    getcwd(currentDir, 100);

    directory = opendir(currentDir);
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
                
                if (!strcmp(argv[2], "-i")) {
                    stat(readDir -> d_name, &fileStats);
                    if (errno != 0) {
                        printf ("[!] Could not retrieve file statistics\n");
                        exit(-1);
                    }
                }

                if (!strcmp(argv[1], "-m") && !strcmp(argv[2], "-i")) {
                    if (counter == 1) {
                        printf("%d %s", fileStats.st_ino, readDir -> d_name);    
                    }
                    else {
                        printf(", %d %s", fileStats.st_ino, readDir -> d_name);    
                    }
                    counter++;
                }

                else if (!strcmp(argv[1], "-m") && !strcmp(argv[2], "NO")) {
                    printf("HELLLOOOO?\n");
                    if (counter == 1) {
                        printf("%s", readDir -> d_name);    
                    }
                    else {
                        printf(", %s", readDir -> d_name);    
                    }   
                    counter++; 
                }

                else if (!strcmp(argv[1], "NO") && !strcmp(argv[2], "-i")) {
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