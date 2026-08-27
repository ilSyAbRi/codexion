#include <stdio.h>
#include <pthread.h>

int main()
{
    pthread_mutex_t mutex;
    printf("before init\n");
    pthread_mutex_init(&mutex, NULL);
    printf("mutex_initialized\n");
    pthread_mutex_destroy(&mutex);
    printf("mutex destroyed");
    return 0;
}
