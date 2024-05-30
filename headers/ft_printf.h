/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:50:33 by marvin            #+#    #+#             */
/*   Updated: 2022/07/29 17:50:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

# define HEXAL "0123456789abcdef"
# define HEXAU "0123456789ABCDEF"
# define DEC "0123456789"

typedef unsigned long long	t_ull;

int			ft_check_form(char c, va_list args);
int			ft_putnbr_base(t_ull n, char *base, t_ull baselen, char c);
int			ft_putnbr(long long nbr);
int			ft_putchr(char c);
int			ft_putstr(char const *s);
int			ft_printf(const char *format, ...);

#endif