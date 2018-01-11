/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:11:08 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/11 14:26:53 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_pool	*search_first(t_pool *pool, t_pool *current, t_pool *last)
{
	if (!pool)
		return (current);
	if (!current)
		current = pool;
	while (pool)
	{
		if (pool->mem < current->mem && (!last || pool->mem >= last->mem))
			current = pool;
		pool = pool->next;
	}
	return (current);
}

size_t			display_pool(t_pool *pool)
{
	size_t i;
	size_t total;

	if (pool->sbucket == TINY)
		ft_putstr("TINY : ");
	else if (pool->sbucket == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_putsystox((size_t)pool->mem);
	ft_putstr("\n");
	total = 0;
	i = 0;
	while (i < pool->last)
	{
		ft_putsystox((size_t)pool->content[i].mem);
		ft_putstr(" - ");
		ft_putsystox((size_t)pool->content[i].mem);
		ft_putstr(" : ");
		ft_putnbr(pool->content[i].size);
		ft_putstr(((pool->content[i].size == 1) ? " octet\n" : " octets\n"));
		total += pool->content[i].size;
		i++;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	t_env		*env;
	t_pool		*pool;
	t_pool		*last;
	size_t		total;

	env = getenv();
	last = NULL;
	total = 0;
	ft_putsystox((size_t)env->tiny);
	ft_putsystox((size_t)env->small);
	ft_putsystox((size_t)env->large);
	pool = search_first(env->tiny, NULL, last);
	pool = search_first(env->small, pool, last);
	pool = search_first(env->large, pool, last);
	total += display_pool(pool);
	last = pool;
	while (last)
	{
		pool = search_first(env->tiny, NULL, last);
		pool = search_first(env->small, pool, last);
		pool = search_first(env->large, pool, last);
		if (pool == last || !pool)
			break;
		if (pool->last > 0)
			total += display_pool(pool);
		last = pool;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(((total == 1) ? " octet\n" : " octets\n"));
}
