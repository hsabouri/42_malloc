/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 15:21:09 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/15 11:40:10 by hsabouri         ###   ########.fr       */
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

void	ft_putstr(char const *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	write(1, str, i);
}

long	get_bucket_position(t_pool *pool, void *ptr)
{
	long i;

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

void	ft_putlong(long n)
{
  long	debut;
  long	fin;
  char	current;

  if (n < 0)
    {
      write(1, "-", 1);
      ft_putlong(-n);
    }
  else
    {
      fin = n % 16;
      debut = n / 16;
      if (debut != 0)
		ft_putlong(debut);
		if (fin < 10)
			current = fin + '0';
		else
			current = fin - 10 + 'a';
		write(1, &current, 1);
    }
}