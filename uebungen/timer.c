#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

volatile int flag = 0;

void handle(int sig) {
    flag = 1;
}

int main() {
    signal(SIGALRM, handle);
    struct itimerval i;
    struct timeval v = {1, 0};
    i.it_value = v;
    struct timeval x = {2, 0};
    i.it_interval = x;
    setitimer(ITIMER_REAL, &i, NULL);
    while (1) {
        pause();
        printf("alert! %d\n", time(NULL));
    }
}
