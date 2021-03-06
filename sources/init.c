/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 13:03:13 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/16 16:17:25 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_state			g_state = (t_state) {NULL, NULL,\
	NULL, PTHREAD_MUTEX_INITIALIZER};

static t_bucket	create_bucket(t_uint index)
{
	t_bucket res;

	res.index = index;
	res.allocated = 0;
	res.size = 0;
	return (res);
}

t_pool			*create_pool(t_uint bucketsize, t_uint bucketnumber)
{
	void		*memory;
	t_pool		*res;
	t_uint		i;
	size_t		data_size;

	data_size = sizeof(t_pool);
	if (!(memory = sysalloc(bucketsize * bucketnumber + data_size + ALIGN - 1)))
		return (NULL);
	res = memory;
	res->bucketsize = bucketsize;
	res->bucketnumber = bucketnumber;
	res->edge = 0;
	res->mem = (void *)((uintptr_t)(memory + data_size + ALIGN) & MASK);
	i = 0;
	while (i < bucketnumber)
	{
		res->buckets[i] = create_bucket(i);
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
	allocated_size = get_alloc_size(size + data_size + ALIGN - 1);
	if (!(memory = sysalloc(size + data_size + ALIGN - 1)))
		return (NULL);
	res = memory;
	res->allocated = allocated_size - data_size - ALIGN + 1;
	res->mem = (void *)((size_t)(memory + data_size + ALIGN) & MASK);
	((char *)res->mem)[size] = 0;
	res->next = NULL;
	return (res);
}

t_state			*init_state(void)
{
	if (pthread_mutex_init(&g_state.mutex, NULL) != 0)
		return (NULL);
	return (&g_state);
}

t_state			*get_state(void)
{
	if (g_state.tiny && g_state.small)
		return (&g_state);
	else
		return (init_state());
}
