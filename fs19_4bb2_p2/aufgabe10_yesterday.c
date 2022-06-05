#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <time.h>

struct tm *today, *tomorrow;

int main(int argc, char *argv[]) {
    // get today
    time_t now;
    time(&now);

    // Ça ira mieux demain
    today = localtime(&now);
    tomorrow = today;
    tomorrow->tm_min = 0;
    tomorrow->tm_hour = 0;
    tomorrow->tm_sec = 0;
    tomorrow->tm_mday = tomorrow->tm_mday + 1;

    time_t tomorrow_t = mktime(tomorrow);
    printf("today is: %s\n", ctime(&now));
    printf("tomorrow: %s\n", ctime(&tomorrow_t));
    return 0;
}