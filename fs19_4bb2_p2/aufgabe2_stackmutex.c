#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PUSH_ITEMS 20
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct node {
    struct node *next;
    int item;
} Node;

static Node *stack = NULL;

int stack_pop();
Node* getLastNode();

void stack_push(int item) {
    pthread_mutex_lock(&mutex);
    printf("mutex locked\n");
    Node *n = malloc(sizeof(Node));
    n->item = item;
    n->next = stack;
    stack = n;
    printf("insert %d\n", item);
    pthread_mutex_unlock(&mutex);
    printf("mutex unlocked\n");
}

void *push(void *arg) {
    int r = rand() % 100 + 1;
    stack_push(r);
}


int main() {
    pthread_t threads[PUSH_ITEMS];

    for(int i = 0; i < PUSH_ITEMS; i++) {
        pthread_create(&threads[i], NULL, push, NULL);
    }

    for(int j = 0; j < PUSH_ITEMS; j++) {
        pthread_join(threads[j], NULL);
    }
}

int stack_pop() {
    Node *last = getLastNode();
    printf("pop last node: %d\n", last->item);
    free(last);
}

Node* getLastNode() {
    if (stack != NULL) {
        Node *node = stack;
        if(node->next == NULL) {
            return node;
        } else {
            while(node->next != NULL) {
                node = node->next;
            }
            return node;
        }
    }
}