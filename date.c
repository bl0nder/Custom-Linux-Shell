#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    time_t currentTime;
    

    if (!strcmp(argv[1], "NO") && !strcmp(argv[2], "NO")) {
        time(&currentTime);
        printf("(Local Time) %s", ctime(&currentTime));
    }

    else if (!strcmp(argv[1], "-u") && !strcmp(argv[2], "NO")) {
        setenv("TZ", "UTC", 1);
        tzset();
        time(&currentTime);
        printf("(UTC) %s", ctime(&currentTime));
        setenv("TZ", "UTC-5:30", 1);
        tzset();
    }

    else if ((!strcmp(argv[1], "NO") && !strcmp(argv[2], "-R")) || (!strcmp(argv[1], "-R") && !strcmp(argv[2], "NO"))){
        time(&currentTime);
        struct tm *timeStruct = localtime(&currentTime);
        const int maxSize = 100;
        const char* format = "%a, %e %b %Y %T %z";
        char s[maxSize];

        strftime(s, maxSize, format, timeStruct);

        printf("(RFC-3339) %s\n", s);
    }   

    else if ((!strcmp(argv[1], "-u") && !strcmp(argv[2], "-R")) || (!strcmp(argv[1], "-R") && !strcmp(argv[2], "-u"))) {
        setenv("TZ", "UTC", 1);
        tzset();
        
        time(&currentTime);
        struct tm *timeStruct = localtime(&currentTime);
        const int maxSize = 100;
        const char* format = "%a, %e %b %Y %T %z";
        char s[maxSize];

        strftime(s, maxSize, format, timeStruct);

        printf("(RFC-3339) %s\n", s);
    

        setenv("TZ", "UTC-5:30", 1);
        tzset();
    }

    else {
        printf("[!] Invalid flag(s) entered.\n");
        exit(-1);
    }
    return 0;

}