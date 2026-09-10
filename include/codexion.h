/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:55:43 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/11 00:01:07 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>


typedef struct s_request
{
	long	value;
	int		id;
}	t_request;

typedef struct s_heap
{
	int			size;
	int			capacity;
	t_request	*arr;
}	t_heap;

typedef struct s_config
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compile_required;
	int		dongle_cooldown;
	int		scheduler;
	long	start_time;
	pthread_mutex_t nb_requred_compile_mutex;
}	t_config;

typedef struct s_simulation
{
	int				stop;
	int				finished_coders;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	deadline_mutex;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex_print;
}	t_simulation;

typedef struct s_dongle
{
	int				id;
	int				owner;
	long			cooldown_deadline;
	t_heap			*heap;
	pthread_mutex_t	mutex_dongle;
	pthread_cond_t	cond_dongle;
}	t_dongle;

typedef enum s_task
{
	COMPILE,
	DEBUG,
	REFACTOR,
	BURNOUT,
}	t_task;

typedef struct s_coder
{
	int				id;
	long			start_time;
	long			burnout_deadline;
	int				n_compiles;
	t_dongle		*first_dongle;
	t_dongle		*second_dongle;
	t_simulation	*simulation;
	t_config		*config;
	pthread_mutex_t	mutex_sleep;
}	t_coder;

long	get_time_ms(void);

void	init_dongles_data(t_dongle *dongles_data, int count);

void	init_coders_data(t_coder *coder_data,
			t_dongle *dongles_data, t_simulation *simulation,
			t_config *config);
void	init_simulation(t_simulation *simulation);

void	create_coders(pthread_t *coders, t_coder *coder_data);

void	join_coders(pthread_t *coder, t_coder *coder_data, t_config *config);

void	*coder_routing(void *arg);

void	push_request(t_coder *coder_data, t_dongle *dongle);
int		take_dongles(t_coder *coder_data);
void	release_dongles(t_coder *coder);

void	create_monitor(pthread_t *monitor, t_coder *coder_data);
void	join_monitor(pthread_t monitor);
void	*monitor_routine(void *arg);

void	stop_simulation(t_coder *coder_data, t_simulation *simulation);
int		simulation_stopped(t_simulation *simulation);
long	protect_get_burnout_deadline(t_coder *coder_data);
void	protect_reset_burnout_deadline(t_coder *coder_data);
void	coder_finished(t_simulation *simulation);
int		stop_monitor_all_coder_finished(t_simulation *simulation,
			t_config *config);
int		is_valid_number(char **argv);
int		check_number(char *str);
int		check_atoi_helper(char *argv);
int		check_atoi(char **argv);
int		check_scheduler(char *str);
int		store_data(char **argv, t_config *config);
int		parse_args(int argc, char **argv, t_config *config);
int		thread_sleep(t_coder *coder_data, long time);

int		coder_phase(t_coder *coder_data, long time, t_task task);
void	log_burnout(t_coder *coders_data, int burned_coder);

t_heap	*init_heap(void);
void	heap_push(t_heap *heap, t_request request);
int		heap_pop(t_heap *heap);

void	destroy_simulation(t_simulation *simulation);
void	destroy_dongles_data(t_dongle *dongles_data, int count);
void	destroy_heap(t_heap *heap);

#endif