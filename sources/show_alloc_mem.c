/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:11:08 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/12 17:13:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_pool	*fill(t_pool *p1, t_pool *p2, t_pool *p3, t_pool **arr)
{
	size_t i;

	i = 0;
	while (p1)
	{
		arr[i] = p1;
		p1 = p1->next;
		i++;
	}
	while (p2)
	{
		arr[i] = p2;
		p2 = p2->next;
		i++;
	}
	while (p3)
	{
		arr[i] = p3;
		p3 = p3->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static t_pool	*sort(t_pool *p1, t_pool *p2, t_pool *p3, t_pool **arr)
{
	t_pool	*current;
	t_pool	*tmp;
	size_t	i;
	size_t	j;

	arr = fill(p1, p2, p3, arr);
	current = arr[0];
	i = 0;
	while (arr[i] != NULL)
	{
		j = i;
		while (arr[j] != NULL)
		{
			if (arr[j]->mem < current->mem)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static size_t	getsize(t_pool *p1, t_pool *p2, t_pool *p3)
{
	size_t	len;

	len = 0;
	while (p1)
	{
		len++;
		p1 = p1->next;
	}
	while (p2)
	{
		len++;
		p2 = p2->next;
	}
	while (p3)
	{
		len++;
		p3 = p3->next;
	}
	return (len);
}

void			show_alloc_mem(void)
{
	t_env		*env;
	t_bucket	*sorted;
	size_t		len;

	env = getenv();
	len = getsize(env->tiny, env->small, env->large);
	sorted = (t_pool **)MMAP(sizeof(t_pool *) * (len + 1));
	sorted = sort(env->tiny, env->small, env->large, sorted);
	display_pools(sorted);
	mmunmap(sorted, sizeof(t_pool *) * len);
}
