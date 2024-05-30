/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:20:16 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/16 17:56:36 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_n(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

int	end_here_doc(char *line, int fd, int i, int j)
{
	line = replace_dollar_cmd_heredoc(line);
	if (ft_strlen_n(line) == \
		ft_strlen_n(handler()->smp_cmd[i].redirections[j].str))
	{
		if (!ft_strncmp(line, \
			handler()->smp_cmd[i].redirections[j].str, ft_strlen_n(line)))
		{
			free(line);
			return (1);
		}
	}
	if (fd >= 0)
	{
		write(fd, line, ft_strlen_n(line));
		write(fd, "\n", 1);
	}
	free(line);
	return (0);
}

void	here_doc_aux(int fd, int i, int j)
{
	char	*line;

	signal(SIGINT, sig_int_heredoc);
	line = get_next_line(0);
	if (!line)
	{
		perror("here-document at line 11 delimited by end-of-file");
		close(fd);
		terminate(1, false);
	}
	if (end_here_doc(line, fd, i, j))
	{
		close(fd);
		terminate(1, false);
	}
}

int	here_doc(int fd, int i, int j)
{
	int		status;

	status = 0;
	if (handler()->child > 0)
	{
		waitpid(handler()->id, &status, 0);
		handler()->child--;
	}
	handler()->id = fork();
	handler()->child++;
	while (handler()->id == 0)
		here_doc_aux(fd, i, j);
	wait(&status);
	return (0);
}
