/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 17:21:47 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 17:22:36 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_ops_list	*bonus_lstnew(char *op)
{
	t_ops_list	*new;

	new = malloc(sizeof(t_ops_list));
	if (!new)
		return (NULL);
	new->op = op;
	new->next = NULL;
	return (new);
}

void	bonus_lstadd_back(t_ops_list **lst, t_ops_list *new)
{
	t_ops_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	bonus_lstclear(t_ops_list **lst)
{
	t_ops_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->op);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
