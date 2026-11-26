/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:27:22 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:27:23 by ymoubtas         ###   ########.fr       */
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
