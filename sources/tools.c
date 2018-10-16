/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:21:09 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/16 16:09:23 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t	get_alloc_size(size_t size)
{
	const size_t	pagesize = getpagesize();

	if (size % pagesize == 0)
		return (size);
	else
		return ((size / pagesize) * pagesize + pagesize);
}

t_int	get_bucket_position(t_pool *pool, void *ptr)
{
	t_int i;

	if ((ptr - pool->mem) % pool->bucketsize != 0)
		return (-1);
	i = 0;
	while (i <= pool->edge)
	{
		if (pool->buckets[i].index == (ptr - pool->mem) / pool->bucketsize)
			return (i);
		i++;
	}
	return (-1);
}

void	*sysalloc(size_t size)
{
	struct rlimit	limits;
	void			*res;

	getrlimit(RLIMIT_AS, &limits);
	if (size > limits.rlim_cur)
		return (NULL);
	res = mmap(NULL, get_alloc_size(size), ARGS);
	if (!res || res == (void *)(-1))
		return (NULL);
	else
		return (res);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t index;

	if (src > dst)
	{
		index = 0;
		while (index < len)
		{
			((char *)dst)[index] = ((char *)src)[index];
			index++;
		}
	}
	else if (src < dst)
	{
		index = len;
		while (index > 0)
		{
			index--;
			((char *)dst)[index] = ((char *)src)[index];
		}
	}
	return (dst);
}
