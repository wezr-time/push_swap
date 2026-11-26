/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 11:48:38 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/26 10:02:16 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	is_flag(char *s, char *flag)
{
	return (ft_strncmp(s, flag, ft_strlen(flag)) == 0);
}

static int	set_falg(char *s, char *name, int *field)
{
	if (!is_flag(s, name))
		return (0);
	*field = 1;
	return (1);
}

static int	has_mode(t_flags *f)
{
	return (f->simple || f->medium || f->complex);
}

static void	ft_valid_flag(char *s, t_flags *flags)
{
	flags->adaptive = 1;
	if (!has_mode(flags)
		&& (set_falg(s, SIMPLE, &flags->simple)
			|| set_falg(s, MEDIUM, &flags->medium)
			|| set_falg(s, COMPLEX, &flags->complex)
			|| set_falg(s, ADAPTIVE, &flags->adaptive)))
		return ;
	else if (set_falg(s, BENCH, &flags->bench))
		return ;
	exit (ft_putstr_fd("Error\n", 2));
}

void	ft_flags(int ac, char **av, t_flags *flags, int *i)
{
	if (ac == 2)
		return ;
	while (*i <= 2 && is_flag(av[*i], "--"))
	{
		if (!av[*i + 1] || is_flag(av[*i], av[*i + 1]))
			exit (ft_putstr_fd("Error\n", 2));
		ft_valid_flag(av[(*i)++], flags);
	}
}
