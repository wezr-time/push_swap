/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_nonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 14:25:59 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:16:19 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../checker.h"

void	sp(t_list *node1, t_list *node2)
{
	int	tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

t_list	*psh(t_list *node, t_list **head)
{
	t_list	*tmp;

	if (node == NULL)
	{
		ft_lstclear(head);
		ft_lstclear(&node);
		ft_printf(2, "Error\n");
		exit(1);
	}
	tmp = node->next;
	node->next = *head;
	*head = node;
	return (tmp);
}

void	rrab(t_list **head)
{
	t_list	*curr;
	t_list	*last;

	curr = *head;
	last = NULL;
	while (curr && curr->next)
	{
		if (curr->next->next == NULL)
		{
			last = curr->next;
			curr->next = NULL;
			break ;
		}
		curr = curr->next;
	}
	last->next = *head;
	*head = last;
}

void	rab(t_list **head)
{
	t_list	*first;
	t_list	*curr;

	curr = *head;
	first = *head;
	*head = (*head)->next;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = first;
	first->next = NULL;
}
