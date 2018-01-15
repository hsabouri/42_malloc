/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:06:31 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/15 17:29:07 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		search_bucket(t_pool *pool, void *ptr)
{
	size_t		res;

	res = 0;
	while (res < pool->last && ptr != pool->content[res].mem)
		res++;
	return (res);
}

t_pool		*search_normal(t_pool *lst, t_pool **before, void *ptr)
{
	t_pool	*res;
	int		is_first;

	res = NULL;
	is_first = 1;
	while (!res && lst->next)
	{
		if (ptr >= lst->mem && ptr < lst->mem + lst->size &&\
		(ptr - lst->mem) % lst->sbucket == 0)
		{
			res = lst;
			break ;
		}
		if (is_first)
			is_first = 0;
		else
			*before = lst;
		lst = lst->next;
	}
	if (!res && ptr >= lst->mem && ptr < lst->mem + lst->size &&\
	(ptr - lst->mem) % lst->sbucket == 0)
		res = lst;
	return (res);
}

t_pool		*search_large(t_pool *lst, t_pool **before, void *ptr)
{
	t_pool	*res;

	res = NULL;
	while (!res && lst->next)
	{
		if (ptr == lst->mem)
		{
			res = lst;
			break ;
		}
		*before = lst;
		lst = lst->next;
	}
	if (!res && ptr == lst->mem)
		res = lst;
	return (res);
}

t_pool		*search_pool(t_env *env, t_pool **before, void *ptr)
{
	t_pool	*res;
	t_pool	*tbefore;

	tbefore = NULL;
	res = search_normal(env->tiny, &tbefore, ptr);
	if (!res)
		res = search_normal(env->small, &tbefore, ptr);
	if (!res)
		res = search_large(env->large, &tbefore, ptr);
	if (res)
		*before = tbefore;
	return (res);
}
