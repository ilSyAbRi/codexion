#include "../include/codexion.h"

void	init_coders_data(t_coder *coder_data, t_dongle *dongles_data,
			t_simulation *simulation, t_config *config)
{
	int			i;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;

	i = 0;
	while (i < config->number_of_coders)
	{
		coder_data[i].id = i + 1;
		left_dongle = &dongles_data[i];
		right_dongle = &dongles_data[(i + 1) % config->number_of_coders];
		coder_data[i].first_dongle = (t_dongle *[2]){left_dongle,
			right_dongle}[coder_data[i].id == config->number_of_coders];
		coder_data[i].second_dongle = (t_dongle *[2]){right_dongle,
			left_dongle}[coder_data[i].id == config->number_of_coders];
		coder_data[i].n_compiles = 0;
		coder_data[i].start_time = config->start_time;
		coder_data[i].burnout_deadline = config->start_time
			+ config->time_to_burnout;
		coder_data[i].simulation = simulation;
		coder_data[i].config = config;
		pthread_mutex_init(&coder_data[i].mutex_sleep, NULL);
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

void	join_coders(pthread_t *coder, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(coder[i], NULL);
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
		release_dongles(coder_data);
		if (coder_phase(coder_data,
				coder_data->config->time_to_compile, DEBUG))
			break ;
		if (coder_phase(coder_data,
				coder_data->config->time_to_compile, REFACTOR))
			break ;
		coder_data->n_compiles++;
	}
	if (coder_data->n_compiles
		== coder_data->config->number_of_compile_required)
		coder_finished(coder_data->simulation);
	return (NULL);
}
