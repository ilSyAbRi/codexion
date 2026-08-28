#include "../include/codexion.h"

#define N_CODERS 5
#define TIME_TO_BURNOUT 800
#define TIME_TO_COMPILE 200
#define TIME_TO_DEBUG 200
#define TIME_TO_REFACTOR 200
#define REQUIRED_COMPILES 3
#define DONGLE_COOLDOWN 50

void *coder_routing(void* arg) {
    int id =  *(int*)arg;
    int i = 0;
    printf("coder %d started\n",id);
    while (i < REQUIRED_COMPILES) {

        printf("coder %d is compiling\n", id);
        usleep(TIME_TO_COMPILE * 1000);

        printf("coder %d is debugging\n", id);
        usleep(TIME_TO_DEBUG * 1000);

        printf("coder %d is refactoring\n", id);
        usleep(TIME_TO_REFACTOR * 1000);

        i++;
    }
    return NULL;
}

int main() {
    pthread_t coders[N_CODERS];
    int ids[N_CODERS];
    int i = 0;

    while (i < N_CODERS) {
        ids[i] = i + 1;
        pthread_create(&coders[i], NULL, coder_routing, &ids[i]);
        i++;
    }

    i = 0;
    while (i < N_CODERS) {
        pthread_join(coders[i], NULL);
        i++;
    }
    return 0;
}