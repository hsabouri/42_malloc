/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:10:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/09/30 15:34:10 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	ft_putstr(char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	write(0, str, len);
}

void	*search_and_free(t_pool *pool, void *ptr, int flush)
{
	size_t		position;
	size_t		relative;
	t_bucket	tmp_bucket;

	if (pool == NULL)
	{
		ft_putstr("		NOT FOUND\n");
		return (NULL);
	}
	relative = pool->bucketnumber * pool->bucketsize;
	if (ptr >= pool->mem && ptr < pool->mem + relative)
	{
		ft_putstr("	FOUND");
		position = (ptr - pool->mem) / pool->bucketsize;
		if ((ptr - pool->mem) % pool->bucketsize != 0 ||
		pool->buckets[position].size == 0)
		{
			ft_putstr(" BUT INVALID\n");
			return (NULL);
		}
		pool->buckets[position].size = 0;
		tmp_bucket = pool->buckets[position];
		pool->buckets[position] = pool->buckets[pool->edge];
		pool->buckets[pool->edge] = tmp_bucket;
		pool->edge--;
		return (ptr);
	}
	ft_putstr("		NEXT POOL\n");
	return (search_and_free(pool->next, ptr, 1));
}

void	*search_and_free_large(t_large_pool **pool, void *ptr)
{
	t_large_pool	*to_free;

	if (*pool == NULL)
	{
		ft_putstr("		NOT FOUND !\n");
		return (NULL);
	}
	if ((*pool)->mem == ptr)
	{
		ft_putstr("	FOUND");
		to_free = *pool;
		*pool = to_free->next;
		munmap(to_free, sizeof(t_large_pool) + to_free->allocated);
		return (ptr);
	}
	ft_putstr("		NEXT POOL !\n");
	return (search_and_free_large(&((*pool)->next), ptr));
}

void	free(void *ptr)
{
	t_state	*state;

	ft_putstr("NEW FREE\n");
	if (ptr == NULL)
	{
		ft_putstr("	NULL POINTER\n");
		return ;
	}
	state = get_state();
	if (search_and_free(state->tiny, ptr, 0) != NULL)
	{		
		ft_putstr(" TINY !\n");
		return ;
	}
	else if (search_and_free(state->small, ptr, 0) != NULL)
	{		
		ft_putstr(" SMALL !\n");
		return ;
	}
	else if (search_and_free_large(&state->large, ptr) != NULL)
	{		
		ft_putstr(" LARGE !\n");
		return ;
	}
	ft_putstr("	NOT FOUND\n");
	return ;
}
