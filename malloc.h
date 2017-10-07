/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:51:17 by hsabouri          #+#    #+#             */
/*   Updated: 2017/10/01 19:04:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>

# define TINY 128
# define SMALL 4096
# define BUCKETS 4096

# define MMAP_ARGS 0x01|0x02,0x1000|0x0002,-1,0

typedef struct	s_buck
{
	size_t			size;
	void			*mem;
}				t_buck;

typedef struct	s_pool
{
	size_t			buckets;
	t_buck			*bucks;
	struct s_pool	*next;
	void			*mem;
}				t_pool;

typedef struct	s_env
{
	size_t	tinysize;
	size_t	smallsize;
	size_t	pagesize;
	t_pool	*tiny;
	t_pool	*small;
	t_pool	*large;
}				t_env;


t_pool			*buildpool(size_t buckets, size_t bucketsize, size_t poolsize);
size_t			poolsize(size_t pagesize, size_t buckets, size_t bucketsize);
t_env			*get_env(void);
void			*malloc(size_t size);

#endif
