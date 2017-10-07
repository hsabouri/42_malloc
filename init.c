/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 15:40:03 by hsabouri          #+#    #+#             */
/*   Updated: 2017/10/01 17:53:45 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_pool			*buildpool(size_t buckets, size_t bucketsize, size_t poolsize)
{
	t_pool	*pool;
	size_t	i;

	write(1, "NEW POOL\n", 9);
	pool = (t_pool *)mmap(NULL, sizeof(t_pool), MMAP_ARGS);
	pool->buckets = buckets;
	pool->mem = (void *)mmap(NULL, poolsize, MMAP_ARGS);
	pool->next = NULL;
	pool->bucks = (t_buck *)mmap(NULL, sizeof(t_buck) * buckets, MMAP_ARGS);
	i = 0;
	while (i < buckets)
	{
		pool->bucks[i].size = 0;
		pool->bucks[i].mem = pool->mem + bucketsize * i;
		i++;
	}
	return (pool);
}

size_t			poolsize(size_t pagesize, size_t buckets, size_t bucketsize)
{
	size_t	perfect;

	perfect = bucketsize * buckets;
	if (perfect % pagesize == 0)
		return (perfect);
	else
		return (perfect + (perfect % pagesize) / bucketsize);
}

static t_env	*set_env(void)
{
	t_env	env;
	t_env	*res;

	env.pagesize = getpagesize();
	env.tinysize = poolsize(env.pagesize, BUCKETS, TINY);
	env.smallsize =	poolsize(env.pagesize, BUCKETS, SMALL);
	env.tiny = buildpool(BUCKETS, TINY, env.tinysize);
	env.small = buildpool(BUCKETS, SMALL, env.smallsize);
	env.large = NULL;
	res = (t_env *)mmap(NULL, sizeof(t_env), MMAP_ARGS);
	*res = env;
	return (res);
}

t_env			*get_env(void)
{
	static t_env	*env = NULL;

	if (!env)
		env = set_env();
	return (env);
}
