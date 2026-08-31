#include "../include/codexion.h"
#define N_CODERS 5
#define TIME_TO_BURNOUT 800
#define TIME_TO_COMPILE 200
#define TIME_TO_DEBUG 200
#define TIME_TO_REFACTOR 200
#define REQUIRED_COMPILES 3
#define DONGLE_COOLDOWN 50

void	init_coders(t_coder *coders, long start_time)
{
	int	i;

	i = 0;
	while (i < N_CODERS)
	{
		coders[i].id = i + 1;
		coders[i].start_time = start_time;
 		i++;
	}
}

void	create_coders(pthread_t *threads, t_coder *coders)
{
	int	i;

	i = 0;
	while (i < N_CODERS)
	{
		pthread_create(&threads[i], NULL,
			coder_routing, &coders[i]);
		i++;
	}
}

void	join_coders(pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < N_CODERS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void *coder_routing(void* arg) {
    t_coder *coder =  (t_coder *)arg;
    int i = 0;
    while (i < REQUIRED_COMPILES) {

        printf("%ld %d is compiling\n", get_time_ms() - coder->start_time, coder->id);
        usleep(TIME_TO_COMPILE * 1000);

        printf("%ld %d is debugging\n", get_time_ms() - coder->start_time, coder->id);
        usleep(TIME_TO_DEBUG * 1000);

        printf("%ld %d is refactoring\n", get_time_ms() - coder->start_time, coder->id);
        usleep(TIME_TO_REFACTOR * 1000);

        i++;
    }
    return NULL;
}