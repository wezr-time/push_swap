/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:58:05 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 11:26:55 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_dprintf/ft_dprintf.h"
# include <stdlib.h>
# include <limits.h>

# define SIMPLE "--simple"
# define MEDIUM "--medium"
# define COMPLEX "--complex"
# define ADAPTIVE "--adaptive"
# define BENCH "--bench"

typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_flags
{
	int	simple;
	int	medium;
	int	complex;
	int	adaptive;
	int	bench;
}	t_flags;

typedef struct s_count
{
	int		pa;
	int		pb;
	int		sa;
	int		sb;
	int		ra;
	int		rb;
	int		rrb;
	int		rra;
	float	disorder;
}	t_count;

void			selection_sort(t_list **a, t_list **b, t_count *ops);
void			chunk_sort(t_list **a, t_list **b, t_count *ops);
void			radix_sort(t_list **a, t_list **b, t_count *ops);

void			pa(t_list **b, t_list **a, t_count *ops);
void			pb(t_list **a, t_list **b, t_count *ops);

void			rra(t_list **a, t_count *ops);
void			rrb(t_list **b, t_count *ops);

void			ra(t_list **a, t_count *ops);
void			rb(t_list **b, t_count *ops);

void			sa(t_list *a, t_count *ops);
void			sb(t_list *b, t_count *ops);

t_list			*ft_lstnew(int content);

size_t			ft_strlen(const	char *str);
size_t			in_range(t_list *a, int range);

char			**ft_split(char const *s, char c);

int				sqrt_of(long n);
int				max_pos(t_list *list);
int				ft_lstclear(t_list **lst);
int				ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *nptr, int *check);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				is_sort(t_list *head);

unsigned int	ft_lstsize(t_list *lst);

void			ft_set_index(t_list *a);
void			ft_dup_nbr(t_list **a);
void			ft_sort(t_list **a, t_flags *flags);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_flags(int ac, char **av, t_flags *flags, int *i);
void			ft_stack_fill(t_list **a, int ac, char **av, int i);

#endif