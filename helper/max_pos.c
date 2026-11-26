/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:27:14 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:27:15 by mamehri          ###   ########.fr       */
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
