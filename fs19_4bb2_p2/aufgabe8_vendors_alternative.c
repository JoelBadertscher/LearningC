#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <errno.h>

sem_t sem;

void *start(void *arg) {

    int r = sem_trywait(&sem);
    while(r != EAGAIN){
        sleep(3);
        r = sem_trywait(&sem);
        int s;
        sem_getvalue(&sem, &s);
        printf("%d, \n", s);
    }


}

void main() {

    sem_init(&sem, 0, 99);
    pthread_t t[7];
    for(int i = 0; i < 7; i++) {
        pthread_create(&t[i], NULL, start, NULL);
    }

    for(int i = 0; i < 7; i++) {
        pthread_join(t[i], NULL);
    }
    printf("Done");
}