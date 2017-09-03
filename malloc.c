/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 14:49:14 by hsabouri          #+#    #+#             */
/*   Updated: 2017/09/03 18:20:07 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	pool_size(size_t page_size, size_t bucket_size, size_t buckets)
{
	size_t	perfect_size;

	perfect_size = bucket_size * buckets;
	if (perfect_size % page_size == 0)
		return (perfect_size);
	else
		return (perfect_size + (perfect_size % page_size) / bucket_size);
}

static t_buck	*init_buck(void *ptr)
{
	t_buck	*res;

	res = (t_buck *)mmap(NULL, sizeof(t_buck), MMAP_ARGS);
	res->size = 0;
	res->mem = ptr;
	res->next = NULL;
	return (res);
}

static t_pool	*init_pool(size_t pool_size, size_t bucket_size)
{
	t_pool	*pool;
	t_buck	*cur;
	size_t	i;
	
	pool = (t_pool *)mmap(NULL, sizeof(t_pool), MMAP_ARGS);
	pool->mem = (void *)mmap(NULL, pool_size, MMAP_ARGS);
	pool->size = pool_size;
	pool->first = init_buck(pool->mem);
	pool->next = NULL;
	cur = pool->first;
	pool->last = cur;
	i = 0;
	while (i < pool_size / bucket_size)
	{
		cur->next = init_buck(pool->mem + bucket_size * i);
		cur = cur->next;
		i++;
	}
	cur->next = NULL;
	return (pool);
}

static t_env	init_env(void)
{
	t_env	env;
	size_t	page_size;

	page_size = getpagesize();
	env.tiny_size = pool_size(page_size, TINY, BUCKETS);
	env.small_size = pool_size(page_size, SMALL, BUCKETS);
	env.tiny = init_pool(env.tiny_size, TINY);
	env.small = init_pool(env.small_size, SMALL);
	return (env);
}	

void			*malloc(size_t size)
{
	static t_env	env = (t_env) {0, 0, 0, 0, NULL, NULL, NULL};

	if (env.init == 0)
	{
		env = init_env();
	}
	printf("%s\n", (char *)env.tiny->mem);
	printf("tiny_size: %zu", env.tiny_size);
	printf("%s\n", (char *)env.small->mem);
	printf("small_size: %zu", env.small_size);

	return (NULL);
}
