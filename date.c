#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    time_t currentTime;

    if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "\0")) {
        time(&currentTime);
        printf("%s\n", ctime(&currentTime));
    }

    else if (!strcmp(argv[0], "-u") && !strcmp(argv[1], "\0")) {
        setenv("TZ", "UTC", 1);
        tzset();
        time(&currentTime);
        printf("(UTC) %s\n", ctime(&currentTime));
    }

    //For IST
    return 0;

}