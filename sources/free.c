/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 11:10:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/02 10:30:08 by hsabouri         ###   ########.fr       */
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

void			flush_pool(t_pool **pool)
{
	t_pool	*tmp_pool;

	if ((*pool)->edge == 0)
	{
		ft_putstr("FLUSHING POOL\n");
		tmp_pool = *pool;
		(*pool) = (*pool)->next;
		munmap(tmp_pool,
			tmp_pool->bucketnumber * tmp_pool->bucketsize + sizeof(t_pool));
	}
}

long			get_bucket_position(t_pool *pool, void *ptr)
{
	unsigned int i;

	i = 0;
	ft_putstr("		SEARCHING BUCKET\n");
	while (i <= pool->edge)
	{
		printf("%u ", i);
		if (pool->buckets[i].ptr == ptr && printf("found\n"))
			return (i);
		i++;
	}
	printf("not found\n");
	return (-1);
}

void			*search_and_free(t_pool **pool, void *ptr, int flush)
{
	long		position;
	size_t		relative;
	t_bucket	tmp_bucket;

	if ((*pool) == NULL && printf("		NOT FOUND\n"))
		return (NULL);
	relative = (*pool)->bucketnumber * (*pool)->bucketsize;
	if (ptr >= (*pool)->mem && ptr < (*pool)->mem + relative)
	{
		position = get_bucket_position(*pool, ptr);
		printf("position = %zu | memory displacement = %zu | b_size = %u\n", position, (ptr - (*pool)->mem), (*pool)->buckets[position].size);
		ft_putstr("		FOUND");
		if (position == -1 || (*pool)->buckets[position].size == 0)
		{
			ft_putstr(" BUT INVALID\n");
			return (NULL);
		}
		(*pool)->buckets[position].size = 0;
		printf("		SWAPING %ld and %u (edge)\n", position, (*pool)->edge);
		tmp_bucket = (*pool)->buckets[position];
		(*pool)->buckets[position] = (*pool)->buckets[(*pool)->edge];
		(*pool)->buckets[(*pool)->edge] = tmp_bucket;
		printf("%u ->", (*pool)->edge);
		(*pool)->edge--;
		ft_putstr(" AND FREED\n");
		printf(" %u\n", (*pool)->edge);
		if (flush)
			flush_pool(pool);
		return (ptr);
	}
	ft_putstr("	NEXT POOL\n");
	return (search_and_free(&(*pool)->next, ptr, 1));
}

void			*search_and_free_large(t_large_pool **pool, void *ptr)
{
	t_large_pool	*to_free;

	if (*pool == NULL)
		return (NULL);
	if ((*pool)->mem == ptr)
	{
		to_free = *pool;
		*pool = to_free->next;
		munmap(to_free, sizeof(t_large_pool) + to_free->allocated);
		return (ptr);
	}
	return (search_and_free_large(&((*pool)->next), ptr));
}

void			free(void *ptr)
{
	t_state	*state;

	printf("NEW FREE\n");
	if (ptr == NULL && printf("	NULL POINTER\n"))
		return ;
	state = get_state();
	if (printf("	SEARCHING TINY\n") && search_and_free(&state->tiny, ptr, 0) != NULL)
		return ;
	else if (printf("	SEARCHING SMALL\n") && search_and_free(&state->small, ptr, 0) != NULL)
		return ;
	else if (printf("	SEARCHING LARGE\n") && search_and_free_large(&state->large, ptr) != NULL)
		return ;
	return ;
}
