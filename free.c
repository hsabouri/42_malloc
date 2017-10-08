/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:09:16 by hsabouri          #+#    #+#             */
/*   Updated: 2017/10/08 16:53:58 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	optimize(t_pool *pre, t_pool *pool)
{
	
}

int		freelarge(t_pool *pool, void *ptr)
{
	t_pool *pre;

	while (!(ptr >= pool->mem && ptr < pool->mem + pool->bucks[0].size))
	{
		if (pool->next)
		{
			pool = pool->next;
			pre = pool;
		}
		else
			return (0);
	}
	munmap(ptr, pool->bucks[0].size);
	pre->next = pool->next;
	munmap(pool->bucks, sizeof(bucks));
	munmap(pool, sizeof(pool));
}

int		walker(t_pool *pool, void *ptr, size_t bucketsize)
{
	size_t	position;
	t_pool	*pre;

	while (!(ptr >= pool->mem && ptr < pool->mem + pool->buckets * bucketsize))
	{
		if (pool->next)
			pool = pool->next;
		else
			return (0);
	}
	position = (ptr - pool->mem) / bucketsize;
	pool->bucks[position].size = 0;
	pool->free += 1;
	optimize(pre, pool);
	return (1);
}

void	free(void *ptr)
{
	t_env	*env;

	env = get_env();
	if (ptr)
	{
		if (walker(env->tiny, ptr, TINY))
			return;
		if (walker(env->small, ptr, SMALL))
			return;
		freelarge(env->large, ptr);
	}
	return;
}
