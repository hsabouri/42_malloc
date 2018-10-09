/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:21:09 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/09 17:15:11 by hsabouri         ###   ########.fr       */
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

void	ft_putstr(char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	write(1, str, i);
}

long	get_bucket_position(t_pool *pool, void *ptr)
{
	unsigned int i;

	i = 0;
	while (i <= pool->edge)
	{
		if (pool->buckets[i].index == (pool->mem - ptr) / pool->bucketsize &&
		(pool->mem - ptr) % pool->bucketsize == 0)
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
