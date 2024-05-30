/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 00:01:38 by miguelro          #+#    #+#             */
/*   Updated: 2023/07/31 17:01:46 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	strlen_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	count_arrays(char **tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp && tmp[i])
		i++;
	return (i);
}

char	**copy_double_array(char **array)
{
	int		i;
	char	**tmp;
	char	*tmp2;

	tmp = ft_calloc(count_arrays(array) + 1, sizeof(char *));
	i = 0;
	while (array[i])
	{
		tmp2 = add_aspas(array[i]);
		tmp[i] = ft_strjoin("declare -x ", tmp2);
		free(tmp2);
		i++;
	}
	return (tmp);
}

char	*add_aspas(char *str)
{
	int		i;
	int		j;
	int		equal;
	char	*tmp;

	i = 0;
	equal = 0;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	while (str[i])
	{
		if (str[i] == '=' && equal == 0)
		{
			equal = 1;
			tmp[j++] = str[i++];
			tmp[j++] = '"';
		}
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '"';
	return (tmp);
}

int	alpha_find(char *str)
{
	int	i;

	i = -1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("minishell: not a valid identifier\n", 2);
		return (1);
	}
	while (str[++i] && str[i] != '=')
	{
		if (i > 0)
		{
			if (str[i] != '_' && !ft_isalnum(str[i]))
			{
				ft_putstr_fd("minishell: not a valid identifier\n", 2);
				return (1);
			}
		}
	}
	return (0);
}
