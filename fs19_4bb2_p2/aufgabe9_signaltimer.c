#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

struct timespec t0_buf, t1_buf;

void signalhandler(int signal) {
    clock_gettime(CLOCK_REALTIME, &t1_buf);
    printf("... handling done.\n");
    printf("real \t%ld %lds\n",
           (t1_buf.tv_sec - t0_buf.tv_sec),
           (t1_buf.tv_nsec - t0_buf.tv_nsec));
}

int main(int argc, char *argv[]) {
    signal(SIGUSR1, signalhandler);
    printf("Sending signal ...\n");
    raise(SIGUSR1);

    clock_gettime(CLOCK_REALTIME, &t0_buf);
    pause();
    return 0;
}
