#include "../include/codexion.h"

#define N_CODERS 5

int	main(void)
{
	pthread_t	coders[N_CODERS];
	t_coder		coder_data[N_CODERS];
    t_dongle	dongles[N_CODERS];
	long		start_time;

	start_time = get_time_ms();
	init_coders(coder_data, start_time);
	create_coders(coders, coder_data);
	join_coders(coders);
	return (0);
}