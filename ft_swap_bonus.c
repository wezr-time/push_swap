/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:55:43 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 16:45:54 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	swap(t_list *lst)
{
	int	content;
	int	index;

	if (!lst || !lst->next)
		return ;
	content = lst->content;
	index = lst->index;
	lst->content = lst->next->content;
	lst->index = lst->next->index;
	lst->next->content = content;
	lst->next->index = index;
}

void	sa_checker(t_list *a)
{
	swap(a);
}

void	sb_checker(t_list *b)
{
	swap(b);
}

void	ss_checker(t_list *a, t_list *b)
{
	sa_checker(a);
	sb_checker(b);
}
