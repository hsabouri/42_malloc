/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:31:24 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/02 11:47:28 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>

# define TINY 32
# define SMALL 64
# define REGION_S 5

# define ARGS 0x01|0x02,0x1000|0x0002,-1,0

typedef	unsigned int	t_uint;

typedef struct			s_bucket
{
	t_uint			size;
	t_uint			max;
	void			*ptr;
}						t_bucket;

typedef struct			s_pool
{
	t_uint			bucketsize;
	t_uint			bucketnumber;
	t_uint			edge;
	void			*mem;
	struct s_pool	*next;
	t_bucket		buckets[REGION_S];
}						t_pool;

typedef struct			s_large_pool
{
	size_t				allocated;
	size_t				current;
	void				*mem;
	struct s_large_pool *next;
}						t_large_pool;

typedef struct			s_state
{
	t_pool			*tiny;
	t_pool			*small;
	t_large_pool	*large;
}						t_state;

size_t					get_alloc_size(size_t size);
void					*sysalloc(size_t size);

t_pool					*create_pool(t_uint bucketsize, t_uint bucketnumber);
t_large_pool			*create_large_pool(size_t size);
t_state					*init_state(void);
t_state					*get_state(void);

void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);
void					show_alloc_mem();



void	ft_putstr(char *str);

#endif
