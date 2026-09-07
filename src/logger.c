#include "../include/codexion.h"

void	log_message(t_coder *coder_data, int id, char *message)
{
	pthread_mutex_lock(&coder_data->simulation->mutex_print);
	printf("%ld %d %s\n",
		get_time_ms() - coder_data->start_time,
		id,
		message);
	pthread_mutex_unlock(&coder_data->simulation->mutex_print);
}

void	log_message_burnout(t_coder *coder_data, int id, char *message)
{
	log_message(coder_data,id, message);
}

int	coder_phase(t_coder *coder_data, long time, char *message)
{
	log_message(coder_data, coder_data->id, message);
	return (thread_sleep(coder_data, time));
}