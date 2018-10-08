/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:56:43 by hsabouri          #+#    #+#             */
/*   Updated: 2018/10/08 15:19:05 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void					*calloc(size_t count, size_t size)
{
	ft_putstr("CALLOC\n");
	return (malloc(count * size));
}
