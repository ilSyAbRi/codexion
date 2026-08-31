
#ifndef CODEXION_CODEXION_H
#define CODEXION_CODEXION_H
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_coder
{
    int id;
    long start_time;
} t_coder;

typedef struct s_dongle
{
    pthread_mutex_t mutex;
} t_dongle;

#endif //CODEXION_CODEXION_H