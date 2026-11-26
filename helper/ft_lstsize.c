/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 16:55:10 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/21 09:50:48 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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
