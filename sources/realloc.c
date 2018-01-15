/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:22:10 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/15 15:26:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*resize_pool(t_pool *pool, size_t size, t_bucket *bucket)
{
	size_t	rsize;
	void	*tmp;
	void	*res;

	res = pool->mem;
	if (size > pool->size)
	{
		rsize = poolsize(size);
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

void	*realloc_bucket(t_pool *pool, t_pool **before, size_t i, size_t size)
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
		free_bucket(pool, i);
		del_pool(pool, *before);
	}
	return (res);
}

void	*realloc(void *ptr, size_t size)
{
	t_env 	*env;
	t_pool	*pool;
	t_pool	*before;
	size_t	bucket;
	void	*res;

	if (!ptr || !size)
		return (NULL);
	env = getenv();
	before = NULL;
	if (!(pool = search_pool(env, &before, ptr)))
		return (NULL);
	bucket = search_bucket(pool, ptr);
	res = realloc_bucket(pool, &before, bucket, size);
	return (res);
}
