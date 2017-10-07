/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 17:38:44 by hsabouri          #+#    #+#             */
/*   Updated: 2017/10/07 14:18:27 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>

void	ft_putstr(const char *str)
{
	size_t i;

	i = 0;
	while (i < TINY)
	{
		write(1, str + i, 1);
		i++;
	}
}

int main(void)
{
	size_t i = 0;
	char *ptr;
	
	while (i < BUCKETS * 10)
	{
		ptr = malloc(TINY);
		ptr = strcpy(ptr, "BONJOUR JE SUIS UNE STRING\n");
		i++;
	}

	return (0);
}
