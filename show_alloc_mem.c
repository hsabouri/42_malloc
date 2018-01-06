/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:11:08 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/06 17:49:53 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void     putsystox(size_t addr)
{
    char    *sym = "0123456789ABCDEF";

    if (addr)
    {
        putsystox(addr / 16);
        if (!(addr / 16))
            write(1, "0x", 2);
        write(1, &sym[addr % 16], 1);
    }
}

void    show_alloc_mem(void)
{
	
}
