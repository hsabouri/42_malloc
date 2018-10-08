/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 14:32:51 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/08 16:32:00 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*allocate(t_pool *pool, size_t size)
{
	t_bucket	*to_allocate;

	if (pool->edge == pool->bucketnumber)
	{
		if (!pool->next)
			pool->next = create_pool(pool->bucketsize, pool->bucketnumber);
		return (allocate(pool->next, size));
	}
	to_allocate = pool->buckets + pool->edge;
	to_allocate->size = size;
	pool->edge++;
	return (to_allocate->ptr);
}

void	*allocate_large(t_large_pool **pool, size_t size)
{
	while (*pool != NULL)
		pool = &((*pool)->next);
	*pool = create_large_pool(size);
	return ((*pool)->mem);
}

void	*malloc(size_t size)
{
	t_state	*state;
	void	*res;

	ft_putstr("SUCCESS MALLOC\n");
	if (size == 0)
		return (NULL);
	if ((state = get_state()) == NULL)
		return (NULL);
	pthread_mutex_lock(&state->mutex);
	if (size <= TINY)
	{
		ft_putstr("	TINY\n");
		res = allocate(state->tiny, size);
	}
	else if (size <= SMALL)
	{
		ft_putstr("	SMALL\n");
		res = allocate(state->small, size);
	}
	else
	{
		ft_putstr("	LARGE\n");
		res = allocate_large(&(state->large), size);
	}
	pthread_mutex_unlock(&state->mutex);
	return (res);
}
