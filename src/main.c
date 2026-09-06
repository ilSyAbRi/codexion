#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	t_config config;

	if (parse_args(argc, argv, &config))
		return 1;
	config.start_time = get_time_ms();

	pthread_t	coders[config.number_of_coders];
	pthread_t	monitor;
	t_simulation	simulation;
	t_coder		coder_data[config.number_of_coders];
    t_dongle	dongles_data[config.number_of_coders];

	init_simulation(&simulation);
    init_dongles_data(dongles_data, config.number_of_coders);
	init_coders_data(coder_data, dongles_data, &simulation, &config);
	create_coders(coders, coder_data);
	create_monitor(&monitor, coder_data);
	join_coders(coders, &config);
	join_monitor(monitor);
	return (0);
}