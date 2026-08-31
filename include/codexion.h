#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	long		start_time;
	t_dongle	*dongles;
}	t_coder;

long	get_time_ms(void);

void	init_coders(t_coder *coders, long start_time);
void	create_coders(pthread_t *threads, t_coder *coders);
void	join_coders(pthread_t *threads);
void	*coder_routing(void *arg);

#endif