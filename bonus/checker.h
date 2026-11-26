/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:55:09 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 11:55:10 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../push_swap.h"
# include "gnl/get_next_line.h"

void	pa(t_list **b, t_list **a, t_count *ops);
void	pb(t_list **a, t_list **b, t_count *ops);

void	rra(t_list **a, t_count *ops);
void	rrb(t_list **b, t_count *ops);

void	ra(t_list **a, t_count *ops);
void	rb(t_list **b, t_count *ops);

void	sa(t_list *a, t_count *ops);
void	sb(t_list *b, t_count *ops);

#endif