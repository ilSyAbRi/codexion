#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define N_CODERS 5
# define TIME_TO_BURNOUT 800
# define TIME_TO_COMPILE 200
# define TIME_TO_DEBUG 200
# define TIME_TO_REFACTOR 200
# define REQUIRED_COMPILES 3
# define DONGLE_COOLDOWN 50

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	long		start_time;
    t_dongle* first_dongle;
    t_dongle* second_dongle;
}	t_coder;

long	get_time_ms(void);

void	init_dongles_data(t_dongle *dongles_data, int count);

void	init_coders_data(t_coder *coder_data,
		t_dongle *dongles_data, long start_time);

void	create_coders(pthread_t *coders, t_coder *coder_data);

void	join_coders(pthread_t *coder);

void	*coder_routing(void *arg);


#endif