/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:47:17 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/10 14:59:13 by hsabouri         ###   ########.fr       */
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

	test1 = (char *)malloc(10);
	test1 = (char *)realloc(test1, 129);
	ft_putsystox((size_t)test1);
	ft_putstr("\n");
	test1 = (char *)realloc(test1, 456);
	ft_putsystox((size_t)test1);
	ft_putstr("\n");
	test1 = (char *)realloc(test1, 1205);
	ft_putsystox((size_t)test1);
	ft_putstr("\n");
	test1 = (char *)realloc(test1, 129);
	ft_putsystox((size_t)test1);
	ft_putstr("\n");
	test1 = (char *)realloc(test1, 386);
	ft_putsystox((size_t)test1);
	ft_putstr("\n");
	free(test1);

#ifdef HISTORY
	show_alloc_mem_ex();
#endif
}
