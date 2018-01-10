/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:22:10 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/10 16:23:08 by hsabouri         ###   ########.fr       */
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

	i = 0;
	buckets = pool->content;
	while (i < pool->last)
	{
		if (ptr == buckets[i].mem)
			return (i);
		i++;
	}
	return (pool->nbuckets + 1);
}

void	*realloc_ptr(void *ptr, t_pool *pool, size_t size, size_t pos)
{
	t_bucket	*buckets;
	void		*new;
	
	buckets = pool->content;
	if (buckets[pos].mem == ptr)
	{
		if (buckets[pos].max >= size)
		{
			buckets[pos].size = size;
			return (ptr);
		}
		else if (pool->nbuckets == 1)
			return (resize_pool(pool, size));
		else
		{
			if (!(new = malloc(size)))
				return (NULL);
			new = ft_memmove(new, ptr, buckets[pos].size);
			free_bucket(pool, pos, ptr);
			return (new);
		}
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	t_env	*env;
	t_pool	*pool;
	t_pool	**before;
	size_t	pos;
	void	*res;

	if (!ptr)
		return (NULL);
	env = getenv();
	before = NULL;
	if (!(pool = search_pool(env, before, ptr)))
		return (NULL);
	pos = locate_ptr(pool, ptr);
#ifdef HISTORY
	store(ptr, HIST_REALLOC_BEGIN, pool->content[pos].size);
#endif
	res = realloc_ptr(ptr, pool, size, pos);
#ifdef HISTORY
	store(res, HIST_REALLOC_END, size);
#endif
	return (res);
}
