#include "push_swap.h"

int	is_valid(t_flags *flags)
{
	if (flags->is_adaptive > 1)
		return (0);
	else if (flags->is_simple > 1)
		return (0);
	else if (flags->is_medium > 1)
		return (0);
	else if (flags->is_complex > 1)
		return (0);
	return (1);
}

int	set_flags(char *flag, t_flags *flags)
{
	if (ft_strncmp(flag, SIMPLE, ft_strlen(SIMPLE)) == 0)
		flags->is_simple = 1;
	else if (ft_strncmp(flag, MEDIUM, ft_strlen(MEDIUM)) == 0)
		flags->is_medium = 1;
	else if (ft_strncmp(flag, COMPLEX, ft_strlen(COMPLEX)) == 0)
		flags->is_complex = 1;
	else if (ft_strncmp(flag, BENCH, ft_strlen(BENCH)) == 0)
		flags->is_bench = 1;
	else
		return (0);
	return (1);
}

int	has_mode(t_flags *flags)
{
	return (flags->is_simple || flags->is_medium || flags->is_complex);
}

void	validate_flags(char **av, t_flags *flags, int *i)
{
	while (*i <= 2 && ft_strncmp("--", av[*i], 2) == 0)
	{
		if (has_mode(flags) == 0)
		{
			if (set_flags(av[*i], flags) == 0)
			{
				printf("Error\n");
				exit(1);
			}
		}
		else if (ft_strncmp(av[*i], BENCH, ft_strlen(BENCH)) == 0)
			flags->is_bench = 1;
		else
		{
			printf("Error\n");
			exit(1);
		}
		(*i)++;
	}
	if (has_mode(flags) == 0)
		flags->is_adaptive = 1;
}

int	main(int ac, char **av)
{
	t_list			*stack_a;
	t_flags			flags;
	t_gb_collector	*gb_c;
	int				i;

	if (ac <= 1)
		exit(1);
	flags = (t_flags){0};
	gb_c = NULL;
	stack_a = NULL;
	i = 1;
	validate_flags(av, &flags, &i);
	fill_stack_a(&stack_a, av + i, ac - i, &gb_c);
	// selection_sort(&stack_a);
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
