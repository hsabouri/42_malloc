/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:31:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/09 17:11:33 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>

# include <string.h>

# define TINY 16
# define SMALL 32
# define REGION_S 512

# define ALIGN 16
# define MASK ~(uintptr_t)(ALIGN - 1)

# define ARGS 0x01|0x02,0x1000|0x0002,-1,0
# define MIN(a,b) ((a >= b) ? (b) : (a))

typedef struct		s_bucket
{
	char			allocated;
	uint32_t		index;
}					t_bucket;

typedef struct		s_pool
{
	struct s_pool	*next;
	uint32_t		bucketsize;
	uint32_t		bucketnumber;
	uint32_t		edge;
	void			*mem;
	t_bucket		buckets[REGION_S];
}					t_pool;

typedef struct		s_large_pool
{
	struct s_large_pool *next;
	size_t				allocated;
	void				*mem;
}					t_large_pool;

typedef struct		s_state
{
	t_pool			*tiny;
	t_pool			*small;
	t_large_pool	*large;
	pthread_mutex_t	mutex;
}					t_state;

size_t				get_alloc_size(size_t size);
void				*sysalloc(size_t size);

t_pool				*create_pool(uint32_t bucketsize, uint32_t bucketnumber);
void				flush_pool(t_pool **pool);
t_large_pool		*create_large_pool(size_t size);
t_state				*init_state(void);
t_state				*get_state(void);
long				get_bucket_position(t_pool *pool, void *ptr);

void				*malloc(size_t size);
void				*malloc_locked(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem();

void				free_bucket(t_pool *pool, uint32_t position);

void				ft_putstr(char *str);

#endif
