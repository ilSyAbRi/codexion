#include <pthread.h>
#include <stdio.h>

void *worker(void *arg)
{
    printf("hello from worker\n");
    return NULL;
}

int main(void)
{
    pthread_t thread;
    printf("hello from main\n");

    pthread_create(&thread, NULL, worker, NULL);

    pthread_join(thread, NULL);
    printf("%ld, %ld",&thread, thread);
    
    return 0;
}
