/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 13:26:56 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 13:26:57 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	max_pos(t_list *list)
{
	t_list	*curr;
	int		value;
	int		pos;

	curr = list;
	value = list->content;
	while (curr)
	{
		if (curr->content > value)
			value = curr->content;
		curr = curr->next;
	}
	pos = 0;
	while (list && list->content != value)
	{
		pos++;
		list = list->next;
	}
	return (pos);
}
