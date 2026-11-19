#include "push_swap.h"

static t_list	*min(t_list *list)
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
	return ((float)mistakes / total_pairs);
}
