#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "garbage_collector/garbage_collector.h"

# define ADAPTIVE "--adaptive"
# define SIMPLE "--simple"
# define MEDIUM "--medium"
# define COMPLEX "--complex"
# define BENCH "--bench"

typedef struct s_list
{
	int				nbr;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_flags
{
	int	is_adaptive;
	int	is_simple;
	int	is_medium;
	int	is_complex;
	int	is_bench;
}	t_flags;


#include <stdio.h>

void	push_swap(t_list *stack_a);
void	fill_stack_a(t_list **stack_a, char **av, int ac,
			t_gb_collector **gb_c);
int		ft_atoi(const char *nptr, t_gb_collector **gb_c, char **splitted);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const	char *str);
void	free_splitted(char **splitted);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned int	ft_lstsize(t_list *lst);

void	bubble_sort(t_list **stack_a);

// Moves
void	ra(t_list **stack_a);
void	rb(t_list **stack_b);

void	rra(t_list **stack_a);
void	rrb(t_list **stack_b);

void	pa(t_list **stack_b, t_list **stack_a);
void	pb(t_list **stack_a, t_list **stack_b);

#endif