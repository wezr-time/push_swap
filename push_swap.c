#include "push_swap.h"


void	validate_flags(char **av, t_flags *flags)
{
	int	i;

	i = 0;
	while (i <= 2 && is_valid(av[i]))
	{
		if (ft_strncmp(av[i], SIMPLE, ft_strlen(av[i])) == 0)
		i++;
	}
	
}

int	main(int ac, char **av)
{
	t_list			*stack_a;
	t_flags			*flags;
	t_gb_collector	*gb_c;

	if (ac <= 1)
		exit(1);
	flags = (t_flags *){0};
	gb_c = NULL;
	stack_a = NULL;
	validate_flags(av, flags);
	fill_stack_a(&stack_a, av, ac, &gb_c);
	// REMOVE LATER
	printf("\n===============\n");
	t_list *curr = stack_a;
	while (curr)
	{
		printf("%d ", curr->nbr);
		curr = curr->next;
	}
	printf("\n===============\n");
	clean_gb(&gb_c);
}
