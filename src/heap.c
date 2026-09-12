/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:54:10 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/11 23:08:41 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	is_less(t_request request_1, t_request request_2)
{
	if (request_1.value != request_2.value)
		return (request_1.value < request_2.value);
	if (request_1.id % 2 != request_2.id % 2)
		return (request_1.id % 2 != 0);
	return (request_1.id < request_2.id);
}

void	heap_down(t_heap *heap)
{
	t_request	temp;
	int			left_child;
	int			right_child;
	int			i;
	int			smallest;

	i = 0;
	smallest = i;
	while (i < heap->size)
	{
		left_child = i * 2 + 1;
		right_child = i * 2 + 2;
		if (left_child < heap->size
			&& is_less(heap->arr[left_child], heap->arr[smallest]))
			smallest = left_child;
		if (right_child < heap->size
			&& is_less(heap->arr[right_child], heap->arr[smallest]))
			smallest = right_child;
		if (smallest == i)
			break ;
		temp = heap->arr[i];
		heap->arr[i] = heap->arr[smallest];
		heap->arr[smallest] = temp;
		i = smallest;
	}
}

void	heapfy_up(t_heap *heap)
{
	t_request	temp;
	int			last_element;
	int			parent;

	last_element = heap->size - 1;
	parent = (last_element - 1) / 2;
	while (last_element > 0
		&& is_less(heap->arr[last_element], heap->arr[parent]))
	{
		temp = heap->arr[last_element];
		heap->arr[last_element] = heap->arr[parent];
		heap->arr[parent] = temp;
		last_element = parent;
		parent = (last_element - 1) / 2;
	}
}

int	heap_pop(t_heap *heap)
{
	int	root;

	if (heap->size == 0)
		return (-1);
	root = heap->arr[0].id;
	heap->arr[0] = heap->arr[heap->size - 1];
	heap->size -= 1;
	heap_down(heap);
	return (root);
}

void	heap_push(t_heap *heap, t_request request)
{
	if (heap->size >= heap->capacity)
		return ;
	heap->arr[heap->size] = request;
	heap->size += 1;
	heapfy_up(heap);
}
