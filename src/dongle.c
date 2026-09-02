#include "../include/codexion.h"

void init_dongles_data(t_dongle *dongles_data, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        dongles_data[i].id = i + 1;
        pthread_mutex_init(&dongles_data[i].mutex, NULL);
        i++;
    }
}

void take_dongles(t_coder *coder_data)
{
    if (coder_data->second_dongle->id > coder_data->first_dongle->id)
    {
        pthread_mutex_lock(&coder_data->second_dongle->mutex);
        pthread_mutex_lock(&coder_data->first_dongle->mutex);
    }
    else
    {
        pthread_mutex_lock(&coder_data->first_dongle->mutex);
        pthread_mutex_lock(&coder_data->second_dongle->mutex);
    }
}

void release_dongles(t_coder *coder_data)
{
    pthread_mutex_unlock(&coder_data->first_dongle->mutex);
    pthread_mutex_unlock(&coder_data->second_dongle->mutex);
}