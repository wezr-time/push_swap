/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 09:57:14 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/28 08:21:22 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "get_next_line.h"
# include "ft_dprintf_bonus.h"
# include <limits.h>

typedef struct s_ops_list
{
	void				*op;
	struct s_ops_list	*next;
}	t_ops_list;

typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_list;

void			pa_checker(t_list **b, t_list **a);
void			pb_checker(t_list **a, t_list **b);

void			rra_checker(t_list **a);
void			rrb_checker(t_list **b);
void			rrr_checker(t_list **a, t_list **b);

void			ra_checker(t_list **a);
void			rb_checker(t_list **b);
void			rr_checker(t_list **a, t_list **b);

void			sa_checker(t_list *a);
void			sb_checker(t_list *b);
void			ss_checker(t_list *a, t_list *b);

t_list			*ft_lstnew(int content);

t_ops_list		*bonus_lstnew(char *op);

size_t			ft_strlen(const	char *str);

char			**ft_split(char const *s, char c);

int				is_sort(t_list *head);
int				ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *nptr, int *check);
int				ft_ops(t_list **a, t_list **b, char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

unsigned int	ft_lstsize(t_list *lst);

void			ft_dup_nbr(t_list **a);
void			ft_set_index(t_list *a);
void			ft_lstclear(t_list **lst);
void			bonus_lstclear(t_ops_list **lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			bonus_lstadd_back(t_ops_list **lst, t_ops_list *new);
void			ft_stack_fill(t_list **a, int ac, char **av, int i);

#endif