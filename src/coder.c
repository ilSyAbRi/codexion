/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:25:38 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/11 00:53:53 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	init_coder(t_coder *coder, t_dongle *dongles, int i)
{
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	coder->id = i + 1;
	left_dongle = &dongles[i];
	right_dongle = &dongles[(i + 1) % coder->config->number_of_coders];
	coder->first_dongle = (t_dongle *[2]){left_dongle,
		right_dongle}[coder->id == coder->config->number_of_coders];
	coder->second_dongle = (t_dongle *[2]){right_dongle,
		left_dongle}[coder->id == coder->config->number_of_coders];
	coder->n_compiles = 0;
	coder->start_time = coder->config->start_time;
	coder->burnout_deadline = coder->config->start_time
		+ coder->config->time_to_burnout;
	pthread_mutex_init(&coder->mutex_sleep, NULL);
}

void	init_coders_data(t_coder *coder_data, t_dongle *dongles_data,
			t_simulation *simulation, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		coder_data[i].simulation = simulation;
		coder_data[i].config = config;
		init_coder(&coder_data[i], dongles_data, i);
		i++;
	}
}

void	create_coders(pthread_t *coder, t_coder *coder_data)
{
	int	i;

	i = 0;
	while (i < coder_data->config->number_of_coders)
	{
		push_request(&coder_data[i], coder_data[i].first_dongle);
		push_request(&coder_data[i], coder_data[i].second_dongle);
		pthread_create(&coder[i], NULL,
			coder_routing, &coder_data[i]);
		i++;
	}
}

void	join_coders(pthread_t *coder, t_coder *coder_data, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(coder[i], NULL);
		pthread_mutex_destroy(&coder_data[i].mutex_sleep);
		i++;
	}
}

void	*coder_routing(void *arg)
{
	t_coder	*coder_data;

	coder_data = (t_coder *)arg;
	while (coder_data->n_compiles
		< coder_data->config->number_of_compile_required
		&& !simulation_stopped(coder_data->simulation))
	{
		if (take_dongles(coder_data))
			break ;
		protect_reset_burnout_deadline(coder_data);
		if (coder_phase(coder_data,
				coder_data->config->time_to_compile, COMPILE))
			break ;
		coder_data->n_compiles++;
		release_dongles(coder_data);
		if (coder_phase(coder_data,
				coder_data->config->time_to_debug, DEBUG))
			break ;
		if (coder_phase(coder_data,
				coder_data->config->time_to_refactor, REFACTOR))
			break ;
	}
	coder_finished(coder_data->simulation);
	return (NULL);
}
