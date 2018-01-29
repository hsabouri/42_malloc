/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:22:10 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/29 17:33:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*resize_pool(t_pool *pool, size_t size, t_bucket *bucket)
{
	size_t	rsize;
	void	*tmp;
	void	*res;

	res = pool->mem;
	if (size > pool->size)
	{
		rsize = ft_poolsize(size);
		tmp = pool->mem;
		pool->mem = MMAP(rsize);
		pool->mem = ft_memmove(pool->mem, tmp, pool->size);
		munmap(tmp, pool->size);
		pool->size = rsize;
		pool->sbucket = size;
		bucket->max = rsize;
		bucket->size = size;
		bucket->mem = pool->mem;
		res = pool->mem;
	}
	return (res);
}

static void	*realloc_bucket(t_pool *pool, t_pool **before, size_t i, size_t size)
{
	void		*res;
	t_bucket	*bucket;

	bucket = pool->content + i;
	res = bucket->mem;
	if (size <= bucket->max)
		bucket->size = size;
	else if (size > SMALL && size > pool->size)
		res = resize_pool(pool, size, bucket);
	else if (size > SMALL)
	{
		pool->sbucket = size;
		bucket->max = size;
		bucket->size = size;
		res = pool->mem;
	}
	else if (size > pool->sbucket)
	{
		if (!(res = malloc(size)))
			return (NULL);
		res = ft_memmove(res, bucket->mem, bucket->size);
		ft_free_bucket(pool, i);
		ft_del_pool(pool, *before);
	}
	return (res);
}

void	*realloc(void *ptr, size_t size)
{
	t_env	*env;
	t_pool	*pool;
	t_pool	*before;
	size_t	bucket;
	void	*res;

	ft_putstr("realloc\n");
	if (!ptr || !size)
		return (NULL);
	env = ft_getenv();
	before = NULL;
	if (!(pool = ft_search_pool(env, &before, ptr)))
		return (NULL);
	bucket = ft_search_bucket(pool, ptr);
	ft_store(ptr, HIST_REALLOC_BEGIN, pool->content[bucket].size,\
			pool->content[bucket].max);
	res = realloc_bucket(pool, &before, bucket, size);
	ft_store(res, HIST_REALLOC_END, size, size);
	return (res);
}
