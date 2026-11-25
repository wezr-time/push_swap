#include "../push_swap.h"

static void	ft_lstadd_back(t_list **stack_a, t_list *node)
{
	t_list	*curr;

	curr = *stack_a;
	while (curr && curr->next)
		curr = curr->next;
	if (curr == NULL)
		*stack_a = node;
	else
		curr->next = node;
}

static void	fill(t_list **stack_a, t_gb_collector **gb_c, char **splitted)
{
	t_list	*node;
	int		i;

	i = 0;
	while (splitted[i])
	{
		node = gb_malloc(sizeof(t_list), gb_c);
		if (!node)
		{
			clean_gb(gb_c);
			return ;
		}
		node->nbr = ft_atoi(splitted[i], gb_c, splitted);
		node->index = -1;
		node->next = NULL;
		ft_lstadd_back(stack_a, node);
		i++;
	}
}

void	free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	fill_stack_a(t_list **stack_a, char **av, int ac, t_gb_collector **gb_c)
{
	int		i;
	char	**splitted;

	i = 0;
	while (i < ac)
	{
		splitted = ft_split(av[i], ' ');
		if (!splitted || !*splitted)
		{
			printf("Error\n");
			free_splitted(splitted);
			clean_gb(gb_c);
			exit(1);
		}
		fill(stack_a, gb_c, splitted);
		i++;
		free_splitted(splitted);
	}
}
