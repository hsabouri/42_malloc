/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 17:34:07 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/08 18:24:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*forward(int *dst, int *src, size_t size, size_t mod)
{
	size_t	i;
	void	*edst;
	void	*esrc;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	edst = (void *)(dst + i);
	esrc = (void *)(src + i);
	i = 0;
	while (i < mod)
	{
		edst[i] = esrc[i];
		i++;
	}
	return (dst);
}

void	*backward(int *dst, int *src, size_t size, size_t mod)
{
	size_t	i;
	void	*edst;
	void	*esrc;

	edst = (void *)(dst + size * sizeof(int) + i);
	esrc = (void *)(src + size * sizeof(int) + i);
	i = mod - 1;
	while (i >= mod)
	{
		edst[i] = esrc[i];
		i--;
	}
	i = size - 1;
	while (i >= 0)
	{
		dst[i] = src[i];
		i--;
	}
	return (dst);
}

void	*ft_memmove(void *dst, void *src, size_t size)
{
	int		*fsrc;
	int		*fdst;
	size_t	fourth;
	size_t	mod;

	fdst = (int *)dst;
	fsrc = (int *)src;
	fourth = size / sizeof(int);
	mod = size % sizeof(int);
	if (dst < src)
		return (forward(fdst, fsrc, fourth, mod));
	if (dst > src)
		return (backward(fdst, fsrc, fourth, mod));
	return (dst);
}
