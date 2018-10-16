/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 13:29:33 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/16 15:29:36 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static t_pool		*display_pool(t_pool *pool, size_t *total, const char *name)
{
	t_uint	index;

	ft_putstr(name);
	ft_putaddr((size_t)pool->mem, 16);
	ft_putstr("\n");
	index = 0;
	while (index < pool->edge)
	{
		ft_putstr("	");
		ft_putaddr((size_t)pool->mem + pool->bucketsize * index, 16);
		ft_putstr(" - ");
		ft_putaddr((size_t)pool->mem + index * pool->bucketsize +\
			pool->buckets[index].size, 16);
		ft_putstr(" : ");
		ft_putaddr((size_t)pool->buckets[index].size, 10);
		ft_putstr(" octets\n");
		*total += pool->buckets[index].size;
		index++;
	}
	return (pool->next);
}

static t_large_pool	*display_large_pool(t_large_pool *pool,\
size_t *total, const char *name)
{
	ft_putstr(name);
	ft_putaddr((size_t)pool->mem, 16);
	ft_putstr(" - ");
	ft_putaddr((size_t)pool->mem + pool->allocated, 16);
	ft_putstr(" : ");
	ft_putaddr((size_t)pool->allocated, 10);
	ft_putstr(" octets\n");
	*total += pool->allocated;
	return (pool->next);
}

void				show_alloc_mem(void)
{
	size_t			total;
	t_pool			*current;
	t_large_pool	*lcurrent;
	t_state			*state;

	if ((state = get_state()) == NULL)
		return ;
	ft_putstr(">>>> SHOW ALLOC MEM 2000 >>>>\n");
	total = 0;
	current = state->tiny;
	while (current != NULL)
		current = display_pool(current, &total, "TINY : ");
	current = state->small;
	while (current != NULL)
		current = display_pool(current, &total, "SMALL : ");
	lcurrent = state->large;
	while (lcurrent != NULL)
		lcurrent = display_large_pool(lcurrent, &total, "LARGE : ");
	ft_putstr("Total : ");
	ft_putaddr(total, 10);
	ft_putstr(" octets\n");
}
