/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:07:16 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/15 19:09:05 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_hist			*get_last_hist(void)
{
	t_env	*env;

	env = getenv();
	if (!env->hist)
	{
		env->hist = (t_hist *)MMAP(sizeof(t_hist));
		env->last = env->hist;
	}
	else
	{
		env->last->next = (t_hist *)MMAP(sizeof(t_hist));
		env->last = env->last->next;
	}
	return (env->last);
}

void			store(void *ptr, int type, size_t size, size_t rsize)
{
	t_hist *last;

	last = get_last_hist();
	last->type = type;
	last->ptr = ptr;
	last->next = NULL;
	last->size = size;
	last->rsize = rsize;
}

static t_hist	*show_realloc(t_hist *lst)
{
	ft_putstr("\n\n# Reallocation\n\t");
	ft_putstr("from address: ");
	ft_putsystox((size_t)lst->ptr);
	ft_putstr("\n\tfrom size: ");
	ft_putnbr(lst->size);
	while (lst->type != HIST_REALLOC_END && lst)
		lst = lst->next;
	ft_putstr("\n\tto address: ");
	ft_putsystox((size_t)lst->ptr);
	ft_putstr("\n\tto size: ");
	ft_putnbr(lst->size);
	return (lst);
}

static t_hist	*show_other(t_hist *lst)
{
	if (lst->type == HIST_DEL_POOL)
		ft_putstr("\n\n# Pool deletion\n\t");
	else if (lst->type == HIST_NEW_POOL)
		ft_putstr("\n\n# Pool creation\n\t");
	else if (lst->type == HIST_ALLOC)
		ft_putstr("\n\n# Allocation\n\t");
	if (lst->type == HIST_FREE)
		ft_putstr("\n\n# Free\n\t");
	ft_putstr("address: ");
	ft_putsystox((size_t)lst->ptr);
	ft_putstr("\n\tsize: ");
	ft_putnbr(lst->size);
	ft_putstr("\n\treal size: ");
	ft_putnbr(lst->rsize);
	return (lst);
}

void			show_alloc_mem_ex(void)
{
	t_hist	*lst;
	size_t	alloc;

	lst = getenv()->hist;
	alloc = 0;
	while (lst)
	{
		if (lst->type == HIST_ALLOC || lst->type == HIST_FREE)
			alloc += lst->type;
		if (lst->type == HIST_REALLOC_BEGIN)
			lst = show_realloc(lst);
		else
			lst = show_other(lst);
		lst = lst->next;
	}
}
