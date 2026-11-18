#include "push_swap.h"
#include <stdio.h>

t_list	*min(t_list *list)
{
	t_list	*the_min;

	the_min = list;
	while (list)
	{
		if (the_min->content > list->content && list->index == -1)
			the_min = list;
		list = list->next;
	}
	if (the_min->index != -1)
		return (NULL);
	return (the_min);
}

void	update_index(t_list *list)
{
	int		pos;
	t_list	*curr;

	pos = 0;
	while (1)
	{
		curr = min(list);
		if (curr == NULL)
			return ;
		curr->index = pos++;
	}
}

float	compute_disorder(t_list *stack_a)
{
	t_list	*curr;
	int		mistakes;
	int		total_pairs;

	mistakes = 0;
	total_pairs = 0;
	while (stack_a)
	{
		curr = stack_a->next;
		while (curr)
		{
			total_pairs += 1;
			if (stack_a->content > curr->content)
				mistakes++;
			curr = curr->next;
		}
		stack_a = stack_a->next;
	}
	int disorder = ((float)mistakes / total_pairs) * 100;
	return ((float)disorder / 100);
}

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