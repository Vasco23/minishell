/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:18:51 by miguelro          #+#    #+#             */
/*   Updated: 2023/09/04 15:40:59 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes(int i, bool red_less_fail)
{
	if (i == 0)
		child(0, handler()->smp_cmd[i].fds[1], i);
	else if (i == handler()->smp_cmd_size - 1)
	{
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
		if (red_less_fail == true)
			close(handler()->smp_cmd[i - 1].fds[1]);
		child(handler()->smp_cmd[i - 1].fds[0], 1, i);
	}
	else
	{
		if (red_less_fail == true)
		{
			close(handler()->smp_cmd[i - 1].fds[1]);
			child(handler()->smp_cmd[i - 1].fds[0], \
				handler()->smp_cmd[i].fds[1], i);
		}
		else
			child(handler()->smp_cmd[i - 1].fds[0], \
				handler()->smp_cmd[i].fds[1], i);
	}
	return (0);
}

void	executer_aux(int i, bool red_less_fail)
{
	if (handler()->smp_cmd_size == 1)
	{
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
		do_builtin(find_builtins(i), 1, i);
		if (handler()->built_in == 0)
			child(0, 1, i);
	}
	else if (i < handler()->smp_cmd_size && \
		handler()->smp_cmd[i].nmr_redir == 0)
	{
		executer_redir(i);
		if (handler()->built_in == 0)
			pipes(i, red_less_fail);
	}
}

int	exec_save_lines(int i, int j)
{
	while (j < handler()->smp_cmd[i].nmr_redir && \
		handler()->smp_cmd[i].redirections[j].token)
	{
		if (handler()->smp_cmd[i].redirections[j].token == 4)
			if (less(i, j) == 1)
				return (1);
		if (handler()->smp_cmd[i].redirections[j].token == 5)
			less_less(i, j);
		j++;
	}
	j = 0;
	while (j < handler()->smp_cmd[i].nmr_redir && \
			handler()->smp_cmd[i].redirections[j].token)
	{
		if (handler()->smp_cmd[i].redirections[j].token == 2)
			great(i, j);
		if (handler()->smp_cmd[i].redirections[j].token == 3)
			great_great(i, j);
		j++;
	}
	return (0);
}

void	executer(void)
{
	bool	red_less_fail;
	int		i;
	int		j;

	j = 0;
	i = -1;
	red_less_fail = false;
	while (++i < handler()->smp_cmd_size)
	{
		handler()->built_in = 0;
		if (handler()->smp_cmd[i].nmr_redir > 0)
		{
			if (exec_save_lines(i, j) == 1)
				red_less_fail = true;
		}
		else if (handler()->smp_cmd[i].nmr_redir == 0 \
			&& handler()->smp_cmd[i].cmd[0])
			executer_aux(i, red_less_fail);
	}
	return ;
}

void	child(int fd_in, int fd_out, int n)
{
	int	i;

	handler()->child++;
	handler()->id = fork();
	if (handler()->id == 0)
	{
		signal(SIGQUIT, sig_quit_cmd);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			terminate(1, false);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			terminate(1, false);
		close_fd(fd_in, fd_out);
		i = -1;
		while (++i < handler()->smp_cmd_size - 1)
			close(handler()->smp_cmd[i].fds[0]);
		do_comand(env_finder("PATH="), n);
		execve(handler()->command_path, handler()->smp_cmd[n].cmd,
			handler()->envp);
		child_save_lines(fd_in, fd_out);
	}
	close_fd(fd_in, fd_out);
	return ;
}
