/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 00:10:09 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/17 17:44:28 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(int fd)
{
	int	i;

	i = 0;
	while (handler()->export && handler()->export[i])
	{
		make_export(false);
		write(fd, handler()->export[i], ft_strlen(handler()->export[i]));
		write(fd, "\n", 1);
		i++;
	}
}

void	add_string_env(char *str)
{
	int		i;
	char	**new_envp;

	new_envp = NULL;
	i = count_arrays(handler()->envp);
	new_envp = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (handler()->envp && handler()->envp[++i])
		new_envp[i] = ft_strdup(handler()->envp[i]);
	new_envp[i++] = ft_strdup(str);
	new_envp[i] = NULL;
	if (handler()->envp)
		ft_free_arr(handler()->envp);
	handler()->envp = new_envp;
	handler()->change_env = true;
}

void	make_export_aux(char **tmp_env, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp_env[i])
	{
		j = i + 1;
		while (tmp_env[j])
		{
			if (strcmp(tmp_env[i], tmp_env[j]) > 0)
			{
				tmp = tmp_env[i];
				tmp_env[i] = tmp_env[j];
				tmp_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	make_export(bool tog)
{
	char	*tmp;
	char	**tmp_env;

	tmp = NULL;
	if (tog)
		tmp_env = copy_double_array(handler()->envp);
	else
		tmp_env = handler()->export;
	make_export_aux(tmp_env, tmp);
	handler()->export = tmp_env;
}

int	add_declare(char **array, char *str, int i)
{
	char	*tmp;

	tmp = add_aspas(str);
	free(array[i]);
	array[i] = ft_strjoin("declare -x ", tmp);
	free(tmp);
	return (i);
}
