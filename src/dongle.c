#include "../include/codexion.h"

void init_dongles_data(t_dongle *dongles_data, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        dongles_data[i].id = i + 1;
        pthread_mutex_init(&dongles_data[i].mutex_dongle, NULL);
        i++;
    }
}

void td(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->mutex_dongle);
}

void take_dongles(t_coder *coder_data)
{
    td(coder_data->first_dongle);
    td(coder_data->second_dongle);
}

void release_dongles(t_coder *coder_data)
{
    pthread_mutex_unlock(&coder_data->first_dongle->mutex_dongle);
    pthread_mutex_unlock(&coder_data->second_dongle->mutex_dongle);
}