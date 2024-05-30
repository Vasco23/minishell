/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:44:06 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/13 15:47:00 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_istoken(char *str)
{
	if (!str || ft_strlen(str) > 2)
		return (false);
	else if (!ft_strcmp(str, "|") || !ft_strcmp(str, "<") || !ft_strcmp(str, \
		"<<") || !ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (true);
	return (false);
}

char	**remove_empty_cmd_aux(int i)
{
	int	j;
	int	empty_nbr;
	int	new_cmd_size;

	j = -1;
	empty_nbr = 0;
	while (handler()->smp_cmd[i].cmd[++j])
	{
		if (handler()->smp_cmd[i].cmd[j][0] == '\4')
			empty_nbr++;
	}
	if (!empty_nbr)
		return (NULL);
	new_cmd_size = count_arrays(handler()->smp_cmd[i].cmd) - empty_nbr + 1;
	return (ft_calloc(new_cmd_size, sizeof(char *)));
}

void	remove_empty_cmd(void)
{
	int		j;
	int		k;
	int		i;
	char	**new_cmd;

	i = -1;
	while (++i < handler()->smp_cmd_size)
	{
		new_cmd = remove_empty_cmd_aux(i);
		if (!new_cmd)
			continue ;
		j = -1;
		k = -1;
		while (handler()->smp_cmd[i].cmd[++j])
		{
			if (handler()->smp_cmd[i].cmd[j][0] != '\4')
				new_cmd[++k] = ft_strdup(handler()->smp_cmd[i].cmd[j]);
		}
		new_cmd[++k] = 0;
		ft_free_arr(handler()->smp_cmd[i].cmd);
		handler()->smp_cmd[i].cmd = new_cmd;
	}
}

t_tokens	ft_tokenize(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (LESS);
	else if (!ft_strcmp(str, "<<"))
		return (LESS_LESS);
	else if (!ft_strcmp(str, ">"))
		return (GREAT);
	else if (!ft_strcmp(str, ">>"))
		return (GREAT_GREAT);
	return (0);
}

void	verify_smp_cmd(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < handler()->smp_cmd_size)
	{
		j = -1;
		while (++j < handler()->smp_cmd[i].nmr_redir)
		{
			if (handler()->smp_cmd[i].redirections[j].token && \
				!handler()->smp_cmd[i].redirections[j].str)
			{
				perror("minishell: syntax error " \
					"near unexpected token");
				handler()->new_prompt = true;
			}
		}
	}
}
