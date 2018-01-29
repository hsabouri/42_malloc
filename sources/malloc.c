/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 16:38:54 by hsabouri          #+#    #+#             */
/*   Updated: 2018/01/29 17:33:42 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*alloc(t_pool *lst, size_t size)
{
	void	*res;

	while (lst->next && lst->last == lst->nbuckets)
		lst = lst->next;
	if (lst->next == NULL && lst->last == lst->nbuckets)
	{
		if (!(lst->next = ft_setpool(lst->size, lst->sbucket)))
			return (NULL);
		lst = lst->next;
	}
	res = lst->content[lst->last].mem;
	lst->content[lst->last].size = size;
	lst->last++;
	ft_store(res, 1, size, lst->sbucket);
	return (res);
}

static void	*alloc_large(t_pool **lst, size_t size)
{
	void	*res;
	size_t	rsize;
	t_pool	*new;
	t_pool	*curr;

	rsize = ft_poolsize(size);
	if (!rsize || !(new = ft_setpool(rsize, size)))
		return (NULL);
	new->last = 1;
	new->content[0].size = size;
	if (!*lst)
		*lst = new;
	else
	{
		curr = *lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	res = new->mem;
	ft_store(res, HIST_ALLOC, size, rsize);
	return (res);
}

void	*malloc(size_t size)
{
	t_env	*env;
	void	*res;

	ft_putstr("malloc\n");
	env = ft_getenv();
	if (!size)
		return (NULL);
	if (size <= TINY)
		res = alloc(env->tiny, size);
	else if (size <= SMALL)
		res = alloc(env->small, size);
	else
		res = alloc_large(&env->large, size);
	return (res);
}
