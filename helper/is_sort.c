/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 14:44:31 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/21 14:44:32 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_sort(t_list *head)
{
	while (head && head->next)
	{
		if (head->content > head->next->content)
			return (0);
		head = head->next;
	}
	return (1);
}
