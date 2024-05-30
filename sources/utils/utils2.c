/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:48:57 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/24 14:56:14 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_aspas_smp(void)
{
	int		i;
	int		j;

	i = -1;
	while (++i < handler()->smp_cmd_size)
	{
		j = -1;
		while (handler()->smp_cmd[i].cmd[++j])
		{
			(handler()->smp_cmd[i].cmd[j]) = \
				remove_aspas(handler()->smp_cmd[i].cmd[j], 0, -1);
		}
		j = -1;
		while (++j < handler()->smp_cmd[i].nmr_redir)
		{
			(handler()->smp_cmd[i].redirections[j].str) = \
				remove_aspas(handler()->smp_cmd[i].redirections[j].str, 0, -1);
		}
	}
}

void	close_all_fds(void)
{
	int	i;

	i = 0;
	while (i < handler()->smp_cmd_size)
	{
		if (handler()->smp_cmd[i].fds[1] != -1)
			close(handler()->smp_cmd[i].fds[1]);
		if (handler()->smp_cmd[i].fds[0] != -1)
			close(handler()->smp_cmd[i].fds[0]);
		i++;
	}
	if (handler()->file_fd != -1)
		close(handler()->file_fd);
}

int	count_dollar(char *line)
{
	int	i;
	int	dollar;

	i = -1;
	dollar = 0;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] && \
			(line[i + 1] == '?' || ft_isalnum(line[i + 1])))
			dollar++;
	}
	return (dollar);
}

char	*env_var_value_new(char *key)
{
	int		j;
	char	*str;

	j = (check_var(key, 1, handler()->export));
	if (j >= 0 || key[0] == '?')
		str = env_var_value_aux2(key, j);
	else
		str = ft_calloc(1, sizeof(char));
	return (str);
}

bool	create_seperators_aux(char *cpy_line, char *str, int j, int i)
{
	cpy_line[j] = str[i];
	return (false);
}

/* void	print_parser(void)
{
	int	i;
	int	cmd_it;
	int	redi_it;

	cmd_it = -1;
	while (++cmd_it < handler()->smp_cmd_size)
	{
		printf("\n\n======%d========\n\n", cmd_it);
		printf("-----redirections %d-------\n", \
			handler()->smp_cmd[cmd_it].nmr_redir);
		redi_it = -1;
		while (++redi_it < handler()->smp_cmd[cmd_it].nmr_redir)
		{
			printf("redirection %d: \n%s %d\n", redi_it, \
				handler()->smp_cmd[cmd_it].redirections[redi_it].str, \
				handler()->smp_cmd[cmd_it].redirections[redi_it].token);
		}
		printf("\n-----flags-------\n");
		i = -1;
		while (handler()->smp_cmd[cmd_it].cmd[++i])
			printf("cmd %d: %s\n", i, handler()->smp_cmd[cmd_it].cmd[i]);
	}
} */
