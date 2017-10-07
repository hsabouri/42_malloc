/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 14:49:14 by hsabouri          #+#    #+#             */
/*   Updated: 2017/10/01 19:04:32 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*alloclarge(t_env *env, size_t size)
{
	size_t	finalsize;
	t_pool*	large;
	t_pool* current;

	finalsize = (size % env->pagesize != 0) ?
			((size / env->pagesize) + 1) * env->pagesize : size;
	large = buildpool(1, finalsize, finalsize);

	if (env->large == NULL)
		env->large = large;
	else
	{
		current = env->large;
		while (current->next != NULL)
			current = current->next;
		current->next = large;
	}
	return (large->mem);
}

void	*allocate(t_pool *pool, size_t size, size_t bucketsize)
{
	size_t	i;

	i = 0;
	while (i < pool->buckets)
	{
		if (pool->bucks[i].size == 0)
		{
			pool->bucks[i].size = size;
			return (pool->bucks[i].mem);
		}
		i++;
		if (i == pool->buckets)
		{
			if (pool->next == NULL)
				pool->next = buildpool(pool->buckets, bucketsize,\
					pool->buckets * bucketsize);
			pool = pool->next;
			i = 0;
		}
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	t_env	*env;
	void	*res;

	env = get_env();
	res = NULL;
	if (size <= TINY && size > 0)
		res = allocate(env->tiny, size, TINY);
	else if (size <= SMALL && size > 0)
		res = allocate(env->small, size, SMALL);
	else
		res = alloclarge(env, size);
	return (res);
}
