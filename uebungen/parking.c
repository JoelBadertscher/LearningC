#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

sem_t sem;

void *car(void *arg) {
    pthread_t id = pthread_self();
    while (1) {
        int res = sem_trywait(&sem);
        if (res == 0) {
            printf("%d: entering parking...\n", id);
            sleep(random() % 3);
            printf("%d: leaving parking...", id);
            sem_post(&sem);
        } else {
            assert(errno == EAGAIN);
        }
        sleep(random() % 10);
    }
    return NULL;
}

void *display(void *arg) {
    while (1) {
        int cur_spaces;
        sem_getvalue(&sem, &cur_spaces);
        printf("free spaces: %d\n", cur_spaces);
        sleep(1);
    }
}

int main() {
    int max_spaces = 5;
    int res = sem_init(&sem, 0, max_spaces);
    int n_cars = 7;
    for (int i = 0; i < n_cars; i++) {
        pthread_t thread;
        pthread_create(&thread, NULL, car, NULL);
        pthread_detach(thread);
    }
    pthread_t display_thread;
    pthread_create(&display_thread, NULL, display, NULL);
    pthread_detach(display_thread);
    pthread_exit(0);
    return 0;
}