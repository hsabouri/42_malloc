/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valloc_reallocf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 16:23:15 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/16 16:08:19 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

extern void	*valloc(size_t s)
{
	return (malloc(s));
}

extern void	*reallocf(void *addr, size_t size)
{
	void *res;

	res = realloc(addr, size);
	if (res == NULL)
	{
		free(addr);
		return (NULL);
	}
	return (res);
}
