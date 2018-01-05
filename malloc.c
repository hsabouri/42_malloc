/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 16:38:54 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/05 17:58:06 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*alloc(t_pool *lst, size_t size)
{
	void	*res;

	while (lst->next && lst->last == lst->nbuckets)
		lst = lst->next;
	if (lst->next == NULL && lst->last == lst->nbuckets)
	{
		lst->next = setpool(lst->nbuckets, lst->sbucket);
		lst = lst->next;
	}
	res = lst->content[lst->last].mem;
	lst->content[lst->last].size = size;
#ifdef HISTORY
	store(res, 1, size);
#endif
	return (res);
}

void	*alloc_large(t_pool **lst, size_t size)
{
	void	*res;
	t_pool	*new;

	new = setpool(1, size);
	if (!*lst)
		*lst = new;
	else
	{
		while ((*lst)->next)
			lst = &((*lst)->next);
		*lst = new;
	}
#ifdef HISTORY
	store(res, 1, size);
#endif
	res = new->mem;
	return (res);
}

void	*malloc(size_t size)
{
	t_env	*env;
	void	*res;

	env = getenv();
	if (size <= TINY)
		res = alloc(env->tiny, size);
	else if (size <= SMALL)
		res = alloc(env->small, size);
	else
		res = alloc_large(&env->large, size);
	return (res);
}
