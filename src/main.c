#include "../include/codexion.h"

int	main(void)
{
	pthread_t	coders[N_CODERS];
	pthread_t	monitor;
	t_coder		coder_data[N_CODERS];
    t_dongle	dongles_data[N_CODERS];
	t_simulation	simulation;
	long		start_time;

	simulation.stop = 0;
	start_time = get_time_ms();
    init_dongles_data(dongles_data, N_CODERS);
	init_coders_data(coder_data, dongles_data, start_time);
	create_coders(coders, coder_data);
	create_monitor(&monitor, coder_data);
	join_coders(coders);
	join_monitor(monitor);
	return (0);
}