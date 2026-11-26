/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 14:56:41 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/21 09:50:43 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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
