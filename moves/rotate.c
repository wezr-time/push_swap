#include "../push_swap.h"

static void	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;

	if (*stack == NULL || (*stack)->next == NULL)
		return ;
	first = (*stack);
	last = first;
	while (last && last->next)
		last = last->next;
	last->next = first;
	(*stack) = first->next;
	first->next = NULL;
}

void	ra(t_list **stack_a, t_count *count_ops)
{
	rotate(stack_a);
	count_ops->ra++;
	printf("ra\n");
}

void	rb(t_list **stack_b, t_count *count_ops)
{
	rotate(stack_b);
	count_ops->rb++;
	printf("rb\n");
}
