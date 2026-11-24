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

typedef struct s_list
{
	int				nbr;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_flags
{
	int	is_adaprtive;
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

#endif