#include "../include/codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

int	thread_sleep(t_coder *coder_data, long time)
{
	struct timespec	ts;

	ts.tv_sec = (get_time_ms() + time) / 1000;
	ts.tv_nsec = ((get_time_ms()+time) % 1000) * 1000000;

	pthread_mutex_lock(&coder_data->mutex_sleep);
	pthread_cond_timedwait(&coder_data->simulation->cond, &coder_data->mutex_sleep, &ts);
	pthread_mutex_unlock(&coder_data->mutex_sleep);
	return (simulation_stopped(coder_data->simulation));
}