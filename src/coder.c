#include "../include/codexion.h"

void	init_coders_data(t_coder *coder_data,t_dongle *dongles_data, t_simulation *simulation, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		coder_data[i].id = i + 1;
		if (i+1 == config->number_of_coders)
		{
			coder_data[i].first_dongle = &dongles_data[i];
			coder_data[i].second_dongle = &dongles_data[(i + 1) % config->number_of_coders];
		}
		else{
			coder_data[i].second_dongle = &dongles_data[i];
			coder_data[i].first_dongle = &dongles_data[(i + 1) % config->number_of_coders];
		}

		coder_data[i].start_time = config->start_time;
		coder_data[i].burnout_deadline = config->start_time + config->time_to_burnout;
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
	t_coder	*coder;
	int		i;

	coder = (t_coder *)arg;
	i = 0;
	while (i < coder->config->number_of_compile_required
		&& !simulation_stopped(coder->simulation))
	{
		take_dongles(coder);
		if (simulation_stopped(coder->simulation))
			break;
		protect_reset_burnout_deadline(coder);
		if (coder_phase(coder, coder->config->time_to_compile,
				"is compiling"))
			break;
		release_dongles(coder);
		if (coder_phase(coder, coder->config->time_to_debug, "is debugging")
			|| coder_phase(coder, coder->config->time_to_refactor,
				"is refactoring"))
			break;
		i++;
	}
	if (i == coder->config->number_of_compile_required)
		coder_finished(coder->simulation);
	return (NULL);
}