#include "../push_swap.h"

void	chunk_v2(t_list **a, t_list **b, t_count *ops)
{
	size_t	offset;
	size_t	size;
	size_t	pushed;

	size = ft_lstsize(*a);
	offset = sqrt_of(size);
	pushed = 0;
	while (*a)
	{
		if ((*a)->index <= pushed + offset)
		{
			pb(a, b, ops);
			if ((*a)->index <= pushed)
				rb()
		}
	}
	

}