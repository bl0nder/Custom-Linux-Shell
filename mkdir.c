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
    }

    // //-m flag only
    // else if (!strcmp(argv[0], "-m") && !strcmp(argv[1], "\0")) {
    //     int createDir = mkdir(argv[2], S_IRWXU);
    // }
    exit(0);
    return 0;
}