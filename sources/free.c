/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:10:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/02 11:47:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	ft_putstr(char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	write(0, str, len);
}

void			flush_pool(t_pool **pool)
{
	t_pool	*tmp_pool;

	if ((*pool)->edge == 0)
	{
		tmp_pool = *pool;
		(*pool) = (*pool)->next;
		munmap(tmp_pool,
			tmp_pool->bucketnumber * tmp_pool->bucketsize + sizeof(t_pool));
	}
}

long			get_bucket_position(t_pool *pool, void *ptr)
{
	unsigned int i;

	i = 0;
	while (i <= pool->edge)
	{
		if (pool->buckets[i].ptr == ptr)
			return (i);
		i++;
	}
	return (-1);
}

void			*search_and_free(t_pool **pool, void *ptr, int flush)
{
	long		position;
	size_t		relative;
	t_bucket	tmp_bucket;

	if ((*pool) == NULL)
		return (NULL);
	relative = (*pool)->bucketnumber * (*pool)->bucketsize;
	if (ptr >= (*pool)->mem && ptr < (*pool)->mem + relative)
	{
		position = get_bucket_position(*pool, ptr);
		if (position == -1 || (*pool)->buckets[position].size == 0)
		{
			return (NULL);
		}
		(*pool)->buckets[position].size = 0;
		tmp_bucket = (*pool)->buckets[position];
		(*pool)->buckets[position] = (*pool)->buckets[(*pool)->edge];
		(*pool)->buckets[(*pool)->edge] = tmp_bucket;
		(*pool)->edge--;
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

	ft_putstr("SUCCESS FREE");
	if (ptr == NULL)
		return ;
	state = get_state();
	if (search_and_free(&state->tiny, ptr, 0) != NULL)
		return ;
	else if (search_and_free(&state->small, ptr, 0) != NULL)
		return ;
	else if (search_and_free_large(&state->large, ptr) != NULL)
		return ;
	return ;
}
