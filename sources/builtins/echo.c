/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@strtudentstr.42listrboa.com>  +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:10:33 by miguelro          #+#    #+#             */
/*   Updated: 2023/04/16 15:43:00 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[i++] != '-')
		return (false);
	else
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (false);
			i++;
		}
		if (i < 2)
			return (false);
	}
	return (true);
}

void	echo_aux(char **str, int fd, int i)
{
	int		j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
			write(fd, &str[i][j++], 1);
		if (str[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
}

void	error_handling_built_in(bool error)
{
	handler()->child++;
	handler()->id = fork();
	if (handler()->id == 0 && error == true)
		terminate(1, false);
	else if (handler()->id == 0 && error == false)
		terminate(0, false);
	return ;
}

void	echo(char **str, int fd, bool new_line)
{
	int		i;

	if (!str[1])
	{
		write(fd, "\n", 1);
		return ;
	}
	i = 1;
	while (check_flag(str[i]) == true)
	{
		new_line = false;
		i++;
	}
	echo_aux (str, fd, i);
	if (new_line)
		write(fd, "\n", 1);
	error_handling_built_in(false);
}
