/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:49:18 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/06 18:32:21 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_pool  *setpool(size_t memsize, size_t sbucket)
{
    t_pool  *pool;
    size_t  i;
    
    pool = (t_pool *)MMAP(sizeof(t_pool));
    pool->next = NULL;
    pool->content = (t_bucket *)MMAP(sizeof(t_bucket) * BUCKETS);
    pool->last = 0;
	pool->size = memsize;
    pool->nbuckets = BUCKETS;
    pool->sbucket = sbucket;
    pool->mem = (void *)MMAP(memsize);
    i = 0;
    while (i < BUCKETS)
    {
        pool->content[i].mem = pool->mem + i * sbucket;
        pool->content[i].size = 0;
        pool->content[i].max = sbucket;
        i++;
    }
#ifdef HISTORY
	store(pool->mem, 2, memsize);
#endif
	putstr("NEW POOL\n");
    return (pool);
}

size_t  poolsize(size_t sbucket)
{
	size_t overflow;

	overflow = sbucket * BUCKETS % getpagesize();
	if (overflow == 0)
		return (sbucket * BUCKETS);
	else
		return (sbucket * BUCKETS + getpagesize() * (overflow / getpagesize() + 1));
}

t_env   *setenv(void)
{
    t_env   *env;

    env = (t_env *)MMAP(sizeof(t_env));
    env->stiny = poolsize(TINY);
    env->ssmall = poolsize(SMALL);
    env->tiny = setpool(env->stiny, TINY);
    env->small = setpool(env->ssmall, SMALL);
    env->large = NULL;
    return (env);
}

t_env   *getenv(void)
{
    static t_env    *env = NULL;

    if (!env)
        env = setenv();
    return (env);
}
