// Idee: 2 semaphoren
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

sem_t *stock;
sem_t *vendors;

void *sell(void *arg) {
    sem_wait(stock);
    pthread_t *pthread = (pthread_t *) arg;
    int r = rand() % 3 + 1;
    sleep(r);
    printf("Sold a ticket - ");

    int *active_vendors;
    active_vendors = malloc(sizeof(int));
    sem_getvalue(vendors, active_vendors);
    printf("Free vendors: %d\n", 7 - *active_vendors);
    sem_post(vendors);
    free(pthread);
}

int main(void) {
    stock = malloc(sizeof(sem_t));
    vendors = malloc(sizeof(sem_t));
    sem_init(stock, 0, 99);
    sem_init(vendors, 0, 7);

    while(1) {
        sem_wait(vendors);
        pthread_t *pthread = malloc(sizeof(pthread_t));
        pthread_create(pthread, NULL, sell, pthread);
    }
}