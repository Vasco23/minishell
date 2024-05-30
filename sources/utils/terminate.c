/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:09:03 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/19 12:47:31 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	terminate(handler()->exit_status, true);
}

void	free_smp_cmd(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < handler()->smp_cmd_size)
	{
		ft_free_arr(handler()->smp_cmd[i].cmd);
		j = -1;
		while (++j < handler()->smp_cmd[i].nmr_redir)
			free(handler()->smp_cmd[i].redirections[j].str);
		free(handler()->smp_cmd[i].redirections);
	}
	if (handler()->smp_cmd)
		free(handler()->smp_cmd);
	handler()->smp_cmd_size = 0;
}

void	free_parser(void)
{
	if (handler()->line)
		free(handler()->line);
	if (handler()->export)
		ft_free_arr(handler()->export);
	if (handler()->envp)
		ft_free_arr(handler()->envp);
	if (handler()->pwd)
		free(handler()->pwd);
	if (handler()->old_pwd)
		free(handler()->old_pwd);
	if (handler()->command_path)
		free(handler()->command_path);
	free_smp_cmd();
}

long long	exit_atoll_aux(char *new_str, bool is_neg, int i)
{
	unsigned long long	exit_number;
	long long			fin_nbr;

	exit_number = 0;
	while (new_str[++i])
	{
		exit_number = 10 * exit_number + (new_str[i] - '0');
		if ((exit_number > 9223372036854775807 && is_neg == false) || \
			exit_number > 9223372036854775808ULL)
		{
			free(new_str);
			return (2);
		}
	}
	if (is_neg)
		fin_nbr = -exit_number;
	else
		fin_nbr = exit_number;
	fin_nbr %= 256;
	if (fin_nbr < 0)
		fin_nbr = (fin_nbr + 256) % 256;
	free(new_str);
	return (fin_nbr);
}

void	terminate(int i, bool print)
{
	close_all_fds();
	free_parser();
	if (print)
		ft_putstr_fd("exit\n", 1);
	exit(i);
}
