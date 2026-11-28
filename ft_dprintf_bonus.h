/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoubtas <ymoubtas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 11:52:10 by mamehri           #+#    #+#             */
/*   Updated: 2026/11/27 10:57:39 by ymoubtas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_BONUS_H
# define FT_DPRINTF_BONUS_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int	ft_dprintf(int fd, const char *f, ...);
int	ft_printchar(int fd, int c);
int	ft_printnbr_base(int fd, long n, char *srcbase);
int	ft_printstr(int fd, char *s);
int	ft_print_float(int fd, double nbr_float);

#endif