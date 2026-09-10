/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:54:36 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/10 18:56:34 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	log_task(t_coder *coder_data, t_task task)
{
	long	time;

	pthread_mutex_lock(&coder_data->simulation->mutex_print);
	if (!simulation_stopped(coder_data->simulation))
	{
		time = get_time_ms() - coder_data->start_time;
		if (task == COMPILE)
		{
			printf("%ld %d has taken a dongle\n", time, coder_data->id);
			printf("%ld %d has taken a dongle\n", time, coder_data->id);
			printf("%ld %d is compiling\n", time, coder_data->id);
		}
		else if (task == DEBUG)
			printf("%ld %d is debugging\n", time, coder_data->id);
		else if (task == REFACTOR)
			printf("%ld %d is refactoring\n", time, coder_data->id);
	}
	pthread_mutex_unlock(&coder_data->simulation->mutex_print);
}

void	log_burnout(t_coder *coders_data, int burned_coder)
{
	long	time;

	pthread_mutex_lock(&coders_data[burned_coder].simulation->mutex_print);
	time = get_time_ms() - coders_data[burned_coder].start_time;
	printf("%ld %d burned out\n", time, coders_data[burned_coder].id);
	stop_simulation(coders_data, coders_data[burned_coder].simulation);
	pthread_mutex_unlock(&coders_data[burned_coder].simulation->mutex_print);
}

int	coder_phase(t_coder *coder_data, long time, t_task task)
{
	log_task(coder_data, task);
	return (thread_sleep(coder_data, time));
}
