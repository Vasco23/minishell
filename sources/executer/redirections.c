/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:27:47 by miguelro          #+#    #+#             */
/*   Updated: 2023/09/04 15:59:06 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	great(int i, int j)
{
	(handler()->file_fd) = \
		open(handler()->smp_cmd[i].redirections[j].str, \
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (handler()->file_fd == -1)
		error_handling_red();
	if (j + 1 < handler()->smp_cmd[i].nmr_redir && \
		(handler()->smp_cmd[i].redirections[j + 1].token == 2 || \
			handler()->smp_cmd[i].redirections[j + 1].token == 3))
	{
		close(handler()->file_fd);
		return (0);
	}
	great_utils(i);
	return (0);
}

int	great_great(int i, int j)
{
	(handler()->file_fd) = \
		open(handler()->smp_cmd[i].redirections[j].str, \
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (handler()->file_fd == -1)
		error_handling_red();
	if (j + 1 < handler()->smp_cmd[i].nmr_redir && \
		(handler()->smp_cmd[i].redirections[j + 1].token == 2 || \
			handler()->smp_cmd[i].redirections[j + 1].token == 3))
		close(handler()->file_fd);
	great_great_utils(i);
	return (0);
}

int	less(int i, int j)
{
	if (save_lines_less(i, j) == 1)
		return (1);
	if (j + 1 < handler()->smp_cmd[i].nmr_redir && \
		(handler()->smp_cmd[i].redirections[j + 1].token == 4 || \
			handler()->smp_cmd[i].redirections[j + 1].token == 5))
		close(handler()->file_fd);
	else if (handler()->smp_cmd_size == i + 1 && check_greats(i) == 0)
	{
		do_builtin(find_builtins(i), 1, i);
		if (handler()->built_in == 0)
		{
			close_fd(handler()->smp_cmd[i].fds[0], \
				handler()->smp_cmd[i].fds[1]);
			child(handler()->file_fd, 1, i);
		}
		else
			close_fd(handler()->file_fd, handler()->smp_cmd[i].fds[1]);
	}
	else
		less_utils(i);
	return (0);
}

int	less_less_aux(int i, int j)
{
	if (save_lines_less_less_2() == 1)
		return (1);
	here_doc(handler()->fds_tmp[1], i, j);
	close(handler()->fds_tmp[1]);
	child(handler()->fds_tmp[0], handler()->smp_cmd[i].fds[1], i);
	return (0);
}

int	less_less(int i, int j)
{
	if (j + 1 < handler()->smp_cmd[i].nmr_redir && \
		(handler()->smp_cmd[i].redirections[j + 1].token == 4 \
			|| handler()->smp_cmd[i].redirections[j + 1].token == 5))
	{
		if (save_lines_less_less_2() == 1)
			return (1);
		save_lines_less_less(i, j);
	}
	else if (!handler()->smp_cmd[i].cmd[0])
	{
		here_doc(handler()->smp_cmd[i].fds[1], i, j);
		close(handler()->smp_cmd[i].fds[1]);
	}
	else if (handler()->smp_cmd_size - 1 == i && check_greats(i) == 0)
	{
		here_doc(handler()->smp_cmd[i].fds[1], i, j);
		close(handler()->smp_cmd[i].fds[1]);
		child(handler()->smp_cmd[i].fds[0], 1, i);
	}
	else if (less_less_aux(i, j))
		return (1);
	return (0);
}
