/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 13:51:17 by hsabouri          #+#    #+#             */
/*   Updated: 2017/09/03 18:18:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>

# define TINY 128
# define SMALL 4096
# define BUCKETS 128

# define MMAP_ARGS 0x01|0x02,0x1000|0x0002,-1,0

typedef struct	s_buck
{
	size_t			size;
	void			*mem;
	struct s_buck	*next;
}				t_buck;

typedef struct	s_pool
{
	size_t			size;
	t_buck			*first;
	t_buck			*last;
	struct s_pool	*next;
	void			*mem;
}				t_pool;

typedef struct	s_env
{
	int		init;
	size_t	res;
	size_t	tiny_size;
	size_t	small_size;
	t_pool	*tiny;
	t_pool	*small;
	t_buck	*large;
}				t_env;

void			*malloc(size_t size);

#endif
