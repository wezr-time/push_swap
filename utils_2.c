/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:56:33 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 10:14:02 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;

	if (!lst)
		return (NULL);
	curr = lst;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

int	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	return (1);
}

unsigned int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	size_t	i;

	if (!lst)
		return (0);
	i = 0;
	curr = lst;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->index = 0;
	new->next = NULL;
	return (new);
}
