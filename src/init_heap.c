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
