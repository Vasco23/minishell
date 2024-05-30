/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:27:06 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/14 15:24:01 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_fd(int fd_in, int fd_out)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd_in);
		if (!line)
			break ;
		write(fd_out, line, ft_strlen(line));
		free(line);
	}
}

void	close_fd(int fd_in, int fd_out)
{
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
}

void	make_fds(void)
{
	int	i;

	i = 0;
	while (i < handler()->smp_cmd_size)
	{
		if (pipe(handler()->smp_cmd[i].fds) == -1)
		{
			perror("error on pipe");
			return ;
		}
		i++;
	}
}

int	find_builtins(int i)
{
	if (i < handler()->smp_cmd_size && handler()->smp_cmd[i].cmd)
	{
		if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "pwd"))
			return (1);
		else if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "env"))
			return (2);
		else if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "export"))
			return (3);
		else if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "echo"))
			return (4);
		else if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "unset"))
			return (5);
		else if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "exit"))
			return (6);
		else if (!ft_strcmp(handler()->smp_cmd[i].cmd[0], "cd"))
			return (7);
	}
	return (0);
}

void	do_builtin(int i, int fd, int j)
{
	if (i > 0)
		handler()->built_in = 1;
	if (i == 1)
		pwd(fd);
	if (i == 2)
		env_call(fd, j);
	if (i == 3)
		export_call(j, 0, 0, fd);
	if (i == 4)
		echo(handler()->smp_cmd[j].cmd, fd, true);
	if (i == 5)
		unset_call();
	if (i == 6)
		exit_call();
	if (i == 7)
		cd();
}
