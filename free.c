/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:58:22 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/07 18:24:51 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_pool	*search_pool(t_pool *lst, t_pool **before, void *ptr)
{
	t_pool	*res;

	res = NULL;
	while (!res && lst->next)
	{
		if (ptr >= lst->mem && ptr < lst->mem + lst->size &&\
		(ptr - lst->mem) % lst->sbucket == 0)
		{
			res = lst;
			break;
		}
		*before = lst;
		lst = lst->next;
	}
	if (!res && ptr >= lst->mem && ptr < lst->mem + lst->size &&\
	(ptr - lst->mem) % lst->sbucket == 0)
		res = lst;
	return (res);
}

static t_pool	*search_large(t_pool *lst, t_pool **before, void *ptr)
{
	t_pool	*res;

	res = NULL;
	while (!res && lst->next)
	{
		if (ptr == lst->mem)
		{
			res = lst;
			break;
		}
		*before = lst;
		lst = lst->next;
	}
	if (!res && ptr == lst->mem)
		res = lst;
	return (res);
}

static void		del_pool(t_pool *pool, t_pool *before)
{
	before->next = pool->next;
	munmap(pool, sizeof(pool));
}

static int		free_ptr(t_pool *pool, void *ptr)
{
	t_bucket	*buckets;
	t_bucket	tmp;
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
			buckets[i].size = 0;
			tmp = buckets[i];
			buckets[i] = buckets[pool->last - 1];
			buckets[pool->last - 1] = buckets[i];
			pool->last--;
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

	env = getenv();
	before = NULL;
	pool = search_pool(env->tiny, &before, ptr);
	if (!pool)
		pool = search_pool(env->small, &before, ptr);
	if (!pool)
		pool = search_large(env->large, &before, ptr);
	if (!pool)
	{
		putstr("not found");
		return ;
	}
	free_ptr(pool, ptr);
	if (pool->last == 0 && before != NULL)
		del_pool(pool, before);
}
