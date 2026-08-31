#include "../include/codexion.h"

void	init_coders_data(t_coder *coder_data,t_dongle *dongles_data, long start_time)
{
	int	i;

	i = 0;
	while (i < N_CODERS)
	{
		coder_data[i].id = i + 1;
        coder_data[i].first_dongle = &dongles_data[i];
        coder_data[i].second_dongle = &dongles_data[(i + 1) % N_CODERS];
		coder_data[i].start_time = start_time;
 		i++;
	}
}

void	create_coders(pthread_t *coder, t_coder *coder_data)
{
	int	i;

	i = 0;
	while (i < N_CODERS)
	{
		pthread_create(&coder[i], NULL,
			coder_routing, &coder_data[i]);
		i++;
	}
}

void	join_coders(pthread_t *coder)
{
	int	i;

	i = 0;
	while (i < N_CODERS)
	{
		pthread_join(coder[i], NULL);
		i++;
	}
}

void *coder_routing(void* arg) {
    t_coder *coder_data =  (t_coder *)arg;
    int i = 0;
    while (i < REQUIRED_COMPILES) {

        pthread_mutex_lock(&coder_data->first_dongle->mutex);
        pthread_mutex_lock(&coder_data->second_dongle->mutex);
        printf("%ld %d is compiling\n", get_time_ms() - coder_data->start_time, coder_data->id);
        usleep(TIME_TO_COMPILE * 1000);
        pthread_mutex_unlock(&coder_data->first_dongle->mutex);
        pthread_mutex_unlock(&coder_data->second_dongle->mutex);

        printf("%ld %d is debugging\n", get_time_ms() - coder_data->start_time, coder_data->id);
        usleep(TIME_TO_DEBUG * 1000);

        printf("%ld %d is refactoring\n", get_time_ms() - coder_data->start_time, coder_data->id);
        usleep(TIME_TO_REFACTOR * 1000);

        i++;
    }
    return NULL;
}