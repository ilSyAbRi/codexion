#include "../include/codexion.h"

void init_dongles_data(t_dongle *dongles_data, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        pthread_mutex_init(&dongles_data[i].mutex, NULL);
        i++;
    }
}