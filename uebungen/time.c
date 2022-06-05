#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t = time(NULL);
    printf("%ld\n", t);

    struct tm *ltm = localtime(&t);
    char *ls = asctime(ltm);
    printf("%s\n", ls);

    struct tm *gtm = gmtime(&t); // UTC
    char *gs = asctime(gtm);
    printf("%s\n", gs);

    char *buf = malloc(32);
    strftime(buf, 32, "%Y-%m-%dT%H:%M:%SZ", gtm);
    printf("%s\n", buf);
}