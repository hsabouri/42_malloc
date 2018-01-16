/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:58:22 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/16 14:14:48 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_bucket(t_pool *pool, size_t i)
{
	t_bucket *buckets;
	t_bucket tmp;

	buckets = pool->content;
	store(buckets[i].mem, HIST_FREE, buckets[i].size, pool->sbucket);
	buckets[i].size = 0;
	tmp = buckets[i];
	buckets[i] = buckets[pool->last - 1];
	buckets[pool->last - 1] = buckets[i];
	pool->last--;
}

void	del_pool(t_pool *pool, t_pool *before)
{
	if (!before || pool->last > 0)
		return ;
	before->next = pool->next;
	munmap(pool->mem, pool->size);
	munmap(pool->content, sizeof(t_bucket) * pool->nbuckets);
	munmap(pool, sizeof(t_pool));
}

void	del_pool_first(t_pool **lst)
{
	t_pool	*tmp;

	tmp = (*lst)->next;
	munmap((*lst)->mem, (*lst)->size);
	munmap((*lst)->content, sizeof(t_bucket) * (*lst)->nbuckets);
	munmap(*lst, sizeof(t_pool));
	*lst = tmp;
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
			free_bucket(pool, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free(void *ptr)
{
	t_env	*env;
	t_pool	*before;
	t_pool	*pool;

	if (!ptr)
		return ;
	env = ft_getenv();
	before = NULL;
	if (!(pool = search_pool(env, &before, ptr)))
		return ;
	free_ptr(pool, ptr);
	if (pool->last == 0 && before != NULL)
		del_pool(pool, before);
	else if (pool->last == 0 && before == NULL && pool->sbucket > SMALL)
		del_pool_first(&env->large);
}
