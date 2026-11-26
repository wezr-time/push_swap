#include "../push_swap.h"

static void	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;

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
	if (!(*stack_a) || !(*stack_a)->next)
		return ;
	rotate(stack_a);
	count_ops->ra++;
	printf("ra\n");
}

void	rb(t_list **stack_b, t_count *count_ops)
{
	if (!(*stack_b) || !(*stack_b)->next)
		return ;
	rotate(stack_b);
	count_ops->rb++;
	printf("rb\n");
}
