#include "../include/codexion.h"

#define N_CODERS 5
#define TIME_TO_BURNOUT 800
#define TIME_TO_COMPILE 200
#define TIME_TO_DEBUG 200
#define TIME_TO_REFACTOR 200
#define REQUIRED_COMPILES 3
#define DONGLE_COOLDOWN 50

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

void *coder_routing(void* arg) {
    t_coder *coder =  (t_coder *)arg;
    int i = 0;
    while (i < REQUIRED_COMPILES) {

        printf("%ld %d is compiling\n", get_time_ms() - coder->start_time, coder->id);
        usleep(TIME_TO_COMPILE * 1000);

        printf("%ld %d is debugging\n", get_time_ms() - coder->start_time, coder->id);
        usleep(TIME_TO_DEBUG * 1000);

        printf("%ld %d is refactoring\n", get_time_ms() - coder->start_time, coder->id);
        usleep(TIME_TO_REFACTOR * 1000);

        i++;
    }
    return NULL;
}

int main() {
    pthread_t coders[N_CODERS];
    t_coder coder_data[N_CODERS];
    int i = 0;
    long start_time = get_time_ms();

    while (i < N_CODERS) {
        coder_data[i].id = i + 1;
        coder_data[i].start_time = start_time;
        pthread_create(&coders[i], NULL, coder_routing, &coder_data[i]);
        i++;
    }

    i = 0;
    while (i < N_CODERS) {
        pthread_join(coders[i], NULL);
        i++;
    }
    return 0;
}