/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:55:56 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/11 00:41:05 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	init_simulation_data(t_simulation *simulation,
		t_coder *coder_data, t_dongle *dongles_data, t_config *config)
{
	init_simulation(simulation);
	init_dongles_data(dongles_data, config->number_of_coders);
	init_coders_data(coder_data, dongles_data, simulation, config);
}

void	cleanup_simulation(t_dongle *dongles_data,
		t_simulation *simulation, t_config *config)
{
	destroy_dongles_data(dongles_data, config->number_of_coders);
	destroy_simulation(simulation);
}

void	run_simulation(t_config *config)
{
	pthread_t		*coders;
	pthread_t		monitor;
	t_simulation	simulation;
	t_coder			*coder_data;
	t_dongle		*dongles_data;

	coders = malloc(sizeof(pthread_t) * config->number_of_coders);
	coder_data = malloc(sizeof(t_coder) * config->number_of_coders);
	dongles_data = malloc(sizeof(t_dongle) * config->number_of_coders);
	if (!coders || !coder_data || !dongles_data)
	{
		free(coders);
		free(coder_data);
		free(dongles_data);
		return ;
	}
	init_simulation_data(&simulation, coder_data, dongles_data, config);
	create_coders(coders, coder_data);
	create_monitor(&monitor, coder_data);
	join_coders(coders, coder_data, config);
	join_monitor(monitor);
	cleanup_simulation(dongles_data, &simulation, config);
	free(coders);
	free(coder_data);
	free(dongles_data);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (parse_args(argc, argv, &config))
		return (1);
	config.start_time = get_time_ms();
	run_simulation(&config);
	return (0);
}
