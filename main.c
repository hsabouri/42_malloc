/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:47:17 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/07 18:17:42 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char *strdup(const char *str)
{
	int i = 0;
	char *dst;

	while (str[i])
		i++;
	dst = (char *)malloc(i);
	while (i >= 0)
	{
		dst[i] = str[i];
		i--;
	}
	return (dst);
}

void	putstr(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	write(1, str, i);
}

char	*fillstr(char *dst, char l, size_t size)
{
	size_t i;

	i = 0;
	while (i < size - 1)
	{
		dst[i] = l;
		i++;
	}
	dst[i] = 0;
	return dst;
}

int main(void)
{
	char *test1;
	int i = 0;

	while (i < 10)
	{
		test1 = strdup("Hello");
		i++;
	}
	free(test1);
#ifdef HISTORY
	show_alloc_mem_ex();
#endif
}
