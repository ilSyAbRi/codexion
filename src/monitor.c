/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:53:38 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/12 02:41:13 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	create_monitor(pthread_t *monitor, t_coder *coder_data)
{
	pthread_create(monitor, NULL, monitor_routine, coder_data);
}

void	join_monitor(pthread_t monitor)
{
	pthread_join(monitor, NULL);
}

long	protect_get_burnout_deadline(t_coder *coder_data)
{
	long	deadline;

	pthread_mutex_lock(&coder_data->simulation->deadline_mutex);
	deadline = coder_data->burnout_deadline;
	pthread_mutex_unlock(&coder_data->simulation->deadline_mutex);
	return (deadline);
}

void	protect_reset_burnout_deadline(t_coder *coder_data)
{
	pthread_mutex_lock(&coder_data->simulation->deadline_mutex);
	coder_data->burnout_deadline = get_time_ms()
		+ coder_data->config->time_to_burnout;
	pthread_mutex_unlock(&coder_data->simulation->deadline_mutex);
}

void	*monitor_routine(void *arg)
{
	t_coder	*coders_data;
	int		i;
	long	deadline;

	coders_data = (t_coder *)arg;
	while (1)
	{
		i = 0;
		while (i < coders_data->config->number_of_coders)
		{
			deadline = protect_get_burnout_deadline(&coders_data[i]);
			if (get_time_ms() > deadline && coders_data[i].n_compiles
				<= protect_number_of_coders(&coders_data[i]))
			{
				log_burnout(coders_data, i);
				return (NULL);
			}
			i++;
		}
		if (stop_monitor_all_coder_finished(coders_data->simulation,
				coders_data->config))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
