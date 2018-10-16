/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 14:32:51 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/16 11:45:29 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static void	*allocate(t_pool *pool, size_t size)
{
	t_bucket	*to_allocate;

	if (pool->edge == pool->bucketnumber)
	{
		if (!pool->next)
			pool->next = create_pool(pool->bucketsize, pool->bucketnumber);
		return (allocate(pool->next, size));
	}
	to_allocate = pool->buckets + pool->edge;
	to_allocate->allocated = 1;
	to_allocate->size = size;
	((char *)(pool->mem + to_allocate->index * pool->bucketsize))[size] = 0;
	pool->edge++;
	return (to_allocate->index * pool->bucketsize + pool->mem);
}

static void	*allocate_large(t_large_pool **pool, size_t size)
{
	while (*pool != NULL)
		pool = &((*pool)->next);
	*pool = create_large_pool(size);
	return ((*pool)->mem);
}

void		*malloc_locked(size_t size)
{
	t_state	*state;
	void	*res;

	if (size == 0)
		size = 1;
	if ((state = get_state()) == NULL)
		return (NULL);
	if (size < TINY)
	{
		if (!state->tiny)
			state->tiny = create_pool(TINY, REGION_S);
		res = allocate(state->tiny, size);
	}
	else if (size < SMALL)
	{
		if (!state->small)
			state->small = create_pool(SMALL, REGION_S);
		res = allocate(state->small, size);
	}
	else
		res = allocate_large(&(state->large), size);
	return (res);
}

void		*malloc(size_t size)
{
	t_state	*state;
	void	*res;

	if (size == 0)
		size = 1;
	if ((state = get_state()) == NULL)
		return (NULL);
	pthread_mutex_lock(&state->mutex);
	if (size < TINY)
	{
		if (!state->tiny)
			state->tiny = create_pool(TINY, REGION_S);
		res = allocate(state->tiny, size);
	}
	else if (size < SMALL)
	{
		if (!state->small)
			state->small = create_pool(SMALL, REGION_S);
		res = allocate(state->small, size);
	}
	else
		res = allocate_large(&(state->large), size);
	pthread_mutex_unlock(&state->mutex);
	return (res);
}
