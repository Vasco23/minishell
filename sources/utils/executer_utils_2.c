/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:47:16 by vcacador          #+#    #+#             */
/*   Updated: 2023/08/17 15:27:06 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	executer_aux_aux_aux(int i, bool red_less_fail)
{
	do_builtin(find_builtins(i), handler()->smp_cmd[i].fds[1], i);
	if (handler()->built_in > 0)
	{
		close(handler()->smp_cmd[i].fds[1]);
		if (i > 0)
			close(handler()->smp_cmd[i - 1].fds[0]);
	}
	if (handler()->built_in > 0)
		close(handler()->smp_cmd[i].fds[1]);
	else if (handler()->built_in == 0)
		pipes(i, red_less_fail);
} */

void	executer_aux_aux(int i, bool red_less_fail)
{
	if (i + 1 == handler()->smp_cmd_size)
	{
		do_builtin(find_builtins(i), 1, i);
		if (handler()->built_in > 0)
		{
			close(handler()->smp_cmd[i].fds[1]);
			if (i > 0)
				close(handler()->smp_cmd[i - 1].fds[0]);
		}
	}
	else if (i + 1 != handler()->smp_cmd_size)
	{
		do_builtin(find_builtins(i), handler()->smp_cmd[i].fds[1], i);
		if (handler()->built_in > 0)
		{
			close(handler()->smp_cmd[i].fds[1]);
			if (i > 0)
				close(handler()->smp_cmd[i - 1].fds[0]);
		}
	}
	if (handler()->built_in == 0)
		pipes(i, red_less_fail);
}

/* void	pipe_save_lines(int i, bool red_less_fail)
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
} */

void	great_child_close(int i, int fd_in, int fd_out, int fd_in2)
{
	close_fd(fd_in, fd_out);
	child(fd_in2, handler()->file_fd, i);
}
