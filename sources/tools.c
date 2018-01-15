/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:36:04 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/10 14:48:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*csrc;
	unsigned char	*cdst;
	size_t			i;

	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	if (!len)
		return (dst);
	if (dst > src)
	{
		i = len - 1;
		while (i > 0)
		{
			cdst[i] = csrc[i];
			i--;
		}
		cdst[0] = csrc[0];
		return (dst);
	}
	i = 0;
	while (i < len && i++)
		cdst[i - 1] = csrc[i - 1];
	return (dst);
}
