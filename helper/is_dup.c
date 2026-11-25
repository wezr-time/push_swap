#include "../push_swap.h"

void	is_dup(t_list *stack_a)
{
	t_list	*curr;

	while (stack_a)
	{
		curr = stack_a->next;
		while (curr)
		{
			if (stack_a->nbr == curr->nbr)
			{
				printf("Error\n");
				exit(1);
			}
			curr = curr->next;
		}
		stack_a = stack_a->next;
	}
}
