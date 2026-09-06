#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	pthread_t	coders[N_CODERS];
	pthread_t	monitor;
	t_config config;
	t_simulation	simulation;
	t_coder		coder_data[N_CODERS];
    t_dongle	dongles_data[N_CODERS];
	long		start_time;

	start_time = get_time_ms();
	if (parse_args(argc, argv, &config))
			return 1;
	init_simulation(&simulation);
    init_dongles_data(dongles_data, N_CODERS);
	init_coders_data(coder_data, dongles_data, start_time, &simulation);
	create_coders(coders, coder_data);
	create_monitor(&monitor, coder_data);
	join_coders(coders);
	join_monitor(monitor);
	return (0);
}