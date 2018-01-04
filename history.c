/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:07:16 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/04 14:32:43 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#ifdef HISTORY

void    store(void *ptr, int type, size_t size)
{
    t_hist **lst;
    t_hist *last;

    lst = &getenv()->history;
    if (*lst == NULL)
    {
        *lst = (t_hist *)MMAP(sizeof(t_hist));
        last = *lst;
    }
    else
    {
        last = *lst;
        while (last->next != NULL)
            last = last->next;
        last->next = (t_hist *)MMAP(sizeof(t_hist));
        last = last->next;
    }
    last->type = type;
    last->ptr = ptr;
    last->next = NULL;
    last->size = size;
}

void    malloc_history(void)
{
    t_hist  *lst;

    lst = getenv()->hist;
    while (lst)
    {
        if (lst->type == HIST_MALLOC)
            ft_putstr("\n\n# Malloc allocation\n\t");
        else if (lst->type == HIST_ALLOC)
            ft_putstr("\n\n# Allocation\n\t");
        else if (lst->type == HIST_REALLOC)
            ft_putstr("\n\n# Reallocation\n\t");
        if (lst->type == HIST_REALLOC)
            ft_putstr("\n\n# Free\n\t");
        putsystox((size_t)lst->ptr);
        ft_putstr("\n\t");
        ft_putsize_t(lst->size);
        lst = lst->next;
    }
}

#endif
