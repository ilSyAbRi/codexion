/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:54:26 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/10 18:54:27 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

t_heap	*init_heap(void)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->size = 0;
	heap->capacity = 2;
	heap->arr = malloc(sizeof(t_request) * heap->capacity);
	if (!heap->arr)
		return (NULL);
	return (heap);
}
