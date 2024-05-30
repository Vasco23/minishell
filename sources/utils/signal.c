/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:41:34 by miguelro          #+#    #+#             */
/*   Updated: 2023/09/04 15:17:12 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (handler()->child == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_int_heredoc(int sig)
{
	(void)sig;
	terminate(0, false);
}

void	sig_quit_cmd(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	executer_redir(int i)
{
	if (i + 1 == handler()->smp_cmd_size)
	{
		do_builtin(find_builtins(i), 1, i);
		if (handler()->built_in > 0)
		{
			close_fd(handler()->smp_cmd[i].fds[0], \
				handler()->smp_cmd[i].fds[1]);
			if (i > 0)
				close(handler()->smp_cmd[i - 1].fds[0]);
		}
	}
	else
	{
		do_builtin(find_builtins(i), handler()->smp_cmd[i].fds[1], i);
		if (handler()->built_in > 0)
		{
			close(handler()->smp_cmd[i].fds[1]);
			if (i > 0)
				close(handler()->smp_cmd[i - 1].fds[0]);
		}
	}
}
