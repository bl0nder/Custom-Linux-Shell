#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]) {
    
    const char* file = argv[2];

    if (!strcmp(argv[0], "-i")) {
        printf("Remove file '%s' (y/n)?", file);
        char ans[10];
        scanf(ans);

        if (!strcmp(ans, "y") || !strcmp(ans, "Y") || !strcmp(ans, "yes")) {
            remove(file);

            if (errno != 0) {
                printf("[!] File %s does not exist\n", file);
                exit(-1);
            }

        }
    }

    else if (!strcmp(argv[0], "-f")) {
        remove(file);
    }

    else {
        remove (file);
        if (errno != 0) {
            printf("[!] File %s does not exist\n", file);
            exit(-1);
        }
    }
    
    return 0;
}