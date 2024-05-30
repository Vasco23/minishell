/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelro <miguelro@students.42lisboa.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:21:10 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/23 22:59:37 by miguelro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_handler	*handler(void)
{
	static t_handler	handler;

	return (&handler);
}

char	*rl_get(void)
{
	char	*line_read;

	line_read = readline("minishell: ");
	if (!line_read)
		terminate(0, true);
	if (line_read && *line_read)
		add_history(line_read);
	return (replace_dollar(line_read));
}

bool	ft_isseperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	validate_pipe(char *str)
{
	int		i;
	bool	inside_aspas;
	char	aspas;

	i = -1;
	inside_aspas = false;
	aspas = 0;
	if (str[0] == '|')
		return (false);
	while (str[++i])
	{
		if (str[i] == aspas)
			inside_aspas = false;
		if (str[i] == '\'' || str[i] == '"')
		{
			aspas = str[i];
			inside_aspas = true;
		}
		if (!inside_aspas)
			if (str[i] == '|' && str[i + 1] && str[i + 1] == '|')
				return (false);
	}
	return (true);
}

void	close_fd_1(int j)
{
	int	i;

	i = -1;
	while (++i <= j)
		close(handler()->smp_cmd[i].fds[1]);
}
