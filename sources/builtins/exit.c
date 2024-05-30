/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:56:09 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/16 15:28:56 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ignore_aspas_aux(char *new_str, char *str, int i)
{
	int		j;
	char	aspas;

	aspas = str[i];
	j = i++;
	while (str[++j] && str[j] != aspas)
		;
	if (!str[j] && str[j - 1] != aspas)
	{
		new_str[0] = 'e';
		return (new_str);
	}
	return (new_str);
}

char	*ignore_aspas(char *str)
{
	int		i;
	int		newi;
	char	*new_str;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	newi = -1;
	while (str[i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
			new_str[++newi] = str[i++];
		if (str[i])
		{
			new_str = ignore_aspas_aux(new_str, str, i);
			if (new_str[0] == 'e')
				return (new_str);
			i++;
		}
	}
	new_str[++newi] = 0;
	return (new_str);
}

char	*check_exit_string(char *exit_str)
{
	int		i;
	char	*new_str;

	new_str = ignore_aspas(exit_str);
	if (new_str[0] == 'e')
		return (new_str);
	if (!ft_isdigit(new_str[0]) && new_str[0] != '+' && new_str[0] != '-')
	{
		new_str[0] = 'e';
		return (new_str);
	}
	i = 0;
	while (new_str[++i])
	{
		if (!ft_isdigit(new_str[i]))
		{
			new_str[0] = 'e';
			return (new_str);
		}
	}
	return (new_str);
}

int	exit_atoll(char *exit_str)
{
	int					i;
	char				*new_str;
	bool				is_neg;

	is_neg = false;
	if (!exit_str)
		return (handler()->exit_status);
	new_str = check_exit_string(exit_str);
	if (new_str[0] == 'e')
	{
		free(new_str);
		return (2);
	}
	i = -1;
	if (new_str[0] == '+' || new_str[0] == '-')
		i++;
	if (new_str[0] == '-')
		is_neg = true;
	return (exit_atoll_aux(new_str, is_neg, i));
}

void	exit_call(void)
{
	int	exit_status;

	if (handler()->smp_cmd_size != 1)
		return ;
	if (ft_strcmp(handler()->smp_cmd[0].cmd[0], "exit") == 0)
	{
		if (count_arrays(handler()->smp_cmd[0].cmd) > 2)
		{
			ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
			terminate(1, true);
		}
		exit_status = exit_atoll(handler()->smp_cmd[0].cmd[1]);
		if (exit_status == 2)
		{
			ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
			terminate(2, true);
		}
		terminate(exit_status, true);
	}
}
