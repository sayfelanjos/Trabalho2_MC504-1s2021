#include "spectators.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem_

void *spectators_routine(void *args) {
    sem_wait(&);
    // sem_wait(&mutex);
    sleep(1);
    printf("Thread %d recebeu %d e entregou %d\n", *(int*)args, soma, soma + 1);
    soma++;
    // sem_post(&mutex);
    sem_post(&semaphore);
    free(args);
}