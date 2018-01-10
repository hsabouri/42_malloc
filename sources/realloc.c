/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:22:10 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/08 17:47:40 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*resize_pool(t_pool *pool, size_t size)
{
	size_t memsize;

	memsize = poolsize(size);
	if (!memsize)
		return (NULL);
	if (!(pool->mem = (void *)mmap(pool->mem, memsize, MMAP_ARGS)))
		return (NULL);
	return (pool->mem);
}

size_t	locate_ptr(t_pool *pool, void *ptr)
{
	t_bucket	*buckets;
	size_t		i;

	buckets = pool->content;
	i = 0;
	while (i < pool->last)
	{
		if (ptr == buckets[i].mem)
			return (i);
		i++;
	}
	return (pool->nbuckets + 1);
}

void	*realloc_ptr(t_env *env, void *ptr, t_pool *pool, size_t size)
{
	t_bucket	*buckets;
	void		*new;
	size_t		i;
	
	buckets = pool->content;
	i = locate_ptr(pool, ptr);
	if (buckets[i].mem == ptr)
	{
		if (buckets[i].max >= size)
		{
			buckets[i].size = size;
			return (ptr);
		}
		else if (pool->nbuckets == 1)
			return (resize_pool(pool, size));
		else
		{
			if ((new = malloc(size)))
				return (NULL);
			new = ft_memmove(new, ptr, buckets[i].size);
			free_bucket(pool, i);
			return (new);
		}
	}
}

void	*realloc(void *ptr, size_t size)
{
	t_env	*env;
	t_pool	*pool;
	t_pool	**before;

	if (!ptr)
		return (NULL);
	env = getenv();
	before = NULL;
	if (!(pool = search_pool(env, before, ptr))
		return (NULL);
	return (realloc_ptr);
}
