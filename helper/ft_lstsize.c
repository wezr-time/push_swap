#include "../push_swap.h"

unsigned int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*curr;

	if (!lst)
		return (0);
	curr = lst;
	i = 0;
	while (curr)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}