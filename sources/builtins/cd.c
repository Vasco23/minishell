/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:27:14 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/16 15:28:48 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_rlt_path(char *str)
{
	int	i;

	i = 0;
	while (handler()->envp[i])
	{
		if (!ft_strncmp(str, handler()->envp[i], ft_strlen(str)))
			return (ft_substr(handler()->envp[i], ft_strlen(str),
					ft_strlen(handler()->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(char *str)
{
	char	*tmp;
	int		error;

	tmp = find_rlt_path(str);
	error = chdir(tmp);
	free(tmp);
	if (error)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (error);
}

void	add_path_to_env(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (handler()->envp[i])
	{
		if (!ft_strncmp(handler()->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", handler()->pwd);
			free(handler()->envp[i]);
			handler()->envp[i] = tmp;
		}
		else if (!ft_strncmp(handler()->envp[i], "OLDPWD=", 7)
			&& handler()->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", handler()->old_pwd);
			free(handler()->envp[i]);
			handler()->envp[i] = tmp;
		}
		i++;
	}
}

void	change_path(int error)
{
	char	*tmp;

	if (error)
	{
		error_handling_built_in(true);
		return ;
	}
	tmp = ft_strdup(handler()->pwd);
	free(handler()->old_pwd);
	handler()->old_pwd = tmp;
	free(handler()->pwd);
	(handler()->pwd) = getcwd(NULL, 0);
	add_path_to_env();
	add_path_to_export();
	error_handling_built_in(false);
}

void	cd(void)
{
	int		error;

	error = 0;
	if (handler()->smp_cmd_size != 1)
		return ;
	if (count_arrays(handler()->smp_cmd[0].cmd) > 2)
	{
		error = 1;
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
	}
	else if (!handler()->smp_cmd[0].cmd[1])
		error = specific_path("HOME=");
	else if (!ft_strncmp(handler()->smp_cmd[0].cmd[1], "-", 1))
		error = specific_path("OLDPWD=");
	else
	{
		error = cd_aux(error);
	}
	change_path(error);
}
