#include "push_swap.h"
#include <stdio.h>

typedef struct s_flags
{
	int	is_adaptive;
	int	is_simple;
	int	is_medium;
	int	is_complex;
	int	is_bench;
} t_flags;

// static void	init_flags(t_flags *flags)
// {
// 	flags->is_adaptive = 0;
// 	flags->is_simple = 0;
// 	flags->is_medium = 0;
// 	flags->is_complex = 0;
// 	flags->is_bench = 0;
// }

int	select_flag(char	*s, t_flags *flags_list)
{
	// init_flags(flags_list);
	if (ft_strncmp("--simple", s, ft_strlen(s)) == 0)
		flags_list->is_simple = 1;
	else if (ft_strncmp("--medium", s, ft_strlen(s)) == 0)
		flags_list->is_medium = 1;
	else if (ft_strncmp("--complex", s, ft_strlen(s)) == 0)
		flags_list->is_complex = 1;
	else if (ft_strncmp("--adaptive", s, ft_strlen(s)) == 0)
		flags_list->is_adaptive = 1;
	else
		return (0);
	return (1);
}

void	init_stack_a(t_list **stack_a, int argc, char **argv)
{
	t_list	*node;
	int		i;

	i = 0;
	*stack_a = NULL;
	while (i < argc)
	{
		int x = ft_atoi(argv[i]);
		node = ft_lstnew(x);
		if (!node)
		{
			ft_lstclear(stack_a);
			exit(1);
		}
		ft_lstadd_back(stack_a, node);
		i++;
	}
	update_index(*stack_a);
}

void	adapt_algo(t_list **stack_a,  t_count *count_op, t_flags *flags)
{
	count_op->disorder = compute_disorder(*stack_a);
	if (count_op->disorder < 0.2)
	{
		flags->is_simple = 1;
		bubble_sort(stack_a, count_op);
	}
	else if (count_op->disorder < 0.5)
	{
		flags->is_medium = 1;
		chunk_sort(stack_a, count_op);
	}
	else
	{
		flags->is_complex = 1;
		radix_sort(stack_a, count_op);
	}
}

void	which_sort(t_list **stack_a, t_flags *flags)
{
	t_count	count_op;

	count_op = (t_count){0,0,0,0,0,0, 0, 0};
	if (flags->is_complex == 1)
		radix_sort(stack_a, &count_op);
	else if (flags->is_medium == 1)
		chunk_sort(stack_a, &count_op);
	else if (flags->is_simple == 1)
		bubble_sort(stack_a, &count_op);
	else if (flags->is_adaptive == 1)
		adapt_algo(stack_a, &count_op, flags);
	// if (flags->is_bench)
	// 	cal_bench(flags, count_op);
}

int main(int argc, char **argv)
{
	t_list	*stack_a;
	t_flags	flags_list;
	int	i;

	// don't forget <= not <
	if (argc <= 1)
		return (0);
	flags_list = (t_flags){0, 0, 0, 0, 0};
	i = 1;
	if (ft_strncmp(argv[i], "--bench", ft_strlen(argv[i])) == 0)
	{
		flags_list.is_bench = 1;
		i++;
	}
	if (argv[i] && !select_flag(argv[i], &flags_list))
		flags_list.is_adaptive = 1;
	else
		i++;
	init_stack_a(&stack_a, argc - i, argv + i);

	which_sort(&stack_a, &flags_list);
	// radix_sort(&stack_a, &count_op); // 33136
	// chunk_sort(&stack_a, &count_op); // 52323
	// bubble_sort(&stack_a, &count_op); // 5997000


	// ################################################
	printf("SORT NOW\n");
	t_list *curr = stack_a;
	while (curr)
	{
		printf("%d ", (curr->content));
		curr = curr->next;
	}
	if (flags_list.is_adaptive)
	{
		printf("adaptive / ");
		if (flags_list.is_complex)
			printf("n log n");
		else if (flags_list.is_medium)
			printf("n√n");
		if (flags_list.is_simple)
			printf("n²");
	}
	else if (flags_list.is_complex)
		printf("complex");
	else if (flags_list.is_medium)
		printf("medium");
	else if (flags_list.is_simple)
		printf("simple");
	printf("\n");
	ft_lstclear(&stack_a);
}

/*
int main()
{
	int arr[10] = {10, 2, 4, 8, 3, -4, 0, 7, 6, 5};
	size_t count = 10;
	t_list	*stack_a = NULL;
	for (size_t i = 0; i < count; i++)
		ft_lstadd_back(&stack_a, ft_lstnew(arr[i]));
	update_index(stack_a);

	printf("disorder: %.2f\n", compute_disorder(stack_a));
	// bubble_sort(&stack_a); // ==> 79 moves / 12 vs 7
	// chunk_sort(&stack_a);
	radix_sort(&stack_a);
	printf("\n");
	t_list *curr = stack_a;
	while (curr)
	{
		printf("%d ", (curr->content));
		curr = curr->next;
	}
	ft_lstclear(&stack_a);
}

*/