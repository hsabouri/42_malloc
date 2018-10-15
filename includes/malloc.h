/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:31:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/15 16:47:11 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

# define TINY 128
# define SMALL 512
# define REGION_S 2048


typedef uint16_t	t_uint;
typedef int32_t		t_int;

# define ALIGN 16
# define MASK ~(uintptr_t)(ALIGN - 1)

# define ARGS 0x01|0x02,0x1000|0x0002,-1,0

typedef struct		s_bucket
{
	char			allocated;
	t_uint			index;
}					t_bucket;

typedef struct		s_pool
{
	struct s_pool	*next;
	t_uint			bucketsize;
	t_uint			bucketnumber;
	t_uint			edge;
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

t_pool				*create_pool(t_uint bucketsize, t_uint bucketnumber);
void				flush_pool(t_pool **pool);
t_large_pool		*create_large_pool(size_t size);
t_state				*init_state(void);
t_state				*get_state(void);
t_int				get_bucket_position(t_pool *pool, void *ptr);
void				free_bucket(t_pool *pool, t_uint position);

extern void			*malloc(size_t size);
extern void			*malloc_locked(size_t size);
extern void			*realloc(void *ptr, size_t size);
extern void			free(void *ptr);
extern void			*calloc(size_t count, size_t size);
void				show_alloc_mem();

extern void			*valloc(size_t s);
extern void			*reallocf(void *addr, size_t size);

void				ft_putstr(char const *str);
void				ft_putlong(long n);
void				*ft_memmove(void *dst, const void *src, size_t len);

#endif
