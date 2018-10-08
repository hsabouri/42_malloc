/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 10:34:59 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/08 15:19:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void					*realloc(void *ptr, size_t size)
{
	ft_putstr("REALLOC\n");
	free(ptr);
	return (malloc(size));
}