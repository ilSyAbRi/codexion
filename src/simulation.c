#include "../include/codexion.h"

void	init_simulation(t_simulation *simulation)
{
	simulation->stop = 0;
    pthread_mutex_init(&simulation->mutex, NULL);
}

void	stop_simulation(t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->mutex);
	simulation->stop = 1;
    pthread_mutex_unlock(&simulation->mutex);
}

int	simulation_stopped(t_simulation *simulation)
{
	int	stop;

	pthread_mutex_lock(&simulation->mutex);
	stop = simulation->stop;
	pthread_mutex_unlock(&simulation->mutex);
	return (stop);
}