/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:44:06 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/24 14:56:03 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_expansion(char *line, char **expansions, int *k, int i)
{
	int	j;

	if (!line[i + 1] || (line[i + 1] != '?' && !ft_isalnum(line[i + 1])))
		line[i] = '\1';
	else
	{
		j = -1;
		expansions[(*k)] = ft_calloc(ft_strlen(line), sizeof(char));
		if (line[i + 1] == '?')
			expansions[(*k)][++j] = line[++i];
		while (line[++i] && ft_isalnum(line[i]))
			expansions[(*k)][++j] = line[i];
		i--;
		(*k)++;
	}
	return (i);
}

int	create_expansions_aux(char *line, char **expansions, int i, int *k)
{
	char	quote;

	quote = line[i];
	while (line[++i] != quote)
	{
		if (quote == '"' && line[i] == '$')
			i = copy_expansion(line, expansions, k, i);
		else if (quote == '\'' && line[i] == '$')
			line[i] = '\1';
	}
	if (!line[i])
		i--;
	return (i);
}

char	**create_expansions(char *line)
{
	int		i;
	int		k;
	char	**expansions;

	i = -1;
	k = 0;
	expansions = ft_calloc(count_dollar(line) + 1, sizeof(char *));
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = create_expansions_aux(line, expansions, i, &k);
		else if (line[i] == '$')
		{
			if (!line[i + 1] || \
				(line[i + 1] != '?' && !ft_isalnum(line[i + 1])))
				line[i] = '\1';
			else
				i = copy_expansion(line, expansions, &k, i);
		}
	}
	return (expansions);
}

char	**convert_expansions(char **expansions)
{
	int		i;
	char	**new_expansions;

	i = -1;
	if (!expansions)
		return (NULL);
	new_expansions = ft_calloc(count_arrays(expansions) + 1, sizeof(char *));
	while (expansions[++i])
		new_expansions[i] = env_var_value_new(expansions[i]);
	ft_free_arr(expansions);
	return (new_expansions);
}

char	*replace_dollar(char *str)
{
	char	**expansions;
	char	*fin_line;

	expansions = convert_expansions(create_expansions(str));
	fin_line = expand_line(str, expansions, -1, -1);
	free(str);
	ft_free_arr(expansions);
	return (fin_line);
}
