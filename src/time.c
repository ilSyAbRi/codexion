/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:55:19 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/10 18:55:19 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (time <= 0)
		return (0);
	ts.tv_sec = (get_time_ms() + time) / 1000;
	ts.tv_nsec = ((get_time_ms() + time) % 1000) * 1000000;
	pthread_mutex_lock(&coder_data->mutex_sleep);
	while (!simulation_stopped(coder_data->simulation))
	{
		if (pthread_cond_timedwait(&coder_data->simulation->cond,
				&coder_data->mutex_sleep, &ts) != 0)
			break ;
	}
	pthread_mutex_unlock(&coder_data->mutex_sleep);
	return (simulation_stopped(coder_data->simulation));
}
