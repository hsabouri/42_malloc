/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:11:08 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/04 14:23:57 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void     putsystox(size_t addr)
{
    char    *sym = "0123456789ABCDEF";
    size_t  i = 7;

    if (addr)
    {
        putsystox(addr / 16);
        if (!(addr / 16))
            write(0, "0x", 2);
        write(0, &sym[addr % 16], 1);
    }
}

void    show_alloc_mem(void)
{

}
