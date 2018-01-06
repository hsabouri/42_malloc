/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:58:22 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/06 18:37:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_pool	*search_pool(t_pool *lst, t_pool **before, void *ptr)
{
	t_pool	*res;

	res = NULL;
	if (ptr >= lst->mem && ptr < lst->mem + lst->nbuckets * lst->sbucket &&\
	(ptr - lst->mem) % lst->sbucket == 0)
	{
		putstr("Found in one time\n");
		res = lst;
		putsystox((size_t)lst->mem);
		putstr("\n");
	}
	while (lst->next && !res)
	{
		if (ptr >= lst->mem && ptr < lst->mem + lst->nbuckets * lst->sbucket &&\
		(ptr - lst->mem) % lst->sbucket == 0)
		{
			putstr("Found after list exploration\n");
			res = lst;
			putsystox((size_t)lst->mem);
			putstr("\n");
			break ;
		}
		else
		{
			*before = lst;
			lst = lst->next;
		}
	}
	return (res);
}

static t_pool	*search_large(t_pool *lst, t_pool **before, void *ptr)
{
	return (NULL);
}

static void		del_pool(t_pool *pool, t_pool *before)
{

}

static void		free_ptr(t_pool *pool, void *ptr)
{

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
		return ;
		putstr("Not found\n");
	}
	free_ptr(pool, ptr);
	if (pool->last == 0 && before != NULL)
		del_pool(pool, before);
}
