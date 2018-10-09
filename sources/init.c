/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 13:03:13 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/09 10:01:44 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_state			g_state = (t_state) {NULL, NULL, NULL, {}};

static t_bucket	create_bucket(t_uint bucketsize, void *ptr)
{
	t_bucket res;

	res.size = 0;
	res.max = bucketsize;
	res.ptr = ptr;
	return (res);
}

t_pool			*create_pool(t_uint bucketsize, t_uint bucketnumber)
{
	void	*memory;
	t_pool	*res;
	size_t	i;
	size_t	data_size;

	data_size = sizeof(t_pool);
	if (!(memory = sysalloc(bucketsize * bucketnumber + data_size + ALIGN - 1)))
		return (NULL);
	res = memory;
	res->bucketsize = bucketsize;
	res->bucketnumber = bucketnumber;
	res->edge = 0;
	res->mem = (void *)((size_t)(memory + data_size + ALIGN) & MASK);
	i = 0;
	while (i < bucketnumber)
	{
		res->buckets[i] = create_bucket(bucketsize, i * bucketsize + res->mem);
		i++;
	}
	res->next = NULL;
	return (res);
}

t_large_pool	*create_large_pool(size_t size)
{
	void			*memory;
	size_t			allocated_size;
	t_large_pool	*res;
	size_t			data_size;

	data_size = sizeof(t_large_pool);
	allocated_size = get_alloc_size(size + data_size);
	if (!(memory = sysalloc(size + data_size + ALIGN - 1)))
		return (NULL);
	res = memory;
	res->allocated = allocated_size - data_size;
	res->current = size;
	res->mem = (void *)((size_t)(memory + data_size + ALIGN) & MASK);
	res->next = NULL;
	return (res);
}

t_state			*init_state(void)
{
	g_state.tiny = create_pool(TINY, REGION_S);
	g_state.small = create_pool(SMALL, REGION_S);
	if (pthread_mutex_init(&g_state.mutex, NULL) != 0)
		return (NULL);
	if (g_state.tiny && g_state.small)
		return (&g_state);
	else
		return (NULL);
}

t_state			*get_state(void)
{
	if (g_state.tiny && g_state.small)
		return (&g_state);
	else
		return (init_state());
}
