/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:02:08 by vcacador          #+#    #+#             */
/*   Updated: 2023/08/16 15:28:04 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_greats(int i)
{
	int	j;

	j = 0;
	while (j < handler()->smp_cmd[i].nmr_redir \
		&& handler()->smp_cmd[i].redirections[j].token)
	{
		if (handler()->smp_cmd[i].redirections[j].token == 2 || \
			handler()->smp_cmd[i].redirections[j].token == 3)
			return (1);
		j++;
	}
	return (0);
}

int	check_less(int i)
{
	int	j;

	j = 0;
	while (j < handler()->smp_cmd[i].nmr_redir && \
			handler()->smp_cmd[i].redirections[j].token)
	{
		if (handler()->smp_cmd[i].redirections[j].token == 4 || \
				handler()->smp_cmd[i].redirections[j].token == 5)
			return (1);
		j++;
	}
	return (0);
}

void	child_save_lines(int fd_in, int fd_out)
{
	close_fd(fd_in, fd_out);
	if (fd_out == 1)
		close(fd_out);
	ft_putstr_fd("minishell: no such file or directory\n", 2);
	if (access(handler()->command_path, X_OK) == -1)
		terminate(127, false);
	if (access(handler()->command_path, F_OK) == -1)
		terminate(127, false);
	terminate(126, false);
}

char	*remove_aspas(char *str, int i, int j)
{
	char	*new_str;
	char	aspas;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		while (str[i] && str[i] != '\"' && str[i] != '\'')
			new_str[++j] = str[i++];
		if (!str[i])
		{
			free(str);
			return (new_str);
		}
		aspas = str[i];
		while (str[++i] && str[i] != aspas)
			new_str[++j] = str[i];
		if (!str[i])
		{
			free(str);
			return (new_str);
		}
	}
	new_str[++j] = 0;
	return (new_str);
}

int	cd_aux(int error)
{
	char	*str;

	if (!ft_strncmp(handler()->smp_cmd[0].cmd[1], "~", 1))
	{
		str = ft_strjoin("/home", &handler()->smp_cmd[0].cmd[1][1]);
		error = chdir(str);
		free(str);
	}
	else
		error = chdir(handler()->smp_cmd[0].cmd[1]);
	if (error)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(handler()->smp_cmd[0].cmd[1], STDERR_FILENO);
		perror(" ");
	}
	return (error);
}
