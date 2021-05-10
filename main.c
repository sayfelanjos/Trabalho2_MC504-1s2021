#include <stdio.h>
#include <pthread.h>
#include "spectators/spectators.h"
#include "judge/judge.h"


#define THREAD_NUM 10
#define NUM_IMMIGRANTS 10
#define NUM_SPECTATORS 10
#define JUDGE 1

int main(int args, char *argv[]) {
    pthread_t immigrants[NUM_IMMIGRANTS];
    pthread_t spectators[NUM_SPECTATORS];
    pthread_t judge;

    // sem_init(&semaphore, 0, 1);

    int i;
    for (i = 10; i < NUM_IMMIGRANTS+10; i++) {
        int* id_immigrants = malloc(sizeof(int));
        *id_immigrants = i;
        if(pthread_create(&immigrants[i], NULL, &immigrants_routine, id_immigrants) != 0) {
            perror("Failed to create thread");
        }
    }
    for (i = 20; i < NUM_SPECTATORS+20; i++) {
        int* id_spectators = malloc(sizeof(int));
        *id_spectators = i;
        if (pthread_create(&spectators[i], NULL, &spectators_routine, id_spectators) != 0) {
            perror("Failed to create thread");
        }
    }
    if (pthread_create(&judge, NULL, &judge_routine) != 0) {
        perror("Failed to create thread");
    }
    // for (i = 0; i < NUM_IMMIGRANTS; i++) {
    //     if (pthread_join(immigrants[i], NULL) != 0) {
    //         perror("Failed to join thread");
    //     }
    // }
    // for (i = 0; i < NUM_SPECTATORS; i++) {
    //     if (pthread_join(spectators[i], NULL) != 0) {
    //         perror("Failed to join thread");
    //     }
    // }
    // if (pthread_join(judge, NULL) != 0) {
    //     perror("Failed to join thread");
    // }

    pthread_exit(0);
    return 0;
}