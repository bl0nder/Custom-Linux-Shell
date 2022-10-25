#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    
    setenv("TZ", "IST", 1);
    tzset();

    time_t currentTime;
    time(&currentTime);



    printf("%s\n", ctime(&currentTime));
    return 0;

}