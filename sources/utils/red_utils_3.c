/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:30:52 by vcacador          #+#    #+#             */
/*   Updated: 2023/09/04 15:32:06 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	great_utils(int i)
{
	do_builtin(find_builtins(i), handler()->file_fd, i);
	if (handler()->built_in == 1)
	{
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
		close (handler()->file_fd);
	}
	else if (check_less(i) == 0 && i == 0)
	{
		child(0, handler()->file_fd, i);
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
	}
	else if (check_less(i) == 0 && i > 0)
	{
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
		child(handler()->smp_cmd[i - 1].fds[0], handler()->file_fd, i);
	}
	else
		child(handler()->smp_cmd[i].fds[0], handler()->file_fd, i);
	close_fd_0(i);
}

void	great_great_utils(int i)
{
	do_builtin(find_builtins(i), handler()->file_fd, i);
	if (handler()->built_in == 1)
	{
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
		close (handler()->file_fd);
	}
	else if (check_less(i) == 0 && i == 0)
	{
		child(0, handler()->file_fd, i);
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
	}
	else if (check_less(i) == 0 && i > 0)
	{
		close_fd(handler()->smp_cmd[i].fds[0], handler()->smp_cmd[i].fds[1]);
		child(handler()->smp_cmd[i - 1].fds[0], handler()->file_fd, i);
	}
	else
		child(handler()->smp_cmd[i].fds[0], handler()->file_fd, i);
	close_fd_0(i);
}

void	less_utils(int i)
{
	do_builtin(find_builtins(i), handler()->smp_cmd[i].fds[1], i);
	if (handler()->built_in == 0)
		child(handler()->file_fd, handler()->smp_cmd[i].fds[1], i);
	else
		close_fd(handler()->file_fd, handler()->smp_cmd[i].fds[1]);
}
