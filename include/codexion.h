#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define N_CODERS 5
# define TIME_TO_BURNOUT 10000
# define TIME_TO_COMPILE 200
# define TIME_TO_DEBUG 200
# define TIME_TO_REFACTOR 200
# define REQUIRED_COMPILES 3
# define DONGLE_COOLDOWN 50

typedef struct s_simulation
{
	int	stop;
	int				finished_coders;
	pthread_mutex_t finished_mutex;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	deadline_mutex;
}	t_simulation;

typedef struct s_dongle
{
	int id;
	pthread_mutex_t	mutex_dongle;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	long		start_time;
	long		burnout_deadline;
    t_dongle* first_dongle;
    t_dongle* second_dongle;
	t_simulation	*simulation;
}	t_coder;



long	get_time_ms(void);

void	init_dongles_data(t_dongle *dongles_data, int count);

void	init_coders_data(t_coder *coder_data,
		t_dongle *dongles_data, long start_time,
		t_simulation *simulation);
void	init_simulation(t_simulation *simulation);

void	create_coders(pthread_t *coders, t_coder *coder_data);

void	join_coders(pthread_t *coder);

void	*coder_routing(void *arg);

void    take_dongles(t_coder *coder);
void    release_dongles(t_coder *coder);

void	create_monitor(pthread_t *monitor, t_coder *coder_data);
void	join_monitor(pthread_t monitor);
void	*monitor_routine(void *arg);

void	stop_simulation(t_simulation *simulation);
int		simulation_stopped(t_simulation *simulation);
long protect_get_burnout_deadline(t_coder *coder_data);
void protect_reset_burnout_deadline(t_coder *coder_data);
void	coder_finished(t_simulation *simulation);
int stop_monitor_all_coder_finished(t_simulation *simulation);


#endif