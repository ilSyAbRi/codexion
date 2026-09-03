#include "../include/codexion.h"

void create_monitor(pthread_t *monitor, t_coder *coder_data)
{
    pthread_create(monitor, NULL, monitor_routine, coder_data);
}

void join_monitor(pthread_t monitor)
{
    pthread_join(monitor,NULL);
}

void *monitor_routine(void *arg)
{
    	t_coder	*coders_data;
        int i;

        coders_data = (t_coder*) arg;
        while(1)
        {
            i = 0;
            while (i < N_CODERS)
            {
                if (get_time_ms() >= coders_data[i].burnout_deadline)
                {
                    printf("%ld %d burned out\n",get_time_ms() - coders_data[i].start_time ,coders_data[i].id);
                    stop_simulation(coders_data[i].simulation);
                    return NULL;
                }
            i++;
            }
            usleep(1000);
        }
        return (NULL);
}