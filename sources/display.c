/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:43:43 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/08 16:18:20 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_putstr(const char *str)
{
	size_t len = 0;

	while (str[len])
		len++;
	write(1, str, len);
}

void static	putsystoxrec(size_t addr)
{
    char    *sym = "0123456789ABCDEF";

    if (addr)
    {
        putsystoxrec(addr / 16);
        if (!(addr / 16))
            write(1, "0x", 2);
        write(1, &sym[addr % 16], 1);
    }
}

void		ft_putsystox(size_t addr)
{
	if (addr == 0)
		write(1, "0x0", 4);
	else
		putsystoxrec(addr);
}

static void	putnbrrec(size_t n)
{
	char	tmp[1];
	if (n)
	{
		putnbrrec(n / 10);
		tmp[0] = n % 10 + '0';
		write(1, tmp, 1);
	}
}

void		ft_putnbr(size_t n)
{
	if (n == 0)
		write(1, "0", 2);
	else
		putnbrrec(n);
}
