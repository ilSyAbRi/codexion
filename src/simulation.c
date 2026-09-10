/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:55:10 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/10 22:11:01 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	init_simulation(t_simulation *simulation)
{
	simulation->stop = 0;
	simulation->finished_coders = 0;
	pthread_mutex_init(&simulation->mutex_stop, NULL);
	pthread_mutex_init(&simulation->deadline_mutex, NULL);
	pthread_mutex_init(&simulation->finished_mutex, NULL);
	pthread_cond_init(&simulation->cond, NULL);
	pthread_mutex_init(&simulation->mutex_print, NULL);
}

void	stop_simulation(t_coder *coder_data, t_simulation *simulation)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&simulation->mutex_stop);
	simulation->stop = 1;
	while (i < coder_data->config->number_of_coders)
	{
		pthread_cond_broadcast(&coder_data[i].first_dongle->cond_dongle);
		pthread_cond_broadcast(&coder_data[i].second_dongle->cond_dongle);
		i++;
	}
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

int	stop_monitor_all_coder_finished(t_simulation *simulation, t_config *config)
{
	int	finished;

	pthread_mutex_lock(&simulation->finished_mutex);
	finished = simulation->finished_coders;
	pthread_mutex_unlock(&simulation->finished_mutex);
	return (finished == config->number_of_coders);
}
