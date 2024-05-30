/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:57:59 by vcacador          #+#    #+#             */
/*   Updated: 2023/09/04 15:40:55 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_lines_less_less(int i, int j)
{
	here_doc(handler()->fds_tmp[1], i, j);
	close (handler()->fds_tmp[1]);
	close (handler()->fds_tmp[0]);
}

int	save_lines_less_less_2(void)
{
	if (pipe(handler()->fds_tmp) == -1)
	{
		ft_putstr_fd("error on pipe", 2);
		return (1);
	}
	return (0);
}

int	save_lines_less(int i, int j)
{
	(handler()->file_fd) = \
		open(handler()->smp_cmd[i].redirections[j].str, O_RDONLY, 0644);
	if (handler()->file_fd == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		if (!handler()->command_path || \
			access(handler()->command_path, F_OK) == -1)
			handler()->exit_status = 127;
		handler()->exit_status = 1;
		if (i + 1 == handler()->smp_cmd_size)
			close_fd(handler()->smp_cmd[i].fds[0], \
				handler()->smp_cmd[i].fds[1]);
		return (1);
	}
	if (!handler()->smp_cmd[i].cmd[0])
		close(handler()->file_fd);
	return (0);
}

void	error_handling_red(void)
{
	handler()->child++;
	handler()->id = fork();
	if (handler()->id == 0)
	{
		close(handler()->file_fd);
		terminate(1, false);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	close(handler()->file_fd);
	return ;
}

void	close_fd_0(int j)
{
	int	i;

	i = -1;
	while (++i <= j)
		close(handler()->smp_cmd[i].fds[0]);
}
