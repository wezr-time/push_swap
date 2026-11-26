/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:25:49 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:25:50 by ymoubtas         ###   ########.fr       */
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
