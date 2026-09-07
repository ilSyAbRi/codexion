#include "../include/codexion.h"

void create_monitor(pthread_t *monitor, t_coder *coder_data)
{
    pthread_create(monitor, NULL, monitor_routine, coder_data);
}

void join_monitor(pthread_t monitor)
{
    pthread_join(monitor,NULL);
}

long protect_get_burnout_deadline(t_coder *coder_data)
{
    long deadline;

    pthread_mutex_lock(&coder_data->simulation->deadline_mutex);
	deadline = coder_data->burnout_deadline;
	pthread_mutex_unlock(&coder_data->simulation->deadline_mutex);

    return deadline;
}

void protect_reset_burnout_deadline(t_coder *coder_data)
{
    pthread_mutex_lock(&coder_data->simulation->deadline_mutex);
	coder_data->burnout_deadline = get_time_ms() + coder_data->config->time_to_burnout;
	pthread_mutex_unlock(&coder_data->simulation->deadline_mutex);
}

void *monitor_routine(void *arg)
{
    t_coder	*coders_data;
    int i;
    long deadline;

    coders_data = (t_coder*) arg;
    while(1)
    {
        i = 0;
        while (i < coders_data->config->number_of_coders)
        {
            deadline = protect_get_burnout_deadline(&coders_data[i]);
            if (get_time_ms() >= deadline)
            {
                log_message_burnout(&coders_data[i] ,coders_data[i].id,"is burnout");
                stop_simulation(coders_data[i].simulation);
                return NULL;
            }
            i++;
        }
        if (stop_monitor_all_coder_finished(coders_data->simulation, coders_data->config))
            return NULL;
    }
    return (NULL);
}