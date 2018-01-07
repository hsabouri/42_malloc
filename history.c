/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 12:07:16 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/07 18:24:58 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#ifdef HISTORY

void    store(void *ptr, int type, size_t size)
{
    t_hist **lst;
    t_hist *last;

    lst = &getenv()->hist;
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

void    show_alloc_mem_ex(void)
{
    t_hist  *lst;
	size_t	alloc;

    lst = getenv()->hist;
	alloc = 0;
    while (lst)
    {
		if (lst->type == HIST_ALLOC || lst->type == HIST_FREE)
			alloc += lst->type;
        if (lst->type == HIST_DEL_POOL)
            putstr("\n\n# Pool deletion\n\t");
		else if (lst->type == HIST_NEW_POOL)
            putstr("\n\n# Pool creation\n\t");
        else if (lst->type == HIST_ALLOC)
            putstr("\n\n# Allocation\n\t");
        else if (lst->type == HIST_REALLOC)
            putstr("\n\n# Reallocation\n\t");
        if (lst->type == HIST_FREE)
            putstr("\n\n# Free\n\t");
        putstr("address: ");
        putsystox((size_t)lst->ptr);
        putstr("\n\tsize: ");
        putsystox(lst->size);
        lst = lst->next;
    }
}

#endif
