#include "../push_swap.h"

static int	ft_convert_to_nbr(const char *nptr, int sign, t_gb_collector **gb_c,
		char **splitted)
{
	size_t	i;
	long		nbr;

	i = 0;
	nbr = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - '0';
		if (nbr > INT_MAX)
			break ;
		i++;
	}
	if (nbr > INT_MAX || nptr[i] != '\0')
	{
		printf("Error\n");
		free_splitted(splitted);
		clean_gb(gb_c);
		exit(1);
	}
	return (nbr * sign);
}

int	ft_atoi(const char *nptr, t_gb_collector **gb_c, char **splitted)
{
	size_t	i;
	int		sign;

	printf("|%s|\n", nptr);
	if (!*nptr)
		return (0);
	i = 0;
	sign = 1;

	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_convert_to_nbr(nptr + i, sign, gb_c, splitted));
}
