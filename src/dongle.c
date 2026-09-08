#include "../include/codexion.h"

void init_dongles_data(t_dongle *dongles_data, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        dongles_data[i].id = i + 1;
        dongles_data[i].owner = -1;
        dongles_data[i].cooldown_deadline = 0;
        pthread_cond_init(&dongles_data[i].cond_dongle, NULL);
        pthread_mutex_init(&dongles_data[i].mutex_dongle, NULL);
        i++;
    }
}

int request_dongle(t_coder *coder_data, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->mutex_dongle);
    while (!simulation_stopped(coder_data->simulation))
    {
        if (thread_sleep(coder_data, dongle->cooldown_deadline-get_time_ms()))
            break;

        if (dongle->owner == -1)
            break;

        if (simulation_stopped(coder_data->simulation))
            break;
        pthread_cond_wait(&dongle->cond_dongle, &dongle->mutex_dongle);
    }
    dongle->owner = coder_data->id;
    pthread_mutex_unlock(&dongle->mutex_dongle);
    return simulation_stopped(coder_data->simulation);
}

int take_dongles(t_coder *coder_data)
{
    if (request_dongle(coder_data, coder_data->first_dongle))
        return 1;

    if (request_dongle(coder_data, coder_data->second_dongle))
        return 1;
    return 0;
}

void release_dongles(t_coder *coder_data)
{
    pthread_mutex_lock(&coder_data->first_dongle->mutex_dongle);
    coder_data->first_dongle->owner = -1;
    coder_data->first_dongle->cooldown_deadline = get_time_ms() + coder_data->config->dongle_cooldown;
    pthread_cond_broadcast(&coder_data->first_dongle->cond_dongle);
    pthread_mutex_unlock(&coder_data->first_dongle->mutex_dongle);
    pthread_mutex_lock(&coder_data->second_dongle->mutex_dongle);
    coder_data->second_dongle->owner = -1;
    coder_data->second_dongle->cooldown_deadline = get_time_ms() + coder_data->config->dongle_cooldown;
    pthread_cond_broadcast(&coder_data->second_dongle->cond_dongle);
    pthread_mutex_unlock(&coder_data->second_dongle->mutex_dongle);
}