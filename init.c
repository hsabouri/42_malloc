/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:49:18 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/04 16:02:28 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_pool  *setpool(size_t nbuckets, size_t sbucket)
{
    t_pool  *pool;
    size_t  i;
    
    pool = (t_pool *)MMAP(sizeof(t_pool));
    pool->next = NULL;
    pool->content = (t_bucket *)MMAP(sizeof(t_bucket) * nbuckets);
    pool->last = 0;
    pool->nbuckets = nbuckets;
    pool->sbucket = sbucket;
    pool->mem = (void *)MMAP(sbucket * nbuckets);
    i = 0;
    while (i < nbuckets)
    {
        pool->content[i].mem = pool->mem + i * sbucket;
        pool->content[i].size = 0;
        pool->content[i].max = sbucket;
        i++;
    }
    return (pool);
}

size_t  poolsize(size_t sbucket)
{
    size_t perfect;
    size_t pagesize;
    
    pagesize = getpagesize();
    perfect = sbucket * BUCKETS;
    if (perfect % pagesize == 0)
        return (perfect);
    else
        return (perfect + (perfect % pagesize) / sbucket);
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
