/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:06:31 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/12 10:49:47 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_pool	*search_normal(t_pool *lst, t_pool **before, void *ptr)
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

t_pool	*search_large(t_pool *lst, t_pool **before, void *ptr)
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

t_pool	*search_pool(t_env *env, t_pool **before, void *ptr)
{
	t_pool *res;

	res = search_normal(env->tiny, before, ptr);
	if (!res)
		res = search_normal(env->small, before, ptr);
	if (!res)
		res = search_large(env->large, before, ptr);
	return (res);
}
