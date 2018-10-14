/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 10:34:59 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/14 16:14:15 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*move_allocation(t_pool *pool, void *ptr, size_t size, uint32_t pos)
{
	void	*res;

	if ((res = malloc_locked(size)) == NULL)
		return (NULL);
	res = ft_memmove(res, ptr, size);
	//((char *)res)[size] = 0;
	free_bucket(pool, pos);
	return (res);
}

void	*search_and_realloc(t_pool **pool, void *ptr, size_t size, int flush)
{
	void		*res;
	int64_t		position;
	size_t		relative;

	if ((*pool) == NULL)
		return (NULL);
	relative = (*pool)->bucketnumber * (*pool)->bucketsize;
	if (ptr >= (*pool)->mem && ptr < (*pool)->mem + relative)
	{
		position = get_bucket_position(*pool, ptr);
		if (position < 0 || (*pool)->buckets[position].allocated == 0)
			return (NULL);
		if ((*pool)->bucketsize >= size)
		{
			((char *)ptr)[size] = 0;
			return (ptr);
		}
		res = move_allocation(*pool, ptr, size, (uint32_t)position);
		if (flush)
			flush_pool(pool);
		return (res);
	}
	return (search_and_realloc(&(*pool)->next, ptr, size, 1));
}

void	*search_and_realloc_large(t_large_pool **pool, void *ptr, size_t size)
{
	t_large_pool	*to_realloc;
	void			*res;

	if (*pool == NULL)
		return (NULL);
	if ((*pool)->mem == ptr)
	{
		to_realloc = *pool;
		if (to_realloc->allocated > size)
		{
			((char *)ptr)[size] = 0;
			return (ptr);
		}
		*pool = to_realloc->next;
		if ((res = malloc_locked(size)) == NULL)
			return (NULL);
		ft_memmove(res, ptr, to_realloc->allocated);
		munmap(to_realloc, sizeof(t_large_pool) + to_realloc->allocated + ALIGN - 1);
		return (res);
	}
	return (search_and_realloc_large(&((*pool)->next), ptr, size));
}

void	*realloc(void *ptr, size_t size)
{
	t_state	*state;
	void	*res;

	ft_putstr("REALLOC of size ");
	ft_putlong(size);
	ft_putstr(" addr : ");
	ft_putlong((long)ptr);
	if (ptr == NULL)
		return (malloc(size));
	if ((state = get_state()) == NULL)
		return (NULL);
	pthread_mutex_lock(&state->mutex);
	if ((res = search_and_realloc(&state->tiny, ptr, size, 0)) != NULL)
		pthread_mutex_unlock(&state->mutex);
	else if ((res = search_and_realloc(&state->small, ptr, size, 0)) != NULL)
		pthread_mutex_unlock(&state->mutex);
	else if ((res = search_and_realloc_large(&state->large, ptr, size)) !=
	NULL)
		pthread_mutex_unlock(&state->mutex);
	else
	{
		ft_putstr(" with malloc locked");
		res = malloc_locked(size);
		pthread_mutex_unlock(&state->mutex);
	}
	ft_putstr(" to ");
	ft_putlong((long)res);
	ft_putstr(" with size of ");
	ft_putlong((long)size);
	ft_putstr("\n");
	return (res);
}
