/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcacador <vcacador@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:18:41 by miguelro          #+#    #+#             */
/*   Updated: 2023/08/21 17:44:26 by vcacador         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	int		i;
	int		v;
	char	*newstr;

	i = 0;
	v = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!newstr)
		return (NULL);
	if (!s1 && !s2)
		return (NULL);
	while (s1[v])
	{
		newstr[i] = s1[v];
		i++;
		v++;
	}
	newstr[i++] = '/';
	v = 0;
	while (s2 && s2[v])
		newstr[i++] = s2[v++];
	newstr[i] = '\0';
	return (newstr);
}

char	*env_finder(char *str)
{
	int	i;

	i = 0;
	while (handler()->envp && handler()->envp[i])
	{
		if (ft_strncmp(handler()->envp[i], str, ft_strlen(str)) == 0)
			return (ft_substr(handler()->envp[i], 5,
					strlen(handler()->envp[i])));
		i++;
	}
	return (NULL);
}

bool	find_div_path(char **div_path, char *path, char *path_send, int n)
{
	int	i;

	i = -1;
	while (div_path[++i])
	{
		path_send = ft_strjoin_path(div_path[i], handler()->smp_cmd[n].cmd[0]);
		if (access(path_send, F_OK) == 0)
		{
			ft_free_arr(div_path);
			free(path);
			handler()->command_path = path_send;
			return (true);
		}
		free(path_send);
	}
	return (false);
}

void	do_comand(char *path, int n)
{
	char	**div_path;
	char	*path_send;

	div_path = ft_split(path, ':');
	path_send = NULL;
	if (!div_path || !*div_path)
	{
		handler()->command_path = ft_strdup(handler()->smp_cmd[n].cmd[0]);
		return ;
	}
	if (find_div_path(div_path, path, path_send, n))
		return ;
	free(path);
	ft_free_arr(div_path);
	handler()->command_path = ft_strdup(handler()->smp_cmd[n].cmd[0]);
}
