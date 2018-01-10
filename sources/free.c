/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:58:22 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/08 16:16:59 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free_bucket(t_pool *pool, size_t i)
{
	t_bucket *buckets;
	t_bucket tmp;

	buckets = pool->content;
	buckets[i].size = 0;
	tmp = buckets[i];
	buckets[i] = buckets[pool->last - 1];
	buckets[pool->last - 1] = buckets[i];
	pool->last--;
}

void		del_pool(t_pool *pool, t_pool *before)
{
#ifdef HISTORY
	store(pool->mem, HIST_DEL_POOL, pool->size);
#endif
	before->next = pool->next;
	munmap(pool, sizeof(pool));
}

int		free_ptr(t_pool *pool, void *ptr)
{
	t_bucket	*buckets;
	size_t		i;

	i = 0;
	buckets = pool->content;
	while (i < pool->last)
	{
		if (buckets[i].mem == ptr)
		{
#ifdef HISTORY
			store(ptr, HIST_FREE, buckets[i].size);
#endif
			free_bucket(pool, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void			free(void *ptr)
{
	t_env	*env;
	t_pool	*before;
	t_pool	*pool;

	if (!ptr)
		return;
	env = getenv();
	before = NULL;
	if (!(pool = search_pool(env, &before, ptr)))
		return ;
	free_ptr(pool, ptr);
	if (pool->last == 0 && before != NULL)
		del_pool(pool, before);
}
