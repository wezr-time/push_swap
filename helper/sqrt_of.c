#include "../push_swap.h"

size_t	sqrt_of(size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 1;
	while (i < n / i)
		i++;
	return (i);
}
