#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]) {
    
    const char* file = argv[3];

    if ((!strcmp(argv[2], "-i") && !strcmp(argv[1], "NO")) || (!strcmp(argv[1], "-i") && !strcmp(argv[2], "NO"))) {
        printf("Remove file '%s' (y/n)? ", file);
        char ans[10];
        scanf("%s", ans);

        if (!strcmp(ans, "y") || !strcmp(ans, "Y") || !strcmp(ans, "yes")) {
            remove(file);

            if (errno != 0) {
                printf("[!] File %s does not exist\n", file);
                exit(-1);
            }

        }
    }

    else if ((!strcmp(argv[1], "-f")&& !strcmp(argv[2], "NO")) || (!strcmp(argv[2], "-f")&& !strcmp(argv[1], "NO"))) {
        remove(file);
    }

    else if (!strcmp(argv[1], "NO") && !strcmp(argv[2], "NO")) {
        remove (file);
        if (errno != 0) {
            printf("[!] File %s does not exist\n", file);
            exit(-1);
        }
    }

    else if ((!strcmp(argv[1], "-f") && !strcmp(argv[2], "-i")) || (!strcmp(argv[1], "-i") && !strcmp(argv[2], "-f"))) {
        printf("[!] Both flags cannot be used for this command\n");
        exit(-1);
    }

    else {
        printf("[!] Illegal flag(s) entered\n");
        exit(-1);
    }
    
    return 0;
}