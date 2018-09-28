/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:10:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/09/28 16:59:19 by hsabouri         ###   ########.fr       */
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
		return (NULL);
	relative = pool->bucketnumber * pool->bucketsize;
	if (ptr >= pool->mem && ptr < pool->mem + relative)
	{
		position = (ptr - pool->mem) / pool->bucketsize;
		if (position % pool->bucketsize != 0 ||
		pool->buckets[position].size == 0)
			return (NULL);
		pool->buckets[position].size = 0;
		tmp_bucket = pool->buckets[position];
		pool->buckets[position] = pool->buckets[pool->edge];
		pool->buckets[pool->edge] = tmp_bucket;
		pool->edge--;
		return (ptr);
	}
	return (search_and_free(pool->next, ptr, 1));
}

/*
void	*search_and_free_large(t_large_pool **pool, void *ptr)
{
	t_large_pool	*to_free;

	if (*pool == NULL)
		return (NULL);
	if ((*pool)->mem == ptr)
	{
	}
	return (search_and_free_large(&((*pool)->next), ptr));
}
*/

void	free(void *ptr)
{
	t_state	*state;

	if (ptr == NULL)
		return ;
	state = get_state();
	if ((search_and_free(state->tiny, ptr, 0)) != NULL)
		return ;
	if ((search_and_free(state->small, ptr, 0)) != NULL)
		return ;
	//if ((search_and_free_large(state->large, ptr)) != NULL)
	//	return ;
	return ;
}
