/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:10:39 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/16 14:52:08 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		ft_putstr(char const *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

static void	ft_putaddr_after(size_t n, size_t base)
{
	size_t	begin;
	size_t	end;
	char	current;

	end = n % base;
	begin = n / base;
	if (base < 10 || base > 16)
		base = 10;
	if (begin != 0)
		ft_putaddr_after(begin, base);
	if (end < 10)
		current = end + '0';
	else
		current = end - 10 + 'A';
	write(1, &current, 1);
}

void		ft_putaddr(size_t n, size_t base)
{
	if (base == 16)
		ft_putstr("0x");
	ft_putaddr_after(n, base);
}
