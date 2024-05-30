/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:24:30 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/28 17:35:31 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_variable_equals(char **array, char *str, int v, int i)
{
	int		str_len;

	if (strlen_equal(str) > strlen_equal(&array[i][v]))
		str_len = strlen_equal(str);
	else
		str_len = strlen_equal(&array[i][v]);
	if (ft_strncmp(&array[i][v], str, str_len))
		return (false);
	return (true);
}

int	check_variable_aux(char **array, char *str, int v, int n)
{
	int		i;
	bool	equal;

	i = -1;
	while (array && array[++i])
	{
		equal = check_variable_equals(array, str, v, i);
		if (equal && n == 0 && v)
			return (add_declare(array, str, i));
		else if (equal && n == 0 && !v)
		{
			free(array[i]);
			array[i] = ft_strdup(str);
			return (i);
		}
		else if (equal && n == 1)
			return (i);
		equal = true;
	}
	return (-1);
}

int	check_var(char *str, int n, char **array)
{
	int		v;

	v = 0;
	if (!array || !*array)
		return (-1);
	if (!strncmp(array[0], "declare -x ", 11))
		v = 11;
	return (check_variable_aux(array, str, v, n));
}

void	add_string_export(char *str, int n)
{
	int		i;
	char	**new_export;
	char	*tmp;

	new_export = NULL;
	i = count_arrays(handler()->export);
	new_export = ft_calloc((i + 2), sizeof(char *));
	i = -1;
	while (handler()->export && handler()->export[++i])
		new_export[i] = ft_strdup(handler()->export[i]);
	if (n == 0)
	{
		tmp = add_aspas(str);
		new_export[i++] = ft_strjoin("declare -x ", tmp);
		free(tmp);
	}
	else
		new_export[i++] = ft_strjoin("declare -x ", str);
	new_export[i] = NULL;
	if (handler()->export)
		ft_free_arr(handler()->export);
	handler()->export = new_export;
}

void	add_path_to_export(void)
{
	int		i;
	char	*tmp;
	char	*aspas_pwd;

	i = -1;
	while (handler()->export[++i])
	{
		if (!ft_strncmp(handler()->export[i], "declare -x PWD=", 15))
		{
			aspas_pwd = add_aspas(handler()->pwd);
			tmp = ft_strjoin("declare -x PWD=", aspas_pwd);
			free(handler()->export[i]);
			free(aspas_pwd);
			handler()->export[i] = tmp;
		}
		else if (!ft_strncmp(handler()->export[i], "declare -x OLDPWD=", 18)
			&& handler()->old_pwd)
		{
			aspas_pwd = add_aspas(handler()->old_pwd);
			tmp = ft_strjoin("declare -x OLDPWD=", aspas_pwd);
			free(handler()->export[i]);
			free(aspas_pwd);
			handler()->export[i] = tmp;
		}
	}
}
