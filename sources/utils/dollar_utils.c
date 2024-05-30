/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:03:16 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/24 13:12:32 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_new_line(char **expansions, char *line)
{
	int		len;
	int		i;
	char	*new_line;

	len = 0;
	i = -1;
	while (expansions[++i])
		len += ft_strlen(expansions[i]);
	len += ft_strlen(line);
	new_line = ft_calloc(len + 1, sizeof(char));
	return (new_line);
}

void	expand_line_aux(char *line, char *new_line, int *i, int *n)
{
	if (!line[(*i)])
			(*i)--;
	else if (line[(*i)] == '\1')
		new_line[++(*n)] = '$';
	else
		new_line[++(*n)] = line[(*i)];
}

char	*expand_line(char *line, char **expansions, int i, int n)
{
	int		k;
	int		j;
	char	*new_line;

	if (!expansions)
		return (line);
	new_line = alloc_new_line(expansions, line);
	k = 0;
	while (line[++i])
	{
		while (line[i] == '$')
		{
			j = -1;
			while (expansions[k][++j])
				new_line[++n] = expansions[k][j];
			k++;
			while (line[++i] && ft_isalnum(line[i]))
				;
			if (line[i] && line[i] == '?')
				i++;
		}
		expand_line_aux(line, new_line, &i, &n);
	}
	return (new_line);
}

char	*replace_dollar_cmd_heredoc(char *str)
{
	str[ft_strlen_n(str)] = '\0';
	str = replace_dollar(str);
	str[ft_strlen_n(str)] = '\n';
	return (str);
}

char	*env_var_value_aux2(char *key_dup, int j)
{
	char	*str;

	if (key_dup[0] == '?')
		str = ft_itoa(handler()->exit_status);
	else
	{
		str = ft_strchr(handler()->export[j], '=') + 1;
		str = ft_substr(str, 1, ft_strlen(str) - 2);
	}
	return (str);
}
