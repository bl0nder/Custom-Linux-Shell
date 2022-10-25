#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    time_t currentTime;
    

    if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "\0")) {
        time(&currentTime);
        printf("(Local Time) %s\n", ctime(&currentTime));
    }

    else if (!strcmp(argv[0], "-u") && !strcmp(argv[1], "\0")) {
        setenv("TZ", "UTC", 1);
        tzset();
        time(&currentTime);
        printf("(UTC) %s\n", ctime(&currentTime));
        setenv("TZ", "UTC-5:30", 1);
        tzset();
    }

    else if (!strcmp(argv[0], "\0") && !strcmp(argv[1], "-R")){
        time(&currentTime);
        struct tm *timeStruct = localtime(&currentTime);
        const int maxSize = 100;
        const char* format = "%a, %e %b %Y %T %z";
        char s[maxSize];

        strftime(s, maxSize, format, timeStruct);

        printf("(RFC-3339) %s\n", s);
    }   
    return 0;

}