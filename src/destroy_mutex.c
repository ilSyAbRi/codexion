/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 00:29:47 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/11 00:29:47 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	destroy_dongles_data(t_dongle *dongles_data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_cond_destroy(&dongles_data[i].cond_dongle);
		pthread_mutex_destroy(&dongles_data[i].mutex_dongle);
		destroy_heap(dongles_data[i].heap);
		i++;
	}
}

void	destroy_heap(t_heap *heap)
{
	if (!heap)
		return ;
	free(heap->arr);
	free(heap);
}

void	destroy_simulation(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->mutex_stop);
	pthread_mutex_destroy(&simulation->deadline_mutex);
	pthread_mutex_destroy(&simulation->finished_mutex);
	pthread_cond_destroy(&simulation->cond);
	pthread_mutex_destroy(&simulation->mutex_print);
}
