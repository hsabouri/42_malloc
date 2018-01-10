/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 11:54:46 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/08 16:16:46 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# define TINY 128
# define SMALL 2048
# define BUCKETS 4096

# define MMAP(size) mmap(NULL,size,0x01|0x02,0x1000|0x0002,-1,0)
# define MMAP_ARGS 0x01|0x02,0x1000|0x0002,-1,0

typedef struct  s_bucket
{
    void    *mem;
    size_t  size;
    size_t  max;
}               t_bucket;

typedef struct  s_pool
{
    struct s_pool   *next;
    t_bucket        *content;
    size_t          last;
	size_t			size;
    size_t          nbuckets;
    size_t          sbucket;
    void            *mem;
}               t_pool;

# ifdef HISTORY

#  define HIST_ALLOC 1
#  define HIST_REALLOC 0
#  define HIST_FREE -1
#  define HIST_NEW_POOL 2
#  define HIST_DEL_POOL -2

typedef struct  s_hist
{
    int             type;
    size_t          size;
    void            *ptr;
    struct s_hist   *next;
}               t_hist;

/*
**  s_hist type precisions
**      1 -> alloc			-> HIST_ALLOC
**      0 -> realloc		-> HIST_REALLOC
**      -1 -> free			-> HIST_FREE
**		2 -> new pool		-> HIST_NEW_POOL
**		-2 -> deleting pool	-> HIST_DEL_POOL
**  if ptr == NULL, operation failed
*/

# endif

typedef struct  s_env
{
    size_t  stiny;
    size_t  ssmall;
    t_pool  *tiny;
    t_pool  *small;
    t_pool  *large;
# ifdef HISTORY
    t_hist  *hist;
# endif
}               t_env;

t_env           *getenv(void);
t_pool			*setpool(size_t nbuckets, size_t sbucket);
size_t			poolsize_large(size_t size);
size_t			poolsize(size_t sbucket);

void            *malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void            free(void *ptr);

t_pool			*search_pool(t_env *env, t_pool **before, void *ptr);
t_pool			*search_normal(t_pool *lst, t_pool **before, void *ptr);
t_pool			*search_large(t_pool *lst, t_pool **before, void *ptr);
void			del_pool(t_pool *pool, t_pool *before);
int				free_ptr(t_pool *pool, void *ptr);

void            putsystox(size_t addr);
void			store(void *ptr, int type, size_t size);
void            show_alloc_mem(void);
void            show_alloc_mem_ex(void);

void			ft_putstr(const char *str);
void			ft_putsystox(size_t addr);
void			ft_putnbr(size_t n);

#endif
