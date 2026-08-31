#include "../include/codexion.h"

void init_dongles(t_dongle *dongles, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        pthread_mutex_init(&dongles[i].mutex, NULL)
        i++;
    }
}