/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:10:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/15 16:37:02 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void			flush_pool(t_pool **pool)
{
	t_pool	*tmp_pool;

	if ((*pool)->edge == 0)
	{
		tmp_pool = *pool;
		(*pool) = (*pool)->next;
		munmap(tmp_pool, tmp_pool->bucketnumber *
			tmp_pool->bucketsize + sizeof(t_pool) + ALIGN - 1);
	}
}

void			free_bucket(t_pool *pool, t_uint position)
{
	t_bucket	tmp_bucket;

	pool->buckets[position].allocated = 0;
	memset(pool->mem + pool->buckets[position].index * pool->bucketsize, 0, pool->bucketsize);
	tmp_bucket = pool->buckets[position];
	pool->buckets[position] = pool->buckets[pool->edge - 1];
	pool->buckets[pool->edge - 1] = tmp_bucket;
	pool->edge--;
}

void			*search_and_free(t_pool **pool, void *ptr, int flush)
{
	t_int		position;
	size_t		relative;

	if ((*pool) == NULL)
		return (NULL);
	relative = (*pool)->bucketnumber * (*pool)->bucketsize;
	if (ptr >= (*pool)->mem && ptr < (*pool)->mem + relative)
	{
		position = get_bucket_position(*pool, ptr);
		if (position < 0 || (*pool)->buckets[position].allocated == 0)
			return (NULL);
		free_bucket(*pool, (t_uint)position);
		if (flush)
			flush_pool(pool);
		return (ptr);
	}
	return (search_and_free(&(*pool)->next, ptr, 1));
}

void			*search_and_free_large(t_large_pool **pool, void *ptr)
{
	t_large_pool	*to_free;

	if (*pool == NULL)
		return (NULL);
	if ((*pool)->mem == ptr)
	{
		to_free = *pool;
		*pool = to_free->next;
		munmap(to_free, sizeof(t_large_pool) + to_free->allocated);
		return (ptr);
	}
	return (search_and_free_large(&((*pool)->next), ptr));
}

void			free(void *ptr)
{
	t_state	*state;

	if (ptr == NULL)
		return ;
	if ((state = get_state()) == NULL)
		return ;
	pthread_mutex_lock(&state->mutex);
	if (search_and_free(&state->tiny, ptr, 0) != NULL)
		pthread_mutex_unlock(&state->mutex);
	else if (search_and_free(&state->small, ptr, 0) != NULL)
		pthread_mutex_unlock(&state->mutex);
	else if (search_and_free_large(&state->large, ptr) != NULL)
		pthread_mutex_unlock(&state->mutex);
	else
		pthread_mutex_unlock(&state->mutex);
}
