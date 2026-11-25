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

float	compute_disorder(t_list *stack)
{
	t_list	*curr;
	int	mistakes;
	int	total;

	total = 0;
	mistakes = 0;
	while (stack)
	{
		curr = stack->next;
		while (curr)
		{
			total++;
			if (curr->nbr < stack->nbr)
				mistakes++;
			curr = curr->next;
		}
		stack = stack->next;
	}
	return ((float)mistakes / total);
}

void	adapt_algo(t_list **stack_a, t_flags *flags, t_list **stack_b, t_count *count_ops)
{
	float	disorder;

	disorder = compute_disorder(*stack_a);
	if (disorder < 0.2)
	{
		flags->is_simple = 1;
		selection_sort(stack_a, stack_b, count_ops);
	}
	else if (disorder < 0.5)
	{
		flags->is_medium = 1;
		chunk_sort(stack_a, stack_b, count_ops);
	}
	else
	{
		flags->is_complex = 1;
		return ;
	}
}

int	ft_sum(t_count *count_ops)
{
	return (count_ops->sa + count_ops->sb + count_ops->ss + count_ops->pa + count_ops->pb +
	count_ops->ra + count_ops->rb + count_ops->rr + count_ops->rra + count_ops->rrb + count_ops->rrr);
}

void	call_bench(t_list *stack_a, t_flags *flags, t_count *count_ops)
{
	float	disorder;

	disorder = compute_disorder(stack_a);
	printf("[bench] disorder: %f%%\n", disorder * 100);
	printf("[bench] strategy: ");
	if (flags->is_adaptive == 1)
		printf("Adaptive / ");
	else if (flags->is_simple)
		printf("Simple / ");
	else if (flags->is_medium)
		printf("Medium / ");
	else if (flags->is_complex)
		printf("Complex / ");
	if (flags->is_simple)
		printf("n²\n");
	else if (flags->is_medium)
		printf("O(n√n)\n");
	else if (flags->is_complex)
		printf("O(n ㏒ n)\n");
	printf("[bench] total_ops: %d\n", ft_sum(count_ops));
	printf("[bench] sa:	%d	sb:	%d	ss:	%d	pa:	%d	pb:	%d\n",
		count_ops->sa, count_ops->sb, count_ops->ss, count_ops->pa, count_ops->pb);
	printf("[bench] ra:	%d	rb:	%d	rr:	%d	rra:	%d	rrb:	%d	rrr:	%d\n",
		count_ops->ra, count_ops->rb, count_ops->rr, count_ops->rra, count_ops->rrb, count_ops->rrr);
}

void	ft_sort(t_list **stack_a, t_flags *flags, t_count *count_ops)
{
	t_list	*stack_b;

	stack_b = NULL;
	if (flags->is_simple == 1)
		selection_sort(stack_a, &stack_b, count_ops);
	else if (flags->is_medium == 1)
		chunk_sort(stack_a, &stack_b, count_ops);
	else if (flags->is_complex == 1)
		return ;
	else if (flags->is_adaptive == 1)
		adapt_algo(stack_a, flags, &stack_b, count_ops);
	if (flags->is_bench == 1)
		call_bench(*stack_a, flags, count_ops);
}

int	main(int ac, char **av)
{
	t_list			*stack_a;
	t_flags			flags;
	t_count			count_ops;
	t_gb_collector	*gb_c;
	int				i;

	if (ac <= 1)
		exit(1);
	flags = (t_flags){0};
	count_ops = (t_count){0};
	gb_c = NULL;
	stack_a = NULL;
	i = 1;
	validate_flags(av, &flags, &i);
	fill_stack_a(&stack_a, av + i, ac - i, &gb_c);
	is_dup(stack_a);
	ft_sort(&stack_a, &flags, &count_ops);
	// REMOVE LATER
	// printf("\n===============\n");
	// t_list *curr = stack_a;
	// while (curr)
	// {
	// 	printf("%d ", curr->nbr);
	// 	curr = curr->next;
	// }
	// printf("\n===============\n");
	clean_gb(&gb_c);
}
