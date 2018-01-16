/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 13:45:58 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/16 14:09:39 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		bucket_content(t_pool *pool)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	while (i < pool->last)
	{
		ft_putstr("\t");
		ft_putsystox((size_t)pool->content[i].mem);
		ft_putstr(" - ");
		ft_putsystox((size_t)pool->content[i].mem + pool->content[i].size);
		ft_putstr(" : ");
		ft_putnbr(pool->content[i].size);
		ft_putstr((pool->content[i].size > 1) ? " octets\n" : " octet\n");
		total += pool->content[i].size;
		i++;
	}
	return (total);
}

void		total_footer(size_t total)
{
	if (total)
	{
		ft_putstr("Total : ");
		ft_putnbr(total);
		ft_putstr("\n");
	}
}

void		size_header(t_pool *pool)
{
	if (pool->sbucket == TINY)
		ft_putstr("TINY : ");
	else if (pool->sbucket == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_putsystox((size_t)pool->mem);
	ft_putstr("\n");
}
