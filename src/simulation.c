#include "../include/codexion.h"

void	init_simulation(t_simulation *simulation)
{
	simulation->stop = 0;
	simulation->finished_coders = 0;
    pthread_mutex_init(&simulation->mutex_stop, NULL);
	pthread_mutex_init(&simulation->deadline_mutex, NULL);
	pthread_mutex_init(&simulation->finished_mutex, NULL);
}

void	stop_simulation(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->mutex_stop);
	simulation->stop = 1;
    pthread_mutex_unlock(&simulation->mutex_stop);
}

int	simulation_stopped(t_simulation *simulation)
{
	int	stop;

	pthread_mutex_lock(&simulation->mutex_stop);
	stop = simulation->stop;
	pthread_mutex_unlock(&simulation->mutex_stop);
	return (stop);
}

void	coder_finished(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->finished_mutex);
	simulation->finished_coders++;
	pthread_mutex_unlock(&simulation->finished_mutex);
}

int stop_monitor_all_coder_finished(t_simulation *simulation)
{
	int finished;

	pthread_mutex_lock(&simulation->finished_mutex);
	finished = simulation->finished_coders;
	pthread_mutex_unlock(&simulation->finished_mutex);

	return (finished == N_CODERS);
}