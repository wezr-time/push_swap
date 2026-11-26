/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 17:13:16 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/21 09:51:05 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_set_index(t_list *a)
{
	t_list	*current_i;
	t_list	*current_j;

	current_i = a;
	while (current_i)
	{
		current_j = a;
		while (current_j)
		{
			if (current_i->content > current_j->content)
				current_i->index++;
			current_j = current_j->next;
		}
		current_i = current_i->next;
	}
}

void	ft_dup_nbr(t_list **stack_a)
{
	t_list	*curr_i;
	t_list	*curr_j;

	curr_i = *stack_a;
	while (curr_i)
	{
		curr_j = curr_i->next;
		while (curr_j)
		{
			if (curr_i->content == curr_j->content)
			{
				ft_lstclear(stack_a);
				exit(ft_putstr_fd("Error\n", 2));
			}
			curr_j = curr_j->next;
		}
		curr_i = curr_i->next;
	}
}
