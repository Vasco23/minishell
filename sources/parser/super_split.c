/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:37:55 by miguelro          #+#    #+#             */
/*   Updated: 2023/09/04 15:57:14 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cpy_until_c(char *cpy_line, int *i, int *j, char c)
{
	int	k;

	k = *i + 1;
	while (handler()->line[(k)] && handler()->line[(k)] != c)
		k++;
	if (!handler()->line[k])
		return (false);
	cpy_line[(*j)++] = handler()->line[(*i)++];
	while (handler()->line[(*i)] && handler()->line[(*i)] != c)
		cpy_line[(*j)++] = handler()->line[(*i)++];
	cpy_line[(*j)] = handler()->line[(*i)];
	return (true);
}

bool	cpy_until_quotes(char *cpy_line, int *i, int *j, char *str)
{
	if (str[*i] == '\"')
	{
		if (!cpy_until_c(cpy_line, i, j, '\"'))
			return (false);
	}
	else if (str[*i] == '\'')
	{
		if (!cpy_until_c(cpy_line, i, j, '\''))
			return (false);
	}
	return (true);
}

bool	super_split_extension(bool tog_sep, char *cpy_line, int *i, int *j)
{
	char	*str;

	str = handler()->line;
	if (tog_sep)
	{
		ft_putstr_fd("minishell: syntax error " \
			"near unexpected token `|'\n", 2);
		return (false);
	}
	else if (str[(*i)] == '|')
	{
		cpy_line[(*j)] = '\3';
		tog_sep = true;
	}
	else
	{
		cpy_line[(*j)] = '\2';
		cpy_line[++(*j)] = str[(*i)];
		if (str[(*i) + 1] && (str[(*i)] == '<' || str[(*i)] == '>')
			&& str[(*i)] == str[(*i) + 1])
			cpy_line[++(*j)] = str[++(*i)];
		tog_sep = true;
	}
	cpy_line[++(*j)] = '\2';
	return (tog_sep);
}

bool	create_seperators(char *str, char *cpy_line, int i, int j)
{
	bool	tog_sep;

	tog_sep = false;
	while (str && str[++i])
	{
		j++;
		if (!cpy_until_quotes(cpy_line, &i, &j, str) && j > 0)
			j--;
		else if (ft_isspace(str[i]))
		{
			tog_sep = false;
			cpy_line[j] = '\2';
		}
		else if ((str[i] == '\\' || str[i] == ';') && j > 0)
			j--;
		else if (ft_isseperator(str[i]))
		{
			tog_sep = super_split_extension(tog_sep, cpy_line, &i, &j);
			if (!tog_sep)
				return (false);
		}
		else
			tog_sep = create_seperators_aux(cpy_line, str, j, i);
	}
	return (true);
}

char	**super_split(char *str)
{
	char	*cpy_line;
	char	**result;

	result = NULL;
	if (!str)
		return (NULL);
	cpy_line = ft_calloc(3 * ft_strlen(str) + 1, sizeof(char));
	if (!create_seperators(str, cpy_line, -1, -1))
	{
		free(cpy_line);
		return (NULL);
	}
	result = ft_split(cpy_line, '\3');
	free(cpy_line);
	return (result);
}
