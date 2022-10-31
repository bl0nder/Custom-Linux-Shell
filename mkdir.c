#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


int main (int argc, char* argv[]) {

    //No flags
    if (!strcmp(argv[1], "NO") && !strcmp(argv[2], "NO")) {
        int createDir = mkdir(argv[3], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        if (createDir!=0) {
            printf("[!] There was an error in creating directory '%s'.\n", argv[3]);
            exit(-1);
        }
        else {
            exit(0);
        }
    }
    else if ((!strcmp(argv[1], "-m") && !strcmp(argv[2], "NO")) || (!strcmp(argv[1], "NO") && !strcmp(argv[2], "-m"))) {
        int mode;
        printf("Enter mode: ");
        scanf("%d", &mode);

        int createDir = mkdir(argv[3], (const int) mode);

        if (createDir!=0) {
            printf("[!] There was an error in creating directory '%s'.\n", argv[3]);
            exit(-1);
        }
        else {
            exit(0);
        }
    }
    else if ((!strcmp(argv[1], "-v") && !strcmp(argv[2], "NO")) || (!strcmp(argv[1], "NO") && !strcmp(argv[2], "-v"))) {
        
        int createDir = mkdir(argv[3], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (createDir!=0) {
            printf("[!] There was an error in creating directory '%s'.\n", argv[3]);
            exit(-1);
        }
        else {
            printf("The directory %s has been created.\n", argv[3]);
            exit(0);
        }
    }

    // //-m flag only
    // else if (!strcmp(argv[0], "-m") && !strcmp(argv[1], "\0")) {
    //     int createDir = mkdir(argv[2], S_IRWXU);
    // }
    return 0;
}