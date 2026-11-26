/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:55:43 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:18:42 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_list *lst)
{
	int	content;
	int	index;

	if (!lst)
		return ;
	content = lst->content;
	index = lst->index;
	lst->content = lst->next->content;
	lst->index = lst->next->index;
	lst->next->content = content;
	lst->next->index = index;
}

void	sa(t_list *stack_a, t_count *count_op)
{
	swap(stack_a);
	ft_dprintf(1, "sa\n");
	count_op->sa++;
}

void	sb(t_list *stack_b, t_count *count_op)
{
	swap(stack_b);
	ft_dprintf(1, "sb\n");
	count_op->sb++;
}
