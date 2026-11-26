/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamehri <mamehri@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 14:10:56 by ymoubtas          #+#    #+#             */
/*   Updated: 2026/11/26 11:17:07 by mamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int	ft_dprintf(int fd, const char *f, ...);
int	ft_printchar(int fd, int c);
int	ft_printnbr_base(int fd, long n, char *srcbase);
int	ft_printstr(int fd, char *s);
int	ft_printaddress(int fd, void *p);

#endif